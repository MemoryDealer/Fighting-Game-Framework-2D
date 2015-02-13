// ========================================================================= //
// Fighting game framework (2D) with online multiplayer.
// Copyright(C) 2014 Jordan Sparks <unixunited@live.com>
//
// This program is free software; you can redistribute it and / or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 3
// of the License, or(at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
// ========================================================================= //
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
m_mode(Game::Mode::IDLE),
m_playing(Game::Playing::NIL),
m_error(0),
m_username("Anonymous"),
m_redPlayerName(""),
m_bluePlayerName(""),
m_useSimulator(false),
m_simulatedPing(0),
m_simulatedPacketLoss(0.0f)
{
	Config c(Engine::getSingletonPtr()->getSettingsFile());

	m_useSimulator = !!(c.parseIntValue("net", "useSimulator"));
	m_simulatedPing = c.parseIntValue("net", "simulatedPing");
	m_simulatedPacketLoss = static_cast<float>(c.parseDoubleValue("net", "simulatedPacketLoss"));
}

// ================================================ //

Game::~Game(void)
{

}

// ================================================ //