// ================================================ //

#ifndef __SERVER_HPP__
#define __SERVER_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

class Server : public Singleton<Server>
{
public:
	explicit Server(void);
	~Server(void);

	void testRecv(void);

private:
	Uint32		m_port;
	UDPsocket	m_sock;
	UDPpacket*	m_packet;
	bool		m_active;
};

// ================================================ //

#endif

// ================================================ //