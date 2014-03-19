// ================================================ //

#include "MenuStateImpl.hpp"
#include "Engine.hpp"

// ================================================ //

MenuStateImpl::MenuStateImpl(void)
	:	m_bQuit(false)
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
}

// ================================================ //

void MenuStateImpl::exit(void)
{
	Log::getSingletonPtr()->logMessage("Exiting MenuState...");
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
	static SDL_Texture* tex = nullptr; // just temporary hack to make sure SDL is working
	
	if(tex == nullptr){
		tex = Engine::getSingletonPtr()->loadTexture("D:/2D/B/cave.jpg");
	}

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
			break;
		}

		Engine::getSingletonPtr()->clearRenderer();

		Engine::getSingletonPtr()->renderTexture(tex);

		Engine::getSingletonPtr()->renderPresent();
	}
}

// ================================================ //