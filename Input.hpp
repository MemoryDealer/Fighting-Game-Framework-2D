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
// File: Input.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines Input class.
// ================================================ //

#ifndef __INPUT_HPP__
#define __INPUT_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

typedef unsigned long long ButtonValue;

// ================================================ //

// Holds the status for all input buttons/keys for a Player. 
// Loads the button map from a .bmap file.
class Input
{
public:
	// Sets all key states to false, and loads the button map.
	Input(const std::string& bmap);

	// Empty destructor.
	~Input(void);

	// All types of input a Player can receive.
	enum{
		BUTTON_UP = 0,
		BUTTON_DOWN,
		BUTTON_LEFT,
		BUTTON_RIGHT,

		BUTTON_START,
		BUTTON_SELECT, // such as A button, for menus (will be a duplicate)
		BUTTON_BACK,

		BUTTON_LP,

		NUM_BUTTONS
	};

	// Player can move with the directional pad or the joystick.
	enum MovementMode{
		JOYSTICK = 0,
		DPAD
	};

	// Parses all keyboard and button maps, as well as the deadzone.
	void loadButtonMap(const std::string& file);

	// Sets all button states to false (not pressed).
	void resetAllButtons(void);

	// Getters

	// Returns true if the specified button is pressed.
	const bool getButton(const int button) const;

	// Returns true if a button is reactivated.
	const bool getReactivated(const int button) const;

	// Returns the value of the mapped button. Returns the keyboard value if 
	// gamepad is false, and the gamepad value if gamepad is true.
	const ButtonValue getMappedButton(const int button, const bool gamepad = false) const;

	// Returns the input value (e.g., BUTTON_LEFT or BUTTON_RIGHT) associated 
	// with the mapped input key/button parameter button.
	// O(n) complexity, since it must search for match.
	const int SDLButtonToMappedButton(const int button, const bool gamepad = false);

	// Returns a pointer to the SDL_GameController held by this Input.
	SDL_GameController* getPad(void) const;

	// Returns the instance ID of the gamepad. Returns -1 if there is no valid gamepad.
	const int getPadID(void) const;

	// Returns the circular range of the deadzone for the gamepad.
	const int getPadDeadzone(void) const;

	// Returns either JOYSTICK or DPAD.
	const int getMovementMode(void) const;

	// Setters

	// Sets the state of a button.
	void setButton(const int button, const bool state);

	// Sets the reactivation status of a button.
	void setReactivated(const int button, const bool state);

	// Sets the gamepad to be used by this Input.
	void setPad(SDL_GameController* pad);

	// Sets the gamepad's deadzone.
	void setPadDeadzone(const int deadzone);

	// Sets movement mode to either JOYSTICK or DPAD.
	void setMovementMode(const int movementMode);
	
private:
	// State of each button (true = pushed, false = released).
	bool m_buttons[NUM_BUTTONS];

	// True if the button has been released since the last press.
	bool m_reactivated[NUM_BUTTONS];

	ButtonValue m_keyboardMap[NUM_BUTTONS];
	ButtonValue m_gamepadMap[NUM_BUTTONS];
	SDL_GameController* m_pad;
	int m_padDeadzone;
	int m_movementMode;
};

// ================================================ //

// Getters

inline const bool Input::getButton(const int button) const{
	return m_buttons[button];
}

inline const bool Input::getReactivated(const int button) const{
	return m_reactivated[button];
}

inline SDL_GameController* Input::getPad(void) const{
	return m_pad;
}

inline const ButtonValue Input::getMappedButton(const int button, const bool gamepad) const{
	return (gamepad == true) ? m_gamepadMap[button] : m_keyboardMap[button];
}

inline const int Input::getPadDeadzone(void) const{
	return m_padDeadzone;
}

inline const int Input::getMovementMode(void) const{
	return m_movementMode;
}

// Setters

inline void Input::setButton(const int button, const bool state){
	m_buttons[button] = state;
}

inline void Input::setReactivated(const int button, const bool state){
	m_reactivated[button] = state;
}

inline void Input::setPad(SDL_GameController* pad){
	m_pad = pad;
}

inline void Input::setPadDeadzone(const int deadzone){
	m_padDeadzone = deadzone;
}

inline void Input::setMovementMode(const int movementMode){
	m_movementMode = movementMode;
}

// ================================================ //

#endif

// ================================================ //