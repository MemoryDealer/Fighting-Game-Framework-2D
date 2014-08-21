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

	// Sends a connect request to server.
	int connect(void);

	// Sends disconnect message to server if connected, returns 0 if not.
	int disconnect(void);

	// Sends a chat message to server.
	int chat(const std::string& msg);

	// Sends needed data to server.
	int update(double dt);

	// Setters

private:
	RakNet::RakPeerInterface* m_peer;
	RakNet::Packet* m_packet;
	RakNet::SystemAddress m_serverAddr;
	std::string m_server;
	unsigned short m_port;
	bool m_connected;
	int m_timeout;
};

// ================================================ //

#endif

// ================================================ //