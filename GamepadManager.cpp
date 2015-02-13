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
// File: GamepadManager.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements GamepadManager singleton class.
// ================================================ //

#include "GamepadManager.hpp"
#include "Engine.hpp"
#include "PlayerManager.hpp"
#include "Input.hpp"

// ================================================ //

template<> GamepadManager* Singleton<GamepadManager>::msSingleton = nullptr;

// ================================================ //

GamepadManager::GamepadManager(void) :
m_gamepads()
{

}

// ================================================ //

GamepadManager::~GamepadManager(void)
{

}

// ================================================ //

int GamepadManager::addPad(const int id)
{
	Log::getSingletonPtr()->logMessage("Adding gamepad...");

	// See if it's a gamepad.
	if (SDL_IsGameController(id)){
		Gamepad gamepad;

		gamepad.pad = SDL_GameControllerOpen(id);
		if (gamepad.pad){

			// Get the actual instance ID of the device.
			SDL_Joystick* joy = SDL_JoystickOpen(id);
			gamepad.id = SDL_JoystickInstanceID(joy);
			Log::getSingletonPtr()->logMessage("Gamepad has ID " + Engine::toString(gamepad.id));

			m_gamepads.push_back(gamepad);

			SDL_JoystickClose(joy);
			return gamepad.id;
		}
	}

	Log::getSingletonPtr()->logMessage("ERROR: Failed to add gamepad");
	return -1;
}

// ================================================ //

void GamepadManager::removePad(const int id)
{
	Log::getSingletonPtr()->logMessage("Removing gamepad with ID " + Engine::toString(id) + "...");

	for (GamepadList::iterator itr = m_gamepads.begin();
		itr != m_gamepads.end();
		++itr){
		// Find the right gamepad instance ID.
		if (itr->id == id){
			// Remove the controller from SDL and manager.
			SDL_GameControllerClose(itr->pad);
			itr = m_gamepads.erase(itr);
			Log::getSingletonPtr()->logMessage("Gamepad successfully removed");
			return;
		}
	}

	Log::getSingletonPtr()->logMessage("ERROR: Gamepad not found");
}

// ================================================ //

void GamepadManager::addAllConnectedPads(void)
{
	Log::getSingletonPtr()->logMessage("Adding all connected gamepads...");

	for (int i = 0; i < SDL_NumJoysticks(); ++i){
		this->addPad(i);
	}
}

// ================================================ //