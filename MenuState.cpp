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
	m_pImpl->enter();
}

// ================================================ //

void MenuState::exit(void)
{
	m_pImpl->exit();
}

// ================================================ //

bool MenuState::pause(void)
{
	return m_pImpl->pause();
}

// ================================================ //

void MenuState::resume(void)
{
	m_pImpl->resume();
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