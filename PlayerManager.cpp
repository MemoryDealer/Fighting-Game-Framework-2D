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
	Log::getSingletonPtr()->logMessage("Initializing PlayerManager...");

	m_pRedPlayer->setSide(PlayerSide::LEFT);
	m_pBluePlayer->setSide(PlayerSide::RIGHT);

	Config game("Data/Config/game.cfg");

	// Should be dependent on Stage data and fighter height (TODO: query Stage singleton)
	m_pRedPlayer->setPosition(game.parseIntValue("game", "redX"), m_pRedPlayer->getPosition().y);
	m_pBluePlayer->setPosition(game.parseIntValue("game", "blueX"), m_pBluePlayer->getPosition().y);
}

// ================================================ //

PlayerManager::~PlayerManager(void)
{
	 
}

// ================================================ //

void PlayerManager::update(double dt)
{
	// Check for K.O.
	// ...

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

	// Test hitbox collisions
	// Damage boxes to opponent hitbox
	for(int i=Player::DBOX1; i<=Player::DBOX2; ++i){
		for(int j=Player::HBOX_LOWER; j<=Player::HBOX_HEAD; ++j){
			if(m_pRedPlayer->getHitbox(i).intersects(m_pBluePlayer->getHitbox(j))){
				printf("DAMAGE!!!!!!\n");
			}
		}
	}

	// Normal hitbox collision
	for(int i=0; i<4; ++i){
		for(int j=0; j<4; ++j){
			if((m_pRedPlayer->getHitbox(i).intersects(m_pBluePlayer->getHitbox(j)))){
				m_pRedPlayer->setColliding();
				m_pBluePlayer->setColliding();
			}
		}
	}

	// Update each player
	m_pRedPlayer->update(dt);
	m_pBluePlayer->update(dt);
}

// ================================================ //