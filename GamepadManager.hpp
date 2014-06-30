// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: GamepadManager.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines GamepadManager singleton class.
// ================================================ //

#ifndef __GAMEPADMANAGER_HPP__
#define __GAMEPADMANAGER_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

typedef struct{
	SDL_GameController* pad;
	int id;
} Gamepad;

typedef std::vector<Gamepad> GamepadList;

// ================================================ //

// Holds a list of all connected gamepads. Used for easy management
// of gamepads during game states.
class GamepadManager : public Singleton<GamepadManager>
{
public:
	// Empty constructor.
	GamepadManager(void);

	// Empty destructor.
	~GamepadManager(void);

	// Adds a new gamepad to the manager. Finds the instance ID of the pad
	// before adding it and returns it. Returns -1 on failure.
	int addPad(const int id);

	// Removes a gamepad from SDL and the manager.
	void removePad(const int id);

	// Finds all connected gamepads and adds them to the manager.
	void addAllConnectedPads(void);

	// Getters

	// Returns the SDL_GameController pointer for the specified pad ID.
	SDL_GameController* getPad(const int id);

private:
	GamepadList m_gamepads;
};

// ================================================ //

// Getters

inline SDL_GameController* GamepadManager::getPad(const int id){
	for (GamepadList::iterator itr = m_gamepads.begin();
		itr != m_gamepads.end();
		++itr){
		if (itr->id == id){
			return itr->pad;
		}
	}

	return nullptr;
}

// ================================================ //

#endif

// ================================================ //