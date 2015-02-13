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
// File: MenuState.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines MenuState class.
// ================================================ //

#ifndef __MENUSTATE_HPP__
#define __MENUSTATE_HPP__

// ================================================ //

#include "AppState.hpp"

// ================================================ //

class GUI;
class Stage;

// ================================================ //

// The state for the main menu. Has a GUI and renders a 
// Stage object for a background.
class MenuState : public AppState
{
public:
	// Initializes background to "Data/Stages/mainmenu.stage" and allocates
	// GUI to the .gui file defined in ExtMF.cfg.
	explicit MenuState(void);

	// Empty destructor.
	~MenuState(void);

	// Registers this AppState.
	DECLARE_APPSTATE_CLASS(MenuState);

	// Allocates the Camera (needed for Stage update).
	void enter(void);

	// Frees the Camera.
	void exit(void);

	// Logs the pause.
	bool pause(void);

	// Logs the resumption.
	void resume(void);

	// Processes keyboard and gamepad input for GUI.
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