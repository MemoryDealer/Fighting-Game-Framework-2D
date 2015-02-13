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
// File: GUILobbyState.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines GUILobbyState class, the GUI object for the menu state.
// ================================================ //

#ifndef __GUILOBBYSTATE_HPP__
#define __GUILOBBYSTATE_HPP__

// ================================================ //

#include "GUI.hpp"

// ================================================ //

// Derived GUI object for use by the LobbyState.
class GUILobbyState : public GUI
{
public:
	// Calls GUI::GUI(), loads and saves the theme textures (e.g, GUI::ButtonTexture, etc.), 
	// Allocates each GUILayer and loads the corresponding Widgets from the .gui file for each.
	// Sets starting layer to Root.
	explicit GUILobbyState(const std::string& file);

	// Empty destructor.
	virtual ~GUILobbyState(void);

	// Layer names.
	enum Layer{
		ROOT = 2
	};

	// Calls GUI::update().
	virtual void update(double dt);

private:

};

// ================================================ //

// Provide a namespace for MenuState's GUILayer's.
// Each layer's constructor sets the ID and name to the corresponding values.
// Each layer enumerates all of its Widget IDs.
namespace GUILobbyStateLayer{

	// ================================================ //

	class Root : public GUILayer
	{
	public:
		explicit Root(void);

		enum Widget{
			BUTTON_READY = 0,
			BUTTON_START,
			BUTTON_SEND,
			BUTTON_EXIT,
			TEXTBOX_SEND,
			LISTBOX_PLAYERS,
			LISTBOX_CHAT
		};
	};

	// ================================================ //
}

// ================================================ //

#endif

// ================================================ //