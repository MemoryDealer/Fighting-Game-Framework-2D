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
#include "MUDP.hpp"

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

	// Sets the handle for packet data to be copied to so game states can access it.
	void setPacketHandle(MUDP::Packet* handle);

private:
	std::shared_ptr<MUDP::Socket> m_pSD;
	MUDP::IP m_serverAddress;
	MUDP::Packet* m_packet;
	// Time since last packet received from server.
	std::shared_ptr<Timer> m_pLastResponse;
	bool m_connected;
	int m_timeout;
};

// ================================================ //

inline void Client::setPacketHandle(MUDP::Packet* handle){
	m_packet = handle;
}

// ================================================ //

#endif

// ================================================ //