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

struct ClientConnection{
	RakNet::SystemAddress addr;
	std::string username;
};

struct ClientReady{
	std::string username;
	Uint32 fighter;
};

// ================================================ //

struct Packet;
typedef std::vector<ClientConnection> ClientList;
typedef std::list<ClientReady> ReadyQueue;
class Timer;

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

	// Broadcasts READY packet and adds server player to ready queue.
	Uint32 ready(const Uint32 fighter);

	// Broadcasts a SERVER_STARTING_GAME packet.
	Uint32 startGame(void);

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

	// Adds username to ready queue if it doesn't exist in the queue.
	// Returns true if successfully added, false means it already exists.
	bool addToReadyQueue(const std::string& username, const Uint32 fighter);

	// Removes a client from the ready queue.
	void removeFromReadyQueue(const std::string& username);

	// Debugging

	// Prints all connected clients addresses and usernames.
	void dbgPrintAllConnectedClients(void);

	// Prints the ready queue.
	void dbgPrintReadyQueue(void);

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

	// The order in which players "ready up." The server process this as 
	// first come, first server; so first to ready up will play first. After
	// the game starts, they are removed from the queue and the next two play.
	// The std::string should specify the username.
	ReadyQueue m_readyQueue;

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

inline bool Server::addToReadyQueue(const std::string& username, const Uint32 fighter){
	// See if username is already in queue.
	for (ReadyQueue::iterator itr = m_readyQueue.begin();
		itr != m_readyQueue.end();
		++itr){
		if (itr->username.compare(username) == 0){
			return false;
		}
	}

	ClientReady ready;
	ready.username = username;
	ready.fighter = fighter;
	m_readyQueue.push_back(ready);
	return true;
}

inline void Server::removeFromReadyQueue(const std::string& username){
	Log::getSingletonPtr()->logMessage("SERVER: Removing client " + 
		username + " from ready queue.");
	for (ReadyQueue::iterator itr = m_readyQueue.begin();
		itr != m_readyQueue.end();
		++itr){
		if (itr->username.compare(username) == 0){
			itr = m_readyQueue.erase(itr);
			return;
		}
	}
	Log::getSingletonPtr()->logMessage("SERVER: Client not found in ready queue..");
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