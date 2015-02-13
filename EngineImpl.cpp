// ========================================================================= //
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
// File: EngineImpl.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements EngineImpl class.
// ================================================ //

#include "EngineImpl.hpp"
#include "Engine.hpp"
#include "Config.hpp"
#include "Object.hpp"

// ================================================ //

EngineImpl::EngineImpl(void) :
m_pWindow(nullptr),
m_pRenderer(nullptr),
m_width(854),
m_height(480),
m_logicalWidth(854),
m_logicalHeight(480),
m_maxFrameRate(60),
m_windowTitle("Fighting Game Framework 2D - Pre-alpha Build " + Engine::toString(Engine::VERSION_MAJOR) + "." +
Engine::toString(Engine::VERSION_MINOR1) + Engine::toString(Engine::VERSION_MINOR2)),
m_settingsFile("Data/ExtMF.cfg"),
m_dataDirectory("Data"),
m_clockSpeed(1.0)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		throw std::exception("SDL_Init() failed.");

	Log::getSingletonPtr()->logMessage("SDL initialized with SDL_INIT_EVERYTHING");

	if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) < 0)
		throw std::exception("IMG_Init() failed.");

	Log::getSingletonPtr()->logMessage("SDL_image initialized with IMG_INIT_JPG | IMG_INIT_PNG");

	if (TTF_Init() != 0)
		throw std::exception("TTF_Init() failed.");

	Log::getSingletonPtr()->logMessage("SDL_ttf initialized");

	// Find location of settings file.
	Config c("config.ini");
	if (c.isLoaded()){
		m_dataDirectory = c.parseValue("core", "data", true);
		m_settingsFile = m_dataDirectory + "/ExtMF.cfg";
	}
	else{
		Log::getSingletonPtr()->logMessage("ERROR: No config.ini found, generating default config.ini and Data/ExtMF.cfg");
		// TODO: Generate a default config files...

		// ...
	}

	Config cfg(m_settingsFile);
	if (!cfg.isLoaded()){
		throw std::exception(std::string("Failed to load \"" + m_settingsFile + "\"").c_str());
	}

	// Create the rendering window.
	m_width = cfg.parseIntValue("window", "width");
	m_height = cfg.parseIntValue("window", "height");
	m_pWindow = SDL_CreateWindow(m_windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, 0);
	if (m_pWindow == nullptr)
		throw std::exception("SDL_CreateWindow() failed.");

	Log::getSingletonPtr()->logMessage("SDL_Window created successfully");

	// Create the renderer for the window to use.
	Uint32 flags = (cfg.parseIntValue("window", "vsync")) ? SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC :
		SDL_RENDERER_ACCELERATED;
	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, flags);
	if (m_pRenderer == nullptr)
		throw std::exception("SDL_CreateRenderer() failed.");

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, cfg.parseValue("core", "renderScaleQuality").c_str());

	// Set virtual resolution.
	SDL_RenderSetLogicalSize(m_pRenderer, cfg.parseIntValue("window", "logicalWidth"), 
		cfg.parseIntValue("window", "logicalHeight"));

	m_maxFrameRate = cfg.parseIntValue("window", "maxFPS");
	
	Log::getSingletonPtr()->logMessage("SDL_Renderer created successfully");
}

// ================================================ //

EngineImpl::~EngineImpl(void)
{
	Log::getSingletonPtr()->logMessage("Destroying SDL_Window and SDL_Renderer...");
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);

	Log::getSingletonPtr()->logMessage("Quitting SDL...");
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

// ================================================ //

void EngineImpl::clearRenderer(void)
{
	SDL_RenderClear(m_pRenderer);
}

// ================================================ //

void EngineImpl::renderPresent(void)
{
	SDL_RenderPresent(m_pRenderer);
}

// ================================================ //

SDL_Texture* EngineImpl::loadTexture(const std::string& filename)
{
	SDL_Texture* tex = nullptr;

	tex = IMG_LoadTexture(m_pRenderer, filename.c_str());
	if (tex == nullptr)
		Log::getSingletonPtr()->logMessage("Failed to load texture from file: \"" + std::string(filename) + "\"");

	Log::getSingletonPtr()->logMessage("Texture \"" + std::string(filename) + "\" loaded!");

	return tex;
}

// ================================================ //

void EngineImpl::destroyTexture(SDL_Texture* pTexture)
{
	SDL_DestroyTexture(pTexture);
}

// ================================================ //

void EngineImpl::setResolution(const int width, const int height)
{
	SDL_SetWindowSize(m_pWindow, m_width = width, m_height = height);
	SDL_SetWindowPosition(m_pWindow, 0, 0);
	//SDL_SetWindowBordered(m_pWindow, SDL_FALSE);
}

// ================================================ //