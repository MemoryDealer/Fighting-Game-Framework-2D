// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: Server.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements Server singleton class.
// ================================================ //

#include "Server.hpp"
#include "NetMessage.hpp"
#include "Engine.hpp"
#include "Config.hpp"
#include "Timer.hpp"
#include "Game.hpp"
#include "PlayerManager.hpp"
#include "StageManager.hpp"
#include "Stage.hpp"
#include "Input.hpp"
#include "Log.hpp"

// ================================================ //

template<> Server* Singleton<Server>::msSingleton = nullptr;

// ================================================ //

Server::Server(const int port) :
m_peer(RakNet::RakPeerInterface::GetInstance()),
m_packet(nullptr),
m_clients(),
m_redAddr(),
m_blueAddr(),
m_redLastProcessedInput(0),
m_blueLastProcessedInput(0),
m_lastProcessedStageShift(0),
m_readyQueue(),
m_pUpdateTimer(new Timer())
{
	Log::getSingletonPtr()->logMessage("Initializing Server...");

	RakNet::SocketDescriptor sd(port, 0);
	m_peer->Startup(Server::MaxClients, &sd, 1);
	m_peer->SetMaximumIncomingConnections(Server::MaxClients);

	// Apply simulated lag, using half the ping since it will be applied to both client
	// and server.
	if (Game::getSingletonPtr()->useNetSimulator()){
		m_peer->ApplyNetworkSimulator(Game::getSingletonPtr()->getNetSimulatedPacketLoss(),
			Game::getSingletonPtr()->getNetSimulatedPing() / 2, 0);
	}

	Log::getSingletonPtr()->logMessage("Server initialized!");
}

// ================================================ //

Server::~Server(void)
{
	RakNet::RakPeerInterface::DestroyInstance(m_peer);
}

// ================================================ //

Uint32 Server::send(const RakNet::BitStream& bit, const RakNet::SystemAddress& addr,
	const PacketPriority priority, const PacketReliability reliability)
{
	return m_peer->Send(&bit, priority, reliability, 0, addr, false);
}

// ================================================ //

Uint32 Server::broadcast(const RakNet::Packet* packet, const PacketPriority priority,
	const PacketReliability reliability, const RakNet::SystemAddress& exclude)
{
	RakNet::BitStream bit(packet->data, packet->length, false);
	
	return m_peer->Send(&bit, priority, reliability, 0, exclude, true);
}

// ================================================ //

Uint32 Server::broadcast(const RakNet::BitStream& bit, const PacketPriority priority, 
	const PacketReliability reliability, const RakNet::SystemAddress& exclude)
{
	return m_peer->Send(&bit, priority, reliability, 0, exclude, true);
}

// ================================================ //

Uint32 Server::chat(const std::string& msg)
{
	RakNet::BitStream bit;
	bit.Write(static_cast<RakNet::MessageID>(NetMessage::CHAT));
	bit.Write(msg.c_str());

	return this->broadcast(bit, HIGH_PRIORITY, RELIABLE_ORDERED);
}

// ================================================ //

Uint32 Server::ready(const Uint32 fighter)
{
	if (this->addToReadyQueue(Game::getSingletonPtr()->getUsername(), fighter)){
		RakNet::BitStream bit;
		bit.Write(static_cast<RakNet::MessageID>(NetMessage::READY));
		bit.Write(Game::getSingletonPtr()->getUsername().c_str());

		return this->broadcast(bit, HIGH_PRIORITY, RELIABLE_ORDERED);
	}

	return 0;
}

// ================================================ //

Uint32 Server::startGame(void)
{
	// First let's tell every client that the game is starting.
	RakNet::BitStream bit;
	bit.Write(static_cast<RakNet::MessageID>(NetMessage::SERVER_STARTING_GAME));
	// Write red and blue player names in order.
	bit.Write(this->getNextRedPlayer().username.c_str());
	bit.Write(this->getNextBluePlayer().username.c_str());
	// Write red and blue fighters in order.
	bit.Write(this->getNextRedPlayer().fighter);
	bit.Write(this->getNextBluePlayer().fighter);
	this->broadcast(bit, IMMEDIATE_PRIORITY, RELIABLE_ORDERED);

	// Then tell any clients that are playing that they are actually playing.
	// Check red player.
	if (Game::getSingletonPtr()->getPlaying() != Game::PLAYING_RED){
		ReadyClient red = this->getNextRedPlayer();
		ClientConnection redConnection = m_clients[this->getClient(red.username)];
		m_redAddr = redConnection.addr;

		RakNet::BitStream play;
		play.Write(static_cast<RakNet::MessageID>(NetMessage::PLAYING_RED));
		this->send(play, m_redAddr, IMMEDIATE_PRIORITY, RELIABLE_ORDERED);
	}

	// Check blue player.
	if (Game::getSingletonPtr()->getPlaying() != Game::PLAYING_BLUE){
		ReadyClient blue = this->getNextBluePlayer();
		ClientConnection blueConnection = m_clients[this->getClient(blue.username)];
		m_blueAddr = blueConnection.addr;

		RakNet::BitStream play;
		play.Write(static_cast<RakNet::MessageID>(NetMessage::PLAYING_BLUE));
		this->send(play, m_blueAddr, IMMEDIATE_PRIORITY, RELIABLE_ORDERED);
	}

	m_pUpdateTimer->restart();

	return 1;
}

// ================================================ //

Uint32 Server::matchOver(const std::string& victor)
{
	RakNet::BitStream bit;
	bit.Write(static_cast<RakNet::MessageID>(NetMessage::MATCH_OVER));
	bit.Write(victor.c_str());

	return this->broadcast(bit, IMMEDIATE_PRIORITY, RELIABLE_ORDERED);
}

// ================================================ //

Uint32 Server::sendPlayerList(const RakNet::SystemAddress& addr, const bool broadcast)
{
	RakNet::BitStream bit;
	bit.Write(static_cast<RakNet::MessageID>(NetMessage::PLAYER_LIST));

	// Write number of connected clients, plus the server.
	bit.Write(m_clients.size() + 1);

	// Write server username.
	bit.Write(Game::getSingletonPtr()->getUsername().c_str());

	// Write each client username.
	for (ClientList::iterator itr = m_clients.begin();
		itr != m_clients.end();
		++itr){
		bit.Write(itr->username.c_str());
	}

	if (broadcast){
		return this->broadcast(bit, HIGH_PRIORITY, RELIABLE);
	}
	else{
		return this->send(bit, addr, HIGH_PRIORITY, RELIABLE);
	}
}

// ================================================ //

Uint32 Server::updatePlayers(void)
{
	RakNet::BitStream bit;
	bit.Write(static_cast<RakNet::MessageID>(NetMessage::UPDATE_PLAYERS));

	// Write red player data.
	PlayerUpdate redPlayer;
	Player* red = PlayerManager::getSingletonPtr()->getRedPlayer();
	redPlayer.lastProcessedInput = m_redLastProcessedInput;
	redPlayer.x = red->getPosition().x;
	redPlayer.y = red->getPosition().y;
	redPlayer.xVel = red->getXVelocity();
	redPlayer.xAccel = red->getXAcceleration();
	redPlayer.state = red->getCurrentState();
	bit.Write(redPlayer);

	// Write blue player data.
	PlayerUpdate bluePlayer;
	Player* blue = PlayerManager::getSingletonPtr()->getBluePlayer();
	bluePlayer.lastProcessedInput = m_blueLastProcessedInput;
	bluePlayer.x = blue->getPosition().x;
	bluePlayer.y = blue->getPosition().y;
	bluePlayer.xVel = blue->getXVelocity();
	bluePlayer.xAccel = blue->getXAcceleration();
	bluePlayer.state = blue->getCurrentState();
	bit.Write(bluePlayer);

	// Write stage shift.
	bit.Write(StageManager::getSingletonPtr()->getStage()->getShift());

	return this->broadcast(bit, IMMEDIATE_PRIORITY, UNRELIABLE_SEQUENCED);
}

// ================================================ //

Uint32 Server::stageShift(const int shift)
{
	RakNet::BitStream bit;
	bit.Write(static_cast<RakNet::MessageID>(NetMessage::STAGE_SHIFT));

	Stage::ShiftUpdate update;
	update.shift = shift;
	update.lastProcessedShift = m_lastProcessedStageShift;
	bit.Write(update);

	return this->broadcast(bit, HIGH_PRIORITY, UNRELIABLE);
}

// ================================================ //

Uint32 Server::updateRedPlayer(const Uint32 inputSeq)
{
	Player* red = PlayerManager::getSingletonPtr()->getRedPlayer();
	PlayerUpdate update;
	update.lastProcessedInput = inputSeq;
	update.x = red->getPosition().x;
	update.y = red->getPosition().y;
	update.xVel = red->getXVelocity();
	update.xAccel = red->getXAcceleration();

	RakNet::BitStream bit;
	bit.Write(static_cast<RakNet::MessageID>(NetMessage::UPDATE_RED_PLAYER));
	bit.Write(update);

	return this->send(bit, m_redAddr, IMMEDIATE_PRIORITY);
}

// ================================================ //

Uint32 Server::updateBluePlayer(const Uint32 inputSeq)
{

	return 0;
}

// ================================================ //

Uint32 Server::broadcastDamage(const int player, const Uint32 damage)
{
	RakNet::BitStream bit;
	bit.Write(static_cast<RakNet::MessageID>((player == Game::Playing::PLAYING_RED) ?
		NetMessage::RED_TAKE_DAMAGE : NetMessage::BLUE_TAKE_DAMAGE));
	bit.Write(damage);

	return this->broadcast(bit, HIGH_PRIORITY, RELIABLE_ORDERED);
}

// ================================================ //

Uint32 Server::sendLastProcessedInput(void)
{
	RakNet::BitStream bit;
	bit.Write(static_cast<RakNet::MessageID>(NetMessage::LAST_PROCESSED_INPUT_SEQUENCE));
	bit.Write(m_redLastProcessedInput);

	return this->send(bit, m_redAddr);
}

// ================================================ //

void Server::registerClient(const char* username, const RakNet::SystemAddress& addr)
{
	ClientConnection client;
	client.username = username;
	client.addr = addr;
	m_clients.push_back(client);
}

// ================================================ //

void Server::removeClient(const RakNet::SystemAddress& addr)
{
	m_clients.erase(m_clients.begin() + this->getClient(addr));
}

// ================================================ //

bool Server::isUsernameInUse(const std::string& username)
{
	if (username.compare(Game::getSingletonPtr()->getUsername()) == 0){
		return true;
	}
	for (ClientList::iterator itr = m_clients.begin();
		itr != m_clients.end();
		++itr){
		if (username.compare(itr->username) == 0){
			return true;
		}
	}

	return false;
}

// ================================================ //

const bool Server::validateInput(const Client::NetInput& input) const
{
	if (input.dt > 0.035){ // This value is under question.
		return false;
	}

	return true;
}

// ================================================ //

void Server::dbgPrintAllConnectedClients(void)
{
	if (m_clients.size() == 0){
		printf("NO CONNECTED CLIENTS.\n");
	}
	else{
		printf("CURRENTLY CONNECTED CLIENTS (FROM CLIENT LIST):\n");
		for (ClientList::iterator itr = m_clients.begin();
			itr != m_clients.end();
			++itr){
			printf("-----------\nUsername: %s\nAddress: %s\n",
				itr->username.c_str(), itr->addr.ToString());
		}
		printf("\nCONNECTED SYSTEMS:\n");
		unsigned short num = Server::MaxClients;
		RakNet::SystemAddress* addrs = new RakNet::SystemAddress[num];
		m_peer->GetConnectionList(addrs, &num);
		for (USHORT u = 0; u < num; ++u){
			printf("%s\n", addrs[u].ToString());
		}
		printf("DONE.\n");
	}
}

// ================================================ //

void Server::dbgPrintReadyQueue(void)
{
	if (m_readyQueue.size() == 0){
		printf("EMPTY READY QUEUE.\n");
	}
	else{
		printf("READY QUEUE:\n");
		Uint32 i = 1;
		for (ReadyQueue::iterator itr = m_readyQueue.begin();
			itr != m_readyQueue.end();
			++itr, ++i){
			printf("%d - %s / %d\n", i, itr->username.c_str(), itr->fighter);
		}
	}
}

// ================================================ //

const char* Server::getPacketStrData(void) const
{
	RakNet::BitStream bit(m_packet->data, m_packet->length, false);
	RakNet::RakString rs;
	bit.IgnoreBytes(sizeof(RakNet::MessageID));
	bit.Read(rs);
	return rs.C_String();
}

// ================================================ //