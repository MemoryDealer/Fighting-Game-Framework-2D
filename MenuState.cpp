// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: MenuState.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements MenuState class.
// ================================================ //

#include "MenuState.hpp"
#include "Engine.hpp"
#include "PlayerManager.hpp"
#include "PlayerData.hpp"
#include "StageManager.hpp"
#include "GUIMenuState.hpp"
#include "Widget.hpp"
#include "Camera.hpp"
#include "Input.hpp"
#include "Config.hpp"
#include "MessageRouter.hpp"
#include "Server.hpp"
#include "AppState.hpp"
#include "App.hpp"
#include "GamepadManager.hpp"

// ================================================ //

MenuState::MenuState(void) :
m_bQuit(false),
m_pGUI(nullptr),
m_pBackground(new Stage("Data/Stages/menu.stage"))
{
	// Parse the location of the .gui file for the main menu and load it.
	Config c("ExtMF.cfg");
	m_pGUI.reset(new GUIMenuState(c.parseValue("GUI", "menustate")));
}

// ================================================ //

MenuState::~MenuState(void)
{

}

// ================================================ //

void MenuState::enter(void)
{
	Log::getSingletonPtr()->logMessage("Entering MenuState...");

	new Camera();
}

// ================================================ //

void MenuState::exit(void)
{
	Log::getSingletonPtr()->logMessage("Exiting MenuState...");

	delete Camera::getSingletonPtr();
}

// ================================================ //

bool MenuState::pause(void)
{
	Log::getSingletonPtr()->logMessage("Pausing MenuState...");

	return true;
}

// ================================================ //

void MenuState::resume(void)
{
	Log::getSingletonPtr()->logMessage("Resuming MenuState...");
}

// ================================================ //

void MenuState::handleInput(SDL_Event& e)
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
			m_bQuit = true;
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
			Config c("ExtMF.cfg");
			m_pGUI.reset(new GUIMenuState(c.parseValue("GUI", "menustate")));
			m_pBackground.reset(new Stage("Data/Stages/mainmenu.stage"));
		}
			break;

		case SDLK_i:
			Engine::getSingletonPtr()->setResolution(1920, 1080);
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

				if (e.cbutton.button == player->getInput()->getMappedButton(Input::BUTTON_UP, true)){
					m_pGUI->setSelectedWidget(pWidget->getLinkID(Widget::Link::UP));
				}
				else if (e.cbutton.button == player->getInput()->getMappedButton(Input::BUTTON_DOWN, true)){
					m_pGUI->setSelectedWidget(pWidget->getLinkID(Widget::Link::DOWN));
				}
				else if (e.cbutton.button == player->getInput()->getMappedButton(Input::BUTTON_LEFT, true)){
					m_pGUI->setSelectedWidget(pWidget->getLinkID(Widget::Link::LEFT));
				}
				else if (e.cbutton.button == player->getInput()->getMappedButton(Input::BUTTON_RIGHT, true)){
					m_pGUI->setSelectedWidget(pWidget->getLinkID(Widget::Link::RIGHT));
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

void MenuState::processGUIAction(const int type)
{
	static int lastSelectedWidget = Widget::NONE;

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
			if (lastSelectedWidget < m_pGUI->getCurrentLayer()->getNumWidgets()){
				m_pGUI->getWidgetPtr(lastSelectedWidget)->setAppearance(Widget::Appearance::IDLE);
				return;
			}
		}

		// Find the current layer, then test that layer's widgets for actions.
		switch (m_pGUI->getCurrentLayer()->getID()){
		default:
			break;

		case GUIMenuState::Layer::ROOT:
			switch (m_pGUI->getSelectedWidget()){
			default:
				break;

			case GUIMenuStateLayer::Root::BUTTON_CAMPAIGN:
				// Prevent selector from improperly re-appearing, see work-log.txt:line 196.
				m_pGUI->setMousePos(-1, -1); 
				this->pushAppState(this->findByName(LOBBY_STATE));
				break;

			case GUIMenuStateLayer::Root::BUTTON_ARCADE:
				printf("ARCADE!!!\n");
				break;

			case GUIMenuStateLayer::Root::BUTTON_OPTIONS:
				m_pGUI->setCurrentLayer(GUIMenuState::Layer::OPTIONS);
				break;

			case GUIMenuStateLayer::Root::BUTTON_QUIT:
				m_bQuit = true;
				break;
			}
			break;

		case GUIMenuState::Layer::OPTIONS:
			switch (m_pGUI->getSelectedWidget()){
			default:
				break;

			case GUIMenuStateLayer::Options::BUTTON_BACK:
				m_pGUI->setCurrentLayer(GUIMenuState::Layer::ROOT);
				break;
			}
			break;
		}
		break; // End FINISH_PRESS.
	}
}

// ================================================ //

void MenuState::update(double dt)
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

		case SDL_QUIT:
			m_bQuit = true;
			break;

		case SDL_KEYDOWN:
			// Send a BEGIN_PRESS action to processGUI() if the selection 
			// button is held.
			if (m_pGUI->getNavigationMode() == GUI::NavMode::SELECTOR){
				if (e.key.keysym.sym == SDLK_RETURN){
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
				if (e.key.keysym.sym == SDLK_RETURN){
					m_pGUI->setSelectorPressed(false);
					this->processGUIAction(GUI::Action::FINISH_PRESS);
				}
			}

			this->handleInput(e);
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

		case SDL_WINDOWEVENT:
			if (e.window.event == SDL_WINDOWEVENT_FOCUS_LOST){
				Engine::getSingletonPtr()->setWindowFocused(false);
			}
			break;

		case SDL_CONTROLLERDEVICEADDED:
		{
			int id = GamepadManager::getSingletonPtr()->addPad(e.cdevice.which);

			// Assign the new controller to the first open slot.
			if (PlayerManager::getSingletonPtr()->getRedPlayerInput()->getPadID() == -1){
				PlayerManager::getSingletonPtr()->getRedPlayerInput()->setPad(
					GamepadManager::getSingletonPtr()->getPad(id));
			}
			else if (PlayerManager::getSingletonPtr()->getBluePlayerInput()->getPadID() == -1){
				PlayerManager::getSingletonPtr()->getBluePlayerInput()->setPad(
					GamepadManager::getSingletonPtr()->getPad(id));
			}
		}
			break;

		case SDL_CONTROLLERDEVICEREMOVED:
			// The player's pad pointer will be gone, so assign it to null to prevent undefined behavior.
			if (PlayerManager::getSingletonPtr()->getRedPlayerInput()->getPadID() == -1){
				PlayerManager::getSingletonPtr()->getRedPlayerInput()->setPad(nullptr);
			}
			if (PlayerManager::getSingletonPtr()->getBluePlayerInput()->getPadID() == -1){
				PlayerManager::getSingletonPtr()->getBluePlayerInput()->setPad(nullptr);
			}

			GamepadManager::getSingletonPtr()->removePad(e.cdevice.which);
			break;

		case SDL_CONTROLLERBUTTONDOWN:
			if (m_pGUI->getNavigationMode() == GUI::NavMode::SELECTOR){
				if (e.cbutton.button == PlayerManager::getSingletonPtr()->getRedPlayerInput()->getMappedButton(Input::BUTTON_START, true) ||
					e.cbutton.button == PlayerManager::getSingletonPtr()->getRedPlayerInput()->getMappedButton(Input::BUTTON_SELECT, true) ||
					e.cbutton.button == PlayerManager::getSingletonPtr()->getBluePlayerInput()->getMappedButton(Input::BUTTON_START, true) ||
					e.cbutton.button == PlayerManager::getSingletonPtr()->getBluePlayerInput()->getMappedButton(Input::BUTTON_SELECT, true)){
					m_pGUI->setSelectorPressed(true);
					this->processGUIAction(GUI::Action::BEGIN_PRESS);
				}
			}

			this->handleInput(e);
			break;

		case SDL_CONTROLLERBUTTONUP:
			if (m_pGUI->getNavigationMode() == GUI::NavMode::SELECTOR){
				if (e.cbutton.button == PlayerManager::getSingletonPtr()->getRedPlayerInput()->getMappedButton(Input::BUTTON_START, true) ||
					e.cbutton.button == PlayerManager::getSingletonPtr()->getRedPlayerInput()->getMappedButton(Input::BUTTON_SELECT, true) ||
					e.cbutton.button == PlayerManager::getSingletonPtr()->getBluePlayerInput()->getMappedButton(Input::BUTTON_START, true) ||
					e.cbutton.button == PlayerManager::getSingletonPtr()->getBluePlayerInput()->getMappedButton(Input::BUTTON_SELECT, true)){
					m_pGUI->setSelectorPressed(false);
					this->processGUIAction(GUI::Action::FINISH_PRESS);
				}
			}

			this->handleInput(e);
			break;

		case SDL_CONTROLLERAXISMOTION:
			this->handleInput(e);
			break;
		}
	}

	Engine::getSingletonPtr()->clearRenderer();

	m_pBackground->update(dt);
	m_pGUI->update(dt);

	Engine::getSingletonPtr()->renderPresent();
}

// ================================================ //