// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: GUIMenuState.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines GUIMenuState class, the GUI object for the menu state.
// ================================================ //

#ifndef __GUIMENUSTATE_HPP__
#define __GUIMENUSTATE_HPP__

// ================================================ //

#include "GUI.hpp"

// ================================================ //

// Derived GUI object for use by the MenuState.
class GUIMenuState : public GUI
{
public:
	// Calls GUI::GUI(), loads and saves the theme textures (e.g, GUI::ButtonTexture, etc.), 
	// Allocates each GUILayer and loads the corresponding Widgets from the .gui file for each.
	// Sets starting layer to Root.
	explicit GUIMenuState(const std::string& file);

	// Empty destructor.
	virtual ~GUIMenuState(void);

	// Layer names enumerated for clarity.
	enum Layer{
		ROOT = 0,
		OPTIONS
	};

	// Calls GUI::update().
	virtual void update(double dt);

private:

};

// ================================================ //

// Provide a namespace for MenuState's GUILayer's.
// Each layer's constructor sets the ID and name to the corresponding values.
namespace GUIMenuStateLayer{

	// ================================================ //

	class Root : public GUILayer
	{
	public:
		explicit Root(void);

		enum Widget{
			BUTTON_CAMPAIGN = 0,
			BUTTON_ARCADE,
			BUTTON_OPTIONS,
			BUTTON_QUIT
		};

		virtual void update(double dt);
	};

	// ================================================ //
	// ================================================ //

	class Options : public GUILayer
	{
	public:
		explicit Options(void);

		enum Widget{
			BUTTON_BACK = 0
		};

		virtual void update(double dt);
	};

}

// ================================================ //

#endif

// ================================================ //