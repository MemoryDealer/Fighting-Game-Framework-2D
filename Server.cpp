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
#include "Log.hpp"

// ================================================ //

template<> Server* Singleton<Server>::msSingleton = nullptr;

// ================================================ //

// Define ExtMF's packet header protocol ID.


// ================================================ //

Server::Server(const int port) :
m_peer(RakNet::RakPeerInterface::GetInstance()),
m_packet(nullptr),
m_clients(),
m_clientTimeout(10000)
{
	Log::getSingletonPtr()->logMessage("Initializing Server...");

	RakNet::SocketDescriptor sd(port, 0);
	m_peer->Startup(MaxClients, &sd, 1);
	m_peer->SetMaximumIncomingConnections(MaxClients);

	Log::getSingletonPtr()->logMessage("Server initialized!");
}

// ================================================ //

Server::~Server(void)
{
	RakNet::RakPeerInterface::DestroyInstance(m_peer);
}

// ================================================ //

int Server::update(double dt)
{
	// Process any incoming packets.
	for (m_packet = m_peer->Receive(); 
		m_packet; 
		m_peer->DeallocatePacket(m_packet), m_packet = m_peer->Receive()){
		switch (m_packet->data[0]){
		case ID_NEW_INCOMING_CONNECTION:
			printf("Connection incoming...\n");
			break;

		case ID_DISCONNECTION_NOTIFICATION:
			printf("A client has disconnected.\n");
			break;

		case ID_CONNECTION_LOST:
			printf("Connection lost from client.\n");
			break;

		case NetMessage::SYSTEM_MESSAGE:
			{
				RakNet::BitStream bit(m_packet->data, m_packet->length, false);
				RakNet::RakString rs;
				bit.IgnoreBytes(sizeof(RakNet::MessageID));
				bit.Read(rs);
				printf("Client says: %s\n", rs.C_String());
			}
			return NetMessage::SYSTEM_MESSAGE;

		case NetMessage::SET_USERNAME:
			{
				RakNet::BitStream bit(m_packet->data, m_packet->length, false);
				RakNet::RakString rs;
				bit.IgnoreBytes(sizeof(RakNet::MessageID));
				bit.Read(rs);
				printf("%s connected!\n", rs.C_String());
				// Add them to the client list.
				this->registerClient(rs.C_String(), m_packet->systemAddress);
			}
			return NetMessage::SET_USERNAME;

		case NetMessage::CHAT:

			return NetMessage::CHAT;
		}
	}

	return 0;
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

int Server::broadcastToAllClients(RakNet::Packet* packet, const bool exclude,
	const RakNet::SystemAddress& excludeAddress)
{
	int numSent = 0;
	for (ClientList::iterator itr = m_clients.begin();
		itr != m_clients.end();
		++itr){
		if (exclude == true && itr->addr == excludeAddress){
			continue;
		}
		/*else if (m_pSD->send(packet, itr->address)){
			++numSent;
		}*/
	}

	return numSent;
}

// ================================================ //

void Server::dbgPrintAllConnectedClients(void)
{
	printf("CURRENTLY CONNECTED CLIENTS:\n");
	for (ClientList::iterator itr = m_clients.begin();
		itr != m_clients.end();
		++itr){
		printf("Username: %s\nAddress: %s\n-----------",
			itr->username.c_str(), itr->addr.ToString());
	}
	printf("\n\n");
}

// ================================================ //