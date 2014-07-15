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
#include "GUILobbyState.hpp"
#include "StageManager.hpp"
#include "PlayerManager.hpp"
#include "GameManager.hpp"
#include "Config.hpp"
#include "App.hpp"
#include "Server.hpp"
#include "Widget.hpp"

// ================================================ //

LobbyState::LobbyState(void) :
m_pGUI(nullptr),
m_pBackground(nullptr)
{
	
}

// ================================================ //

LobbyState::~LobbyState(void)
{

}

// ================================================ //

void LobbyState::enter(void)
{
	Log::getSingletonPtr()->logMessage("Entering LobbyState...");

	// Parse the location of the .gui file for the lobby and load it.
	Config c("ExtMF.cfg");
	m_pGUI.reset(new GUILobbyState(c.parseValue("GUI", "lobbystate")));

	m_pBackground.reset(new Stage("Data/Stages/lobby.stage"));

	// Allocate data for LobbyState and GameState.
	new StageManager();
	StageManager::getSingletonPtr()->load("Data/Stages/test.stage");
}

// ================================================ //

void LobbyState::exit(void)
{
	delete StageManager::getSingletonPtr();

	Log::getSingletonPtr()->logMessage("Exiting LobbyState...");
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
	static int lastSelectedWidget = Widget::NONE;
	m_pGUI->setEditingText(Widget::NONE);

	switch (type){
	default:
		return;

	case GUI::Action::BEGIN_PRESS:
		if (m_pGUI->getSelectedWidget() != Widget::NONE){
			lastSelectedWidget = m_pGUI->getSelectedWidget();
			m_pGUI->getWidgetPtr(lastSelectedWidget)->setAppearance(Widget::Appearance::PRESSED);
		}
		break; // End BEGIN_PRESS.

	case GUI::Action::FINISH_PRESS:
		// When a button is pressed in selector mode, reset it back to select appearance.
		if (m_pGUI->getNavigationMode() == GUI::NavMode::SELECTOR){
			m_pGUI->getSelectedWidgetPtr()->setAppearance(Widget::Appearance::SELECTED);
		}

		// Don't let this button be pressed unless BEGIN_PRESS started on it.
		if (m_pGUI->getSelectedWidget() != lastSelectedWidget){
			if (lastSelectedWidget < m_pGUI->getCurrentLayerPtr()->getNumWidgets()){
				m_pGUI->getWidgetPtr(lastSelectedWidget)->setAppearance(Widget::Appearance::IDLE);
				return;
			}
		}

		// Find the current layer, then test that layer's widgets for actions.
		switch (m_pGUI->getCurrentLayerPtr()->getID()){
		default:
			break;

		case GUILobbyState::Layer::ROOT:
			switch (m_pGUI->getSelectedWidget()){
			default:
				break;

			case GUILobbyStateLayer::Root::BUTTON_READY:

				break;

			case GUILobbyStateLayer::Root::TEXTBOX_SEND:
				m_pGUI->setEditingText(GUILobbyStateLayer::Root::TEXTBOX_SEND);
				break;

			case GUILobbyStateLayer::Root::BUTTON_SEND:

				break;

			case GUILobbyStateLayer::Root::BUTTON_EXIT:
				m_quit = true;
				break;
			}
			break;
		}
		break; // End FINISH_PRESS.
	}
}

// ================================================ //

void LobbyState::update(double dt)
{
	if (m_quit == true){
		this->popAppState();
		return;
	}

	SDL_Event e;
	while (SDL_PollEvent(&e)){
		switch (e.type){
		default:
			break;

		case SDL_QUIT:
			m_quit = true;
			break;

		case SDL_KEYDOWN:
			// Send a BEGIN_PRESS action to processGUI() if the selection 
			// button is held.
			if (m_pGUI->getNavigationMode() == GUI::NavMode::SELECTOR){
				if (!m_pGUI->isEditingText() && e.key.keysym.sym == SDLK_SPACE){
					m_pGUI->setSelectorPressed(true);
					this->processGUIAction(GUI::Action::BEGIN_PRESS);
				}
			}

			this->handleInput(e);
			break;

		case SDL_KEYUP:
			// Send a FINISH_PRESS action to processGUI() if the selection 
			// button is released.
			if (m_pGUI->getNavigationMode() == GUI::NavMode::SELECTOR){
				if (!m_pGUI->isEditingText() && e.key.keysym.sym == SDLK_SPACE){
					m_pGUI->setSelectorPressed(false);
					this->processGUIAction(GUI::Action::FINISH_PRESS);
				}
			}

			this->handleInput(e);
			break;

		case SDL_WINDOWEVENT:
			if (e.window.event == SDL_WINDOWEVENT_FOCUS_LOST){
				// If this is a networked game, we should update even if the window is not 
				// in focus.
				if (GameManager::getSingletonPtr()->getMode() == GameManager::SERVER ||
					GameManager::getSingletonPtr()->getMode() == GameManager::CLIENT){
					break;
				}
				else{
					Engine::getSingletonPtr()->setWindowFocused(false);
				}
			}
			break;

		case SDL_MOUSEMOTION:
			if (m_pGUI->getNavigationMode() == GUI::NavMode::SELECTOR){
				m_pGUI->setNavigationMode(GUI::NavMode::MOUSE);
				m_pGUI->clearSelector();
			}
			m_pGUI->setMousePos(e.motion.x, e.motion.y);
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (m_pGUI->getNavigationMode() == GUI::NavMode::MOUSE){
				if (e.button.button == SDL_BUTTON_LEFT){
					m_pGUI->setLeftMouseDown(true);
					this->processGUIAction(GUI::Action::BEGIN_PRESS);
				}
				else if (e.button.button == SDL_BUTTON_RIGHT){
					m_pGUI->setRightMouseDown(true);
				}
			}
			break;

		case SDL_MOUSEBUTTONUP:
			if (m_pGUI->getNavigationMode() == GUI::NavMode::MOUSE){
				if (e.button.button == SDL_BUTTON_LEFT){
					m_pGUI->setLeftMouseDown(false);
					this->processGUIAction(GUI::Action::FINISH_PRESS);
				}
				else{
					m_pGUI->setRightMouseDown(false);
				}
			}
			break;

		case SDL_TEXTINPUT:
			m_pGUI->handleTextInput(e.text.text);
			break;

		case SDL_TEXTEDITING:
			m_pGUI->handleTextInput(e.edit.text);
			break;
		}
	}

	Engine::getSingletonPtr()->clearRenderer();

	m_pBackground->update(dt);
	m_pGUI->update(dt);
	Server::getSingletonPtr()->testRecv();

	Engine::getSingletonPtr()->renderPresent();
}

// ================================================ //