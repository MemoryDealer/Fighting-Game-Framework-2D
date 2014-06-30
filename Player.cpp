// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: Player.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements Player class.
// ================================================ //

#include "Player.hpp"
#include "Player.hpp"
#include "Hitbox.hpp"
#include "Input.hpp"
#include "Timer.hpp"
#include "FSM.hpp"
#include "FighterMetadata.hpp"
#include "Engine.hpp"
#include "Move.hpp"
#include "MessageRouter.hpp"

// ================================================ //

Player::Player(const std::string& fighterFile, const std::string& buttonMapFile, const int mode) :
Object(),
m_xAccel(0),
m_yAccel(0),
m_xVel(0),
m_yVel(0),
m_xMax(0),
m_yMax(0),
m_currentAction(PlayerAction::NONE),
m_playerSide(PlayerSide::LEFT),
m_pInput(new Input(buttonMapFile)),
m_mode(mode),
m_moves(),
m_pCurrentMove(nullptr),
m_pMoveTimer(new Timer()),
m_hitboxes(),
m_colliding(false),
m_drawHitboxes(false)
{
	// Stop loading here if the fighter file is not specified. Useful for
	// pre-loading button maps for controlling the main menu.
	if (fighterFile.empty()){
		Log::getSingletonPtr()->logMessage("WARNING: No fighter file specified");
		return;
	}

	this->loadFighterData(fighterFile);

	// Add states to core FSM.
	FState* state = new FState(PlayerState::IDLE);

	state->addTransition(PlayerAction::NONE, PlayerState::IDLE);
	state->addTransition(PlayerAction::WALK_FORWARD, PlayerState::WALKING_FORWARD);
	state->addTransition(PlayerAction::WALK_BACK, PlayerState::WALKING_BACK);
	state->addTransition(PlayerAction::LIGHT_PUNCH, PlayerState::ATTACKING);
	state->addTransition(PlayerAction::MEDIUM_PUNCH, PlayerState::ATTACKING);
	state->addTransition(PlayerAction::HEAVY_PUNCH, PlayerState::ATTACKING);
	state->addTransition(PlayerAction::LIGHT_KICK, PlayerState::ATTACKING);
	state->addTransition(PlayerAction::MEDIUM_KICK, PlayerState::ATTACKING);
	state->addTransition(PlayerAction::HEAVY_KICK, PlayerState::ATTACKING);
	m_pFSM->addState(state);

	state = new FState(PlayerState::WALKING_FORWARD);
	state->addTransition(PlayerAction::NONE, PlayerState::IDLE);
	state->addTransition(PlayerAction::WALK_FORWARD, PlayerState::WALKING_FORWARD);
	state->addTransition(PlayerAction::WALK_BACK, PlayerState::WALKING_BACK);
	m_pFSM->addState(state);

	state = new FState(PlayerState::WALKING_BACK);
	state->addTransition(PlayerAction::NONE, PlayerState::IDLE);
	state->addTransition(PlayerAction::WALK_BACK, PlayerState::WALKING_BACK);
	state->addTransition(PlayerAction::WALK_FORWARD, PlayerState::WALKING_FORWARD);
	m_pFSM->addState(state);

	state = new FState(PlayerState::ATTACKING);
	state->addTransition(PlayerAction::NONE, PlayerState::IDLE);
	state->addTransition(PlayerAction::LIGHT_PUNCH, PlayerState::ATTACKING); // light punch cancels into self...
	m_pFSM->addState(state);

	m_pFSM->setCurrentState(PlayerState::IDLE);
}

// ================================================ //

Player::~Player(void)
{
	
}

// ================================================ //

const int Player::getCurrentState(void) const
{
	return m_pFSM->getCurrentStateID();
}

// ================================================ //

void Player::loadFighterData(const std::string& fighterFile)
{
	FighterMetadata m(fighterFile);

	// TODO: Add a fighter data file integrity check here.

	if (!m.isLoaded()){
		throw std::exception((std::string("Failed to load fighter file ") + std::string(fighterFile)).c_str());
	}

	this->setTextureFile(m.parseValue("core", "spriteSheet"));

	// Get player rendering size.
	m_dst.w = m.parseIntValue("size", "w");
	m_dst.h = m.parseIntValue("size", "h");

	m_xAccel = m.parseIntValue("movement", "xAccel");
	m_yAccel = m.parseIntValue("movement", "yAccel");
	m_xMax = m.parseIntValue("movement", "xMax");
	m_yMax = m.parseIntValue("movement", "yMax");

	// Set player Y position 26 units from bottom, adjusting for player height.
	m_dst.y = Engine::getSingletonPtr()->getLogicalWindowHeight() - m_dst.h - 26;

	this->loadMoves(m);

	// Default the source rect to the first frame of move IDLE.
	m_src = m_moves[MoveID::IDLE]->frames[0].toSDLRect();
	m_pCurrentMove = m_moves[MoveID::IDLE];
}

// ================================================ //

void Player::loadMoves(FighterMetadata& m)
{
	for (int i = 0; i<MoveID::END_MOVES; ++i){
		Log::getSingletonPtr()->logMessage("Parsing move \"" + std::string(MoveID::Name[i]) + "\" for " + m_name);

		m_moves.push_back(m.parseMove(MoveID::Name[i]));
		if (m_moves.back() == nullptr){
			std::string exc = "Unable to load move \"" + std::string(MoveID::Name[i]) +
				"\" for fighter " + m_name;
			throw std::exception(exc.c_str());
		}
	}

	// Reserve four normal hitboxes.
	for (int i = 0; i<4; ++i){
		m_hitboxes.push_back(std::shared_ptr<Hitbox>(new Hitbox(HitboxType::NORMAL)));
	}
	// Reserve one throw hitbox.
	m_hitboxes.push_back(std::shared_ptr<Hitbox>(new Hitbox(HitboxType::THROW)));
	// Reserve two damage hitboxes.
	m_hitboxes.push_back(std::shared_ptr<Hitbox>(new Hitbox(HitboxType::DAMAGE)));
	m_hitboxes.push_back(std::shared_ptr<Hitbox>(new Hitbox(HitboxType::DAMAGE)));
	// Reserve two counter hitboxes.
	m_hitboxes.push_back(std::shared_ptr<Hitbox>(new Hitbox(HitboxType::COUNTER)));
	m_hitboxes.push_back(std::shared_ptr<Hitbox>(new Hitbox(HitboxType::COUNTER)));

	m_pMoveTimer->restart();
}

// ================================================ //

void Player::updateLocalInput(void)
{
	m_currentAction = PlayerAction::NONE;

	// Checking both left and right will force the player to cancel out movement 
	// if both are held thus preventing the character from sliding when holding both down.
	if (m_pInput->getButton(Input::BUTTON_LEFT) &&
		!m_pInput->getButton(Input::BUTTON_RIGHT)){
		m_xVel -= m_xAccel;
		if (m_xVel < -m_xMax)
			m_xVel = -m_xMax;

		m_currentAction = (m_playerSide == PlayerSide::LEFT) ?
			PlayerAction::WALK_BACK : PlayerAction::WALK_FORWARD;
	}
	else if (m_pInput->getButton(Input::BUTTON_RIGHT) &&
		!m_pInput->getButton(Input::BUTTON_LEFT)){
		m_xVel += m_xAccel;
		if (m_xVel > m_xMax)
			m_xVel = m_xMax;

		m_currentAction = (m_playerSide == PlayerSide::RIGHT) ?
			PlayerAction::WALK_BACK : PlayerAction::WALK_FORWARD;
	}
	else{
		// Decelerate when nothing is pressed.
		if (m_xVel < 0){
			m_xVel += m_xAccel;
			if (m_xVel > 0){
				m_xVel = 0;
			}
		}
		else if (m_xVel > 0){
			m_xVel -= m_xAccel;
			if (m_xVel < 0){
				m_xVel = 0;
			}
		}
	}

	m_pFSM->stateTransition(m_currentAction);
}

// ================================================ //

void Player::updateMove(double dt)
{
	// Force the current animation to stop instantly if it has changed to a new one.
	if (m_pCurrentMove != m_moves[m_pFSM->getCurrentStateID()]){
		m_pCurrentMove->currentFrame = m_pCurrentMove->repeatFrame;
		m_pMoveTimer->setStartTicks(0);
	}

	switch (m_pFSM->getCurrentStateID()){
	default:
		break;

	case PlayerState::IDLE:
		m_pCurrentMove = m_moves[MoveID::IDLE];
		break;

	case PlayerState::WALKING_FORWARD:
		m_pCurrentMove = m_moves[MoveID::WALKING_FORWARD];
		break;

	case PlayerState::WALKING_BACK:
		m_pCurrentMove = m_moves[MoveID::WALKING_BACK];
		m_xVel = static_cast<int>(m_xVel * 0.90);
		break;

	case PlayerState::BLOCKING:
		printf("BLOCKING\n");
		break;
	}

	// Update current frame.
	if (m_pMoveTimer->getTicks() > m_pCurrentMove->frameGap){
		m_src = m_pCurrentMove->frames[m_pCurrentMove->currentFrame].toSDLRect();

		if (m_pCurrentMove->reverse){
			static bool dir = true;

			if (dir){
				if (++m_pCurrentMove->currentFrame >= m_pCurrentMove->numFrames){
					--m_pCurrentMove->currentFrame;
					dir = false;
				}
			}
			else{
				if (--m_pCurrentMove->currentFrame < m_pCurrentMove->repeatFrame){
					++m_pCurrentMove->currentFrame;
					dir = true;
				}
			}
		}
		else if (++m_pCurrentMove->currentFrame >= m_pCurrentMove->numFrames){
			if (m_pCurrentMove->repeat){
				m_pCurrentMove->currentFrame = m_pCurrentMove->repeatFrame;
			}
		}

		m_pMoveTimer->restart();
	}

	this->updateHitboxes();
}

// ================================================ //

void Player::updateHitboxes(void)
{
	// Assign each Hitbox to originate from the character's center.
	// So a hitbox of (50, 0, 50, 50) will be 50x50 and 50 units to the right
	// of the character's center.
	for (unsigned int i = 0; i < m_hitboxes.size(); ++i){
		SDL_Rect offset = { 0, 0, 0, 0 };
		offset = m_pCurrentMove->frames[m_pCurrentMove->currentFrame].hitboxes[i];

		int xCenter = m_dst.x + (m_dst.w / 2);
		int yCenter = m_dst.y + (m_dst.h / 2);

		if (m_playerSide == PlayerSide::RIGHT)
			offset.x = -offset.x;

		m_hitboxes[i]->setRect((xCenter - (offset.w / 2) + offset.x), (yCenter - (offset.h / 2) + offset.y),
			offset.w, offset.h);
	}
}

// ================================================ //

void Player::sendMessage(const Message& msg)
{
	printf("Received message %d\n", msg.type);
	if (msg.type == MessageType::TYPE_ACTIVATE)
		m_dead = true;
}

// ================================================ //

void Player::setColliding(const bool colliding)
{
	m_colliding = colliding;

	if (m_colliding){
		if (m_pFSM->getCurrentStateID() == PlayerState::IDLE){
			m_pFSM->setCurrentState(PlayerState::WALKING_BACK);
			m_xVel = (m_playerSide == PlayerSide::LEFT) ? -m_xMax : m_xMax;
		}
	}
}

// ================================================ //

void Player::update(double dt)
{
	if (m_mode == PlayerMode::LOCAL){
		this->updateLocalInput();
	}

	this->updateMove(dt);

	if (m_colliding){
		// Move player back upon collision.
		if (m_playerSide == PlayerSide::LEFT){
			m_dst.x = m_dst.x - static_cast<int>(m_xMax * dt);
		}
		else{
			m_dst.x = m_dst.x + static_cast<int>(m_xMax * dt);
		}
	}

	m_dst.x += static_cast<int>(m_xVel * dt);

	this->render();

	// Render hitboxes if debug draw is on.
	if (m_drawHitboxes){
		for (unsigned int i = 0; i < m_hitboxes.size(); ++i){
			m_hitboxes[i]->render();
		}
	}
}

// ================================================ //