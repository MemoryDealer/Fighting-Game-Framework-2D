// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: Client.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements Client singleton class.
// ================================================ //

#include "Client.hpp"
#include "Log.hpp"
#include "Engine.hpp"
#include "Packet.hpp"
#include "Timer.hpp"
#include "GameManager.hpp"

// ================================================ //

template<> Client* Singleton<Client>::msSingleton = nullptr;

// ================================================ //

Client::Client(const std::string& server, const int port) :
m_port(port),
m_sock(nullptr),
m_sendPacket(nullptr),
m_recvPacket(nullptr),
m_serverAddr(),
m_packetHandle(nullptr),
m_pLastResponse(new Timer()),
m_connected(false),
m_timeout(10000)
{
	Log::getSingletonPtr()->logMessage("Initializing Client...");

	m_sock = SDLNet_UDP_Open(0);
	if (!m_sock){
		throw std::exception(std::string("Failed to open UDP client socket on port " +
			Engine::toString(m_port)).c_str());
	}

	if (SDLNet_ResolveHost(&m_serverAddr, server.c_str(), m_port) == -1){
		throw std::exception(std::string("Failed to resolve host" + server).c_str());
	}

	m_sendPacket = SDLNet_AllocPacket(66560);
	m_recvPacket = SDLNet_AllocPacket(66560);

	// Send connection request to server.
	Packet data(Packet::CONNECT_REQUEST);
	data.setMessage(GameManager::getSingletonPtr()->getUsername());
	Packet::send(m_sendPacket, m_sock, m_serverAddr, data);

	m_pLastResponse->restart();

	Log::getSingletonPtr()->logMessage("Client intialized!");
}

// ================================================ //

Client::~Client(void)
{
	if (m_sock){
		SDLNet_UDP_Close(m_sock);
	}
	
	m_sendPacket->data = nullptr;
	m_recvPacket->data = nullptr;
	SDLNet_FreePacket(m_sendPacket);
	SDLNet_FreePacket(m_recvPacket);
}

// ================================================ //

int Client::disconnect(void)
{
	if (m_connected){
		Packet data(Packet::DISCONNECT);
		data.setMessage(GameManager::getSingletonPtr()->getUsername());

		return Packet::send(m_sendPacket, m_sock, m_serverAddr, data);
	}
	
	return 0;
}

// ================================================ //

int Client::chat(const std::string& msg)
{
	Packet data(Packet::CHAT);
	data.setMessage(msg);
	
	return Packet::send(m_sendPacket, m_sock, m_serverAddr, data);
}

// ================================================ //

int Client::update(double dt)
{
	// Process incoming packets.
	if (SDLNet_UDP_Recv(m_sock, m_recvPacket)){
		if (m_recvPacket->address.host == m_serverAddr.host &&
			m_recvPacket->address.port == m_serverAddr.port){

			Packet* data = reinterpret_cast<Packet*>(m_recvPacket->data);
			if (data->header == Packet::PROTOCOL_ID){
				switch (data->type){
				default:
					break;

				case Packet::CONNECT_ACCEPT:
					m_connected = true;
					break;

				case Packet::CHECK:
				{
					Packet data(Packet::ACK);
					Packet::send(m_sendPacket, m_sock, m_serverAddr, data);
					break;
				}
				}

				// Packet received from server, reset timeout timer.
				m_pLastResponse->restart();

				data->clone(m_packetHandle);
				return data->type;
			}
		}
	}
	else{
		if (m_pLastResponse->getTicks() > m_timeout){
			if (!m_connected){
				return Packet::CONNECT_FAILED;
			}
			else{
				m_connected = false;
				return Packet::CONNECTION_LOST;
			}
		}
	}

	return 0;
}

// ================================================ //