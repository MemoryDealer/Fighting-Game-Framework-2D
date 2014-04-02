// ================================================ //

#include "MenuStateImpl.hpp"
#include "Engine.hpp"
#include "PlayerManager.hpp"
#include "PlayerStates.hpp"
#include "Background.hpp"
#include "Input.hpp"
#include "Config.hpp"

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

	new PlayerManager(Fighter::LORD_GRISHNAKH, Fighter::LORD_GRISHNAKH);
	PlayerManager::getSingletonPtr()->getRedPlayer()->setPosition(0, 215);
}

// ================================================ //

void MenuStateImpl::exit(void)
{
	Log::getSingletonPtr()->logMessage("Exiting MenuState...");

	delete PlayerManager::getSingletonPtr();
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

void MenuStateImpl::update(double dt)
{
	SDL_Event e;
	unsigned int input;

	while(SDL_PollEvent(&e)){
		switch(e.type){
		default:
			break;

		case SDL_QUIT:
			m_bQuit = true;
			break;

		case SDL_KEYDOWN:
			if(e.key.keysym.sym == SDLK_ESCAPE)
				m_bQuit = true;
			if(e.key.keysym.sym == SDLK_LEFT)
				input = Input::BUTTON_LEFT;
			break;

		case SDL_WINDOWEVENT:
			if(e.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
				Engine::getSingletonPtr()->setWindowFocused(false);
			break;
		}
	}

	Engine::getSingletonPtr()->clearRenderer();

	m_pObjectManager->update(dt);
	PlayerManager::getSingletonPtr()->getRedPlayer()->update(dt);
	PlayerManager::getSingletonPtr()->getBluePlayer()->update(dt);

	Engine::getSingletonPtr()->renderPresent();
}

// ================================================ //