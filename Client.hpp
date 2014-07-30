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

	// Sends a chat message to server.
	int chat(const std::string& msg);

	// Sends needed data to server.
	Packet* update(double dt);

private:
	int	m_port;
	UDPsocket m_sock;
	UDPpacket* m_sendPacket;
	UDPpacket* m_recvPacket;
	IPaddress m_serverAddr;
	// Time since last packet received from server.
	std::shared_ptr<Timer> m_pLastResponse;
	bool m_connected;
	int m_timeout;
};

// ================================================ //

#endif

// ================================================ //