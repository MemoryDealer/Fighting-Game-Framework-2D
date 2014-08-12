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
#include "Timer.hpp"
#include "Log.hpp"

// ================================================ //

template<> Server* Singleton<Server>::msSingleton = nullptr;

// ================================================ //

// Define ExtMF's packet header protocol ID.


// ================================================ //

Server::Server(const int port) :
m_pSD(new MUDP::Socket(port)),
m_clients(),
m_packet(nullptr),
m_clientTimeout(10000)
{
	Log::getSingletonPtr()->logMessage("Initializing Server...");

	RakNet::RakPeerInterface *peer = RakNet::RakPeerInterface::GetInstance();
	RakNet::SocketDescriptor sd(port, 0);
	peer->Startup(1, &sd, 1);

	Log::getSingletonPtr()->logMessage("Server initialized!");
}

// ================================================ //

Server::~Server(void)
{
	
}

// ================================================ //

int Server::update(double dt)
{
	// Check each client to see if any have timed out.
	
	// Process any incoming packets.
	MUDP::IP source;
	if (m_pSD->recv(m_packet, source)){
		if (this->isClientConnected(source)){
			switch (m_packet->type){
			default:
				break;

			case MUDP::Packet::DISCONNECT:
				this->removeClient(source);
				this->broadcastToAllClients(m_packet);

				// Return here to avoid sending an ACK packet back to disconnected client.
				return m_packet->type;

			case MUDP::Packet::CHAT:
				this->broadcastToAllClients(m_packet, true, source);
				break;

			case MUDP::Packet::ACK:

				break;
			}

			// Reset client's timer, as the server has received a response from them.
			this->resetClientTimer(source);

			// Send ACK packet back to client.
			/*m_packet->type = MUDP::Packet::ACK;
			m_pSD->send(m_packet, source);*/

			return m_packet->type;
		}
		else{
			// New client, see if they are valid.
			if (m_packet->type == MUDP::Packet::CONNECT_REQUEST){
				this->registerClient(m_packet->message, source);
				
				// Send connection acceptance back to new client.
				m_packet->type = MUDP::Packet::CONNECT_ACCEPT;
				m_pSD->send(m_packet, source);

				// Notify other clients of new client.
				this->broadcastToAllClients(m_packet, true, source);

				return m_packet->type;
			}
		}
	}

	return 0;
}

// ================================================ //

void Server::registerClient(const char* username, const MUDP::IP& address)
{
	ClientConnection client;
	client.address = address;
	client.username.assign(m_packet->message);
	client.timer.reset(new Timer());
	client.timer->restart();
	m_clients.push_back(client);
}

// ================================================ //

void Server::removeClient(const MUDP::IP& address)
{
	m_clients.erase(m_clients.begin() + this->getClient(address));
}

// ================================================ //

void Server::resetClientTimer(const MUDP::IP& address)
{
	// Find the client and reset timer.
	for (ClientList::iterator itr = m_clients.begin();
		itr != m_clients.end();
		++itr){
		if (itr->address == address){
			itr->timer.reset();
			return;
		}
	}
}

// ================================================ //

int Server::broadcastToAllClients(MUDP::Packet* packet, const bool exclude, const MUDP::IP excludeAddress)
{
	int numSent = 0;
	for (ClientList::iterator itr = m_clients.begin();
		itr != m_clients.end();
		++itr){
		if (exclude == true && itr->address == excludeAddress){
			continue;
		}
		else if (m_pSD->send(packet, itr->address)){
			++numSent;
		}
	}

	return numSent;
}

// ================================================ //