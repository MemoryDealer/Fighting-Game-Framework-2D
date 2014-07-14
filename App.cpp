// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
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
#include "GamepadManager.hpp"
#include "GameManager.hpp"

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

	new GamepadManager();
	GamepadManager::getSingletonPtr()->addAllConnectedPads();

	new GameManager();

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
	delete GameManager::getSingletonPtr();
	delete GamepadManager::getSingletonPtr();
	delete FontManager::getSingletonPtr();

	// Engine must be available for prior destructors.
	delete Engine::getSingletonPtr(); 
	delete MessageRouter::getSingletonPtr();

	Log::getSingletonPtr()->logMessage("Exiting app...");
}

// ================================================ //