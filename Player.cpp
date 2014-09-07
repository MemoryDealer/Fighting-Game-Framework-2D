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
#include "GameManager.hpp"

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
m_pInput(new Input(buttonMapFile)),
m_playerUpdates()
{
	m_dst.w = m_dst.h = 100;

	// temp.
	m_xAccel = 50;
	m_yAccel = 5;
	m_xMax = 300;
	m_yMax = 10;
}

// ================================================ //

Player::~Player(void)
{

}

// ================================================ //

void Player::updateFromServer(const Server::PlayerUpdate& update)
{
	m_playerUpdates.push(update);
}

// ================================================ //

void Player::processInput(void)
{
	if (m_pInput->getButton(Input::BUTTON_LEFT) == true &&
		m_pInput->getButton(Input::BUTTON_RIGHT) == false){
		m_xVel = -m_xMax;
	}
	else if (m_pInput->getButton(Input::BUTTON_RIGHT) == true &&
		m_pInput->getButton(Input::BUTTON_LEFT) == false){
		m_xVel = m_xMax;
	}
	else{
		m_xVel = 0;
	}
	// Checking both left and right will force the player to cancel out movement 
	// if both are held thus preventing the character from sliding when holding both down.
	//if (m_pInput->getButton(Input::BUTTON_LEFT) == true &&
	//	m_pInput->getButton(Input::BUTTON_RIGHT) == false){
	//	m_xVel -= m_xAccel;
	//	if (m_xVel < -m_xMax){
	//		m_xVel = -m_xMax;
	//	}

	//	// change action...
	//}
	//else if (m_pInput->getButton(Input::BUTTON_RIGHT) == true &&
	//	m_pInput->getButton(Input::BUTTON_LEFT) == false){
	//	m_xVel += m_xAccel;
	//	if (m_xVel > m_xMax){
	//		m_xVel = m_xMax;
	//	}

	//	// change action...
	//}
	//else{
	//	// Declerate when nothing is pressed.
	//	if (m_xVel < 0){
	//		m_xVel += m_xAccel;
	//		if (m_xVel > 0){
	//			m_xVel = 0;
	//		}
	//	}
	//	else if (m_xVel > 0){
	//		m_xVel -= m_xAccel;
	//		if (m_xVel < 0){
	//			m_xVel = 0;
	//		}
	//	}
	//}
}

// ================================================ //

void Player::applyInput(double dt)
{
	m_dst.x += static_cast<int>(m_xVel * dt);
}

// ================================================ //

void Player::update(double dt)
{
	this->processInput();
	this->applyInput(dt);
}

// ================================================ //

void Player::serverReconciliation(void)
{
	// Apply any pending player updates received from server.
	while (!m_playerUpdates.empty()){
		Server::PlayerUpdate update = m_playerUpdates.front();
		m_dst.x = update.x;
		m_xVel = update.xVel;
		m_xAccel = update.xAccel;

		for (Client::ClientInputList::iterator itr = Client::getSingletonPtr()->m_pendingInputs.begin();
			itr != Client::getSingletonPtr()->m_pendingInputs.end();){
			if (itr->seq <= update.lastProcessedInput){
				itr = Client::getSingletonPtr()->m_pendingInputs.erase(itr);
			}
			else{
				this->m_pInput->setButton(itr->input, itr->value);
				this->processInput();
				//m_xVel = itr->vel;
				this->applyInput(itr->dt);
				++itr;
			}
		}

		m_playerUpdates.pop();
	}
}

// ================================================ //

void Player::render(void)
{
	SDL_SetRenderDrawBlendMode(Engine::getSingletonPtr()->getRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(Engine::getSingletonPtr()->getRenderer(), 0, 255, 0, 255);
	SDL_RenderFillRect(Engine::getSingletonPtr()->getRenderer(), &m_dst);
}

// ================================================ //

