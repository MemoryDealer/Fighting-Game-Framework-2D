// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
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