// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
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
	bool m_bQuit;
	std::shared_ptr<GUI> m_pGUI;
	std::shared_ptr<Stage> m_pBackground;
};

// ================================================ //

#endif

// ================================================ //