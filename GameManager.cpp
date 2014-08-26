// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: GameManager.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements GameManager singleton class.
// ================================================ //

#include "GameManager.hpp"

// ================================================ //

template<> GameManager* Singleton<GameManager>::msSingleton = nullptr;

// ================================================ //

GameManager::GameManager(void) :
m_mode(IDLE),
m_state(0),
m_username("Anonymous")
{

}

// ================================================ //

GameManager::~GameManager(void)
{

}

// ================================================ //