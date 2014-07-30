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
#include "Log.hpp"
#include "Engine.hpp"
#include "Packet.hpp"
#include "Timer.hpp"

// ================================================ //

template<> Client* Singleton<Client>::msSingleton = nullptr;

// ================================================ //

Client::Client(const std::string& server, const int port) :
m_port(port),
m_sock(nullptr),
m_sendPacket(nullptr),
m_recvPacket(nullptr),
m_serverAddr(),
m_pLastResponse(new Timer())
{
	Log::getSingletonPtr()->logMessage("Initializing Client...");

	m_sock = SDLNet_UDP_Open(0);
	if (!m_sock){
		throw std::exception(std::string("Failed to open UDP client socket on port " +
			Engine::toString(m_port)).c_str());
	}

	if (SDLNet_ResolveHost(&m_serverAddr, server.c_str(), m_port) == -1){
		throw std::exception(std::string("Failed to resolve host" + server).c_str());
	}

	m_sendPacket = SDLNet_AllocPacket(66560);
	m_recvPacket = SDLNet_AllocPacket(66560);

	// Send connection request to server.
	Packet data;
	data.type = Packet::CONNECT_REQUEST;
	data.setMessage("unixunited");

	Packet::send(m_sendPacket, m_sock, m_serverAddr, data);

	m_pLastResponse->restart();

	Log::getSingletonPtr()->logMessage("Client intialized!");
}

// ================================================ //

Client::~Client(void)
{
	if (m_sock){
		SDLNet_UDP_Close(m_sock);
	}
	
	m_sendPacket->data = nullptr;
	m_recvPacket->data = nullptr;
	SDLNet_FreePacket(m_sendPacket);
	SDLNet_FreePacket(m_recvPacket);
}

// ================================================ //

int Client::chat(const std::string& msg)
{
	Packet data;
	data.type = Packet::CHAT;
	data.setMessage(msg);
	
	return Packet::send(m_sendPacket, m_sock, m_serverAddr, data);
}

// ================================================ //

void Client::update(double dt)
{
	// Process incoming packets.
	if (SDLNet_UDP_Recv(m_sock, m_recvPacket)){
		Packet* packet = reinterpret_cast<Packet*>(m_recvPacket->data);

		printf("Received packet:\nHeader: %s\nID: %d\nType: %d\n",
			packet->header, packet->id, packet->type);
	}
	else{
		printf("No incoming packet %s\n", SDLNet_GetError());
	}
}

// ================================================ //