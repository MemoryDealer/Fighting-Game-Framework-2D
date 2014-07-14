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
#include "Engine.hpp"
#include "Config.hpp"
#include "Log.hpp"

// ================================================ //

template<> Server* Singleton<Server>::msSingleton = nullptr;

// ================================================ //

Server::Server(const int port) :
m_port(port),
m_sock(nullptr),
m_active(false)
{
	Log::getSingletonPtr()->logMessage("Initializing Server...");

	m_sock = SDLNet_UDP_Open(m_port);

	if (!m_sock){
		throw std::exception("Failed to open UDP server socket");
	}
	m_active = true;

	// Allocate space for 65 KB packets.
	m_packet = SDLNet_AllocPacket(66560);

	Log::getSingletonPtr()->logMessage("Server initialized!");
}

// ================================================ //

Server::~Server(void)
{
	if (m_sock){
		SDLNet_UDP_Close(m_sock);
	}

	SDLNet_FreePacket(m_packet);
}

// ================================================ //

void Server::testRecv(void)
{
	if (SDLNet_UDP_Recv(m_sock, m_packet)){
		printf("UDP Packet incoming\n");
		printf("\tChan:    %d\n", m_packet->channel);
		printf("\tData:    %s\n", (char*)m_packet->data);
		printf("\tLen:     %d\n", m_packet->len);
		printf("\tMaxlen:  %d\n", m_packet->maxlen);
		printf("\tStatus:  %d\n", m_packet->status);
		printf("\tAddress: %x %x\n", m_packet->address.host, m_packet->address.port);
	}
	/*else{
		printf("No incoming UDP packet.\n");
	}*/
}

// ================================================ //