// ================================================ //

#include "GamepadManager.hpp"
#include "Engine.hpp"

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

bool GamepadManager::addPad(const int id)
{
	Log::getSingletonPtr()->logMessage("Adding gamepad with device ID " + Engine::toString(id) + "...");

	// See if it's a gamepad
	if (SDL_IsGameController(id)){
		Gamepad gamepad;

		// Open the gamepad
		gamepad.pad = SDL_GameControllerOpen(id);
		if (gamepad.pad){

			// Get the actual instance ID of the device
			SDL_Joystick* joy = SDL_JoystickOpen(id);
			gamepad.id = SDL_JoystickInstanceID(joy);

			// Add gamepad to the PadList
			m_gamepads.push_back(gamepad);

			SDL_JoystickClose(joy);
			return true;
		}
	}

	Log::getSingletonPtr()->logMessage("ERROR: Failed to add gamepad");
	return false;
}

// ================================================ //

void GamepadManager::removePad(const int id)
{
	Log::getSingletonPtr()->logMessage("Removing gamepad with ID " + Engine::toString(id) + "...");

	for (GamepadList::iterator itr = m_gamepads.begin();
		itr != m_gamepads.end();
		++itr){
		if (itr->id == id){
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