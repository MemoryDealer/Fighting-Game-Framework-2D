// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: LobbyState.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements LobbyState class.
// ================================================ //

#include "LobbyState.hpp"
#include "Engine.hpp"
#include "StageManager.hpp"
#include "PlayerManager.hpp"
#include "Config.hpp"
#include "App.hpp"

// ================================================ //

LobbyState::LobbyState(void) :
m_pGUI(nullptr),
m_pBackground(new Stage("Data/Stages/lobby.stage"))
{
	// Parse the location of the .gui file for the lobby and load it.
	Config c("ExtMF.cfg");
	//m_pGUI
}

// ================================================ //

LobbyState::~LobbyState(void)
{

}

// ================================================ //

void LobbyState::enter(void)
{
	Log::getSingletonPtr()->logMessage("Entering LobbyState...");

	// Allocate data for LobbyState and GameState.
	new StageManager();
	StageManager::getSingletonPtr()->load("Data/Stages/test.stage");

	new PlayerManager();
	PlayerManager::getSingletonPtr()->load("Data/Fighters/corpse-explosion.fighter", "Data/Fighters/corpse-explosion.fighter");
}

// ================================================ //

void LobbyState::exit(void)
{
	Log::getSingletonPtr()->logMessage("Exiting LobbyState...");

	delete StageManager::getSingletonPtr();
	delete PlayerManager::getSingletonPtr();
}

// ================================================ //

bool LobbyState::pause(void)
{
	Log::getSingletonPtr()->logMessage("Pausing LobbyState...");

	return true;
}

// ================================================ //

void LobbyState::resume(void)
{
	Log::getSingletonPtr()->logMessage("Resuming LobbyState...");
}

// ================================================ //

void LobbyState::handleInput(SDL_Event& e)
{

}

// ================================================ //

void LobbyState::processGUIAction(const int type)
{

}

// ================================================ //

void LobbyState::update(double dt)
{
	if (m_bQuit == true){
		this->popAppState();
		return;
	}

	SDL_Event e;
	while (SDL_PollEvent(&e)){
		switch (e.type){
		default:
			break;
		}
	}

	// Temporary skip.
	m_bQuit = true;
	this->pushAppState(this->findByName(GAME_STATE));

	Engine::getSingletonPtr()->clearRenderer();

	m_pBackground->update(dt);

	Engine::getSingletonPtr()->renderPresent();
}

// ================================================ //