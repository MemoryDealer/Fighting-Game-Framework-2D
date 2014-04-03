// ================================================ //

#include "PlayerManager.hpp"
#include "PlayerData.hpp"
#include "Config.hpp"
#include "Input.hpp"

// ================================================ //

template<> PlayerManager* Singleton<PlayerManager>::msSingleton = 0;

// ================================================ //

PlayerManager::PlayerManager(unsigned int redFighter, unsigned int blueFighter)
	:	m_pRedPlayer(new Player(redFighter)),
		m_pBluePlayer(new Player(blueFighter))
{
	m_pRedPlayer->setSide(PlayerSide::LEFT);
	m_pBluePlayer->setSide(PlayerSide::RIGHT);

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
	// Process input for each player
	if(redInput != Input::NONE)
		m_pRedPlayer->processInput(redInput);
	if(blueInput != Input::NONE)
		m_pBluePlayer->processInput(blueInput);

	// Switch player sides if necessary
	SDL_Rect red, blue;
	red = m_pRedPlayer->getPosition();
	blue = m_pBluePlayer->getPosition();

	if(m_pRedPlayer->getSide() == PlayerSide::LEFT){
		if(red.x > (blue.x + (blue.w / 2))){
			m_pRedPlayer->setSide(PlayerSide::RIGHT);
			m_pBluePlayer->setSide(PlayerSide::LEFT);
		}
	}
	else{
		if(blue.x > (red.x + (red.w / 2))){
			m_pRedPlayer->setSide(PlayerSide::LEFT);
			m_pBluePlayer->setSide(PlayerSide::RIGHT);
		}
	}

	// Update each player
	m_pRedPlayer->update(dt);
	m_pBluePlayer->update(dt);
}

// ================================================ //