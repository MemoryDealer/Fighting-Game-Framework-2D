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

	// Update each player
	m_pRedPlayer->update(dt);
	m_pBluePlayer->update(dt);

	for(int i=0; i<m_pRedPlayer->getNumberOfHitboxes(); ++i){
		for(int j=0; j<m_pBluePlayer->getNumberOfHitboxes(); ++j){
			if((m_pRedPlayer->getHitbox(i).intersects(m_pBluePlayer->getHitbox(j)))){
				printf("INTERSECTION!!!!!!!!!!!!!!\t%d && %d\n", i, j);
				m_pRedPlayer->setColliding();
			}
		}
	}

	/*printf("(%d,%d,%d,%d) => (%d,%d,%d,%d)\n",
		m_pRedPlayer->getHitbox(3).getRect().x,
		m_pRedPlayer->getHitbox(3).getRect().y,
		m_pRedPlayer->getHitbox(3).getRect().w,
		m_pRedPlayer->getHitbox(3).getRect().h,
		m_pBluePlayer->getHitbox(2).getRect().x,
		m_pBluePlayer->getHitbox(2).getRect().y,
		m_pBluePlayer->getHitbox(2).getRect().w,
		m_pBluePlayer->getHitbox(2).getRect().h);
	if(m_pRedPlayer->getHitbox(0).intersects(m_pBluePlayer->getHitbox(1))){
		printf("INTERSECTION!!!!!!!!!!!!!!\n");
	}*/
}

// ================================================ //