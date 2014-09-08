// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: Game.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements Game singleton class.
// ================================================ //

#include "Game.hpp"
#include "Config.hpp"
#include "Engine.hpp"

// ================================================ //

template<> Game* Singleton<Game>::msSingleton = nullptr;

// ================================================ //

Game::Game(void) :
m_mode(IDLE),
m_playing(NIL),
m_error(0),
m_username("Anonymous"),
m_useSimulator(false),
m_simulatedPing(0),
m_simulatedPacketLoss(0.0f)
{
	Config c(Engine::getSingletonPtr()->getSettingsFile());

	m_useSimulator = c.parseIntValue("net", "useSimulator");
	m_simulatedPing = c.parseIntValue("net", "simulatedPing");
	m_simulatedPacketLoss = static_cast<float>(c.parseDoubleValue("net", "simulatedPacketLoss"));
}

// ================================================ //

Game::~Game(void)
{

}

// ================================================ //