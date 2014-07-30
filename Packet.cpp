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
message()
{
	static Uint32 idctr = 0;

	id = idctr++;
}

// ================================================ //

int Packet::send(UDPpacket* packet, UDPsocket& sock, const IPaddress& addr, Packet& data)
{
	packet->address = addr;
	packet->data = reinterpret_cast<Uint8*>(&data);
	packet->len = sizeof(Packet)+1;

	int ret = SDLNet_UDP_Send(sock, -1, packet);

	return ret;
}

// ================================================ //