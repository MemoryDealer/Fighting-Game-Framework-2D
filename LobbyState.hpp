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
// File: LobbyState.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines LobbyState class.
// ================================================ //

#ifndef __LOBBYSTATE_HPP__
#define __LOBBYSTATE_HPP__

// ================================================ //

#include "AppState.hpp"

// ================================================ //

class GUI;
class Stage;

// ================================================ //

// The state for the lobby, which is in between the menu state and
// the game state. Used for selecting characters and setting up the game.
class LobbyState : public AppState
{
public:
	// Loads the background stage file and parses the location of the .gui file
	// and loads the GUI.
	explicit LobbyState(void);

	// Empty destructor.
	~LobbyState(void);

	// Registers the AppState.
	DECLARE_APPSTATE_CLASS(LobbyState);

	// Allocates StageManager and PlayerManager.
	void enter(void);

	// Frees StageManager and PlayerManager.
	void exit(void);

	// Logs the pause.
	bool pause(void);

	// Logs the resumption.
	void resume(void);

	// Process keyboard/gamepad input for GUI.
	void handleInput(SDL_Event& e);

	// Process events for the GUI.
	void processGUIAction(const int type);

	// Handles SDL_Event and updates GUI and background.
	void update(double dt);

private:
	std::shared_ptr<GUI> m_pGUI;
	std::shared_ptr<Stage> m_pBackground;
};

// ================================================ //

#endif

// ================================================ //