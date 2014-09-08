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
#include "Client.hpp"

// ================================================ //

struct ClientConnection{
	RakNet::SystemAddress addr;
	std::string username;
};

struct ReadyClient{
	std::string username;
	Uint32 fighter;
};

// ================================================ //

struct Packet;
typedef std::vector<ClientConnection> ClientList;
typedef std::list<ReadyClient> ReadyQueue;
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
		const PacketPriority priority = HIGH_PRIORITY, const PacketReliability reliability = UNRELIABLE);

	// Sends a packet to all connected clients, except the excluded address if specified.
	Uint32 broadcast(const RakNet::Packet* packet, const PacketPriority priority = HIGH_PRIORITY,
		const PacketReliability reliability = UNRELIABLE, const RakNet::SystemAddress& exclude = RakNet::UNASSIGNED_SYSTEM_ADDRESS);
	Uint32 broadcast(const RakNet::BitStream& bit, const PacketPriority priority = HIGH_PRIORITY, 
		const PacketReliability reliability = UNRELIABLE, const RakNet::SystemAddress& exclude = RakNet::UNASSIGNED_SYSTEM_ADDRESS);

	// Sends a chat message to all clients.
	Uint32 chat(const std::string& msg);

	// Broadcasts READY packet and adds server player to ready queue.
	Uint32 ready(const Uint32 fighter);

	// Broadcasts a SERVER_STARTING_GAME packet.
	Uint32 startGame(void);

	// Broadcasts a MATCH_OVER packet, containg the username of the victor.
	Uint32 matchOver(const std::string& victor);

	// Sends a list of players to the client. Should be called before the new client
	// is added to the client list.
	Uint32 sendPlayerList(const RakNet::SystemAddress& addr, const bool broadcast = false);
	
	// Broadcasts all relevant player information to clients.
	Uint32 updatePlayers(void);

	// Sends a PlayerUpdate only to the client playing the red player.
	Uint32 updateRedPlayer(const Uint32 inputSeq);

	// Sends a PlayerUpdate only to the client playing the blue player.
	Uint32 updateBluePlayer(const Uint32 inputSeq);

	// Sends the last processed input sequence number to playing clients.
	Uint32 sendLastProcessedInput(void);

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

	// Returns true if client input seems valid.
	const bool validateInput(const Client::NetInput& input) const;

	// Debugging

	// Prints all connected clients addresses and usernames.
	void dbgPrintAllConnectedClients(void);

	// Prints the ready queue.
	void dbgPrintReadyQueue(void);

	// Getters

	// Returns index of client matching the specified IPaddress.
	// Returns -1 if not found.
	int getClient(const RakNet::SystemAddress& addr);

	// Returns index of client matching the username.
	int getClient(const std::string& username);

	// Returns ClientConnection object of client matching username.
	ClientConnection getClientPtr(const std::string& username);

	// Returns the size of the ready queue.
	const int getReadyQueueSize(void) const;

	// Returns ClientReady object from the ready client queue.
	ReadyClient getReadyClient(const Uint32 n);

	// Returns the next client in the ready queue.
	ReadyClient getNextRedPlayer(void);

	// Returns the 2nd next client in the ready queue.
	ReadyClient getNextBluePlayer(void);

	// Returns pointer to internal RakNet RakPeerInterface.
	RakNet::RakPeerInterface* getPeer(void);

	// Returns pointer to internal RakNet Packet.
	RakNet::Packet* getPacket(void);

	// Returns a string of the first set of data of the last packet (skipping
	// the first byte).
	const char* getPacketStrData(void) const;

	// Setters

	// --- //

	typedef struct{
		Uint32 lastProcessedInput;
		RakNet::Time timestamp;
		int x, y;
		int xVel, yVel;
		int xAccel, yAccel;
	} PlayerUpdate;

	// --- //

	static const int MaxClients = 10;

public:
	RakNet::RakPeerInterface* m_peer;
	RakNet::Packet* m_packet;
	ClientList m_clients;

	RakNet::SystemAddress m_redAddr, m_blueAddr;
	Uint32 m_redLastProcessedInput, m_blueLastProcessedInput;

	// The order in which players "ready up." The server process this as 
	// first come, first server; so first to ready up will play first. After
	// the game starts, they are removed from the queue and the next two play.
	// The std::string should specify the username.
	ReadyQueue m_readyQueue;

	// The timer which controls when player updates are sent to the clients.
	std::shared_ptr<Timer> m_pUpdateTimer;
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

	ReadyClient ready;
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

inline int Server::getClient(const std::string& username){
	for (unsigned int i = 0; i < m_clients.size(); ++i){
		if (username.compare(m_clients[i].username) == 0){
			return i;
		}
	}

	return -1;
}

inline ClientConnection Server::getClientPtr(const std::string& username){
	int n = this->getClient(username);
	return m_clients[n];
}

inline const int Server::getReadyQueueSize(void) const{
	return m_readyQueue.size();
}

inline ReadyClient Server::getReadyClient(const Uint32 n){
	int i = 0;
	for (ReadyQueue::iterator itr = m_readyQueue.begin();
		itr != m_readyQueue.end();
		++itr, ++i){
		if (i == n){
			return *itr;
		}
	}

	ReadyClient nil;
	nil.username = "nul";
	nil.fighter = -1;
	return nil;
}

inline ReadyClient Server::getNextRedPlayer(void){
	ReadyQueue::iterator itr = m_readyQueue.begin();
	return *itr;
}

inline ReadyClient Server::getNextBluePlayer(void){
	ReadyQueue::iterator itr = m_readyQueue.begin();
	++itr;
	return *itr;
}

inline RakNet::RakPeerInterface* Server::getPeer(void){
	return m_peer;
}

inline RakNet::Packet* Server::getPacket(void){
	return m_packet;
}

// Setters

// ================================================ //

#endif

// ================================================ //