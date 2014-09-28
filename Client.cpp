// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: Client.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements Client singleton class.
// ================================================ //

#include "Client.hpp"
#include "NetMessage.hpp"
#include "Log.hpp"
#include "Engine.hpp"
#include "Timer.hpp"
#include "Game.hpp"
#include "PlayerManager.hpp"
#include "StageManager.hpp"
#include "Stage.hpp"

// ================================================ //

template<> Client* Singleton<Client>::msSingleton = nullptr;

// ================================================ //

Client::Client(const std::string& server, const int port) :
m_peer(RakNet::RakPeerInterface::GetInstance()),
m_packet(nullptr),
m_server(server),
m_port(port),
m_connected(false),
m_inputSeq(0),
m_pendingInputs(),
m_pendingStageShifts(),
m_stageShiftSeq(0),
m_timeout(10000)
{
	Log::getSingletonPtr()->logMessage("Initializing Client...");

	RakNet::SocketDescriptor sd;
	m_peer->Startup(1, &sd, 1);

	if (Game::getSingletonPtr()->useNetSimulator()){
		m_peer->ApplyNetworkSimulator(Game::getSingletonPtr()->getNetSimulatedPacketLoss(), 
			Game::getSingletonPtr()->getNetSimulatedPing() / 2, 0);
	}

	Log::getSingletonPtr()->logMessage("Client intialized!");
}

// ================================================ //

Client::~Client(void)
{
	RakNet::RakPeerInterface::DestroyInstance(m_peer);
}

// ================================================ //

bool Client::update(void)
{
	switch (m_packet->data[0]){
	default:
		return false;

	case NetMessage::PLAYING_RED:
		Game::getSingletonPtr()->setPlaying(Game::PLAYING_RED);
		break;

	case NetMessage::PLAYING_BLUE:
		Game::getSingletonPtr()->setPlaying(Game::PLAYING_BLUE);
		break;
	}

	return true;
}

// ================================================ //

Uint32 Client::send(const RakNet::BitStream& bit, const PacketPriority priority, const PacketReliability reliability)
{
	return m_peer->Send(&bit, priority, reliability, 0, m_serverAddr, false);
}

// ================================================ //

Uint32 Client::connect(void)
{
	if (!m_connected){
		// Send connection request to server.
		m_peer->Connect(m_server.c_str(), m_port, 0, 0);
	}

	return 0;
}

// ================================================ //

void Client::disconnect(void)
{
	// Send this with immediate priority because the peer connection 
	// will be closed soon after this function is called.
	m_peer->CloseConnection(m_serverAddr, true, 0, IMMEDIATE_PRIORITY);
}

// ================================================ //

Uint32 Client::chat(const std::string& msg)
{
	RakNet::BitStream bit;
	bit.Write(static_cast<RakNet::MessageID>(NetMessage::CHAT));
	bit.Write(msg.c_str());

	return this->send(bit, HIGH_PRIORITY, RELIABLE_ORDERED);
}

// ================================================ //

Uint32 Client::ready(const Uint32 fighter)
{
	RakNet::BitStream bit;
	bit.Write(static_cast<RakNet::MessageID>(NetMessage::READY));
	bit.Write(fighter);

	return this->send(bit, HIGH_PRIORITY, RELIABLE_ORDERED);
}

// ================================================ //

Uint32 Client::sendInput(const Uint32 input, const bool value, const double dt)
{
	const Uint32 seq = m_inputSeq++;

	// Save input for later reconciliation.
	ClientInput clientInput;
	clientInput.input = input;
	clientInput.value = value;
	clientInput.seq = seq;
	clientInput.dt = dt;
	if (Game::getSingletonPtr()->getPlaying() == Game::PLAYING_RED){
		if (PlayerManager::getSingletonPtr()->getRedPlayer()->getCurrentState() == Player::State::JUMPING){
			clientInput.xVel = PlayerManager::getSingletonPtr()->getRedPlayer()->getXJumpVelocity();
		}
		else{
			clientInput.xVel = PlayerManager::getSingletonPtr()->getRedPlayer()->getXVelocity();
		}

		clientInput.yVel = PlayerManager::getSingletonPtr()->getRedPlayer()->getYVelocity();
	}
	else if (Game::getSingletonPtr()->getPlaying() == Game::PLAYING_BLUE){
		if (PlayerManager::getSingletonPtr()->getBluePlayer()->getCurrentState() == Player::State::JUMPING){
			clientInput.xVel = PlayerManager::getSingletonPtr()->getBluePlayer()->getXJumpVelocity();
		}
		else{
			clientInput.xVel = PlayerManager::getSingletonPtr()->getBluePlayer()->getXVelocity();
		}

		clientInput.yVel = PlayerManager::getSingletonPtr()->getBluePlayer()->getYVelocity();
	}

	m_pendingInputs.push_back(clientInput);

	// Create packet and send.
	RakNet::BitStream bit;
	bit.Write(static_cast<RakNet::MessageID>(NetMessage::CLIENT_INPUT));
	NetInput netInput;
	netInput.input = input;
	netInput.value = value;
	netInput.seq = seq;
	netInput.dt = dt;
	bit.Write(netInput);

	// Write stage shift sequence.
	bit.Write(m_stageShiftSeq);

	return this->send(bit, IMMEDIATE_PRIORITY, RELIABLE_ORDERED);
}

// ================================================ //

const char* Client::getPacketStrData(void) const
{
	RakNet::BitStream bit(m_packet->data, m_packet->length, false);
	RakNet::RakString rs;
	bit.IgnoreBytes(sizeof(RakNet::MessageID));
	bit.Read(rs);
	return rs.C_String();
}

// ================================================ //
