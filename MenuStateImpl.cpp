// ================================================ //

#include "MenuStateImpl.hpp"
#include "Engine.hpp"
#include "GameManager.hpp"
#include "PlayerManager.hpp"
#include "PlayerData.hpp"
#include "StageManager.hpp"
#include "GUIManager.hpp"
#include "GUIMenuState.hpp"
#include "Camera.hpp"
#include "Input.hpp"
#include "Config.hpp"
#include "MessageRouter.hpp"
#include "Server.hpp"
#include "AppState.hpp"
#include "App.hpp"

// ================================================ //

MenuStateImpl::MenuStateImpl(AppState* pMenuState)
	:	m_bQuit(false),
		m_pMenuState(pMenuState)
{

}

// ================================================ //

MenuStateImpl::~MenuStateImpl(void)
{

}

// ================================================ //

void MenuStateImpl::enter(void)
{
	Log::getSingletonPtr()->logMessage("Entering MenuState...");

	// Allocate GameManager
	new GameManager();
	GameManager::getSingletonPtr()->setMode(GameMode::SERVER);

	// Allocate StageManager
	new StageManager();
	StageManager::getSingletonPtr()->load("Data/Stages/test.stage");

	// Allocate PlayerManager
	new PlayerManager();
	PlayerManager::getSingletonPtr()->load("Data/Fighters/corpse-explosion.fighter", "Data/Fighters/corpse-explosion.fighter");

	// Allocate Camera singleton
	new Camera();

	// Allocate Network
	if (GameManager::getSingletonPtr()->getMode() == GameMode::SERVER)
		new Server();

	// Push game state and start it
	//m_pMenuState->pushAppState(m_pMenuState->findByName(GAME_STATE));
}

// ================================================ //

void MenuStateImpl::exit(void)
{
	Log::getSingletonPtr()->logMessage("Exiting MenuState...");

	// m_pObjectManager destructed automatically

	// Free all singletons
	delete GameManager::getSingletonPtr();
	delete StageManager::getSingletonPtr();
	delete PlayerManager::getSingletonPtr();
	delete Camera::getSingletonPtr();
	delete Server::getSingletonPtr();
}

// ================================================ //

bool MenuStateImpl::pause(void)
{
	Log::getSingletonPtr()->logMessage("Pausing MenuState...");

	return true;
}

// ================================================ //

void MenuStateImpl::resume(void)
{
	Log::getSingletonPtr()->logMessage("Resuming MenuState...");
}

// ================================================ //

void MenuStateImpl::handleInput(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN){
		switch (e.key.keysym.sym){
		default:
			break;

		case SDLK_ESCAPE:
			m_pMenuState->popAppState();
			break;

		case SDLK_r:
			GUIManager::getSingletonPtr()->reloadAll();
			break;
		}
	}
}

// ================================================ //

void MenuStateImpl::update(double dt)
{
	SDL_Event e;

	while (SDL_PollEvent(&e)){
		switch (e.type){
		default:
			break;

		case SDL_QUIT:
			m_pMenuState->popAppState();
			break;

		case SDL_KEYDOWN:
		case SDL_KEYUP:
			this->handleInput(e);
			break;

		case SDL_WINDOWEVENT:
			if (e.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
				Engine::getSingletonPtr()->setWindowFocused(false);
			break;
		}
	}

	Engine::getSingletonPtr()->clearRenderer();

	GUIManager::getSingletonPtr()->getMenuState()->update(dt);

	Engine::getSingletonPtr()->renderPresent();
}

// ================================================ //