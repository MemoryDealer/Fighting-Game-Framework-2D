// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: MUDP.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines MUDP namespace; Socket class.
// ================================================ //

#ifndef __MUDP_HPP__
#define __MUDP_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

// Metal UDP.
namespace MUDP{

	// ================================================ //

	struct Packet;
	class IP;

	// ================================================ //

	// Processes all sending and receiving on a UDP socket.
	class Socket
	{
	public:
		// Opens a UDP socket on specified port. Allocates UDPPacket pointer
		// for sending/receiving packets.
		explicit Socket(const int port);

		// Closes the UDP socket and frees the UDPPacket.
		~Socket(void);

		// Sends a packet to specified address with data in the Packet struct.
		int send(Packet* packet, IP& dst);

		// Checks for incoming packets and copies the packet data into packet handle
		// if data is received. Returns packet type if received or -1 if nothing.
		int recv(Packet* packet, IP& src);

	private:
		UDPsocket m_sock;
		UDPpacket* m_sendBuffer;
		UDPpacket* m_recvBuffer;
	};

	// ================================================ //
	// ================================================ //

	// Represents and IP address.
	class IP
	{
	public:
		// Calls resolveHostname().
		explicit IP(const std::string& hostname, const int port);

		// Empty constructor.
		explicit IP(void);

		// Empty destructor.
		~IP(void);

		// Returns internal IPaddress for SDLNet operations.
		IPaddress getAddress(void) const;

		// Sets internal IPaddress.
		void setAddress(const IPaddress& address);

		// Converts hostname to IP address.
		bool resolveHostname(const std::string& hostname, const int port);

		// Assigns other to 
		IP operator=(const IP& other);
		bool operator==(const IP& other) const;

	private:
		IPaddress m_address;
	};

	// ================================================ //

	inline IPaddress IP::getAddress(void) const{
		return m_address;
	}

	inline void IP::setAddress(const IPaddress& address){
		m_address = address;
	}

	inline IP IP::operator=(const IP& other){
		if (this == &other){
			return *this;
		}

		//m_address = other.m_address;
		this->setAddress(other.getAddress());
		return *this;
	}

	inline bool IP::operator==(const IP& other) const{
		return (other.m_address.host == m_address.host &&
			other.m_address.port == m_address.port);
	}

	// ================================================ //
	// ================================================ //

	// Holds data sent in UDP packet.
	struct Packet{
	public:
		// Initializes header and id.
		explicit Packet(int type = 0);

		enum Type{
			// Client packet types.

			NIL = 0,
			CONNECT_REQUEST,
			CONNECT_FAILED,
			CONNECTION_LOST,
			DISCONNECT,
			CHAT,
			ACK,

			// Server packet types.

			CONNECT_ACCEPT,
			CHECK
		};

		// Copies str to msg.
		void setMessage(const std::string& str);

		// Clones the current Packet to the parameter clone.
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

		static const Uint32 PROTOCOL_ID; // TODO: does this take up memory in an allocated Packet?
	};

	// ================================================ //

	inline void Packet::setMessage(const std::string& str){
		strcpy(message, "");
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

}

// ================================================ //

#endif

// ================================================ //