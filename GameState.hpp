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
class GUI;
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
	std::shared_ptr<GUI> m_pGUI;
	std::shared_ptr<Timer> m_pServerUpdateTimer, m_pResetServerInputTimer;
};

// ================================================ //

#endif

// ================================================ //