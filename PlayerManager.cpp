// ================================================ //

#include "PlayerManager.hpp"
#include "StageManager.hpp"
#include "PlayerData.hpp"
#include "Camera.hpp"
#include "Hitbox.hpp"
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
		m_redMax(0),
		m_blueMax(0),
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

	// Free any previously allocated pointers and allocate new ones
	m_pRedPlayer.reset(new Player(redFighterFile));
	m_pBluePlayer.reset(new Player(blueFighterFile));

	// Set default starting sides and positions
	m_pRedPlayer->setSide(PlayerSide::LEFT);
	m_pBluePlayer->setSide(PlayerSide::RIGHT);
	const int startingOffset = 40;
	m_pRedPlayer->setPosition(startingOffset, m_pRedPlayer->getPosition().y);
	m_pBluePlayer->setPosition(Engine::getSingletonPtr()->getLogicalWindowWidth() - m_pBluePlayer->getPosition().w - startingOffset, 
		m_pBluePlayer->getPosition().y);

	// Calculate the far right edge at which player movement should stop or move the camera
	m_redMax = Engine::getSingletonPtr()->getLogicalWindowWidth() - m_pRedPlayer->getPosition().w;
	m_blueMax = Engine::getSingletonPtr()->getLogicalWindowWidth() - m_pBluePlayer->getPosition().w;

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
	// Update each player
	m_pRedPlayer->update(dt);
	m_pBluePlayer->update(dt);

	// Clear camera movement
	Camera::getSingletonPtr()->clear();

	// Check for K.O.
	// ...

	SDL_Rect red, blue;
	red = m_pRedPlayer->getPosition();
	blue = m_pBluePlayer->getPosition();
	const int redState = m_pRedPlayer->getCurrentState();
	const int blueState = m_pBluePlayer->getCurrentState();

	// Red player checks
	if (m_pRedPlayer->getSide() == PlayerSide::LEFT){
		// Test for stage edge and camera movement
		if (red.x < 0){
			if (redState == PlayerState::WALKING_BACK ||
				m_pRedPlayer->isColliding()){
				m_pRedPlayer->setPosition(0, red.y);
				// Check if blue player is not at the right edge
				if (blue.x < m_blueMax){
					// Move the camera
					Camera::getSingletonPtr()->moveX = -static_cast<int>(std::abs(m_pRedPlayer->getVelocityX()) * dt * 0.25);

					// Make the blue player "stand still" with camera movement (this feels like a shitty hack)
					m_pBluePlayer->setPosition(blue.x - Camera::getSingletonPtr()->moveX * 2, blue.y);
				}
			}
		}

		// Switch player sides if necessary
		if (red.x > (blue.x + (blue.w / 2))){
			m_pRedPlayer->setSide(PlayerSide::RIGHT);
			m_pBluePlayer->setSide(PlayerSide::LEFT);
		}
	}
	else{
		if (blue.x > (red.x + (red.w / 2))){
			m_pRedPlayer->setSide(PlayerSide::LEFT);
			m_pBluePlayer->setSide(PlayerSide::RIGHT);
		}
	}

	// Blue player checks
	if (m_pBluePlayer->getSide() == PlayerSide::LEFT){
		if (blue.x < 0){

		}		
	}
	else{
		if (blue.x > m_blueMax){
			if (blueState == PlayerState::WALKING_BACK ||
				m_pBluePlayer->isColliding()){
				Camera::getSingletonPtr()->moveX = 1;
				m_pBluePlayer->setPosition(m_blueMax, blue.y);
			}
		}
	}

	// Test hitbox collisions
	// Damage boxes to opponent hitbox
	for(int i=Player::DBOX1; i<=Player::DBOX2; ++i){
		for(int j=Player::HBOX_LOWER; j<=Player::HBOX_HEAD; ++j){
			if (m_pRedPlayer->getHitbox(i).intersects(m_pBluePlayer->getHitbox(j))){
				printf("DAMAGE!!!!!!\n");
			}
		}
	}

	// Reset collisions before testing
	m_pRedPlayer->setColliding(false);
	m_pBluePlayer->setColliding(false);

	// Normal hitbox collision
	for(int i=0; i<4; ++i){
		for(int j=0; j<4; ++j){
			if ((m_pRedPlayer->getHitbox(i).intersects(m_pBluePlayer->getHitbox(j)))){
				m_pRedPlayer->setColliding(true);
				m_pBluePlayer->setColliding(true);
			}
		}
	}
}

// ================================================ //