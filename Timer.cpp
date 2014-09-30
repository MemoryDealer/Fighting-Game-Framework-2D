// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: Timer.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements Timer class.
// ================================================ //

#include "stdafx.hpp"
#include "Timer.hpp"

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
			SDL_GetTicks() - m_startTicks;
	}

	return 0;
}

// ================================================ //