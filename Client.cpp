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

// ================================================ //

template<> Client* Singleton<Client>::msSingleton = nullptr;

// ================================================ //

Client::Client(const std::string& server, const int port) :
m_port(port),
m_sock(nullptr),
m_packet(),
m_serverAddr()
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

	m_packet = SDLNet_AllocPacket(66560);

	// Send connection request to server.
	Packet connect;
	connect.header = Packet::PROTOCOL_ID;
	connect.id = 0;
	connect.type = Packet::CONNECT_REQUEST;
	strcpy(connect.buf, "unixunited");

	m_packet->address.host = m_serverAddr.host;
	m_packet->address.port = m_serverAddr.port;
	m_packet->data = reinterpret_cast<Uint8*>(&connect);
	m_packet->len = sizeof(connect)+1;

	SDLNet_UDP_Send(m_sock, -1, m_packet);

	Log::getSingletonPtr()->logMessage("Client intialized!");
}

// ================================================ //

Client::~Client(void)
{
	if (m_sock){
		SDLNet_UDP_Close(m_sock);
	}
	
	m_packet->data = nullptr;
	SDLNet_FreePacket(m_packet);
}

// ================================================ //

void Client::update(double dt)
{
	// Process incoming packets.
	/*m_packet->data = nullptr;
	if (SDLNet_UDP_Recv(m_sock, m_packet)){
		Packet* packet = reinterpret_cast<Packet*>(m_packet->data);

		printf("Received packet:\nHeader: %s\nID: %d\nType: %d\n",
			packet->header, packet->id, packet->type);
	}
	else{
		printf("No incoming packet\n");
	}*/
}

// ================================================ //