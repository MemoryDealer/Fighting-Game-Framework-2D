// ================================================ //

#include "Engine.hpp"
#include "EngineImpl.hpp"

// ================================================ //

template<> Engine* Singleton<Engine>::msSingleton = 0;

// ================================================ //

Engine::Engine(void)
	: m_pImpl(new EngineImpl())
{

}

// ================================================ //

Engine::~Engine(void)
{

}

// ================================================ //

void Engine::clearRenderer(void)
{
	return m_pImpl->clearRenderer();
}

// ================================================ //

void Engine::renderObject(const Object* pObject)
{
	return m_pImpl->renderObject(pObject);
}

// ================================================ //

void Engine::renderPresent(void)
{
	return m_pImpl->renderPresent();
}

// ================================================ //

SDL_Texture* Engine::loadTexture(const char* filename)
{
	return m_pImpl->loadTexture(filename);
}

// ================================================ //

void Engine::destroyTexture(SDL_Texture* pTexture)
{
	return m_pImpl->destroyTexture(pTexture);
}

// ================================================ //
// Setter functions
// ================================================ //

void Engine::setWindowFocused(const bool focused)
{
	return m_pImpl->setWindowFocused(focused);
}

// ================================================ //
// Getter functions
// ================================================ //

const int Engine::getWindowWidth(void) const
{
	return m_pImpl->getWindowWidth();
}

// ================================================ //

const int Engine::getWindowHeight(void) const
{
	return m_pImpl->getWindowHeight();
}

// ================================================ //

const bool Engine::isWindowFocused(void) const
{ 
	return m_pImpl->isWindowFocused();
}

// ================================================ //