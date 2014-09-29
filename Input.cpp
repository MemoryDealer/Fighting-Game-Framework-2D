// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: Input.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements Input class.
// ================================================ //

#include "Input.hpp"
#include "Config.hpp"

// ================================================ //

Input::Input(const std::string& bmap) :
m_pad(nullptr),
m_padDeadzone(1000),
m_movementMode(Input::MovementMode::JOYSTICK)
{
	// Set all button states to false
	std::fill_n(m_buttons, static_cast<int>(Input::NUM_BUTTONS), false);
	std::fill_n(m_reactivated, static_cast<int>(Input::NUM_BUTTONS), true);
	std::fill_n(m_keyboardMap, static_cast<int>(Input::NUM_BUTTONS), 0);
	std::fill_n(m_gamepadMap, static_cast<int>(Input::NUM_BUTTONS), 0);

	// Load button map
	this->loadButtonMap(bmap);
}

// ================================================ //

Input::~Input(void)
{

}

// ================================================ //

void Input::loadButtonMap(const std::string& file)
{
	Log::getSingletonPtr()->logMessage("Loading button map from \"" + file + "\"");

	Config c(file);
	if (c.isLoaded()){
		// Load keyboard keys.
		m_keyboardMap[BUTTON_UP] = c.parseIntValue("keyboard", "up");
		m_keyboardMap[BUTTON_DOWN] = c.parseIntValue("keyboard", "down");
		m_keyboardMap[BUTTON_LEFT] = c.parseIntValue("keyboard", "left");
		m_keyboardMap[BUTTON_RIGHT] = c.parseIntValue("keyboard", "right");
		m_keyboardMap[BUTTON_LP] = c.parseIntValue("keyboard", "LP");

		// Load gamepad buttons.
		m_gamepadMap[BUTTON_UP] = c.parseIntValue("gamepad", "up");
		m_gamepadMap[BUTTON_DOWN] = c.parseIntValue("gamepad", "down");
		m_gamepadMap[BUTTON_LEFT] = c.parseIntValue("gamepad", "left");
		m_gamepadMap[BUTTON_RIGHT] = c.parseIntValue("gamepad", "right");
		m_gamepadMap[BUTTON_START] = c.parseIntValue("gamepad", "start");
		m_gamepadMap[BUTTON_SELECT] = c.parseIntValue("gamepad", "select");
		m_gamepadMap[BUTTON_BACK] = c.parseIntValue("gamepad", "back");

		m_padDeadzone = c.parseIntValue("gamepad", "deadzone");

		Log::getSingletonPtr()->logMessage("Button map loaded!");
	}
	else{
		Log::getSingletonPtr()->logMessage("ERROR: Failed to open button map file!");
	}
}

// ================================================ //

void Input::resetAllButtons(void)
{
	std::fill_n(m_buttons, static_cast<int>(Input::NUM_BUTTONS), false);
}

// ================================================ //

const int Input::SDLButtonToMappedButton(const int button, const bool gamepad)
{
	// Test each mapped button to see if it matches the button parameter.
	if (gamepad){
		for (int i = 0; i < NUM_BUTTONS; ++i){
			if (button == m_gamepadMap[i]){
				return i;
			}
		}
	}
	else{
		for (int i = 0; i < NUM_BUTTONS; ++i){
			if (button == m_keyboardMap[i]){
				return i;
			}
		}
	}

	// No mapped button found.
	return -1;
}

// ================================================ //

const int Input::getPadID(void) const
{
	// Get the instance ID of the controller using the underlying joystick.
	SDL_Joystick* joystick = nullptr;

	joystick = SDL_GameControllerGetJoystick(m_pad);
	if (joystick){
		return SDL_JoystickInstanceID(joystick);
	}

	return -1;
}

// ================================================ //