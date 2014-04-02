// ================================================ //

#include "MenuState.hpp"
#include "MenuStateImpl.hpp"

// ================================================ //

MenuState::MenuState(void)
	:	m_pImpl(new MenuStateImpl())
{

}

// ================================================ //

MenuState::~MenuState(void)
{

}

// ================================================ //

void MenuState::enter(void)
{
	return m_pImpl->enter();
}

// ================================================ //

void MenuState::exit(void)
{
	return m_pImpl->exit();
}

// ================================================ //

bool MenuState::pause(void)
{
	return m_pImpl->pause();
}

// ================================================ //

void MenuState::resume(void)
{
	return m_pImpl->resume();
}

// ================================================ //

void MenuState::handleInput(SDL_Event& e)
{
	return m_pImpl->handleInput(e);
}

// ================================================ //

void MenuState::update(double dt)
{
	m_pImpl->update(dt);

	if(m_pImpl->shouldQuit()){
		this->popAppState();
	}
}

// ================================================ //