// ================================================ //

#include "GameStateImpl.hpp"
#include "Engine.hpp"
#include "ObjectManager.hpp"
#include "GameManager.hpp"
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

GameStateImpl::GameStateImpl(void)
	:	m_bQuit(false),
		m_pObjectManager(new ObjectManager())
{
	
}

// ================================================ //

GameStateImpl::~GameStateImpl(void)
{

}

// ================================================ //

void GameStateImpl::enter(void)
{
	Log::getSingletonPtr()->logMessage("Entering GameState...");
}

// ================================================ //

void GameStateImpl::exit(void)
{
	Log::getSingletonPtr()->logMessage("Exiting GameState...");
	m_bQuit = false;
}

// ================================================ //

bool GameStateImpl::pause(void)
{
	Log::getSingletonPtr()->logMessage("Pausing GameState...");

	return true;
}

// ================================================ //

void GameStateImpl::resume(void)
{
	Log::getSingletonPtr()->logMessage("Resuming GameState...");
}

// ================================================ //

void GameStateImpl::handleInput(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN){

		// Mapped buttons
		// Red Player
		if (e.key.keysym.sym == PlayerManager::getSingletonPtr()->getRedPlayerInput()->getMappedButton(Input::BUTTON_LEFT)){
			PlayerManager::getSingletonPtr()->getRedPlayer()->getInput()->setButton(Input::BUTTON_LEFT, true);
		}
		else if (e.key.keysym.sym == PlayerManager::getSingletonPtr()->getRedPlayerInput()->getMappedButton(Input::BUTTON_RIGHT)){
			PlayerManager::getSingletonPtr()->getRedPlayer()->getInput()->setButton(Input::BUTTON_RIGHT, true);
		}

		// Blue Player
		if (e.key.keysym.sym == PlayerManager::getSingletonPtr()->getBluePlayerInput()->getMappedButton(Input::BUTTON_LEFT)){
			PlayerManager::getSingletonPtr()->getBluePlayer()->getInput()->setButton(Input::BUTTON_LEFT, true);
		}
		else if (e.key.keysym.sym == PlayerManager::getSingletonPtr()->getBluePlayerInput()->getMappedButton(Input::BUTTON_RIGHT)){
			PlayerManager::getSingletonPtr()->getBluePlayer()->getInput()->setButton(Input::BUTTON_RIGHT, true);
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
			PlayerManager::getSingletonPtr()->getRedPlayer()->getInput()->setButton(Input::BUTTON_LEFT, false);
		}
		else if (e.key.keysym.sym == PlayerManager::getSingletonPtr()->getRedPlayerInput()->getMappedButton(Input::BUTTON_RIGHT)){
			PlayerManager::getSingletonPtr()->getRedPlayer()->getInput()->setButton(Input::BUTTON_RIGHT, false);
		}

		// Blue Player
		if (e.key.keysym.sym == PlayerManager::getSingletonPtr()->getBluePlayerInput()->getMappedButton(Input::BUTTON_LEFT)){
			PlayerManager::getSingletonPtr()->getBluePlayer()->getInput()->setButton(Input::BUTTON_LEFT, false);
		}
		else if (e.key.keysym.sym == PlayerManager::getSingletonPtr()->getBluePlayerInput()->getMappedButton(Input::BUTTON_RIGHT)){
			PlayerManager::getSingletonPtr()->getBluePlayer()->getInput()->setButton(Input::BUTTON_RIGHT, false);
		}

		// Hard-coded keys
		/*switch (e.key.keysym.sym){
		default:
			
			break;
		}*/
	}

	// Gamepad input
	if (e.type == SDL_CONTROLLERBUTTONDOWN){
		printf("(Gamepad ID): %d\n", e.cdevice.which);

		// Red Player
		if (e.cdevice.which == PlayerManager::getSingletonPtr()->getRedPlayerInput()->getPadID()){
			if (e.cbutton.button == PlayerManager::getSingletonPtr()->getRedPlayerInput()->getMappedButton(Input::BUTTON_LEFT, true)){
				PlayerManager::getSingletonPtr()->getRedPlayer()->getInput()->setButton(Input::BUTTON_LEFT, true);
			}
			else if (e.cbutton.button == PlayerManager::getSingletonPtr()->getRedPlayerInput()->getMappedButton(Input::BUTTON_RIGHT, true)){
				PlayerManager::getSingletonPtr()->getRedPlayer()->getInput()->setButton(Input::BUTTON_RIGHT, true);
			}
		}
		// Blue Player
		else if (e.cdevice.which == PlayerManager::getSingletonPtr()->getBluePlayerInput()->getPadID()){
			if (e.cbutton.button == PlayerManager::getSingletonPtr()->getBluePlayerInput()->getMappedButton(Input::BUTTON_LEFT, true)){
				PlayerManager::getSingletonPtr()->getBluePlayer()->getInput()->setButton(Input::BUTTON_LEFT, true);
			}
			else if (e.cbutton.button == PlayerManager::getSingletonPtr()->getBluePlayerInput()->getMappedButton(Input::BUTTON_RIGHT, true)){
				PlayerManager::getSingletonPtr()->getBluePlayer()->getInput()->setButton(Input::BUTTON_RIGHT, true);
			}
		}
	}
	else if (e.type == SDL_CONTROLLERBUTTONUP){
		// Red Player
		if (e.cdevice.which == PlayerManager::getSingletonPtr()->getRedPlayerInput()->getPadID()){
			if (e.cbutton.button == PlayerManager::getSingletonPtr()->getRedPlayerInput()->getMappedButton(Input::BUTTON_LEFT, true)){
				PlayerManager::getSingletonPtr()->getRedPlayer()->getInput()->setButton(Input::BUTTON_LEFT, false);
			}
			else if (e.cbutton.button == PlayerManager::getSingletonPtr()->getRedPlayerInput()->getMappedButton(Input::BUTTON_RIGHT, true)){
				PlayerManager::getSingletonPtr()->getRedPlayer()->getInput()->setButton(Input::BUTTON_RIGHT, false);
			}
			else if (e.cbutton.button == PlayerManager::getSingletonPtr()->getRedPlayerInput()->getMappedButton(Input::BUTTON_START, true)){
				m_bQuit = true;
			}
		}
		// Blue Player
		else if (e.cdevice.which == PlayerManager::getSingletonPtr()->getBluePlayerInput()->getPadID()){
			if (e.cbutton.button == PlayerManager::getSingletonPtr()->getBluePlayerInput()->getMappedButton(Input::BUTTON_LEFT, true)){
				PlayerManager::getSingletonPtr()->getBluePlayer()->getInput()->setButton(Input::BUTTON_LEFT, false);
			}
			else if (e.cbutton.button == PlayerManager::getSingletonPtr()->getBluePlayerInput()->getMappedButton(Input::BUTTON_RIGHT, true)){
				PlayerManager::getSingletonPtr()->getBluePlayer()->getInput()->setButton(Input::BUTTON_RIGHT, false);
			}
		}
	}
}

// ================================================ //

void GameStateImpl::update(double dt)
{
	SDL_Event e;

	while(SDL_PollEvent(&e)){
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
			printf("[Gamepad Button ID]: %d\n", e.cbutton.button);
			this->handleInput(e);
			break;
		}
	}

	Engine::getSingletonPtr()->clearRenderer();

	// Update and render all game objects and players
	StageManager::getSingletonPtr()->update(dt);
	m_pObjectManager->update(dt);
	PlayerManager::getSingletonPtr()->update(dt);

	// Update with any authoritative information from server
	switch (GameManager::getSingletonPtr()->getMode()){
	case GameMode::LOCAL:

		break;

	case GameMode::CLIENT:

		break;

	case GameMode::SERVER:

		break;
	}

	printf("RedID: %d\tBlueID: %d\n", PlayerManager::getSingletonPtr()->getRedPlayerInput()->getPadID(),
		PlayerManager::getSingletonPtr()->getBluePlayerInput()->getPadID());

	Engine::getSingletonPtr()->renderPresent();
}

// ================================================ //