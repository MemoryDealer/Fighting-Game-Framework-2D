// ================================================ //

#include "PlayerManager.hpp"

// ================================================ //

template<> PlayerManager* Singleton<PlayerManager>::msSingleton = 0;

// ================================================ //

PlayerManager::PlayerManager(const char* redTexture, const char* blueTexture)
	:	m_pRedPlayer(new Player(redTexture)),
		m_pBluePlayer(new Player(blueTexture))
{

}

// ================================================ //

PlayerManager::~PlayerManager(void)
{
	 
}

// ================================================ //