// ================================================ //

#include "MenuStateImpl.hpp"
#include "Engine.hpp"
#include "GameManager.hpp"
#include "PlayerManager.hpp"
#include "PlayerData.hpp"
#include "StageManager.hpp"
#include "GUIMenuState.hpp"
#include "Camera.hpp"
#include "Input.hpp"
#include "Config.hpp"
#include "MessageRouter.hpp"
#include "Server.hpp"
#include "AppState.hpp"
#include "App.hpp"
#include "GamepadManager.hpp"

// ================================================ //

MenuStateImpl::MenuStateImpl(AppState* pMenuState) :	
m_bQuit(false),
m_pMenuState(pMenuState),
m_pGUI(nullptr),
m_pBackground(new Stage("Data/Stages/mainmenu.stage"))
{
	// Locate GUI file and allocate
	Config c("ExtMF.cfg");
	m_pGUI.reset(new GUIMenuState(c.parseValue("GUI", "menustate")));
}

// ================================================ //

MenuStateImpl::~MenuStateImpl(void)
{

}

// ================================================ //

void MenuStateImpl::enter(void)
{
	Log::getSingletonPtr()->logMessage("Entering MenuState...");

	// Allocate GameManager
	new GameManager();
	GameManager::getSingletonPtr()->setMode(GameMode::SERVER);

	// Allocate StageManager
	new StageManager();
	StageManager::getSingletonPtr()->load("Data/Stages/test.stage");

	// Allocate PlayerManager
	new PlayerManager();
	PlayerManager::getSingletonPtr()->load("Data/Fighters/corpse-explosion.fighter", "Data/Fighters/corpse-explosion.fighter");

	// Allocate Camera singleton
	new Camera();

	// Allocate Network
	if (GameManager::getSingletonPtr()->getMode() == GameMode::SERVER)
		new Server();
}

// ================================================ //

void MenuStateImpl::exit(void)
{
	Log::getSingletonPtr()->logMessage("Exiting MenuState...");

	// Free all singletons
	delete GameManager::getSingletonPtr();
	delete StageManager::getSingletonPtr();
	delete PlayerManager::getSingletonPtr();
	delete Camera::getSingletonPtr();
	delete Server::getSingletonPtr();
}

// ================================================ //

bool MenuStateImpl::pause(void)
{
	Log::getSingletonPtr()->logMessage("Pausing MenuState...");

	return true;
}

// ================================================ //

void MenuStateImpl::resume(void)
{
	Log::getSingletonPtr()->logMessage("Resuming MenuState...");
}

// ================================================ //

void MenuStateImpl::handleInput(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN){

		// Hard-coded keys
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
			if (m_pGUI->getNavigationMode() == GUI::NavMode::MOUSE){
				m_pGUI->setNavigationMode(GUI::NavMode::SELECTOR);
			}

			// Navigate to the widget's link
			if(!m_pGUI->getSelectorPressed()){ // prevents user from navigating away while pressing a button
				int widget = m_pGUI->getSelectedWidget();
				if (widget == Widget::NONE){
					m_pGUI->setSelectedWidget(0);
				}
				else{
					Widget* pWidget = m_pGUI->getCurrentLayer()->getWidget(widget);
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
				// Reload GUI and background
				Config c("ExtMF.cfg");
				m_pGUI.reset(new GUIMenuState(c.parseValue("GUI", "menustate")));
				m_pBackground.reset(new Stage("Data/Stages/mainmenu.stage"));
			}
			break;
		}
	}

	if (e.type == SDL_CONTROLLERBUTTONDOWN){

		if (m_pGUI->getNavigationMode() == GUI::NavMode::MOUSE){
			m_pGUI->setNavigationMode(GUI::NavMode::SELECTOR);
		}

		// Gamepad buttons
		if (!m_pGUI->getSelectorPressed()){ // prevents user from navigating away while pressing a button
			int widget = m_pGUI->getSelectedWidget();
			if (widget == Widget::NONE){
				m_pGUI->setSelectedWidget(0);
			}
			else{
				Widget* pWidget = m_pGUI->getCurrentLayer()->getWidget(widget);

				// Red player
				if (e.cbutton.button == PlayerManager::getSingletonPtr()->getRedPlayerInput()->getMappedButton(Input::BUTTON_UP, true)){
					m_pGUI->setSelectedWidget(pWidget->getLinkID(Widget::Link::UP));
				}
				else if (e.cbutton.button == PlayerManager::getSingletonPtr()->getRedPlayerInput()->getMappedButton(Input::BUTTON_DOWN, true)){
					m_pGUI->setSelectedWidget(pWidget->getLinkID(Widget::Link::DOWN));
				}
				else if (e.cbutton.button == PlayerManager::getSingletonPtr()->getRedPlayerInput()->getMappedButton(Input::BUTTON_LEFT, true)){
					m_pGUI->setSelectedWidget(pWidget->getLinkID(Widget::Link::LEFT));
				}
				else if (e.cbutton.button == PlayerManager::getSingletonPtr()->getRedPlayerInput()->getMappedButton(Input::BUTTON_RIGHT, true)){
					m_pGUI->setSelectedWidget(pWidget->getLinkID(Widget::Link::RIGHT));
				}
			}
		}
	}
}

// ================================================ //

void MenuStateImpl::processGUIAction(const int type)
{
	switch (type){
	default:
		return;

	case GUI::Action::BEGIN_PRESS:
		if (m_pGUI->getSelectedWidget() != Widget::NONE){
			m_pGUI->getCurrentLayer()->getWidget(m_pGUI->getSelectedWidget())->setAppearance(Widget::Appearance::PRESSED);
		}
		break; // BEGIN_PRESS

	case GUI::Action::FINISH_PRESS: // mouse button or key released
		
		// Switch the button appearance from pressed back to selected
		if (m_pGUI->getNavigationMode() == GUI::NavMode::SELECTOR){
			m_pGUI->getCurrentLayer()->getWidget(m_pGUI->getSelectedWidget())->setAppearance(Widget::Appearance::SELECTED);
		}

		// Find the current layer, then look in that layer's widgets
		switch (m_pGUI->getCurrentLayer()->getID()){
		default:
			break;

		// Root layer
		case GUIMenuState::Layer::ROOT:
			switch (m_pGUI->getSelectedWidget()){
			default:
				break;

			case GUIMenuStateLayer::Root::BUTTON_CAMPAIGN:
				m_pGUI->setMousePos(-1, -1); // Prevents selector from improperly re-appearing, see work-log.txt:line 196
				m_pMenuState->pushAppState(m_pMenuState->findByName(GAME_STATE));
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

		// Options layer
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
		break; // FINISH_PRESS
	}
}

// ================================================ //

void MenuStateImpl::update(double dt)
{
	if (m_bQuit == true){
		m_pMenuState->popAppState();
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
			if (m_pGUI->getNavigationMode() == GUI::NavMode::SELECTOR){
				if (e.key.keysym.sym == SDLK_RETURN){
					m_pGUI->setSelectorPressed(true);
					this->processGUIAction(GUI::Action::BEGIN_PRESS);
				}
			}

			this->handleInput(e);
			break;
		
		case SDL_KEYUP:
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

		// Gamepad events
		case SDL_CONTROLLERDEVICEADDED:
			{
				int id = GamepadManager::getSingletonPtr()->addPad(e.cdevice.which);

				// Assign the new controller to the first open slot
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
			// The player's pad pointer will be gone, so assign it to null to prevent undefined behavior
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
					e.cbutton.button == PlayerManager::getSingletonPtr()->getRedPlayerInput()->getMappedButton(Input::BUTTON_SELECT, true)){
					m_pGUI->setSelectorPressed(true);
					this->processGUIAction(GUI::Action::BEGIN_PRESS);
				}
			}

			this->handleInput(e);
			break;

		case SDL_CONTROLLERBUTTONUP:
			if (m_pGUI->getNavigationMode() == GUI::NavMode::SELECTOR){
				if (e.cbutton.button == PlayerManager::getSingletonPtr()->getRedPlayerInput()->getMappedButton(Input::BUTTON_START, true) ||
					e.cbutton.button == PlayerManager::getSingletonPtr()->getRedPlayerInput()->getMappedButton(Input::BUTTON_SELECT, true)){
					m_pGUI->setSelectorPressed(false);
					this->processGUIAction(GUI::Action::FINISH_PRESS);
				}
			}

			this->handleInput(e);
			break;

		case SDL_CONTROLLERAXISMOTION:
			const Sint16 value = SDL_GameControllerGetAxis(GamepadManager::getSingletonPtr()->getPad(0), (SDL_GameControllerAxis)0);
			printf("axis: %d\n", value);
			break;
		}
	}

	Engine::getSingletonPtr()->clearRenderer();

	m_pBackground->update(dt);
	m_pGUI->update(dt);

	Engine::getSingletonPtr()->renderPresent();
}

// ================================================ //