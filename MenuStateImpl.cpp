// ================================================ //

#include "MenuStateImpl.hpp"

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

	while(SDL_PollEvent(&e)){
		switch(e.type){
		default:
			break;

		case SDL_QUIT:
			m_bQuit = true;
			break;
		}
	}
}

// ================================================ //