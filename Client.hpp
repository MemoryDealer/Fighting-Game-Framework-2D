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
struct Packet;

// ================================================ //

// Handles all client-side operations.
class Client : public Singleton<Client>
{
public:
	// Opens a UDP socket and sends connection request to server.
	explicit Client(const std::string& server, const int port);

	// Closes the socket and frees the packet buffer.
	~Client(void);

	// Send-to-server functions.

	// Sends disconnect message to server if connected, returns 0 if not.
	int disconnect(void);

	// Sends a chat message to server.
	int chat(const std::string& msg);

	// Sends needed data to server.
	int update(double dt);

	// Setters

	// Sets the handle for packet data to be copied to so game states can access it.
	void setPacketHandle(Packet* handle);

private:
	int	m_port;
	UDPsocket m_sock;
	UDPpacket* m_sendPacket;
	UDPpacket* m_recvPacket;
	IPaddress m_serverAddr;
	Packet* m_packetHandle;
	// Time since last packet received from server.
	std::shared_ptr<Timer> m_pLastResponse;
	bool m_connected;
	int m_timeout;
};

// ================================================ //

inline void Client::setPacketHandle(Packet* handle){
	m_packetHandle = handle;
}

// ================================================ //

#endif

// ================================================ //