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

	m_pBackground = new Object("D:/2D/B/cave.jpg");
	SDL_Rect rc;
	rc.x = rc.y = 0;
	rc.w = Engine::getSingletonPtr()->getWindowWidth();
	rc.h = Engine::getSingletonPtr()->getWindowHeight();
	m_pBackground->setPosition(rc);

	m_pObject = new Object("D:/2D/Sprites/s.png");
}

// ================================================ //

void MenuStateImpl::exit(void)
{
	Log::getSingletonPtr()->logMessage("Exiting MenuState...");

	delete m_pObject;
	delete m_pBackground;
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

		case SDL_KEYDOWN:
			if(e.key.keysym.sym == SDLK_ESCAPE)
				m_bQuit = true;
			break;
		}

		Engine::getSingletonPtr()->clearRenderer();

		Engine::getSingletonPtr()->renderObject(m_pBackground);
		Engine::getSingletonPtr()->renderObject(m_pObject);

		Engine::getSingletonPtr()->renderPresent();
	}
}

// ================================================ //