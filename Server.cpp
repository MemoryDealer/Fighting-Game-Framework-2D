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

Server::Server(const int port) :
m_peer(RakNet::RakPeerInterface::GetInstance()),
m_packet(nullptr),
m_buffer(),
m_clients(),
m_clientTimeout(10000)
{
	Log::getSingletonPtr()->logMessage("Initializing Server...");

	RakNet::SocketDescriptor sd(port, 0);
	m_peer->Startup(Server::MaxClients, &sd, 1);
	m_peer->SetMaximumIncomingConnections(Server::MaxClients);

	Log::getSingletonPtr()->logMessage("Server initialized!");
}

// ================================================ //

Server::~Server(void)
{
	RakNet::RakPeerInterface::DestroyInstance(m_peer);
}

// ================================================ //

Uint32 Server::send(const RakNet::BitStream& bit, const RakNet::SystemAddress& addr,
	const PacketPriority priority)
{
	return m_peer->Send(&bit, priority, RELIABLE_ORDERED, 0, addr, false);
}

// ================================================ //

Uint32 Server::broadcast(const RakNet::Packet* packet, const RakNet::SystemAddress& exclude,
	const PacketPriority priority)
{
	RakNet::BitStream bit(packet->data, packet->length, false);
	
	return m_peer->Send(&bit, priority, RELIABLE_ORDERED, 0, exclude, true);
}

// ================================================ //

Uint32 Server::broadcast(const RakNet::BitStream& bit, const RakNet::SystemAddress& exclude,
	const PacketPriority priority)
{
	return m_peer->Send(&bit, priority, RELIABLE_ORDERED, 0, exclude, true);
}

// ================================================ //

Uint32 Server::chat(const std::string& msg)
{
	RakNet::BitStream bit;
	bit.Write(static_cast<RakNet::MessageID>(NetMessage::CHAT));
	bit.Write(msg.c_str());

	return this->broadcast(bit);
}

// ================================================ //

int Server::update(double dt)
{
	// Process any incoming packets.
	for (m_packet = m_peer->Receive(); 
		m_packet; 
		m_peer->DeallocatePacket(m_packet), m_packet = m_peer->Receive()){
		switch (m_packet->data[0]){
		default:

			break;

		case ID_NEW_INCOMING_CONNECTION:
			// Wait for SET_USERNAME message.
			break;

		case ID_DISCONNECTION_NOTIFICATION:
			m_buffer = m_clients[this->getClient(m_packet->systemAddress)].username;
			Log::getSingletonPtr()->logMessage("SERVER: Removing client [" +
				std::string(m_packet->systemAddress.ToString()) + "]");
			this->removeClient(m_packet->systemAddress);

			// Tell all other clients.
			{
				RakNet::BitStream bit;
				bit.Write(static_cast<RakNet::MessageID>(NetMessage::CLIENT_DISCONNECTED));
				bit.Write(m_buffer.c_str());
				this->broadcast(bit);
			}
			break;

		case ID_CONNECTION_LOST:
			m_buffer = m_clients[this->getClient(m_packet->systemAddress)].username;
			Log::getSingletonPtr()->logMessage("SERVER: Removing client [" +
				std::string(m_packet->systemAddress.ToString()) + "]");
			this->removeClient(m_packet->systemAddress);
			{
				RakNet::BitStream bit;
				bit.Write(static_cast<RakNet::MessageID>(NetMessage::CLIENT_LOST_CONNECTION));
				bit.Write(m_buffer.c_str());
				this->broadcast(bit);
			}
			break;

		case NetMessage::SYSTEM_MESSAGE:
			{
				RakNet::BitStream bit(m_packet->data, m_packet->length, false);
				RakNet::RakString rs;
				bit.IgnoreBytes(sizeof(RakNet::MessageID));
				bit.Read(rs);
				printf("Client says: %s\n", rs.C_String());
			}
			break;

		case NetMessage::SET_USERNAME:
			{
				RakNet::BitStream bit(m_packet->data, m_packet->length, false);
				RakNet::RakString rs;
				bit.IgnoreBytes(sizeof(RakNet::MessageID));
				bit.Read(rs);

				Log::getSingletonPtr()->logMessage("SERVER: Client [" + std::string(m_packet->systemAddress.ToString()) +
					"] connected with username \"" + rs.C_String() + "\"");
				
				// Add them to the client list.
				this->registerClient(rs.C_String(), m_packet->systemAddress);

				this->broadcast(m_packet, m_packet->systemAddress);
			}
			break;

		case NetMessage::CHAT:
			this->broadcast(m_packet, m_packet->systemAddress);
			break;
		}

		return m_packet->data[0];
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

void Server::dbgPrintAllConnectedClients(void)
{
	if (m_clients.size() == 0){
		printf("NO CONNECTED CLIENTS.\n");
	}
	else{
		printf("CURRENTLY CONNECTED CLIENTS:\n");
		for (ClientList::iterator itr = m_clients.begin();
			itr != m_clients.end();
			++itr){
			printf("-----------\nUsername: %s\nAddress: %s\n",
				itr->username.c_str(), itr->addr.ToString());
		}
		printf("\n");
	}
}

// ================================================ //

const char* Server::getLastPacketStrData(void) const
{
	RakNet::BitStream bit(m_packet->data, m_packet->length, false);
	RakNet::RakString rs;
	bit.IgnoreBytes(sizeof(RakNet::MessageID));
	bit.Read(rs);
	return rs.C_String();
}

// ================================================ //