// ================================================ //

#include "PlayerManager.hpp"
#include "Config.hpp"

// ================================================ //

template<> PlayerManager* Singleton<PlayerManager>::msSingleton = 0;

// ================================================ //

PlayerManager::PlayerManager(unsigned int redFighter, unsigned int blueFighter)
	:	m_pRedPlayer(new Player(redFighter)),
		m_pBluePlayer(new Player(blueFighter))
{
	
}

// ================================================ //

PlayerManager::~PlayerManager(void)
{
	 
}

// ================================================ //