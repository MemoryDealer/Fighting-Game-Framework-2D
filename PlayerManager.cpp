// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: PlayerManager.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements PlayerManager singleton class.
// ================================================ //

#include "PlayerManager.hpp"
#include "StageManager.hpp"
#include "Stage.hpp"
#include "Hitbox.hpp"
#include "Config.hpp"
#include "Input.hpp"
#include "Engine.hpp"
#include "GamepadManager.hpp"
#include "Game.hpp"
#include "Move.hpp"
#include "Camera.hpp"

// ================================================ //

template<> PlayerManager* Singleton<PlayerManager>::msSingleton = nullptr;

// ================================================ //

PlayerManager::PlayerManager(void) :	
m_pRedPlayer(nullptr),
m_pBluePlayer(nullptr),
m_redFighter(0),
m_blueFighter(0),
m_redMax(0),
m_blueMax(0),
m_fighters()
{
	Log::getSingletonPtr()->logMessage("Initializing PlayerManager...");

	Config c(Engine::getSingletonPtr()->getDataDirectory() + "/Fighters/fighters.cfg");
	const int numFighters = c.parseIntValue("core", "numFighters");

	for(int i=1; i<=numFighters; ++i){
		FighterEntry fighter;
		std::string fighterName = "fighter" + Engine::toString(i);

		fighter.name = c.parseValue(fighterName.c_str(), "name", true);
		fighter.file = c.parseValue(fighterName.c_str(), "file", true);

		// TODO: load portrait texture.

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
	Config c(Engine::getSingletonPtr()->getSettingsFile());

	// Free any previously allocated Players and allocate new ones.
	m_pRedPlayer.reset(new Player(redFighterFile, 
		Engine::getSingletonPtr()->getDataDirectory() + "/" + c.parseValue("controls", "red")));
	m_pBluePlayer.reset(new Player(blueFighterFile, 
		Engine::getSingletonPtr()->getDataDirectory() + "/" + c.parseValue("controls", "blue")));

	// Set default player gamepads.
	if (GamepadManager::getSingletonPtr()->getPad(1) == nullptr){
		m_pRedPlayer->getInput()->setPad(GamepadManager::getSingletonPtr()->getPad(0));
		m_pBluePlayer->getInput()->setPad(nullptr);
	}
	else{
		m_pRedPlayer->getInput()->setPad(GamepadManager::getSingletonPtr()->getPad(1));
		m_pBluePlayer->getInput()->setPad(GamepadManager::getSingletonPtr()->getPad(0));
	}

	// Set default starting sides and positions.
	m_pRedPlayer->setSide(Player::Side::LEFT);
	m_pBluePlayer->setSide(Player::Side::RIGHT);

	// startingOffset is the virtual pixel width each player starts from the edge of the viewport.
	const int startingOffset = 40;
	m_pRedPlayer->setPosition(startingOffset, m_pRedPlayer->getPosition().y);
	m_pBluePlayer->setPosition(Engine::getSingletonPtr()->getLogicalWindowWidth() - m_pBluePlayer->getPosition().w - startingOffset, 
		m_pBluePlayer->getPosition().y);

	return (m_pRedPlayer.get() != nullptr) && (m_pBluePlayer.get() != nullptr);
}

// ================================================ //

bool PlayerManager::load(const Uint32 redFighter, const Uint32 blueFighter)
{
	Log::getSingletonPtr()->logMessage("Loading fighter files from \"" +
		Engine::getSingletonPtr()->getDataDirectory() + "/Fighters\"");
	bool ret = this->load(Engine::getSingletonPtr()->getDataDirectory() + 
		"/Fighters/" + m_fighters[redFighter].file, 
		Engine::getSingletonPtr()->getDataDirectory() + 
		"/Fighters/" + m_fighters[blueFighter].file);
	if (ret){
		Log::getSingletonPtr()->logMessage("Fighters loaded!");
	}
	else{
		Log::getSingletonPtr()->logMessage("ERROR: Failed to load fighters");
	}

	m_redFighter = redFighter;
	m_blueFighter = blueFighter;

	return ret;
}

// ================================================ //

bool PlayerManager::reload(void)
{
	return this->load(m_redFighter, m_blueFighter);
}

// ================================================ //

bool PlayerManager::reset(void)
{
	Config c(Engine::getSingletonPtr()->getSettingsFile());

	if (c.isLoaded()){
		m_pRedPlayer.reset(new Player("", Engine::getSingletonPtr()->getDataDirectory() + 
			"/" + c.parseValue("controls", "red")));
		m_pBluePlayer.reset(new Player("", Engine::getSingletonPtr()->getDataDirectory() + 
			"/" + c.parseValue("controls", "blue")));

		// Set default player gamepads.
		if (GamepadManager::getSingletonPtr()->getPad(1) == nullptr){
			m_pRedPlayer->getInput()->setPad(GamepadManager::getSingletonPtr()->getPad(0));
			m_pBluePlayer->getInput()->setPad(nullptr);
		}
		else{
			m_pRedPlayer->getInput()->setPad(GamepadManager::getSingletonPtr()->getPad(1));
			m_pBluePlayer->getInput()->setPad(GamepadManager::getSingletonPtr()->getPad(0));
		}

		return true;
	}

	return false;
}

// ================================================ //

void PlayerManager::update(double dt)
{
	// Store red and blue x values for calculating distance moved.
	const int redOldX = m_pRedPlayer->getPosition().x;
	const int blueOldX = m_pBluePlayer->getPosition().x;

	// Perform game mode specific operations.
	switch (Game::getSingletonPtr()->getMode()){
	default:
		break;

	// Perform server-side calculations.
	case Game::SERVER:
	case Game::LOCAL:
		m_pRedPlayer->update(dt);
		m_pBluePlayer->update(dt);

		// Test hitbox collisions (this is predicted on the client).
		for (int i = Hitbox::DBOX1; i <= Hitbox::DBOX2; ++i){
			for (int j = Hitbox::HBOX_LOWER; j <= Hitbox::HBOX_HEAD; ++j){
				if (m_pRedPlayer->getHitbox(i)->intersects(m_pBluePlayer->getHitbox(j))){
					if (m_pRedPlayer->hitboxesActive()){
						m_pRedPlayer->setHitboxesActive(false);
						Move* pMove = m_pRedPlayer->getCurrentMove();
						bool hit = m_pBluePlayer->takeHit(pMove);

						if (Game::getSingletonPtr()->getMode() == Game::SERVER){
							// Send damage notification to client.
							if (hit){
								Server::getSingletonPtr()->broadcastHit(Game::Playing::PLAYING_BLUE,
																		pMove->damage, pMove->hitstun);
							}
							else{
								Server::getSingletonPtr()->broadcastHitBlock(Game::Playing::PLAYING_BLUE,
																			 pMove->blockstun);
							}
						}
					}
				}
				if (m_pBluePlayer->getHitbox(i)->intersects(m_pRedPlayer->getHitbox(j))){
					if (m_pBluePlayer->hitboxesActive()){
						m_pBluePlayer->setHitboxesActive(false);
						Move* pMove = m_pBluePlayer->getCurrentMove();
						bool hit = m_pRedPlayer->takeHit(pMove);

						if (Game::getSingletonPtr()->getMode() == Game::SERVER){
							if (hit){
								Server::getSingletonPtr()->broadcastHit(Game::Playing::PLAYING_RED,
																		pMove->damage, pMove->hitstun);
							}
							else{
								Server::getSingletonPtr()->broadcastHitBlock(Game::Playing::PLAYING_RED,
																			 pMove->blockstun);
							}
						}
					}
				}
			}
		}
		break;

	case Game::CLIENT:
		if (Game::getSingletonPtr()->getPlaying() == Game::PLAYING_RED){
			m_pRedPlayer->update(dt);
			m_pRedPlayer->serverReconciliation();			
		}
		else if (Game::getSingletonPtr()->getPlaying() == Game::PLAYING_BLUE){
			m_pBluePlayer->update(dt);
			m_pBluePlayer->serverReconciliation();			
		}
		break;
	}

	m_pRedPlayer->render();
	m_pBluePlayer->render();

	// How much the other player shifts for adjustment.
	SDL_Rect redPos, bluePos;
	redPos = m_pRedPlayer->getPosition();
	bluePos = m_pBluePlayer->getPosition();

	const int vRedX = (redPos.x + m_pRedPlayer->getRenderWidthDiff());
	const int vBlueX = (bluePos.x + m_pBluePlayer->getRenderWidthDiff());
	const int vMid = (vRedX + vBlueX) / 2;

	int x = Camera::getSingletonPtr()->getX();

	Camera::getSingletonPtr()->setX(vMid - (StageManager::getSingletonPtr()->getStage()->m_layers[0].src.w) / 2);
	
	// Re-position non-moving player.
	// TODO: Move this logic into Player class.
	if (m_pBluePlayer->getCurrentState() != Player::State::WALKING_BACK &&
		m_pBluePlayer->getCurrentState() != Player::State::WALKING_FORWARD){
		bluePos.x += x - Camera::getSingletonPtr()->getX();
	}
	else if (m_pRedPlayer->getCurrentState() != Player::State::WALKING_BACK &&
		m_pRedPlayer->getCurrentState() != Player::State::WALKING_FORWARD){
		redPos.x += x - Camera::getSingletonPtr()->getX();
	}

	// Test normal hitbox collision (hitboxes 0 through 3).
	for(int i=0; i<4; ++i){
		for(int j=0; j<4; ++j){
			if ((m_pRedPlayer->getHitbox(i)->intersects(m_pBluePlayer->getHitbox(j)))){
				// Calculate distance between each player's x component of this hitbox.
				const int offset = 300;
				int dist = (m_pRedPlayer->getSide() == Player::Side::LEFT) ?
					std::abs(m_pBluePlayer->getHitbox(j)->getRect().x -
					m_pRedPlayer->getHitbox(i)->getRect().x -
					m_pRedPlayer->getHitbox(i)->getRect().w) :
					std::abs(m_pRedPlayer->getHitbox(i)->getRect().x -
					m_pBluePlayer->getHitbox(j)->getRect().x -
					m_pBluePlayer->getHitbox(j)->getRect().w);
				// Re-calculate the distance the player(s) should move based on collision.
				if (dist > 0){
					dist = static_cast<int>((offset + dist) * dt);
				}
				else{
					dist = -static_cast<int>((offset + dist) * dt);
				}

				// Apply collision handling on a case-by-case basis.
				const StateID redState = m_pRedPlayer->getCurrentState();
				const StateID blueState = m_pBluePlayer->getCurrentState();
				if ((redState != Player::State::JUMPING && blueState != Player::State::JUMPING) ||
					(redState == Player::State::JUMPING && blueState == Player::State::JUMPING)){
					redPos.x += (m_pRedPlayer->getSide() == Player::Side::LEFT) ? -dist : dist;
					bluePos.x += (m_pRedPlayer->getSide() == Player::Side::LEFT) ? dist : -dist;			
				}
				else if (redState == Player::State::JUMPING && blueState != Player::State::JUMPING){
					redPos.x += (m_pRedPlayer->getSide() == Player::Side::LEFT) ? -dist : dist;
				}
				else if (blueState == Player::State::JUMPING && redState != Player::State::JUMPING){
					bluePos.x += (m_pRedPlayer->getSide() == Player::Side::LEFT) ? dist : -dist;
				}										
			}
		}
	}

	// Switch player sides if necessary.
	if (redPos.x > (bluePos.x)){
		if (m_pRedPlayer->getSide() != Player::Side::RIGHT){
			m_pRedPlayer->setSide(Player::Side::RIGHT);
			m_pBluePlayer->setSide(Player::Side::LEFT);
		}
	}
	else if(bluePos.x > (redPos.x)){
		if (m_pBluePlayer->getSide() != Player::Side::RIGHT){
			m_pBluePlayer->setSide(Player::Side::RIGHT);
			m_pRedPlayer->setSide(Player::Side::LEFT);
		}
	}

	m_pRedPlayer->setPosition(redPos);
	m_pBluePlayer->setPosition(bluePos);

	// Render the players.
	/*m_pRedPlayer->render();
	m_pBluePlayer->render();*/
}

// ================================================ //