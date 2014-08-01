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
#include "Timer.hpp"
#include "GameManager.hpp"

// ================================================ //

template<> Client* Singleton<Client>::msSingleton = nullptr;

// ================================================ //

Client::Client(const std::string& server, const int port) :
m_pSD(new MUDP::Socket(0)),
m_serverAddress(server, port),
m_packet(nullptr),
m_pLastResponse(new Timer()),
m_connected(false),
m_timeout(10000)
{
	Log::getSingletonPtr()->logMessage("Initializing Client...");

	Log::getSingletonPtr()->logMessage("Client intialized!");
}

// ================================================ //

Client::~Client(void)
{
	
}

// ================================================ //

int Client::connect(void)
{
	if (!m_connected){
		// Send connection request to server.
		m_packet->type = MUDP::Packet::CONNECT_REQUEST;
		m_packet->setMessage(GameManager::getSingletonPtr()->getUsername());
		m_pSD->send(m_packet, m_serverAddress);

		m_pLastResponse->restart();
	}

	return 0;
}

// ================================================ //

int Client::disconnect(void)
{
	if (m_connected){
		m_packet->type = MUDP::Packet::DISCONNECT;
		m_packet->setMessage(GameManager::getSingletonPtr()->getUsername());

		return m_pSD->send(m_packet, m_serverAddress);
	}
	
	return 0;
}

// ================================================ //

int Client::chat(const std::string& msg)
{
	m_packet->type = MUDP::Packet::CHAT;
	m_packet->setMessage(msg);
	
	return m_pSD->send(m_packet, m_serverAddress);
}

// ================================================ //

int Client::update(double dt)
{
	// Process incoming packets.
	MUDP::IP source;
	if (m_pSD->recv(m_packet, source)){
		if (source == m_serverAddress){
			switch (m_packet->type){
			default:
				break;

			case MUDP::Packet::CONNECT_ACCEPT:
				m_connected = true;
				break;

			case MUDP::Packet::CHECK:
				
				break;
			}

			/*m_packet->type = MUDP::Packet::ACK;
			m_pSD->send(m_packet, m_serverAddress);*/

			m_pLastResponse->restart();

			return m_packet->type;
		}
	}
	
	// No response from server, check timeout.
	/*if (m_pLastResponse->getTicks() > m_timeout){
		if (!m_connected){
			return MUDP::Packet::CONNECT_FAILED;
		}
		else{
			m_connected = false;
			return MUDP::Packet::CONNECTION_LOST;
		}
	}*/

	return 0;
}

// ================================================ //