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