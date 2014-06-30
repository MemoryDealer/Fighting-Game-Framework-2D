// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
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