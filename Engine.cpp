// // ========================================================================= //
// Fighting game framework (2D) with online multiplayer.
// Copyright(C) 2014 Jordan Sparks <unixunited@live.com>
//
// This program is free software; you can redistribute it and / or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 3
// of the License, or(at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
// ========================================================================= //
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
const int Engine::VERSION_MINOR2 =	2;

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

const std::string Engine::getDataDirectory(void) const
{
	return m_pImpl->getDataDirectory();
}

// ================================================ //

const double Engine::getClockSpeed(void) const
{
	return m_pImpl->getClockSpeed();
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

void Engine::setClockSpeed(const double speed)
{
	return m_pImpl->setClockSpeed(speed);
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