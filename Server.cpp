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
#include "Packet.hpp"
#include "Engine.hpp"
#include "Config.hpp"
#include "Timer.hpp"
#include "Log.hpp"

// ================================================ //

template<> Server* Singleton<Server>::msSingleton = nullptr;

// ================================================ //

// Define ExtMF's packet header protocol ID.
Uint32 Packet::PROTOCOL_ID = 666666;

// ================================================ //

Server::Server(const int port) :
m_port(port),
m_sock(nullptr),
m_packet(),
m_clients()
{
	Log::getSingletonPtr()->logMessage("Initializing Server...");

	m_sock = SDLNet_UDP_Open(m_port);

	if (!m_sock){
		throw std::exception("Failed to open UDP server socket");
	}

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

	m_packet->data = nullptr;
	SDLNet_FreePacket(m_packet);
}

// ================================================ //

void Server::update(double dt)
{
	// Process any incoming packets.
	if (SDLNet_UDP_Recv(m_sock, m_packet)){
		Packet* packet = reinterpret_cast<Packet*>(m_packet->data);

		if (packet->header == Packet::PROTOCOL_ID){
			switch (packet->type){
			default:
				break;

			case Packet::CONNECT_REQUEST:
				printf("%s connected!\n", packet->buf);
				{
					Packet data;
					data.header = Packet::PROTOCOL_ID;
					data.type = Packet::CONNECT_ACCEPT;

					ClientConnection client;
					client.addr = m_packet->address;
					client.channel = m_packet->channel;
					strcpy(client.username, packet->buf);
					m_clients.push_back(client);

					m_packet->address.host = client.addr.host;
					m_packet->address.port = client.addr.port;
					m_packet->data = reinterpret_cast<Uint8*>(&data);
					m_packet->len = sizeof(data)+1;
					printf("Send: %d\n", SDLNet_UDP_Send(m_sock, -1, m_packet));
				}
				break;
			}
		}
	}

	// Update all clients.
	/*for (ClientList::iterator itr = m_clients.begin();
		itr != m_clients.end();
		++itr){
		Packet data;
		data.header = Packet::PROTOCOL_ID;
		data.type = Packet::CONNECT_ACCEPT;

		memset(m_packet, 0, sizeof(m_packet));
		m_packet->address = itr->addr;
		m_packet->data = reinterpret_cast<Uint8*>(&data);
		m_packet->len = sizeof(data)+1;
		SDLNet_UDP_Send(m_sock, -1, m_packet);
	}*/
}

// ================================================ //