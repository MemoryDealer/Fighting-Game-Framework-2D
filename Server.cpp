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
const Uint32 Packet::PROTOCOL_ID = 666666;

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

Packet* Server::update(double dt)
{
	// Process any incoming packets.
	if (SDLNet_UDP_Recv(m_sock, m_packet)){
		Packet* data = reinterpret_cast<Packet*>(m_packet->data);

		if (data->header == Packet::PROTOCOL_ID){
			switch (data->type){
			default:
				break;

			case Packet::CONNECT_REQUEST:
				printf("%s connected!\n", data->message);
				{
					Packet accept;
					accept.type = Packet::CONNECT_ACCEPT;
					printf("CONNECT_ACCEPT: %d\n", Packet::send(m_packet, m_sock, m_packet->address, accept));

					ClientConnection client;
					client.addr = m_packet->address;
					client.username.assign(data->message);
					m_clients.push_back(client);
				}
				break;

			case Packet::CHAT:
				if (this->isClientConnected(m_packet->address)){
					Packet* r = new Packet();
					r->setMessage(m_clients[this->getClient(m_packet->address)].username + ": " + data->message);
					r->type = data->type;
					return r;
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

	return nullptr;
}

// ================================================ //