// ================================================ //

#include "MenuStateImpl.hpp"
#include "Engine.hpp"
#include "PlayerManager.hpp"
#include "PlayerData.hpp"
#include "Background.hpp"
#include "Input.hpp"
#include "Config.hpp"

// ================================================ //

MenuStateImpl::MenuStateImpl(void)
	:	m_bQuit(false),
		m_pObjectManager(new ObjectManager()),
		m_input(Input::NONE)
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

void MenuStateImpl::handleInput(SDL_Event& e)
{
	m_input = Input::NONE;

	if(e.type == SDL_KEYDOWN){
		switch(e.key.keysym.sym){
		default:
			
			break;

		case SDLK_LEFT:
			m_input = Input::BUTTON_LEFT_PUSHED;
			break;

		case SDLK_RIGHT:
			m_input = Input::BUTTON_RIGHT_PUSHED;
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
			m_input = Input::BUTTON_LEFT_RELEASED;
			break;

		case SDLK_RIGHT:
			m_input = Input::BUTTON_RIGHT_RELEASED;
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
			if(e.key.keysym.sym == SDLK_f)
				dt *= 0.2;
		case SDL_KEYUP:
			this->handleInput(e);
			break;

		case SDL_WINDOWEVENT:
			if(e.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
				Engine::getSingletonPtr()->setWindowFocused(false);
			break;
		}
	}

	Engine::getSingletonPtr()->clearRenderer();

	m_pObjectManager->update(dt);
	PlayerManager::getSingletonPtr()->update(dt, m_input);

	Engine::getSingletonPtr()->renderPresent();
}

// ================================================ //