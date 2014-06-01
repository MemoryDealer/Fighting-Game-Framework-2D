// ================================================ //

#include "App.hpp"
#include "Engine.hpp"
#include "MessageRouter.hpp"
#include "MenuState.hpp"
#include "GameState.hpp"
#include "GUIManager.hpp"
#include "FontManager.hpp"

// ================================================ //

App::App(void)
	:	m_pAppStateManager(nullptr)
{
	// Initialize log singleton
	new Log();

	// Initialize message router singleton
	Log::getSingletonPtr()->logMessage("Initializing MessageRouter...");
	new MessageRouter();

	// Initialize engine singleton
	Log::getSingletonPtr()->logMessage("Initializing engine...");
	new Engine();

	// Create our state manager
	Log::getSingletonPtr()->logMessage("Creating AppStateManager...");
	m_pAppStateManager = new AppStateManager();

	// Create states
	Log::getSingletonPtr()->logMessage("Creating game states...");
	MenuState::create(m_pAppStateManager, MENU_STATE);
	GameState::create(m_pAppStateManager, GAME_STATE);

	// Allocate FontManager singleton
	new FontManager();
	FontManager::getSingletonPtr()->reloadAll();

	// Allocate GUIManager singleton for use across all states
	new GUIManager();

	Log::getSingletonPtr()->logMessage("App initialized!");

	// Start entry state
	Log::getSingletonPtr()->logMessage("Starting with MENU_STATE...");
	m_pAppStateManager->start(m_pAppStateManager->findByName(MENU_STATE));
}

// ================================================ //

App::~App(void)
{
	delete m_pAppStateManager;
	delete GUIManager::getSingletonPtr();
	delete FontManager::getSingletonPtr();
	delete Engine::getSingletonPtr(); // Engine must be available for AppState's destruction (ObjectManager)
	delete MessageRouter::getSingletonPtr();

	Log::getSingletonPtr()->logMessage("Exiting app...");
}

// ================================================ //