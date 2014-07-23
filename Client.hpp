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

// Handles all client-side operations.
class Client : public Singleton<Client>
{
public:
	// Opens a UDP socket and sends connection request to server.
	explicit Client(const std::string& server, const int port);

	// Closes the socket and frees the packet buffer.
	~Client(void);

	// Sends needed data to server.
	void update(double dt);

private:
	int	m_port;
	UDPsocket m_sock;
	UDPpacket* m_packet;
	IPaddress m_serverAddr;
};

// ================================================ //

#endif

// ================================================ //