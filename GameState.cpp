// ================================================ //

#include "GameState.hpp"
#include "Engine.hpp"
#include "ObjectManager.hpp"
#include "PlayerManager.hpp"
#include "PlayerData.hpp"
#include "StageManager.hpp"
#include "Camera.hpp"
#include "Input.hpp"
#include "Config.hpp"
#include "MessageRouter.hpp"
#include "Server.hpp"
#include "GamepadManager.hpp"

// ================================================ //

GameState::GameState(void) :
m_bQuit(false),
m_pObjectManager(new ObjectManager())
{

}

// ================================================ //

GameState::~GameState(void)
{

}

// ================================================ //

void GameState::enter(void)
{
	Log::getSingletonPtr()->logMessage("Entering GameState...");
}

// ================================================ //

void GameState::exit(void)
{
	Log::getSingletonPtr()->logMessage("Exiting GameState...");
	m_bQuit = false;
}

// ================================================ //

bool GameState::pause(void)
{
	Log::getSingletonPtr()->logMessage("Pausing GameState...");

	return true;
}

// ================================================ //

void GameState::resume(void)
{
	Log::getSingletonPtr()->logMessage("Resuming GameState...");
}

// ================================================ //

void GameState::handleInput(SDL_Event& e)
{
	// Acquire a pointer to the player under the control of the current gamepad here (avoids copied & pasted code below)
	Player* player = nullptr;
	if (e.type == SDL_CONTROLLERBUTTONDOWN ||
		e.type == SDL_CONTROLLERBUTTONUP ||
		e.type == SDL_CONTROLLERAXISMOTION){
		player = (e.cdevice.which == PlayerManager::getSingletonPtr()->getRedPlayerInput()->getPadID()) ?
			PlayerManager::getSingletonPtr()->getRedPlayer() : (e.cdevice.which == PlayerManager::getSingletonPtr()->getBluePlayerInput()->getPadID()) ?
			PlayerManager::getSingletonPtr()->getBluePlayer() : nullptr;

		if (player == nullptr){
			Log::getSingletonPtr()->logMessage("WARNING: Unregistered gamepad sending input (ID: " + Engine::toString(e.cdevice.which) + ")");
			return;
		}
	}

	if (e.type == SDL_KEYDOWN){

		// Mapped buttons
		// Red Player
		if (e.key.keysym.sym == PlayerManager::getSingletonPtr()->getRedPlayerInput()->getMappedButton(Input::BUTTON_LEFT)){
			PlayerManager::getSingletonPtr()->getRedPlayerInput()->setButton(Input::BUTTON_LEFT, true);
		}
		else if (e.key.keysym.sym == PlayerManager::getSingletonPtr()->getRedPlayerInput()->getMappedButton(Input::BUTTON_RIGHT)){
			PlayerManager::getSingletonPtr()->getRedPlayerInput()->setButton(Input::BUTTON_RIGHT, true);
		}

		// Blue Player
		if (e.key.keysym.sym == PlayerManager::getSingletonPtr()->getBluePlayerInput()->getMappedButton(Input::BUTTON_LEFT)){
			PlayerManager::getSingletonPtr()->getBluePlayerInput()->setButton(Input::BUTTON_LEFT, true);
		}
		else if (e.key.keysym.sym == PlayerManager::getSingletonPtr()->getBluePlayerInput()->getMappedButton(Input::BUTTON_RIGHT)){
			PlayerManager::getSingletonPtr()->getBluePlayerInput()->setButton(Input::BUTTON_RIGHT, true);
		}

		// Hard-coded keys
		switch (e.key.keysym.sym){
		default:

			break;

		case SDLK_UP:
			MessageRouter::getSingletonPtr()->routeMessage(
				MessageType::TYPE_ACTIVATE, PlayerManager::getSingletonPtr()->getRedPlayer()->getID(),
				PlayerManager::getSingletonPtr()->getBluePlayer()->getID(),
				1000);
			break;

		case SDLK_r:
			// Reload fighter settings
			StageManager::getSingletonPtr()->reload();
			PlayerManager::getSingletonPtr()->reload();
			break;

		case SDLK_p:
			PlayerManager::getSingletonPtr()->getRedPlayer()->toggleDrawHitboxes();
			PlayerManager::getSingletonPtr()->getBluePlayer()->toggleDrawHitboxes();
			break;

		case SDLK_ESCAPE:
			m_bQuit = true;
			break;
		}
	}
	else if (e.type == SDL_KEYUP){

		// Mapped buttons
		// Red Player
		if (e.key.keysym.sym == PlayerManager::getSingletonPtr()->getRedPlayerInput()->getMappedButton(Input::BUTTON_LEFT)){
			PlayerManager::getSingletonPtr()->getRedPlayerInput()->setButton(Input::BUTTON_LEFT, false);
		}
		else if (e.key.keysym.sym == PlayerManager::getSingletonPtr()->getRedPlayerInput()->getMappedButton(Input::BUTTON_RIGHT)){
			PlayerManager::getSingletonPtr()->getRedPlayerInput()->setButton(Input::BUTTON_RIGHT, false);
		}

		// Blue Player
		if (e.key.keysym.sym == PlayerManager::getSingletonPtr()->getBluePlayerInput()->getMappedButton(Input::BUTTON_LEFT)){
			PlayerManager::getSingletonPtr()->getBluePlayerInput()->setButton(Input::BUTTON_LEFT, false);
		}
		else if (e.key.keysym.sym == PlayerManager::getSingletonPtr()->getBluePlayerInput()->getMappedButton(Input::BUTTON_RIGHT)){
			PlayerManager::getSingletonPtr()->getBluePlayerInput()->setButton(Input::BUTTON_RIGHT, false);
		}
	}

	// Gamepad input
	if (e.type == SDL_CONTROLLERBUTTONDOWN){
		printf("[Gamepad Button ID]: %-5d(Gamepad ID: %d)\n", e.cbutton.button, e.cdevice.which);

		if (e.cbutton.button == player->getInput()->getMappedButton(Input::BUTTON_LEFT, true)){
			player->getInput()->setButton(Input::BUTTON_LEFT, true);
			player->getInput()->setMovementMode(Input::MovementMode::DPAD);
		}
		else if (e.cbutton.button == player->getInput()->getMappedButton(Input::BUTTON_RIGHT, true)){
			player->getInput()->setButton(Input::BUTTON_RIGHT, true);
			player->getInput()->setMovementMode(Input::MovementMode::DPAD);
		}
	}
	else if (e.type == SDL_CONTROLLERBUTTONUP){
		if (e.cbutton.button == player->getInput()->getMappedButton(Input::BUTTON_LEFT, true)){
			player->getInput()->setButton(Input::BUTTON_LEFT, false);
			player->getInput()->setMovementMode(Input::MovementMode::DPAD);
		}
		else if (e.cbutton.button == player->getInput()->getMappedButton(Input::BUTTON_RIGHT, true)){
			player->getInput()->setButton(Input::BUTTON_RIGHT, false);
			player->getInput()->setMovementMode(Input::MovementMode::DPAD);
		}
		else if (e.cbutton.button == player->getInput()->getMappedButton(Input::BUTTON_START, true)){
			m_bQuit = true;
		}
	}
	else if (e.type == SDL_CONTROLLERAXISMOTION){
		Sint16 value = SDL_GameControllerGetAxis(GamepadManager::getSingletonPtr()->getPad(e.cdevice.which), static_cast<SDL_GameControllerAxis>(1));
		const int deadzone = player->getInput()->getPadDeadzone();

		// First see if we should not process the joystick if the player is using the D-pad
		if (player->getInput()->getMovementMode() == Input::MovementMode::DPAD){
			if (value < -deadzone || value > deadzone){
				player->getInput()->setMovementMode(Input::MovementMode::JOYSTICK);
			}
			else{
				value = SDL_GameControllerGetAxis(GamepadManager::getSingletonPtr()->getPad(e.cdevice.which), static_cast<SDL_GameControllerAxis>(0));
				if (value < -deadzone || value > deadzone){
					player->getInput()->setMovementMode(Input::MovementMode::JOYSTICK);
				}
				else{
					// The joystick is not out of the deadzone, so remain in DPAD mode
					return;
				}
			}
		}

		// Y-axis
		value = SDL_GameControllerGetAxis(GamepadManager::getSingletonPtr()->getPad(e.cdevice.which), static_cast<SDL_GameControllerAxis>(1));
		if (value < -deadzone){
			player->getInput()->setButton(Input::BUTTON_UP, true);
		}
		else if (value > deadzone){
			player->getInput()->setButton(Input::BUTTON_DOWN, true);
		}
		else{
			player->getInput()->setButton(Input::BUTTON_UP, false);
			player->getInput()->setButton(Input::BUTTON_DOWN, false);
		}

		// X-axis
		value = SDL_GameControllerGetAxis(GamepadManager::getSingletonPtr()->getPad(e.cdevice.which), static_cast<SDL_GameControllerAxis>(0));
		if (value < -deadzone){
			player->getInput()->setButton(Input::BUTTON_LEFT, true);
		}
		else if (value > deadzone){
			player->getInput()->setButton(Input::BUTTON_RIGHT, true);
		}
		else{
			player->getInput()->setButton(Input::BUTTON_LEFT, false);
			player->getInput()->setButton(Input::BUTTON_RIGHT, false);
		}

		// Process GUI
		// ...
	}
}

// ================================================ //

void GameState::update(double dt)
{
	if (m_bQuit == true){
		this->popAppState();
	}

	SDL_Event e;

	while (SDL_PollEvent(&e)){
		switch (e.type){
		default:
			break;

		case SDL_QUIT:
			m_bQuit = true;
			break;

		case SDL_KEYDOWN:
		case SDL_KEYUP:
			this->handleInput(e);
			break;

		case SDL_WINDOWEVENT:
			if (e.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
				Engine::getSingletonPtr()->setWindowFocused(false);
			break;

			// Gamepad events
		case SDL_CONTROLLERDEVICEADDED:
		{
										  int id = GamepadManager::getSingletonPtr()->addPad(e.cdevice.which);

										  // Assign the new controller to the first open slot
										  if (PlayerManager::getSingletonPtr()->getRedPlayerInput()->getPadID() == -1){
											  PlayerManager::getSingletonPtr()->getRedPlayerInput()->setPad(
												  GamepadManager::getSingletonPtr()->getPad(id));
										  }
										  else if (PlayerManager::getSingletonPtr()->getBluePlayerInput()->getPadID() == -1){
											  PlayerManager::getSingletonPtr()->getBluePlayerInput()->setPad(
												  GamepadManager::getSingletonPtr()->getPad(id));
										  }
		}
			break;

		case SDL_CONTROLLERDEVICEREMOVED:
			// The player's pad pointer will be gone, so assign it to null to prevent undefined behavior
			if (PlayerManager::getSingletonPtr()->getRedPlayerInput()->getPadID() == -1){
				PlayerManager::getSingletonPtr()->getRedPlayerInput()->setPad(nullptr);
			}
			if (PlayerManager::getSingletonPtr()->getBluePlayerInput()->getPadID() == -1){
				PlayerManager::getSingletonPtr()->getBluePlayerInput()->setPad(nullptr);
			}

			GamepadManager::getSingletonPtr()->removePad(e.cdevice.which);
			break;

		case SDL_CONTROLLERBUTTONDOWN:
		case SDL_CONTROLLERBUTTONUP:
			this->handleInput(e);
			break;

		case SDL_CONTROLLERAXISMOTION:
			this->handleInput(e);
			break;
		}
	}

	Engine::getSingletonPtr()->clearRenderer();

	// Update and render all game objects and players
	StageManager::getSingletonPtr()->update(dt);
	m_pObjectManager->update(dt);
	PlayerManager::getSingletonPtr()->update(dt);

	Engine::getSingletonPtr()->renderPresent();
}

// ================================================ //