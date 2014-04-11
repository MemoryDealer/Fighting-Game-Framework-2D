// ================================================ //

#include "MenuStateImpl.hpp"
#include "Engine.hpp"
#include "PlayerManager.hpp"
#include "PlayerData.hpp"
#include "Background.hpp"
#include "Input.hpp"
#include "Config.hpp"
#include "MessageRouter.hpp"
#include "Server.hpp"

// ================================================ //

MenuStateImpl::MenuStateImpl(void)
	:	m_bQuit(false),
		m_pObjectManager(new ObjectManager())
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

	m_pObjectManager->addObject(new Background(0));
	m_pObjectManager->getObject(0)->setTextureFile("D:/2D/B/cave.jpg");

	new PlayerManager(Fighter::CORPSE_EXPLOSION, Fighter::CORPSE_EXPLOSION);

	new Server();
}

// ================================================ //

void MenuStateImpl::exit(void)
{
	Log::getSingletonPtr()->logMessage("Exiting MenuState...");

	delete PlayerManager::getSingletonPtr();

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
			delete PlayerManager::getSingletonPtr();
			new PlayerManager(Fighter::CORPSE_EXPLOSION, Fighter::CORPSE_EXPLOSION);
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
		}
	}
}

// ================================================ //

void MenuStateImpl::update(double dt)
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

	m_pObjectManager->update(dt);
	PlayerManager::getSingletonPtr()->update(dt);

	Engine::getSingletonPtr()->renderPresent();
}

// ================================================ //