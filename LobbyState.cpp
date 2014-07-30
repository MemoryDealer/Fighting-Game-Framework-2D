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
#include "Input.hpp"
#include "GameManager.hpp"
#include "Config.hpp"
#include "App.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Packet.hpp"
#include "Widget.hpp"
#include "WidgetListbox.hpp"
#include "Label.hpp"

// ================================================ //

LobbyState::LobbyState(void) :
m_pGUI(nullptr),
m_pBackground(nullptr),
m_packet(new Packet())
{
	Config c("ExtMF.cfg");
	m_pGUI.reset(new GUILobbyState(c.parseValue("GUI", "lobbystate")));
}

// ================================================ //

LobbyState::~LobbyState(void)
{

}

// ================================================ //

void LobbyState::enter(void)
{
	Log::getSingletonPtr()->logMessage("Entering LobbyState...");

	m_pBackground.reset(new Stage("Data/Stages/lobby.stage"));

	// Allocate data for LobbyState and GameState.
	new StageManager();
	StageManager::getSingletonPtr()->load("Data/Stages/test.stage");

	if (GameManager::getSingletonPtr()->getMode() == GameManager::SERVER){
		static_cast<WidgetListbox*>(m_pGUI->getWidgetPtr(
			GUILobbyStateLayer::Root::LISTBOX_CHAT))->addString("Server initialized.");
		Server::getSingletonPtr()->setPacketHandle(m_packet.get());
	}
}

// ================================================ //

void LobbyState::exit(void)
{
	delete StageManager::getSingletonPtr();

	static_cast<WidgetListbox*>(m_pGUI->getWidgetPtr(GUILobbyStateLayer::Root::LISTBOX_CHAT))->clear();

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
	// Acquire a pointer to the player under the control of the current gamepad here (avoids copied & pasted code below).
	Player* player = nullptr;
	if (e.type == SDL_CONTROLLERBUTTONDOWN ||
		e.type == SDL_CONTROLLERBUTTONUP ||
		e.type == SDL_CONTROLLERAXISMOTION){
		player = (e.cdevice.which == PlayerManager::getSingletonPtr()->getRedPlayerInput()->getPadID()) ?
			PlayerManager::getSingletonPtr()->getRedPlayer() : (e.cdevice.which == PlayerManager::getSingletonPtr()->getBluePlayerInput()->getPadID()) ?
			PlayerManager::getSingletonPtr()->getBluePlayer() : nullptr;

		if (player == nullptr){
			Log::getSingletonPtr()->logMessage("WARNING: Unregistered gamepad sending input (ID: " + Engine::toString(e.cdevice.which) + ")");
			return;
		}
	}

	if (e.type == SDL_KEYDOWN){

		// Process hard-coded keys.
		switch (e.key.keysym.sym){
		default:
			break;

		case SDLK_ESCAPE:
			if (m_pGUI->isEditingText()){
				m_pGUI->setEditingText(Widget::NONE);
			}
			else{
				if (m_pGUI->getCurrentLayer() == GUILobbyState::Layer::ROOT){
					m_quit = true;
				}
				else{
					m_pGUI->popLayer();
				}
			}
			break;

		case SDLK_RETURN:
			if (m_pGUI->isEditingText()){
				// Build message text with user name preceding the message itself.
				std::string message = GameManager::getSingletonPtr()->getUsername() +
					": " + m_pGUI->getWidgetPtr(GUILobbyStateLayer::Root::TEXTBOX_SEND)->getText();
				if (GameManager::getSingletonPtr()->getMode() == GameManager::CLIENT){
					printf("Chat: %d\n", Client::getSingletonPtr()->chat(message));
				}
				static_cast<WidgetListbox*>(m_pGUI->getWidgetPtr(GUILobbyStateLayer::Root::LISTBOX_CHAT))->addString(message);
				m_pGUI->getWidgetPtr(GUILobbyStateLayer::Root::TEXTBOX_SEND)->setLabel("");
			}
			break;

		case SDLK_BACKSPACE:
			if (m_pGUI->isEditingText()){
				m_pGUI->handleTextInput("", true);
			}
			break;

		case SDLK_UP:
		case SDLK_DOWN:
		case SDLK_LEFT:
		case SDLK_RIGHT:
			// Automatically switch to navigation mode when arrows are pressed.
			if (m_pGUI->getNavigationMode() == GUI::NavMode::MOUSE){
				m_pGUI->setNavigationMode(GUI::NavMode::SELECTOR);
			}

			if (!m_pGUI->getSelectorPressed()){
				// Prevent user from navigating away while pressing a button.
				int widget = m_pGUI->getSelectedWidget();
				if (widget == Widget::NONE){
					m_pGUI->setSelectedWidget(0);
				}
				else{
					// Navigate the selector to the linked Widget.
					Widget* pWidget = m_pGUI->getWidgetPtr(widget);
					switch (e.key.keysym.sym){
					default:
					case SDLK_UP:
						m_pGUI->setSelectedWidget(pWidget->getLinkID(Widget::Link::UP));
						break;

					case SDLK_DOWN:
						m_pGUI->setSelectedWidget(pWidget->getLinkID(Widget::Link::DOWN));
						break;

					case SDLK_LEFT:
						m_pGUI->setSelectedWidget(pWidget->getLinkID(Widget::Link::LEFT));
						break;

					case SDLK_RIGHT:
						m_pGUI->setSelectedWidget(pWidget->getLinkID(Widget::Link::RIGHT));
						break;
					}
				}
			}
			break;

		case SDLK_r:
		{
			// Reload GUI and background.
			//Config c("ExtMF.cfg");
			//m_pGUI.reset(new GUILobbyState(c.parseValue("GUI", "lobbystate")));
			m_pBackground.reset(new Stage("Data/Stages/lobby.stage"));
		}
			break;

		case SDLK_i:
			
			break;
		}
	}

	if (e.type == SDL_CONTROLLERBUTTONDOWN){

		if (m_pGUI->getNavigationMode() == GUI::NavMode::MOUSE){
			m_pGUI->setNavigationMode(GUI::NavMode::SELECTOR);
		}

		if (!m_pGUI->getSelectorPressed()){
			// Prevent user from navigating away while pressing a button.
			int widget = m_pGUI->getSelectedWidget();
			if (widget == Widget::NONE){
				m_pGUI->setSelectedWidget(0);
			}
			else{
				// Navigate to the linked Widget.
				Widget* pWidget = m_pGUI->getWidgetPtr(widget);
				switch (player->getInput()->SDLButtonToMappedButton(e.cbutton.button, true)){
				default:
					break;

				case Input::BUTTON_UP:
					m_pGUI->setSelectedWidget(pWidget->getLinkID(Widget::Link::UP));
					break;

				case Input::BUTTON_DOWN:
					m_pGUI->setSelectedWidget(pWidget->getLinkID(Widget::Link::DOWN));
					break;

				case Input::BUTTON_LEFT:
					m_pGUI->setSelectedWidget(pWidget->getLinkID(Widget::Link::LEFT));
					break;

				case Input::BUTTON_RIGHT:
					m_pGUI->setSelectedWidget(pWidget->getLinkID(Widget::Link::RIGHT));
					break;

				case Input::BUTTON_BACK:
					m_pGUI->popLayer();
					break;
				}
			}
		}
	}
	else if (e.type == SDL_CONTROLLERAXISMOTION){

		if (m_pGUI->getNavigationMode() == GUI::NavMode::MOUSE){
			m_pGUI->setNavigationMode(GUI::NavMode::SELECTOR);
		}

		if (!m_pGUI->getSelectorPressed()){
			// Prevent user from navigating away while pressing a button.
			int widget = m_pGUI->getSelectedWidget();
			if (widget == Widget::NONE){
				m_pGUI->setSelectedWidget(0);
			}
			else{
				// These booleans prevent the selector from skipping Widgets in 
				// between two end Widgets when a joystick is held down.
				static bool xAxisReset = true;
				static bool yAxisReset = true;

				Widget* pWidget = m_pGUI->getWidgetPtr(widget);
				const int deadzone = player->getInput()->getPadDeadzone();

				// Process Y-axis movement.
				Sint16 value = SDL_GameControllerGetAxis(player->getInput()->getPad(), static_cast<SDL_GameControllerAxis>(1));
				if (value < -deadzone && yAxisReset){
					m_pGUI->setSelectedWidget(pWidget->getLinkID(Widget::Link::UP));
					yAxisReset = false;
				}
				else if (value > deadzone && yAxisReset){
					m_pGUI->setSelectedWidget(pWidget->getLinkID(Widget::Link::DOWN));
					yAxisReset = false;
				}
				else if (value < deadzone && value > -deadzone){
					yAxisReset = true;
				}

				// Process X-axis movement.
				value = SDL_GameControllerGetAxis(player->getInput()->getPad(), static_cast<SDL_GameControllerAxis>(0));
				if (value < -deadzone && xAxisReset){
					m_pGUI->setSelectedWidget(pWidget->getLinkID(Widget::Link::LEFT));
				}
				else if (value > deadzone && xAxisReset){
					m_pGUI->setSelectedWidget(pWidget->getLinkID(Widget::Link::RIGHT));
				}
				else if (value < deadzone && value > -deadzone){
					xAxisReset = true;
				}
			}
		}
	}
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
			{
				std::string message = GameManager::getSingletonPtr()->getUsername() +
					": " + m_pGUI->getWidgetPtr(GUILobbyStateLayer::Root::TEXTBOX_SEND)->getText();
				if (GameManager::getSingletonPtr()->getMode() == GameManager::CLIENT){
					printf("Chat: %d\n", Client::getSingletonPtr()->chat(message));
				}
				static_cast<WidgetListbox*>(m_pGUI->getWidgetPtr(GUILobbyStateLayer::Root::LISTBOX_CHAT))->addString(message);
				m_pGUI->getWidgetPtr(GUILobbyStateLayer::Root::TEXTBOX_SEND)->setLabel("");
			}
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
	if (GameManager::getSingletonPtr()->getMode() == GameManager::SERVER){
		// Receive a copy of the packet data from the server and process.
		if (Server::getSingletonPtr()->update(dt)){
			switch (m_packet->type){
			default:
			case Packet::NIL:
				break;

			case Packet::CONNECT_REQUEST:
				printf("Connect request from: %s\n", m_packet->message);
				break;

			case Packet::CHAT:
				static_cast<WidgetListbox*>(m_pGUI->getWidgetPtr(GUILobbyStateLayer::Root::LISTBOX_CHAT))->addString(m_packet->message);
				break;
			}
		}
	}
	else if (GameManager::getSingletonPtr()->getMode() == GameManager::CLIENT){
		Packet* data = Client::getSingletonPtr()->update(dt);
		if (data != nullptr){
			switch (data->type){
			default:
			case Packet::NIL:
				break;

			case Packet::CONNECT_ACCEPT:
				static_cast<WidgetListbox*>(m_pGUI->getWidgetPtr(GUILobbyStateLayer::Root::LISTBOX_CHAT))->addString(data->message);
				break;
			}

			delete data;
		}
	}

	Engine::getSingletonPtr()->renderPresent();
}

// ================================================ //