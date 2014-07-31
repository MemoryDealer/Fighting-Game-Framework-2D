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
m_sendPacket(nullptr),
m_recvPacket(nullptr),
m_clients(),
m_packetHandle(nullptr),
m_clientTimeout(10000)
{
	Log::getSingletonPtr()->logMessage("Initializing Server...");

	m_sock = SDLNet_UDP_Open(m_port);

	if (!m_sock){
		throw std::exception("Failed to open UDP server socket");
	}

	// Allocate space for 65 KB packets.
	m_sendPacket = SDLNet_AllocPacket(66560);
	m_recvPacket = SDLNet_AllocPacket(66560);

	Log::getSingletonPtr()->logMessage("Server initialized!");
}

// ================================================ //

Server::~Server(void)
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

int Server::update(double dt)
{
	// Check each client to see if any have timed out.
	for (ClientList::iterator itr = m_clients.begin();
		itr != m_clients.end();){
		if (itr->timer->getTicks() > m_clientTimeout){
			// Notify game state of disconnection
			Packet data(Packet::DISCONNECT);
			data.setMessage(itr->username);

			itr = m_clients.erase(itr);

			this->broadcastToAllClients(&data);
			data.clone(m_packetHandle);
			return data.type;
		} 
		else{
			// If it's been more than half the timeout, send a check-in packet.
			if (itr->timer->getTicks() > (m_clientTimeout / 2)){
				Packet data(Packet::CHECK);
				Packet::send(m_sendPacket, m_sock, itr->addr, data);
			}

			++itr;
		}
	}

	// Process any incoming packets.
	if (SDLNet_UDP_Recv(m_sock, m_recvPacket)){
		Packet* data = reinterpret_cast<Packet*>(m_recvPacket->data);
		if (data->header == Packet::PROTOCOL_ID){
			if (this->isClientConnected(m_recvPacket->address)){
				switch (data->type){
				default:
					break;

				case Packet::DISCONNECT:
					m_clients.erase(m_clients.begin() + this->getClient(m_recvPacket->address));
					this->broadcastToAllClients(data);
					data->clone(m_packetHandle);
					return data->type;

				case Packet::CHAT:
					this->broadcastToAllClients(data, true, m_recvPacket->address);
					break;

				case Packet::ACK:
					break;
				}

				// Reset client's timer.
				m_clients[this->getClient(m_recvPacket->address)].timer->restart();

				Packet ack(Packet::ACK);
				Packet::send(m_sendPacket, m_sock, m_recvPacket->address, ack);

				// Store the packet data in game state's handle.
				data->clone(m_packetHandle);
				return data->type;
			}
			else if(data->type == Packet::CONNECT_REQUEST){
				// Add new client to client list.
				ClientConnection client;
				client.addr = m_recvPacket->address;
				client.username.assign(data->message);
				client.timer.reset(new Timer());
				client.timer->restart();
				m_clients.push_back(client);

				// Send a connection acceptance.
				Packet accept;
				accept.type = Packet::CONNECT_ACCEPT;
				Packet::send(m_sendPacket, m_sock, client.addr, accept);

				// Notify all clients of new client.
				this->broadcastToAllClients(data, true, m_recvPacket->address);

				// Store the packet data in game state's handle.
				data->clone(m_packetHandle);
				return data->type;
			}
		}
	}

	return 0;
}

// ================================================ //

int Server::broadcastToAllClients(Packet* data, const bool exclude, const IPaddress excludeAddr)
{
	int numSent = 0;
	for (ClientList::iterator itr = m_clients.begin();
		itr != m_clients.end();
		++itr){
		if (exclude == true && itr->addr.host == excludeAddr.host &&
			itr->addr.port == excludeAddr.port){
			continue;
		}
		else if (Packet::send(m_sendPacket, m_sock, itr->addr, data)){
			++numSent;
		}
	}

	return numSent;
}

// ================================================ //