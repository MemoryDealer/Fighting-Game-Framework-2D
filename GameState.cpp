// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: GameState.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements GameState class.
// ================================================ //

#include "GameState.hpp"
#include "Engine.hpp"
#include "ObjectManager.hpp"
#include "PlayerManager.hpp"
#include "StageManager.hpp"
#include "Camera.hpp"
#include "Input.hpp"
#include "Config.hpp"
#include "MessageRouter.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "NetMessage.hpp"
#include "GamepadManager.hpp"
#include "GameManager.hpp"

// ================================================ //

GameState::GameState(void) :
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

void GameState::handleInputDt(SDL_Event& e, double dt)
{
	// Acquire a pointer to the player under the control of the current gamepad 
	// here (avoids copied & pasted code below).
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
		// Process mapped buttons.
		// Red Player.
		if (GameManager::getSingletonPtr()->getState() == GameManager::PLAYING_RED){
			switch (PlayerManager::getSingletonPtr()->getRedPlayerInput()->SDLButtonToMappedButton(e.key.keysym.sym)){
			default:
				break;

			case Input::BUTTON_LEFT:
				PlayerManager::getSingletonPtr()->getRedPlayerInput()->setButton(Input::BUTTON_LEFT, true);
				if (GameManager::getSingletonPtr()->getMode() == GameManager::CLIENT){
					Client::getSingletonPtr()->sendInput(Input::BUTTON_LEFT, true, dt);
				}
				break;

			case Input::BUTTON_RIGHT:
				PlayerManager::getSingletonPtr()->getRedPlayerInput()->setButton(Input::BUTTON_RIGHT, true);
				if (GameManager::getSingletonPtr()->getMode() == GameManager::CLIENT){
					Client::getSingletonPtr()->sendInput(Input::BUTTON_RIGHT, true, dt);
				}
				break;
			}
		}

		// Blue Player.
		else if (GameManager::getSingletonPtr()->getState() == GameManager::PLAYING_BLUE){
			switch (PlayerManager::getSingletonPtr()->getBluePlayerInput()->SDLButtonToMappedButton(e.key.keysym.sym)){
			default:
				break;

			case Input::BUTTON_LEFT:
				PlayerManager::getSingletonPtr()->getBluePlayerInput()->setButton(Input::BUTTON_LEFT, true);
				if (GameManager::getSingletonPtr()->getMode() == GameManager::CLIENT){
					Client::getSingletonPtr()->sendInput(Input::BUTTON_LEFT, true, dt);
				}
				break;

			case Input::BUTTON_RIGHT:
				PlayerManager::getSingletonPtr()->getBluePlayerInput()->setButton(Input::BUTTON_RIGHT, true);
				if (GameManager::getSingletonPtr()->getMode() == GameManager::CLIENT){
					Client::getSingletonPtr()->sendInput(Input::BUTTON_RIGHT, true, dt);
				}
				break;
			}
		}
		
		// Process hard-coded keys.
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
			// Reload fighter settings.
			StageManager::getSingletonPtr()->reload();
			PlayerManager::getSingletonPtr()->reload();
			break;

		case SDLK_p:
			//PlayerManager::getSingletonPtr()->getRedPlayer()->toggleDrawHitboxes();
			//PlayerManager::getSingletonPtr()->getBluePlayer()->toggleDrawHitboxes();
			break;

		case SDLK_ESCAPE:
			m_quit = true;
			break;
		}
	}
	else if (e.type == SDL_KEYUP){
		// Process mapped buttons.
		// Red Player.
		if (GameManager::getSingletonPtr()->getState() == GameManager::PLAYING_RED){
			switch (PlayerManager::getSingletonPtr()->getRedPlayerInput()->SDLButtonToMappedButton(e.key.keysym.sym)){
			default:
				break;

			case Input::BUTTON_LEFT:
				PlayerManager::getSingletonPtr()->getRedPlayerInput()->setButton(Input::BUTTON_LEFT, false);
				if (GameManager::getSingletonPtr()->getMode() == GameManager::CLIENT){
					Client::getSingletonPtr()->sendInput(Input::BUTTON_LEFT, false, dt);
				}
				break;

			case Input::BUTTON_RIGHT:
				PlayerManager::getSingletonPtr()->getRedPlayerInput()->setButton(Input::BUTTON_RIGHT, false);
				if (GameManager::getSingletonPtr()->getMode() == GameManager::CLIENT){
					Client::getSingletonPtr()->sendInput(Input::BUTTON_RIGHT, false, dt);
				}
				break;
			}
		}

		// Blue Player.
		else if (GameManager::getSingletonPtr()->getState() == GameManager::PLAYING_BLUE){
			switch (PlayerManager::getSingletonPtr()->getBluePlayerInput()->SDLButtonToMappedButton(e.key.keysym.sym)){
			default:
				break;

			case Input::BUTTON_LEFT:
				PlayerManager::getSingletonPtr()->getBluePlayerInput()->setButton(Input::BUTTON_LEFT, false);
				if (GameManager::getSingletonPtr()->getMode() == GameManager::CLIENT){
					Client::getSingletonPtr()->sendInput(Input::BUTTON_LEFT, false, dt);
				}
				break;

			case Input::BUTTON_RIGHT:
				PlayerManager::getSingletonPtr()->getBluePlayerInput()->setButton(Input::BUTTON_RIGHT, false);
				if (GameManager::getSingletonPtr()->getMode() == GameManager::CLIENT){
					Client::getSingletonPtr()->sendInput(Input::BUTTON_RIGHT, false, dt);
				}
				break;
			}
		}
	}

	// Process gamepad input.
	if (e.type == SDL_CONTROLLERBUTTONDOWN){
		printf("[Gamepad Button ID]: %-5d(Gamepad ID: %d)\n", e.cbutton.button, e.cdevice.which);

		switch (player->getInput()->SDLButtonToMappedButton(e.cbutton.button, true)){
		default:
			break;

		case Input::BUTTON_LEFT:
			player->getInput()->setButton(Input::BUTTON_LEFT, true);
			player->getInput()->setMovementMode(Input::MovementMode::DPAD);
			break;

		case Input::BUTTON_RIGHT:
			player->getInput()->setButton(Input::BUTTON_RIGHT, true);
			player->getInput()->setMovementMode(Input::MovementMode::DPAD);
			break;
		}
	}
	else if (e.type == SDL_CONTROLLERBUTTONUP){
		switch (player->getInput()->SDLButtonToMappedButton(e.cbutton.button, true)){
		default:
			break;

		case Input::BUTTON_LEFT:
			player->getInput()->setButton(Input::BUTTON_LEFT, false);
			player->getInput()->setMovementMode(Input::MovementMode::DPAD);
			break;

		case Input::BUTTON_RIGHT:
			player->getInput()->setButton(Input::BUTTON_RIGHT, false);
			player->getInput()->setMovementMode(Input::MovementMode::DPAD);
			break;

		case Input::BUTTON_START:
			m_quit = true;
			break;
		}
	}
	else if (e.type == SDL_CONTROLLERAXISMOTION){
		// Process joystick information.
		Sint16 value = SDL_GameControllerGetAxis(GamepadManager::getSingletonPtr()->getPad(e.cdevice.which), static_cast<SDL_GameControllerAxis>(1));
		const int deadzone = player->getInput()->getPadDeadzone();

		// First see if we should not process the joystick if the player is using the D-pad.
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
					// The joystick is not out of the deadzone, so remain in DPAD mode.
					return;
				}
			}
		}

		// Process Y-axis joystick movement.
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

		// Process X-axis joystick movement.
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

		// TODO: Process GUI.
	}
}

// ================================================ //

void GameState::update(double dt)
{
	if (m_quit == true){
		this->popAppState();
		return;
	}

	SDL_Event e;

	while (SDL_PollEvent(&e)){
		switch (e.type){
		default:
			break;

		case SDL_QUIT:
			m_quit = true;
			break;

		case SDL_KEYDOWN:
		case SDL_KEYUP:
			this->handleInputDt(e, dt);
			break;

		case SDL_CONTROLLERDEVICEADDED:
		{
			int id = GamepadManager::getSingletonPtr()->addPad(e.cdevice.which);

			// Assign the new controller to the first open slot.
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
			// The player's pad pointer will be gone, so assign it to null to prevent undefined behavior.
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
			this->handleInputDt(e, dt);
			break;

		case SDL_CONTROLLERAXISMOTION:
			this->handleInputDt(e, dt);
			break;
		}
	}

	Engine::getSingletonPtr()->clearRenderer();

	if (GameManager::getSingletonPtr()->getMode() == GameManager::SERVER){
		switch (Server::getSingletonPtr()->update(dt)){
		default:
			break;
		}
	}
	else if (GameManager::getSingletonPtr()->getMode() == GameManager::CLIENT){
		printf("%d unprocessed inputs.\n", Client::getSingletonPtr()->m_pendingInputs.size());
		switch (Client::getSingletonPtr()->update(dt)){
		default:
			break;

		case NetMessage::UPDATE_RED_PLAYER:
			if (GameManager::getSingletonPtr()->getState() == GameManager::PLAYING_RED){
				RakNet::BitStream bit(Client::getSingletonPtr()->getLastPacket()->data,
					Client::getSingletonPtr()->getLastPacket()->length, false);
				bit.IgnoreBytes(sizeof(RakNet::MessageID));

				Server::PlayerUpdate update;
				bit.Read(update);
				//if (update.inputSeq == Client::getSingletonPtr()->m_inputSequence){
					PlayerManager::getSingletonPtr()->getRedPlayer()->updateFromServer(update);
				//}
			}
			break;

		case NetMessage::UPDATE_BLUE_PLAYER:

			break;

		case NetMessage::UPDATE_PLAYERS:
			{
				RakNet::BitStream bit(Client::getSingletonPtr()->getLastPacket()->data,
					Client::getSingletonPtr()->getLastPacket()->length, false);
				bit.IgnoreBytes(sizeof(RakNet::MessageID));

				RakNet::Time time;
				bit.Read(time);
				//printf("UPDATE (%d)\n", time);

				// Update positions.
				Server::PlayerUpdate red;
				bit.Read(red);
				PlayerManager::getSingletonPtr()->getRedPlayer()->updateFromServer(red);

				Server::PlayerUpdate blue;
				bit.Read(blue);
				PlayerManager::getSingletonPtr()->getBluePlayer()->updateFromServer(blue);
			}
			break;
		}
	}

	// Update and render all game objects and players.
	StageManager::getSingletonPtr()->update(dt);
	m_pObjectManager->update(dt);
	PlayerManager::getSingletonPtr()->update(dt);

	Engine::getSingletonPtr()->renderPresent();
}

// ================================================ //