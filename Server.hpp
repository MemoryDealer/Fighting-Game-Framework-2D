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

// Handles all server-side operations.
class Server : public Singleton<Server>
{
public:
	// Opens a UDP socket on specified port. Allocates UDPPacket pointer
	// for sending/receiving packets.
	explicit Server(const int port = 666);

	// Closes the UDP socket and frees the UDPPacket.
	~Server(void);

	// Testing purposes.
	void testRecv(void);

private:
	Uint32		m_port;
	UDPsocket	m_sock;
	UDPpacket*	m_packet;
	bool		m_active;
};

// ================================================ //

#endif

// ================================================ //