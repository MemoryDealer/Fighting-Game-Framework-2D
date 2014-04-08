// ================================================ //

#include "Server.hpp"
#include "Engine.hpp"

// ================================================ //

template<> Server* Singleton<Server>::msSingleton = nullptr;

// ================================================ //

Server::Server(void)
	:	m_port(666),
		m_sock(nullptr)
{
	m_sock = SDLNet_UDP_Open(m_port);
	if(!m_sock){
		throw std::exception("Failed to open UDP server socket");
	}

	m_packet = SDLNet_AllocPacket(10240); // 10 KB
}

// ================================================ //

Server::~Server(void)
{
	if(m_sock){
		SDLNet_UDP_Close(m_sock);
	}

	SDLNet_FreePacket(m_packet);
}

// ================================================ //

void Server::testRecv(void)
{
	if(SDLNet_UDP_Recv(m_sock, m_packet)){
		printf("UDP Packet incoming\n");
		printf("\tChan:    %d\n", m_packet->channel);
		printf("\tData:    %s\n", (char*)m_packet->data);
		printf("\tLen:     %d\n", m_packet->len);
		printf("\tMaxlen:  %d\n", m_packet->maxlen);
		printf("\tStatus:  %d\n", m_packet->status);
		printf("\tAddress: %x %x\n", m_packet->address.host, m_packet->address.port);
	}
	else{
		printf("No incoming UDP packet.\n");
	}
}

// ================================================ //