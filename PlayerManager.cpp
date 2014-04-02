// ================================================ //

#include "PlayerManager.hpp"
#include "Config.hpp"
#include "Input.hpp"

// ================================================ //

template<> PlayerManager* Singleton<PlayerManager>::msSingleton = 0;

// ================================================ //

PlayerManager::PlayerManager(unsigned int redFighter, unsigned int blueFighter)
	:	m_pRedPlayer(new Player(redFighter)),
		m_pBluePlayer(new Player(blueFighter))
{
	Config game("Data/Config/game.cfg");

	m_pRedPlayer->setPosition(game.parseIntValue("game", "redX"), m_pRedPlayer->getPosition().y);
	m_pBluePlayer->setPosition(game.parseIntValue("game", "blueX"), m_pBluePlayer->getPosition().y);
}

// ================================================ //

PlayerManager::~PlayerManager(void)
{
	 
}

// ================================================ //

void PlayerManager::update(double dt, const int redInput, const int blueInput)
{
	if(redInput != Input::EPSILON)
		m_pRedPlayer->processInput(redInput);
	if(blueInput != Input::EPSILON)
		m_pBluePlayer->processInput(blueInput);

	m_pRedPlayer->update(dt);
	m_pBluePlayer->update(dt);
}

// ================================================ //