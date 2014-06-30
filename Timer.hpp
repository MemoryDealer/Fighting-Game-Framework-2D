// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
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
	int restart(void);

	// Stops the timer.
	void stop(void);

	// Pauses the timer.
	void pause(void);

	// Unpauses the timer.
	void unpause(void);

	// Get the time in milliseconds since the timer was started.
	int getTicks(void);

	// Getters

	// Returns true if the timer is active.
	bool isStarted(void) const;

	// Returns true if the timer is paused.
	bool isPaused(void) const;

	// Setters

	// Manually set the start ticks value (determined by SDL_GetTicks() when started).
	void setStartTicks(const int ticks);

private:
	int		m_startTicks;
	int		m_pausedTicks;
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