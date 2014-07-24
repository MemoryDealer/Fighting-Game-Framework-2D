// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: Packet.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements Packet struct.
// ================================================ //

#include "Packet.hpp"

// ================================================ //

Packet::Packet(void) :
header(Packet::PROTOCOL_ID),
id(0),
type(Packet::NIL),
buf(),
bufLength(0)
{
	static Uint32 idctr = 0;

	id = idctr++;
}

// ================================================ //