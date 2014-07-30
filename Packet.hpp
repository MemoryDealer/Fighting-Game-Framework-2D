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

	enum Type{
		// Client packet types.

		NIL = 0,
		CONNECT_REQUEST,
		DISCONNECT,
		CHAT,

		// Server packet types.

		CONNECT_ACCEPT
	};

	// Copies str to msg.
	void setMessage(const std::string& str);

	// Clones the current Packet to parameter clone.
	void clone(Packet* clone);

	// A packet header allows the program the confirm a packet is sent
	// from another client running Extreme Metal Fighter.
	Uint32 header;
	Uint32 id;
	Uint32 type;

	union{
		char message[256];
		int whatever;
	};
	
	// --- //

	// A helper function that sends a packet.
	static int send(UDPpacket* packet, UDPsocket& sock, const IPaddress& addr, Packet& data);

	// A helper function that sends a packet.
	static int send(UDPpacket* packet, UDPsocket& sock, const IPaddress& addr, Packet* data);

	static const Uint32 PROTOCOL_ID; // TODO: does this take up memory in an allocated Packet?
};

// ================================================ //

inline void Packet::setMessage(const std::string& str){
	strncpy(message, str.c_str(), str.length());
}

inline void Packet::clone(Packet* clone){
	// Copy union by copying largest member.
	memcpy(clone->message, this->message, sizeof(this->message));
	clone->header = this->header;
	clone->id = this->id;
	clone->type = this->type;
}

// ================================================ //

#endif

// ================================================ //