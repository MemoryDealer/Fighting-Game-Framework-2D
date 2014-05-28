// ================================================ //

#include "PlayerManager.hpp"
#include "StageManager.hpp"
#include "PlayerData.hpp"
#include "Config.hpp"
#include "Input.hpp"
#include "Engine.hpp"

// ================================================ //

template<> PlayerManager* Singleton<PlayerManager>::msSingleton = nullptr;

// ================================================ //

PlayerManager::PlayerManager(void)
	:	m_pRedPlayer(nullptr),
		m_pBluePlayer(nullptr),
		m_redFighterFile(),
		m_blueFighterFile(),
		m_fighters()
{
	Log::getSingletonPtr()->logMessage("Initializing PlayerManager...");

	Config c("Data/Fighters/fighters.cfg");
	const int numFighters = c.parseIntValue("core", "numFighters");

	for(int i=1; i<=numFighters; ++i){
		FighterEntry fighter;
		std::string fighterName = "fighter" + Engine::toString(i);

		fighter.name = c.parseValue(fighterName.c_str(), "name");
		fighter.file = c.parseValue(fighterName.c_str(), "file");

		// portrait...

		m_fighters.push_back(fighter);

		Log::getSingletonPtr()->logMessage("Fighter entry loaded => Name: " + fighter.name + "\tFile: " + fighter.file);
	}
}

// ================================================ //

PlayerManager::~PlayerManager(void)
{
	 
}

// ================================================ //

bool PlayerManager::load(const std::string& redFighterFile, const std::string& blueFighterFile)
{
	// Store fighter file names in PlayerManager
	m_redFighterFile.assign(redFighterFile);
	m_blueFighterFile.assign(blueFighterFile);

	m_pRedPlayer.reset(new Player(redFighterFile));
	m_pBluePlayer.reset(new Player(blueFighterFile));

	m_pRedPlayer->setSide(PlayerSide::LEFT);
	m_pBluePlayer->setSide(PlayerSide::RIGHT);

	Config game("Data/Config/game.cfg");

	// Should be dependent on Stage data and fighter height (TODO: query Stage singleton)
	m_pRedPlayer->setPosition(game.parseIntValue("game", "redX"), m_pRedPlayer->getPosition().y);
	m_pBluePlayer->setPosition(game.parseIntValue("game", "blueX"), m_pBluePlayer->getPosition().y);

	return( (m_pRedPlayer.get() != nullptr) && (m_pBluePlayer.get() != nullptr) );
}

// ================================================ //

bool PlayerManager::reload(void)
{
	return this->load(m_redFighterFile, m_blueFighterFile);
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