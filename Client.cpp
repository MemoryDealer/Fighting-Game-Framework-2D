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
#include "GameManager.hpp"

// ================================================ //

template<> Client* Singleton<Client>::msSingleton = nullptr;

// ================================================ //

Client::Client(const std::string& server, const int port) :
m_peer(RakNet::RakPeerInterface::GetInstance()),
m_packet(nullptr),
m_buffer(),
m_server(server),
m_port(port),
m_connected(false),
m_timeout(10000)
{
	Log::getSingletonPtr()->logMessage("Initializing Client...");

	RakNet::SocketDescriptor sd;
	m_peer->Startup(1, &sd, 1);

	Log::getSingletonPtr()->logMessage("Client intialized!");
}

// ================================================ //

Client::~Client(void)
{
	
}

// ================================================ //

int Client::connect(void)
{
	if (!m_connected){
		// Send connection request to server.
		m_peer->Connect(m_server.c_str(), m_port, 0, 0);
	}

	return 0;
}

// ================================================ //

int Client::disconnect(void)
{
	/*if (m_connected){
		m_packet->type = MUDP::Packet::DISCONNECT;
		m_packet->setMessage(GameManager::getSingletonPtr()->getUsername());

		return m_pSD->send(m_packet, m_serverAddress);
	}*/
	
	return 0;
}

// ================================================ //

int Client::chat(const std::string& msg)
{
	/*m_packet->type = MUDP::Packet::CHAT;
	m_packet->setMessage(msg);
	
	return m_pSD->send(m_packet, m_serverAddress);*/
	return 0;
}

// ================================================ //

int Client::update(double dt)
{
	// Process incoming packets.
	for (m_packet = m_peer->Receive();
		m_packet;
		m_peer->DeallocatePacket(m_packet), m_packet = m_peer->Receive()){
		switch (m_packet->data[0]){
		default:
			break;

		case ID_CONNECTION_REQUEST_ACCEPTED:
			printf("Connected to server!\n");
			{
				RakNet::BitStream bit;
				bit.Write(static_cast<RakNet::MessageID>(NetMessage::SYSTEM_MESSAGE));
				bit.Write("Hello There! This is Satan.");
				m_peer->Send(&bit, HIGH_PRIORITY, RELIABLE_ORDERED, 0, m_packet->systemAddress, false);
			}
			break;
		}
	}

	return 0;
}

// ================================================ //