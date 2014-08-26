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

	// Sends a packet to the specified client using a BitStream.
	Uint32 send(const RakNet::BitStream& bit, const RakNet::SystemAddress& addr,
		const PacketPriority priority = HIGH_PRIORITY);

	// Sends a packet to all connected clients, except the excluded address if specified.
	Uint32 broadcast(const RakNet::Packet* packet, const RakNet::SystemAddress& exclude = RakNet::UNASSIGNED_SYSTEM_ADDRESS,
		const PacketPriority priority = HIGH_PRIORITY);
	Uint32 broadcast(const RakNet::BitStream& bit, const RakNet::SystemAddress& exclude = RakNet::UNASSIGNED_SYSTEM_ADDRESS,
		const PacketPriority priority = HIGH_PRIORITY);

	// Sends a chat message to all clients.
	Uint32 chat(const std::string& msg);

	// Sends a list of players to the client. Should be called before the new client
	// is added to the client list.
	Uint32 sendPlayerList(const RakNet::SystemAddress& addr);

	// Receives packets and process them.
	int update(double dt);

	// Adds a client to the list of connected clients.
	void registerClient(const char* username, const RakNet::SystemAddress& addr);

	// Removes a client from the list of connected clients.
	void removeClient(const RakNet::SystemAddress& addr);

	// Returns true if client address has already connected.
	bool isClientConnected(const RakNet::SystemAddress& addr);

	// Returns true if a connected client is using the username.
	bool isUsernameInUse(const std::string& username);

	// Debugging

	// Prints all connected clients addresses and usernames.
	void dbgPrintAllConnectedClients(void);

	// Getters

	// Returns index of client matching the specified IPaddress.
	// Returns -1 if not found.
	int getClient(const RakNet::SystemAddress& addr);

	// Returns the internal pointer to the RakNet::Packet which is updated
	// with each step.
	RakNet::Packet* getLastPacket(void) const;

	// Returns a string of the first set of data of the last packet (skipping
	// the first byte).
	const char* getLastPacketStrData(void) const;

	// Returns the internal std::string buffer for passing data between Server 
	// and game states.
	std::string getBuffer(void) const;

	// Setters

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
		if (addr == itr->addr && addr.GetPort() == itr->addr.GetPort()){
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

inline RakNet::Packet* Server::getLastPacket(void) const{
	return m_packet;
}

inline std::string Server::getBuffer(void) const{
	return m_buffer;
}

// Setters

// ================================================ //

#endif

// ================================================ //