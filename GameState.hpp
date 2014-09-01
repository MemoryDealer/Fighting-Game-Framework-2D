// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: GameState.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines GameState class.
// ================================================ //

#ifndef __GAMESTATE_HPP__
#define __GAMESTATE_HPP__

// ================================================ //

#include "AppState.hpp"

// ================================================ //

class ObjectManager;
class Timer;

// ================================================ //

// The state for gameplay. Renders Players, Stage, and handles any network
// or AI stuff.
class GameState : public AppState
{
public:
	// Allocates the ObjectManager.
	explicit GameState(void);

	// Empty destructor.
	~GameState(void);

	// Registers this AppState.
	DECLARE_APPSTATE_CLASS(GameState);

	// Logs the entry.
	void enter(void);

	// Logs the exit, sets m_quit to false to allow re-entry.
	void exit(void);

	// Logs the pause.
	bool pause(void);

	// Logs the resumption.
	void resume(void);

	// Process input for both Players.
	void handleInput(SDL_Event& e){}
	void handleInputDt(SDL_Event& e, double dt);

	// Processes SDL_Event, updates the Stage, Player, and Object Managers.
	void update(double dt);

private:
	std::shared_ptr<ObjectManager> m_pObjectManager;
	std::shared_ptr<Timer> m_pServerUpdateTimer;
};

// ================================================ //

#endif

// ================================================ //