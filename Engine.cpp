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
	m_pImpl->clearRenderer();
}

// ================================================ //

void Engine::renderPresent(void)
{
	m_pImpl->renderPresent();
}

// ================================================ //