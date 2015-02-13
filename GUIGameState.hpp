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