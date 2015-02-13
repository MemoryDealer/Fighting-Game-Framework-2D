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
// File: Timer.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements Timer class.
// ================================================ //

#include "stdafx.hpp"
#include "Timer.hpp"
#include "Engine.hpp"

// ================================================ //

Timer::Timer(void) :
m_startTicks(0),
m_pausedTicks(0),
m_paused(false),
m_started(false)
{

}

// ================================================ //

Timer::~Timer(void)
{

}

// ================================================ //

Uint32 Timer::restart(void)
{
	m_started = true;
	m_paused = false;

	m_startTicks = SDL_GetTicks();
	return m_startTicks;
}

// ================================================ //

void Timer::stop(void)
{
	m_started = false;
	m_paused = false;
}

// ================================================ //

void Timer::pause(void)
{
	if (m_started == true && m_paused == false){
		m_paused = true;

		m_pausedTicks = SDL_GetTicks() - m_startTicks;
	}
}

// ================================================ //

void Timer::unpause(void)
{
	if (m_paused == true){
		m_paused = false;

		m_startTicks = SDL_GetTicks() - m_pausedTicks;

		m_pausedTicks = 0;
	}
}

// ================================================ //

Uint32 Timer::getTicks(void)
{
	if (m_started == true){
		return (m_paused == true) ? m_pausedTicks :
			static_cast<Uint32>((SDL_GetTicks() - m_startTicks) * Engine::getSingletonPtr()->getClockSpeed());
	}

	return 0;
}

// ================================================ //