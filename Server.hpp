// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: Server.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines Server singleton class.
// ================================================ //

#ifndef __SERVER_HPP__
#define __SERVER_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

struct Packet;
struct ClientConnection;
typedef std::vector<ClientConnection> ClientList;
class Timer;

// ================================================ //

struct ClientConnection{
	RakNet::SystemAddress addr;
	std::string username;
	std::shared_ptr<Timer> timer;
};

// ================================================ //

// Handles all server-side operations.
class Server : public Singleton<Server>
{
public:
	// Allocates MUDP socket descriptor.
	explicit Server(const int port = 666);

	// Empty destructor.
	~Server(void);

	// Receives packets and process them.
	int update(double dt);

	// Adds a client to the list of connected clients.
	void registerClient(const char* username, const RakNet::SystemAddress& addr);

	// Removes a client from the list of connected clients.
	void removeClient(const RakNet::SystemAddress& addr);

	// Returns true if client address has already connected.
	bool isClientConnected(const RakNet::SystemAddress& addr);

	// Sends a packet to all connected clients. Excludes excludeAddr if exclude
	// parameter is true.
	int broadcastToAllClients(RakNet::Packet* packet, const bool exclude = false, 
		const RakNet::SystemAddress& excludeAddress = nullptr);

	// Getters

	// Returns index of client matching the specified IPaddress.
	// Returns -1 if not found.
	int getClient(const RakNet::SystemAddress& addr);

	// Setters

	// Sets the handle for packet data to be copied to so game states can access it.
	void setBufferHandle(std::string& buffer);

	// --- //

	static const int MaxClients = 10;

private:
	RakNet::RakPeerInterface* m_peer;
	RakNet::Packet* m_packet;
	std::string m_buffer;
	ClientList m_clients;
	int m_clientTimeout;
};

// ================================================ //

inline bool Server::isClientConnected(const RakNet::SystemAddress& addr){
	for (ClientList::iterator itr = m_clients.begin();
		itr != m_clients.end();
		++itr){
		if (addr == itr->addr){
			return true;
		}
	}

	return false;
}

// Getters

inline int Server::getClient(const RakNet::SystemAddress& addr){
	for (unsigned int i = 0; i < m_clients.size(); ++i){
		if (addr == m_clients[i].addr){
			return i;
		}
	}

	return -1;
}

// Setters

inline void Server::setBufferHandle(std::string& buffer){
	m_buffer = buffer;
}

// ================================================ //

#endif

// ================================================ //