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
// File: Timer.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines Timer class.
// ================================================ //

#ifndef __TIMER_HPP__
#define __TIMER_HPP__

// ================================================ //

// A timer that starts from zero. Uses milliseconds.
class Timer
{
public:
	// Empty constructor.
	explicit Timer(void);

	// Empty destructor.
	~Timer(void);

	// Starts the timer, erasing any previous time.
	Uint32 restart(void);

	// Stops the timer.
	void stop(void);

	// Pauses the timer.
	void pause(void);

	// Unpauses the timer.
	void unpause(void);

	// Get the time in milliseconds since the timer was started.
	Uint32 getTicks(void);

	// Getters

	// Returns true if the timer is active.
	bool isStarted(void) const;

	// Returns true if the timer is paused.
	bool isPaused(void) const;

	// Setters

	// Manually set the start ticks value (determined by SDL_GetTicks() when started).
	void setStartTicks(const int ticks);

private:
	Uint32	m_startTicks;
	Uint32	m_pausedTicks;
	bool	m_paused;
	bool	m_started;
};

// ================================================ //

// Getters

inline bool Timer::isStarted(void) const{ 
	return m_started;
}

inline bool Timer::isPaused(void) const{ 
	return m_paused;
}

// Setters

inline void Timer::setStartTicks(const int ticks){
	m_startTicks = ticks;
}

// ================================================ //

#endif

// ================================================ //