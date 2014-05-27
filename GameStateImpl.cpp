// ================================================ //

#include "GameStateImpl.hpp"
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
	if(e.type == SDL_KEYDOWN){
		switch(e.key.keysym.sym){
		default:
			
			break;

		case SDLK_LEFT: // this value should eventually be retrieved from the Player class
			PlayerManager::getSingletonPtr()->getRedPlayer()->setInput(Input::BUTTON_LEFT, true);
			break;

		case SDLK_RIGHT:
			PlayerManager::getSingletonPtr()->getRedPlayer()->setInput(Input::BUTTON_RIGHT, true);
			break;

		case SDLK_UP:
			MessageRouter::getSingletonPtr()->routeMessage(
				MessageType::TYPE_ACTIVATE, PlayerManager::getSingletonPtr()->getRedPlayer()->getID(),
				PlayerManager::getSingletonPtr()->getBluePlayer()->getID(),
				1000);
			break;

		case SDLK_r:
			// Reload fighter settings
			PlayerManager::getSingletonPtr()->reload();
			StageManager::getSingletonPtr()->reload();
			break;

		case SDLK_j:
			Camera::getSingletonPtr()->moveX = -1;
			break;

		case SDLK_k:
			Camera::getSingletonPtr()->moveX = 1;
			break;

		case SDLK_ESCAPE:
			m_bQuit = true;
			break;
		}
	}
	else if(e.type == SDL_KEYUP){
		switch(e.key.keysym.sym){
		default:
			
			break;

		case SDLK_LEFT:
			PlayerManager::getSingletonPtr()->getRedPlayer()->setInput(Input::BUTTON_LEFT, false);
			break;

		case SDLK_RIGHT:
			PlayerManager::getSingletonPtr()->getRedPlayer()->setInput(Input::BUTTON_RIGHT, false);
			break;

		case SDLK_j:
			Camera::getSingletonPtr()->moveX = 0;
			break;

		case SDLK_k:
			Camera::getSingletonPtr()->moveX = 0;
			break;
		}
	}
}

// ================================================ //

void GameStateImpl::update(double dt)
{
	SDL_Event e;

	while(SDL_PollEvent(&e)){
		switch(e.type){
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
			if(e.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
				Engine::getSingletonPtr()->setWindowFocused(false);
			break;
		}
	}

	Server::getSingletonPtr()->testRecv();

	Engine::getSingletonPtr()->clearRenderer();

	// Update and render all game objects and players
	StageManager::getSingletonPtr()->update(dt);
	m_pObjectManager->update(dt);
	PlayerManager::getSingletonPtr()->update(dt);

	Engine::getSingletonPtr()->renderPresent();
}

// ================================================ //