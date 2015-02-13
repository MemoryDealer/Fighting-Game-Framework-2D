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
// File: App.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements App class.
// ================================================ //

#include "App.hpp"
#include "Engine.hpp"
#include "MessageRouter.hpp"
#include "MenuState.hpp"
#include "LobbyState.hpp"
#include "GameState.hpp"
#include "FontManager.hpp"
#include "GUI.hpp"
#include "GamepadManager.hpp"
#include "Game.hpp"
#include "Config.hpp"

// ================================================ //

App::App(void) :	
m_pAppStateManager(nullptr)
{
	new Log();

	Log::getSingletonPtr()->logMessage("Initializing MessageRouter...");
	new MessageRouter();

	Log::getSingletonPtr()->logMessage("Initializing engine...");
	new Engine();

	new FontManager();
	FontManager::getSingletonPtr()->reloadAll();

	new GUITheme();
	Config e(Engine::getSingletonPtr()->getSettingsFile());
	if (e.isLoaded()){
		GUITheme::getSingletonPtr()->load(Engine::getSingletonPtr()->getDataDirectory() + 
			"/" + e.parseValue("GUI", "theme"));
	}

	new GamepadManager();
	GamepadManager::getSingletonPtr()->addAllConnectedPads();

	new Game();

	Log::getSingletonPtr()->logMessage("Creating AppStateManager...");
	m_pAppStateManager = new AppStateManager();

	// Create all states.
	Log::getSingletonPtr()->logMessage("Creating game states...");
	MenuState::create(m_pAppStateManager, MENU_STATE);
	LobbyState::create(m_pAppStateManager, LOBBY_STATE);
	GameState::create(m_pAppStateManager, GAME_STATE);

	Log::getSingletonPtr()->logMessage("App initialized!");

	// Start game by entering menu state.
	Log::getSingletonPtr()->logMessage("Starting with MENU_STATE...");
	m_pAppStateManager->start(m_pAppStateManager->findByName(MENU_STATE));
}

// ================================================ //

App::~App(void)
{
	delete m_pAppStateManager;
	delete Game::getSingletonPtr();
	delete GamepadManager::getSingletonPtr();
	delete FontManager::getSingletonPtr();
	delete GUITheme::getSingletonPtr();

	// Engine must be available for prior destructors.
	delete Engine::getSingletonPtr(); 
	delete MessageRouter::getSingletonPtr();

	Log::getSingletonPtr()->logMessage("Exiting app...");
}

// ================================================ //