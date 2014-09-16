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

// ================================================ //

Player::Player(const std::string& fighterFile, const std::string& buttonMapFile, const int mode) :
Object(),
m_xAccel(0),
m_yAccel(0),
m_xVel(0),
m_yVel(0),
m_xMax(0),
m_yMax(0),
m_side(Player::Side::LEFT),
m_mode(Player::Mode::LOCAL),
m_hp(100),
m_pHealthBar(nullptr),
m_pInput(new Input(buttonMapFile)),
m_moves(),
m_hitboxes(),
m_pCurrentMove(nullptr),
m_pMoveTimer(new Timer()),
m_clientInputs(),
m_serverUpdates()
{
	// Don't continue loading fighter if file is invalid.
	if (fighterFile.empty()){
		Log::getSingletonPtr()->logMessage("WARNING: No fighter file specified");
		return;
	}

	this->loadFighterData(fighterFile);

	//m_dst.w = m_dst.h = 100;
	//m_dst.y = 380;

	//// temp.
	//m_xAccel = 50;
	//m_yAccel = 5;
	//m_xMax = 300;
	//m_yMax = 10;
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
		m_xVel = update.xVel;
		m_xAccel = update.xAccel;
		m_pFSM->setCurrentState(update.state);

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
				this->processInput();
				// Apply the input.
				m_dst.x += static_cast<int32_t>(itr->xVel * itr->dt);
				++itr;
			}
		}

		m_serverUpdates.pop();
	}
}

// ================================================ //

void Player::processInput(void)
{
	// Checking both left and right will force the player to cancel out movement 
	// if both are held thus preventing the character from sliding when holding both down.
	if (m_pInput->getButton(Input::BUTTON_LEFT) == true &&
		m_pInput->getButton(Input::BUTTON_RIGHT) == false){
		m_xVel -= m_xAccel;
		if (m_xVel < -m_xMax){
			m_xVel = -m_xMax;
		}

		m_pFSM->setCurrentState((m_side == Player::Side::LEFT) ? Player::State::WALKING_BACK :
								Player::State::WALKING_FORWARD);
	}
	else if (m_pInput->getButton(Input::BUTTON_RIGHT) == true &&
		m_pInput->getButton(Input::BUTTON_LEFT) == false){
		m_xVel += m_xAccel;
		if (m_xVel > m_xMax){
			m_xVel = m_xMax;
		}

		m_pFSM->setCurrentState((m_side == Player::Side::LEFT) ? Player::State::WALKING_FORWARD :
								Player::State::WALKING_BACK);
	}
	else{
		m_xVel = 0;

		m_pFSM->setCurrentState(Player::State::IDLE);
	}
}

// ================================================ //

void Player::applyInput(double dt)
{
	m_dst.x += static_cast<int32_t>(m_xVel * dt);
}

// ================================================ //

void Player::update(double dt)
{
	this->processInput();
	this->applyInput(dt);
}

// ================================================ //

void Player::render(void)
{
	this->updateMove();

	SDL_RenderCopyEx(Engine::getSingletonPtr()->getRenderer(), m_pTexture, &m_src, &m_dst, 0, nullptr, m_flip);
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
	}

	// Update the animation frame.
	if (m_pMoveTimer->getTicks() > m_pCurrentMove->frameGap){
		m_src = m_pCurrentMove->frames[m_pCurrentMove->currentFrame].toSDLRect();

		if (++m_pCurrentMove->currentFrame >= m_pCurrentMove->numFrames){
			if (m_pCurrentMove->repeat){
				m_pCurrentMove->currentFrame = m_pCurrentMove->repeatFrame;
			}
		}

		m_pMoveTimer->restart();
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
	this->setTextureFile(m.parseValue("core", "spriteSheet"));

	// Set default rendering size.
	m_dst.w = m.parseIntValue("size", "w");
	m_dst.h = m.parseIntValue("size", "h");

	// Parse physics.
	m_xAccel = m.parseIntValue("movement", "xAccel");
	m_yAccel = m.parseIntValue("movement", "yAccel");
	m_xMax = m.parseIntValue("movement", "xMax");
	m_yMax = m.parseIntValue("movement", "yMax");

	// Set player 26 units from bottom adjusting for player height.
	m_dst.y = Engine::getSingletonPtr()->getLogicalWindowHeight() - m_dst.h - 26;

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
	m_pFSM->addState(state);
	state = new FState(Player::State::WALKING_FORWARD);
	m_pFSM->addState(state);
	state = new FState(Player::State::WALKING_BACK);
	m_pFSM->addState(state);

	// Set default state.
	m_pFSM->setCurrentState(Player::State::IDLE);
}

// ================================================ //

