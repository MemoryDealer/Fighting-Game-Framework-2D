// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: PlayerImpl.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements PlayerImpl Pimpl idiom class. 
// ================================================ //

#include "PlayerImpl.hpp"
#include "Player.hpp"
#include "FSM.hpp"
#include "MessageRouter.hpp"
#include "Move.hpp"
#include "FighterMetadata.hpp"
#include "Timer.hpp"
#include "Input.hpp"
#include "Camera.hpp"
#include "PlayerManager.hpp"
#include "Input.hpp"

// ================================================ //

const int MAX_HITBOXES = 7;

// ================================================ //

PlayerImpl::PlayerImpl(const std::string& fighterFile, const std::string& buttomMapFile, const int mode)
	:	ObjectImpl(),
		m_xAccel(0),
		m_yAccel(0),
		m_xVel(0), 
		m_yVel(0),
		m_xMax(0),
		m_yMax(0),
		m_currentAction(PlayerAction::NONE),
		m_playerSide(PlayerSide::LEFT),
		m_pInput(new Input(buttomMapFile)),
		m_mode(mode),
		m_moves(),
		m_pCurrentMove(nullptr),
		m_pMoveTimer(new Timer()),
		m_hitboxes(),
		m_colliding(false),
		m_drawHitboxes(false)
{
	
}

// ================================================ //

PlayerImpl::~PlayerImpl(void)
{
	Log::getSingletonPtr()->logMessage("Clearing move list for \"" + m_name + "\"");
	for(MoveList::iterator itr = m_moves.begin();
		itr != m_moves.end();
		++itr){
		delete *itr;
	}

	m_moves.clear();
}

// ================================================ //

