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
// File: App.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines App class, and names of each game state.
// ================================================ //

#ifndef __APP_HPP__
#define __APP_HPP__

// ================================================ //

#include "AppStateManager.hpp"

// ================================================ //

const std::string MENU_STATE = "MenuState";
const std::string LOBBY_STATE = "LobbyState";
const std::string GAME_STATE = "GameState";

// ================================================ //

// Contains the AppStateManager for managing the game states. App should
// be allocated to begin the game.
class App
{
public:
	// Initializes the application by loading AppStateManager and game states,
	// along with any other critical game data, such as the Engine, Log, 
	// MessageRouter, FontManager, and GamepadManager singletons.
	explicit App(void);

	// Deletes all singletons allocated in constructor.
	~App(void);

private:
	// Controls all game states, see AppStateManager.hpp.
	AppStateManager* m_pAppStateManager;
};

// ================================================ //

#endif

// ================================================ //