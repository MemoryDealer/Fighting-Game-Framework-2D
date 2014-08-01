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
#include "MUDP.hpp"

// ================================================ //

struct Packet;
struct ClientConnection;
typedef std::vector<ClientConnection> ClientList;
class Timer;

// ================================================ //

struct ClientConnection{
	MUDP::IP address;
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
	void registerClient(const char* username, const MUDP::IP& address);

	// Removes a client from the list of connected clients.
	void removeClient(const MUDP::IP& address);

	// Returns true if client address has already connected.
	bool isClientConnected(const MUDP::IP& address);

	// Resets a client's timer, checking to be sure they are connected.
	void resetClientTimer(const MUDP::IP& address);

	// Sends a packet to all connected clients. Excludes excludeAddr if exclude
	// parameter is true.
	int broadcastToAllClients(MUDP::Packet* packet, const bool exclude = false, 
		const MUDP::IP excludeAddress = MUDP::IP());

	// Getters

	// Returns index of client matching the specified IPaddress.
	// Returns -1 if not found.
	int getClient(const MUDP::IP& address);

	// Setters

	// Sets the handle for packet data to be copied to so game states can access it.
	void setPacketHandle(MUDP::Packet* handle);

private:
	// Socket descriptor.
	std::shared_ptr<MUDP::Socket> m_pSD;
	ClientList m_clients;
	MUDP::Packet* m_packet;
	int m_clientTimeout;
};

// ================================================ //

inline bool Server::isClientConnected(const MUDP::IP& address){
	for (ClientList::iterator itr = m_clients.begin();
		itr != m_clients.end();
		++itr){
		if (address == itr->address){
			return true;
		}
	}

	return false;
}

// Getters

inline int Server::getClient(const MUDP::IP& address){
	for (unsigned int i = 0; i < m_clients.size(); ++i){
		if (address == m_clients[i].address){
			return i;
		}
	}

	return -1;
}

// Setters

inline void Server::setPacketHandle(MUDP::Packet* handle){
	m_packet = handle;
}

// ================================================ //

#endif

// ================================================ //