// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: Client.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines Client singleton class.
// ================================================ //

#ifndef __CLIENT_HPP__
#define __CLIENT_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

class Timer;

// ================================================ //

// Handles all client-side operations.
class Client : public Singleton<Client>
{
public:
	// Allocates socket and server IP.
	explicit Client(const std::string& server, const int port);

	// Empty destructor.
	~Client(void);

	// Send-to-server functions.

	// Sends a packet to the server using a BitStream.
	Uint32 send(const RakNet::BitStream& bit, const PacketPriority priority = HIGH_PRIORITY,
		const PacketReliability reliability = UNRELIABLE);

	// Sends a connect request to server.
	Uint32 connect(void);

	// Sends disconnect message to server if connected, returns 0 if not.
	void disconnect(void);

	// Sends a chat message to server.
	Uint32 chat(const std::string& msg);

	// Sends a READY packet to server.
	Uint32 ready(const Uint32 fighter);

	// Sends an input value to the server.
	Uint32 sendInput(const Uint32 input, const bool value);

	// Sends needed data to server.
	int update(double dt);

	// Getters

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

private:
	RakNet::RakPeerInterface* m_peer;
	RakNet::Packet* m_packet;
	RakNet::SystemAddress m_serverAddr;
	std::string m_server;
	unsigned short m_port;
	std::string m_buffer;
	bool m_connected;
	int m_timeout;
};

// ================================================ //

// Getters

inline RakNet::Packet* Client::getLastPacket(void) const{
	return m_packet;
}

inline std::string Client::getBuffer(void) const{
	return m_buffer;
}

// ================================================ //

#endif

// ================================================ //