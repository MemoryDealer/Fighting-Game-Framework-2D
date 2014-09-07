// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: Engine.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements Engine singleton class.
// ================================================ //

#include "Engine.hpp"
#include "EngineImpl.hpp"

// ================================================ //

template<> Engine* Singleton<Engine>::msSingleton = nullptr;

// ================================================ //

// Version 0.01
const int Engine::VERSION_MAJOR =	0;
//								    .
const int Engine::VERSION_MINOR1 =	0;
const int Engine::VERSION_MINOR2 =	1;

// ================================================ //

Engine::Engine(void) : 
m_pImpl(new EngineImpl())
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

// Getters

SDL_Renderer* Engine::getRenderer(void) const
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

const std::string Engine::getSettingsFile(void) const
{
	return m_pImpl->getSettingsFile();
}

// ================================================ //

// Setters

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

void Engine::setResolution(const int width, const int height)
{
	return m_pImpl->setResolution(width, height);
}

// ================================================ //

// --- //

bool Engine::CustomAssertFunction(bool exp, char* desc, int line, char* file)
{
	if (!exp){
		// Display a message offering whether or not to break for debugging.
		bool ret = false;
#ifdef __WIN32__
		char* msg = new char[strlen(desc) + strlen(file) + 256];
		wsprintfA(msg, "%s\r\nFILE: %s\r\nLINE: %d\r\nDo you wish to break?", desc, file, line);
		if ((int)MessageBoxA(GetForegroundWindow(), msg, "Assert", MB_YESNO | MB_ICONEXCLAMATION) == IDYES){
			ret = true;
		}

		delete[] msg;
		return ret;
#endif
	}

	return false;
}

// ================================================ //