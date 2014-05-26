// ================================================ //

#include "GameState.hpp"
#include "GameStateImpl.hpp"

// ================================================ //

GameState::GameState(void)
	:	m_pImpl(new GameStateImpl())
{

}

// ================================================ //

GameState::~GameState(void)
{

}

// ================================================ //

void GameState::enter(void)
{
	return m_pImpl->enter();
}

// ================================================ //

void GameState::exit(void)
{
	return m_pImpl->exit();
}

// ================================================ //

bool GameState::pause(void)
{
	return m_pImpl->pause();
}

// ================================================ //

void GameState::resume(void)
{
	return m_pImpl->resume();
}

// ================================================ //

void GameState::handleInput(SDL_Event& e)
{
	return m_pImpl->handleInput(e);
}

// ================================================ //

void GameState::update(double dt)
{
	m_pImpl->update(dt);

	if(m_pImpl->shouldPop()){
		this->popAppState();
	}
}

// ================================================ //