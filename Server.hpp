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
	Packet* update(double dt);

private:
	Uint32 m_port;
	UDPsocket m_sock;
	UDPpacket* m_packet;
	ClientList m_clients;
};

// ================================================ //

struct ClientConnection{
	IPaddress addr;
	std::string username;
	Uint32 channel;
	std::shared_ptr<Timer> timer;
};

// ================================================ //

#endif

// ================================================ //