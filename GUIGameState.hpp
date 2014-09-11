// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: GUIGameState.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines GUIGameState class, the GUI object for the game state.
// ================================================ //

#ifndef __GUIGAMESTATE_HPP__
#define __GUIGAMESTATE_HPP__

// ================================================ //

#include "GUI.hpp"

// ================================================ //

class GUIGameState : public GUI
{
public:
	// Calls GUI::GUI(), loads and saves the theme textures (e.g, GUI::ButtonTexture, etc.), 
	// Allocates each GUILayer and loads the corresponding Widgets from the .gui file for each.
	// Sets starting layer to Root.
	explicit GUIGameState(const std::string& file);

	// Empty destructor.
	virtual ~GUIGameState(void);

	// Layer names.
	enum Layer{
		ROOT = 2,
		PREGAME,
		PAUSE
	};

	// Calls GUI::update().
	virtual void update(double dt);

private:

};

// ================================================ //

// Provide a namespace for GameState's GUILayer's.
// Each layer's constructor sets the ID and name to the corresponding values.
// Each layer enumerates all of its Widget IDs.
namespace GUIGameStateLayer{

	// ================================================ //

	// Displayed during gameplay.
	class Root : public GUILayer
	{
	public:
		explicit Root(void);

		enum Widget{
			STATIC_RED_FIGHTER = 0,
			STATIC_BLUE_FIGHTER,
			STATIC_RED_WINS,
			STATIC_BLUE_WINS,
			STATIC_COUNTDOWN,

			HEALTHBAR_RED,
			HEALTHBAR_BLUE
		};
	};

	// ================================================ //

	// Displayed before a match begins, showing each fighter with
	// their detailed portrait.
	class Pregame : public GUILayer
	{
	public:
		explicit Pregame(void);

		enum Widget{

		};
	};

	// ================================================ //

}

// ================================================ //

#endif

// ================================================ //