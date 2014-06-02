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

// ================================================ //

MenuStateImpl::MenuStateImpl(AppState* pMenuState) :	
m_bQuit(false),
m_pMenuState(pMenuState),
m_pGUI(nullptr)
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

	// m_pObjectManager destructed automatically

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
		switch (e.key.keysym.sym){
		default:
			break;

		case SDLK_ESCAPE:
			m_pMenuState->popAppState();
			break;

		case SDLK_UP:
		case SDLK_DOWN:
			if (m_pGUI->getNavigationMode()
				== GUI::NavMode::MOUSE){
				m_pGUI->setNavigationMode(GUI::NavMode::SELECTOR);
			}

			// Navigate to the widget's link
			{
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
					}
				}
			}
			break;

		case SDLK_r:
			{
				// Reload GUI
				Config c("ExtMF.cfg");
				m_pGUI.reset(new GUIMenuState(c.parseValue("GUI", "menustate")));
			}
			break;
		}
	}
}

// ================================================ //

void MenuStateImpl::processGUIAction(const int type)
{
	switch (type){
	default:
		return;

	case GUI::Action::FINISH_SELECT:
		switch (m_pGUI->getSelectedWidget()){
		case GUIMenuStateLayer::Root::BUTTON_CAMPAIGN:
			m_pMenuState->pushAppState(m_pMenuState->findByName(GAME_STATE));
			break;

		case GUIMenuStateLayer::Root::BUTTON_ARCADE:
			printf("ARCADE!!!\n");
			break;

		case GUIMenuStateLayer::Root::BUTTON_OPTIONS:
			printf("OPTIONS!!!\n");
			break;

		case GUIMenuStateLayer::Root::BUTTON_QUIT:
			m_pMenuState->popAppState();
			break;
		}
	}
}

// ================================================ //

void MenuStateImpl::update(double dt)
{
	SDL_Event e;

	while (SDL_PollEvent(&e)){
		switch (e.type){
		default:
			break;

		case SDL_QUIT:
			m_pMenuState->popAppState();
			break;
		
		case SDL_KEYUP:
			if (m_pGUI->getNavigationMode() == GUI::NavMode::SELECTOR){
				if (e.key.keysym.sym == SDLK_RETURN){
					this->processGUIAction(GUI::Action::FINISH_SELECT);
				}
			}

			// fall through...

		case SDL_KEYDOWN:
			this->handleInput(e);
			break;

		case SDL_MOUSEMOTION:
			if (m_pGUI->getNavigationMode() == GUI::NavMode::SELECTOR){
				m_pGUI->setNavigationMode(GUI::NavMode::MOUSE);
			}
			m_pGUI->setMousePos(e.motion.x, e.motion.y);
			break;

		case SDL_MOUSEBUTTONUP:
			if (m_pGUI->getNavigationMode() == GUI::NavMode::MOUSE){
				if (e.button.button == SDL_BUTTON_LEFT){
					this->processGUIAction(GUI::Action::FINISH_SELECT);
				}
			}
			break;

		case SDL_WINDOWEVENT:
			if (e.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
				Engine::getSingletonPtr()->setWindowFocused(false);
			break;
		}
	}

	Engine::getSingletonPtr()->clearRenderer();

	m_pGUI->update(dt);

	Engine::getSingletonPtr()->renderPresent();
}

// ================================================ //