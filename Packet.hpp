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
	Uint32 header;
	int id;
	int type;

	char buf[512];
	
	enum Type{
		// Client packet types.
		CONNECT_REQUEST = 0,
		DISCONNECT,
		CHAT,

		// Server packet types.
		CONNECT_ACCEPT
	};

	static Uint32 PROTOCOL_ID;
};

// ================================================ //

#endif

// ================================================ //