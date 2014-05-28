// ================================================ //

#include "Engine.hpp"
#include "EngineImpl.hpp"

// ================================================ //

template<> Engine* Singleton<Engine>::msSingleton = nullptr;

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

void Engine::renderPresent(void)
{
	return m_pImpl->renderPresent();
}

// ================================================ //

SDL_Texture* Engine::loadTexture(const std::string& filename)
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

void Engine::setMaxFrameRate(const unsigned int max)
{
	return m_pImpl->setMaxFrameRate(max);
}

// ================================================ //
// Getter functions
// ================================================ //

const SDL_Renderer* Engine::getRenderer(void) const
{
	return m_pImpl->getRenderer();
}

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

const int Engine::getLogicalWindowWidth(void) const
{
	return m_pImpl->getLogicalWindowWidth();
}

// ================================================ //

const int Engine::getLogicalWindowHeight(void) const
{
	return m_pImpl->getLogicalWindowHeight();
}

// ================================================ //

const bool Engine::isWindowFocused(void) const
{ 
	return m_pImpl->isWindowFocused();
}

// ================================================ //

const int Engine::getMaxFrameRate(void) const
{
	return m_pImpl->getMaxFrameRate();
}

// ================================================ //

bool Engine::CustomAssertFunction(bool exp, char* desc, int line, char* file)
{
	if(!exp){
		bool ret = false;
#ifdef __WIN32__
		char* msg = new char[strlen(desc) + strlen(file) + 256];
		wsprintfA(msg, "%s\r\nFILE: %s\r\nLINE: %d\r\nDo you wish to break?", desc, file, line);
		if((int)MessageBoxA(GetForegroundWindow(), msg, "Assert", MB_YESNO | MB_ICONEXCLAMATION) == IDYES){
			ret = true;
		}

		delete msg;
		return ret;
#endif
	}

	return false;
}

// ================================================ //