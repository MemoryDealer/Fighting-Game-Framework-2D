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
		CAMPAIGN,
		ARCADE,
			ONLINE,
				HOST,
				JOIN,
		OPTIONS
	};

	// Calls GUI::update().
	virtual void update(double dt);

private:

};

// ================================================ //

// Provide a namespace for MenuState's GUILayer's.
// Each layer's constructor sets the ID and name to the corresponding values.
// Each layer enumerates all of its Widget IDs.
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
	};

	// ================================================ //

	class Campaign : public GUILayer
	{
	public:
		explicit Campaign(void);

		enum Widget{
			BUTTON_NEW = 0,
			BUTTON_LOAD,
			BUTTON_BACK
		};
	};

	// ================================================ //

	class Arcade : public GUILayer
	{
	public:
		explicit Arcade(void);

		enum Widget{
			BUTTON_LOCAL = 0,
			BUTTON_ONLINE,
			BUTTON_BACK
		};
	};

	// ================================================ //

	class Online : public GUILayer
	{
	public:
		explicit Online(void);

		enum Widget{
			BUTTON_HOST = 0,
			BUTTON_JOIN,
			BUTTON_DEDICATED,
			BUTTON_BACK
		};
	};

	// ================================================ //

	class Host : public GUILayer
	{
	public:
		explicit Host(void);

		enum Widget{
			TEXTBOX_PORT = 0,
			TEXTBOX_USERNAME,
			STATIC_PORT,
			STATIC_USERNAME,
			BUTTON_HOST,
			BUTTON_BACK
		};
	};

	// ================================================ //

	class Join : public GUILayer
	{
	public:
		explicit Join(void);

		enum Widgets{
			STATIC_SERVER = 0,
			STATIC_PORT,
			STATIC_USERNAME,
			STATIC_PASSWORD,
			BUTTON_JOIN,
			BUTTON_BACK,
			TEXTBOX_SERVER,
			TEXTBOX_PORT,
			TEXTBOX_USERNAME,
			TEXTBOX_PASSWORD
		};
	};

	// ================================================ //

	class Options : public GUILayer
	{
	public:
		explicit Options(void);

		enum Widget{
			BUTTON_BACK = 0
		};
	};
}

// ================================================ //

#endif

// ================================================ //