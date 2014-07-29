// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: Packet.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines Packet struct.
// ================================================ //

#ifndef __PACKET_HPP__
#define __PACKET_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

struct Packet{
public:
	// Initializes header and id.
	explicit Packet(void);

	// Copies str to msg.
	void setMessage(const std::string& str);

	// A packet header allows the program the confirm a packet is sent
	// from another client running Extreme Metal Fighter.
	Uint32 header;
	Uint32 id;
	Uint32 type;

	union{
		char message[256];
		int whatever;
	};
	
	enum Type{
		// Client packet types.

		NIL = 0,
		CONNECT_REQUEST,
		DISCONNECT,
		CHAT,

		// Server packet types.

		CONNECT_ACCEPT
	};

	// A helper function that sends a packet.
	static int send(UDPpacket* packet, UDPsocket& sock, const IPaddress& addr, Packet& data);

	static const Uint32 PROTOCOL_ID;
};

// ================================================ //

inline void Packet::setMessage(const std::string& str){
	strncpy(message, str.c_str(), str.length());
}

// ================================================ //

#endif

// ================================================ //