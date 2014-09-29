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
#include "Client.hpp"
#include "Game.hpp"
#include "WidgetHealthBar.hpp"
#include "StageManager.hpp"
#include "Stage.hpp"

// ================================================ //

Player::Player(const std::string& fighterFile, const std::string& buttonMapFile, const int mode) :
Object(),
m_xAccel(0),
m_yAccel(0),
m_xVel(0),
m_yVel(0),
m_xMax(0),
m_yMax(0),
m_jumpCeiling(0),
m_xJumpVel(0),
m_up(true),
m_side(Player::Side::LEFT),
m_mode(Player::Mode::LOCAL),
m_maxHP(1200),
m_currentHP(m_maxHP),
m_pHealthBar(nullptr),
m_pInput(new Input(buttonMapFile)),
m_moves(),
m_hitboxes(),
m_pCurrentMove(nullptr),
m_pMoveTimer(new Timer()),
m_drawHitboxes(false),
m_maxXPos(0),
m_colliding(false),
m_clientInputs(),
m_serverUpdates()
{
	// Don't continue loading fighter if file is invalid.
	if (fighterFile.empty()){
		Log::getSingletonPtr()->logMessage("WARNING: No fighter file specified");
		return;
	}

	this->loadFighterData(fighterFile);
}

// ================================================ //

Player::~Player(void)
{

}

// ================================================ //

void Player::enqueueClientInput(const Client::NetInput& input)
{
	if (Game::getSingletonPtr()->getMode() == Game::SERVER){
		m_clientInputs.push(input);
	}
}

// ================================================ //

void Player::updateFromServer(const Server::PlayerUpdate& update)
{
	if (Game::getSingletonPtr()->getMode() == Game::CLIENT){
		m_serverUpdates.push(update);
	}
}

// ================================================ //

void Player::serverReconciliation(void)
{
	// Apply any pending player updates received from server.
	while (!m_serverUpdates.empty()){
		Server::PlayerUpdate update = m_serverUpdates.front();
		// Rewind to the server's latest update.
		m_dst.x = update.x;
		m_dst.y = update.y;
		m_xVel = update.xVel;
		if (update.state == Player::State::JUMPING){
			m_xJumpVel = update.xVel;
		}
		m_yVel = update.yVel;

		// Replay any inputs not yet processed by server.
		for (Client::ClientInputList::iterator itr = Client::getSingletonPtr()->m_pendingInputs.begin();
			 itr != Client::getSingletonPtr()->m_pendingInputs.end();){
			if (itr->seq <= update.lastProcessedInput){
				// This input is old, remove it from the queue.
				itr = Client::getSingletonPtr()->m_pendingInputs.erase(itr);
			}
			else{
				// Input is still unprocessed by the server, re-apply it.
				m_pInput->setButton(itr->input, itr->value);
				this->processInput(itr->dt);
				// Apply the input.
				m_dst.x += static_cast<int32_t>(itr->xVel * itr->dt);
				m_dst.y -= static_cast<int32_t>(itr->yVel * itr->dt);
				++itr;
			}
		}

		m_serverUpdates.pop();
	}

	if (m_dst.x < 0){
		m_dst.x = 0;
	}
	if (m_dst.y > m_floor){
		m_dst.y = m_floor;
	}
}

// ================================================ //

void Player::processInput(double dt)
{
	// Checking both left and right will force the player to cancel out movement 
	// if both are held thus preventing the character from sliding when holding both down.
	if (m_pInput->getButton(Input::BUTTON_LEFT) == true &&
		m_pInput->getButton(Input::BUTTON_RIGHT) == false){
		m_xVel -= m_xAccel;
		if (m_xVel < -m_xMax){
			m_xVel = -m_xMax;
		}

		m_pFSM->stateTransition((m_side == Player::Side::LEFT) ? Player::State::WALKING_BACK :
								Player::State::WALKING_FORWARD);
	}
	else if (m_pInput->getButton(Input::BUTTON_RIGHT) == true &&
				m_pInput->getButton(Input::BUTTON_LEFT) == false){
		m_xVel += m_xAccel;
		if (m_xVel > m_xMax){
			m_xVel = m_xMax;
		}

		m_pFSM->stateTransition((m_side == Player::Side::LEFT) ? Player::State::WALKING_FORWARD :
								Player::State::WALKING_BACK);
	}
	else{
		m_xVel = 0;

		m_pFSM->stateTransition(Player::State::IDLE);
	}

	// Enter jumping if up is pressed and is possible.
	if (m_pInput->getButton(Input::BUTTON_UP)){
		// Prevent x velocity modification in the air.
		if (m_pFSM->getCurrentStateID() != Player::State::JUMPING){
			if (m_pFSM->stateTransition(Player::State::JUMPING) == Player::State::JUMPING){
				if (m_pInput->getButton(Input::BUTTON_RIGHT)){
					m_xJumpVel = static_cast<int>(m_xMax * 1.5);
				}
				else if (m_pInput->getButton(Input::BUTTON_LEFT)){
					m_xJumpVel = -static_cast<int>(m_xMax * 1.5);
				}
				else{
					m_xJumpVel = 0;
				}
			}
		}
	}
	else if (m_pInput->getButton(Input::BUTTON_DOWN)){
		if (m_pFSM->getCurrentStateID() != Player::State::CROUCHED){
			if (m_pFSM->stateTransition(Player::State::CROUCHING) == Player::State::CROUCHING){

			}
		}
	}
	else if (m_pInput->getButton(Input::BUTTON_DOWN) == false){
		if (m_pFSM->getCurrentStateID() == Player::State::CROUCHED){
			m_pFSM->stateTransition(Player::State::UNCROUCHING);
		}
	}

	// Process jumping mechanics.
	if (m_pFSM->getCurrentStateID() == Player::State::JUMPING){	
		if (m_up){
			m_yVel += m_yAccel;
			if (m_yVel > m_yMax){
				m_yVel = m_yMax;
			}
			if (m_dst.y <= m_jumpCeiling){
				m_dst.y = m_jumpCeiling;
				m_up = false;
			}
		}
		else{
			m_yVel -= m_yAccel;
			if (m_yVel < -m_yMax){
				m_yVel = -m_yMax;
			}
			if (m_dst.y >= m_floor){
				m_dst.y = m_floor;
				m_up = true;
				m_pFSM->setCurrentState(Player::State::IDLE);
				m_xVel = m_yVel = 0;
			}
		}
	}
	else if(m_pFSM->getCurrentStateID() == Player::State::CROUCHING ||
			m_pFSM->getCurrentStateID() == Player::State::CROUCHED){
		m_xVel = 0;
	}
}

// ================================================ //

void Player::applyInput(double dt)
{
	if (m_colliding){
		m_dst.x -= static_cast<int32_t>(
			(m_pFSM->getCurrentStateID() == Player::State::JUMPING) ? m_xJumpVel * dt
			: m_xVel * dt);
	}
	else{
		m_dst.x += static_cast<int32_t>(
			(m_pFSM->getCurrentStateID() == Player::State::JUMPING) ? m_xJumpVel * dt
			: m_xVel * dt);
	}

	m_dst.y -= static_cast<int32_t>(m_yVel * dt);
}

// ================================================ //

void Player::update(double dt)
{
	this->processInput(dt);
	this->applyInput(dt);
}

// ================================================ //

void Player::render(void)
{
	this->updateMove();

	SDL_RenderCopyEx(Engine::getSingletonPtr()->getRenderer(), m_pTexture, &m_src, &m_dst, 0, nullptr, m_flip);

	if (m_drawHitboxes){
		for (Uint32 i = 0; i < m_hitboxes.size(); ++i){
			m_hitboxes[i]->render();
		}
	}
}

// ================================================ //

void Player::updateMove(void)
{
	// Force current animation to stop if the state has changed.
	if (m_pCurrentMove != m_moves[m_pFSM->getCurrentStateID()]){
		m_pCurrentMove->currentFrame = m_pCurrentMove->repeatFrame;
		m_pMoveTimer->setStartTicks(0);
	}

	switch (m_pFSM->getCurrentStateID()){
	default:
	case Player::State::IDLE:
		m_pCurrentMove = m_moves[MoveID::IDLE];
		break;

	case Player::State::WALKING_FORWARD:
		m_pCurrentMove = m_moves[MoveID::WALKING_FORWARD];
		break;

	case Player::State::WALKING_BACK:
		m_pCurrentMove = m_moves[MoveID::WALKING_BACK];
		break;

	case Player::State::JUMPING:
		m_pCurrentMove = m_moves[MoveID::JUMPING];
		break;

	case Player::State::CROUCHING:
		m_pCurrentMove = m_moves[MoveID::CROUCHING];
		break;

	case Player::State::CROUCHED:
		m_pCurrentMove = m_moves[MoveID::CROUCHED];
		break;

	case Player::State::UNCROUCHING:
		m_pCurrentMove = m_moves[MoveID::UNCROUCHING];
		break;
	}

	// Update the animation frame.
	if (m_pMoveTimer->getTicks() > m_pCurrentMove->frameGap){
		m_src = m_pCurrentMove->frames[m_pCurrentMove->currentFrame].toSDLRect();

		if (++m_pCurrentMove->currentFrame >= m_pCurrentMove->numFrames){
			if (m_pCurrentMove->repeat == true){
				m_pCurrentMove->currentFrame = m_pCurrentMove->repeatFrame;
			}
			else if (m_pCurrentMove->transition >= 0){				
				m_pCurrentMove->currentFrame -= 1;
				m_pFSM->setCurrentState(m_pCurrentMove->transition);
			}
			else{
				m_pCurrentMove->currentFrame -= 1;
			}
		}

		m_pMoveTimer->restart();
	}

	// Now update the hitboxes for the move.
	// Assign each Hitbox to originate from the character's center.
	// So a hitbox of (50, 0, 50, 50) will be 50x50 and 50 units to the right
	// of the character's center.
	for (Uint32 i = 0; i < m_hitboxes.size(); ++i){
		SDL_Rect offset = { 0, 0, 0, 0 };
		offset = m_pCurrentMove->frames[m_pCurrentMove->currentFrame].hitboxes[i];

		int xCenter = m_dst.x + (m_dst.w / 2);
		int yCenter = m_dst.y + (m_dst.h / 2);

		if (m_side == Player::Side::RIGHT){
			offset.x = -offset.x;
		}

		m_hitboxes[i]->setRect((xCenter - (offset.w / 2) + offset.x), (yCenter - (offset.h / 2) + offset.y),
							   offset.w, offset.h);
	}
}

// ================================================ //

void Player::loadFighterData(const std::string& file)
{
	FighterMetadata m(file);

	if (!m.isLoaded()){
		throw std::exception(std::string("Failed to load fighter file " + file).c_str());
	}

	// Assign the sprite sheet.
	this->setTextureFile(Engine::getSingletonPtr()->getDataDirectory() + 
		"/" + m.parseValue("core", "spriteSheet"));

	// Set default rendering size.
	m_dst.w = m.parseIntValue("size", "w");
	m_dst.h = m.parseIntValue("size", "h");

	// Parse physics.
	m_xAccel = m.parseIntValue("physics", "xAccel");
	m_yAccel = m.parseIntValue("physics", "yAccel");
	m_xMax = m.parseIntValue("physics", "xMax");
	m_yMax = m.parseIntValue("physics", "yMax");
	m_jumpCeiling = m.parseIntValue("physics", "jumpCeiling");

	// Parse any gameplay values.
	m_maxHP = m_currentHP = m.parseIntValue("stats", "HP");

	// Set player 26 units from bottom adjusting for player height.
	m_floor = m_dst.y = Engine::getSingletonPtr()->getLogicalWindowHeight() - m_dst.h - 26;

	// Calculate the far right edge at which player movement should stop or move the camera.
	m_maxXPos = Engine::getSingletonPtr()->getLogicalWindowWidth() - m_dst.w;

	// Load moveset.
	for (int i = 0; i < MoveID::END_MOVES; ++i){
		Log::getSingletonPtr()->logMessage("Parsing move \"" + std::string(MoveID::Name[i]) + "\" for " + m_name);

		m_moves.push_back(m.parseMove(MoveID::Name[i]));
		if (m_moves.back() == nullptr){
			throw std::exception(std::string("Unable to load move \"" + std::string(MoveID::Name[i]) + "\" for fighter" +
				m_name).c_str());
		}
	}

	// Setup default IDLE move.
	m_pMoveTimer->restart();
	m_pCurrentMove = m_moves[MoveID::IDLE];
	m_src = m_moves[MoveID::IDLE]->frames[0].toSDLRect();

	// Setup hitboxes.
	for (int i = 0; i < 4; ++i){
		m_hitboxes.push_back(std::shared_ptr<Hitbox>(new Hitbox(Hitbox::Type::NORMAL)));
	}
	m_hitboxes.push_back(std::shared_ptr<Hitbox>(new Hitbox(Hitbox::Type::THROW)));
	m_hitboxes.push_back(std::shared_ptr<Hitbox>(new Hitbox(Hitbox::Type::DAMAGE)));
	m_hitboxes.push_back(std::shared_ptr<Hitbox>(new Hitbox(Hitbox::Type::DAMAGE)));
	m_hitboxes.push_back(std::shared_ptr<Hitbox>(new Hitbox(Hitbox::Type::COUNTER)));
	m_hitboxes.push_back(std::shared_ptr<Hitbox>(new Hitbox(Hitbox::Type::COUNTER)));

	// Setup state machine.
	FState* state = new FState(Player::State::IDLE);
	state->addTransition(Player::State::WALKING_FORWARD, Player::State::WALKING_FORWARD);
	state->addTransition(Player::State::WALKING_BACK, Player::State::WALKING_BACK);
	state->addTransition(Player::State::JUMPING, Player::State::JUMPING);
	state->addTransition(Player::State::CROUCHING, Player::State::CROUCHING);
	m_pFSM->addState(state);

	state = new FState(Player::State::WALKING_FORWARD);
	state->addTransition(Player::State::IDLE, Player::State::IDLE);
	state->addTransition(Player::State::WALKING_BACK, Player::State::WALKING_BACK);
	state->addTransition(Player::State::JUMPING, Player::State::JUMPING);
	state->addTransition(Player::State::CROUCHING, Player::State::CROUCHING);
	m_pFSM->addState(state);

	state = new FState(Player::State::WALKING_BACK);
	state->addTransition(Player::State::IDLE, Player::State::IDLE);
	state->addTransition(Player::State::WALKING_FORWARD, Player::State::WALKING_FORWARD);
	state->addTransition(Player::State::JUMPING, Player::State::JUMPING);
	state->addTransition(Player::State::CROUCHING, Player::State::CROUCHING);
	m_pFSM->addState(state);

	state = new FState(Player::State::JUMPING);
	m_pFSM->addState(state);

	state = new FState(Player::State::CROUCHING);
	state->addTransition(Player::State::IDLE, Player::State::IDLE);
	state->addTransition(Player::State::CROUCHED, Player::State::CROUCHED);
	state->addTransition(Player::State::JUMPING, Player::State::JUMPING);
	m_pFSM->addState(state);

	state = new FState(Player::State::CROUCHED);
	state->addTransition(Player::State::UNCROUCHING, Player::State::UNCROUCHING);
	state->addTransition(Player::State::JUMPING, Player::State::JUMPING);
	m_pFSM->addState(state);

	state = new FState(Player::State::UNCROUCHING);
	state->addTransition(Player::State::JUMPING, Player::State::JUMPING);
	m_pFSM->addState(state);

	// Set default state.
	m_pFSM->setCurrentState(Player::State::IDLE);
}

// ================================================ //

void Player::takeDamage(const Uint32 damage)
{
	m_currentHP -= damage;
	if (m_currentHP < 0){
		m_currentHP = 0;
		return;
	}

	// Calculate percentage from current HP.
	double percent = static_cast<double>(m_currentHP) / static_cast<double>(m_maxHP);
	percent *= 100.0;

	m_pHealthBar->setPercent(static_cast<int>(percent));
}

// ================================================ //