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
	IPaddress addr;
	std::string username;
	std::shared_ptr<Timer> timer;
};

// ================================================ //

// Handles all server-side operations.
class Server : public Singleton<Server>
{
public:
	// Opens a UDP socket on specified port. Allocates UDPPacket pointer
	// for sending/receiving packets.
	explicit Server(const int port = 666);

	// Closes the UDP socket and frees the UDPPacket.
	~Server(void);

	// Receives packets and process them.
	int update(double dt);

	// Returns true if client address has already connected.
	bool isClientConnected(const IPaddress& addr);

	// Sends a packet to all connected clients. Excludes excludeAddr if exclude
	// parameter is true.
	int broadcastToAllClients(Packet* data, const bool exclude = false, const IPaddress excludeAddr = IPaddress());

	// Getters

	// Returns index of client matching the specified IPaddress.
	// Returns -1 if not found.
	int getClient(const IPaddress& addr);

	// Setters

	// Sets the handle for packet data to be copied to so game states can access it.
	void setPacketHandle(Packet* handle);

private:
	Uint32 m_port;
	UDPsocket m_sock;
	UDPpacket* m_sendPacket;
	UDPpacket* m_recvPacket;
	ClientList m_clients;
	Packet* m_packetHandle;
	int m_clientTimeout;
};

// ================================================ //

inline bool Server::isClientConnected(const IPaddress& addr){
	for (ClientList::iterator itr = m_clients.begin();
		itr != m_clients.end();
		++itr){
		if (addr.host == itr->addr.host && 
			addr.port == itr->addr.port){
			return true;
		}
	}

	return false;
}

// Getters

inline int Server::getClient(const IPaddress& addr){
	for (unsigned int i = 0; i < m_clients.size(); ++i){
		if (addr.host == m_clients[i].addr.host &&
			addr.port == m_clients[i].addr.port){
			return i;
		}
	}

	return -1;
}

// Setters

inline void Server::setPacketHandle(Packet* handle){
	m_packetHandle = handle;
}

// ================================================ //

#endif

// ================================================ //