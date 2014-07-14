// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
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
		ROOT = 0
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

			TEXTBOX_CHAT,
			TEXTBOX_SEND,
			BUTTON_SEND,

			BUTTON_EXIT
		};
	};

	// ================================================ //
}

// ================================================ //

#endif

// ================================================ //