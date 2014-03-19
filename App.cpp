// ================================================ //

#include "App.hpp"
#include "Engine.hpp"
#include "MenuState.hpp"

// ================================================ //

App::App(void)
	:	m_pAppStateManager(nullptr)
{
	// Initialize log singleton
	new Log();

	// Initialize engine singleton
	Log::getSingletonPtr()->logMessage("Initializing engine...");
	new Engine();

	// Create our state manager
	m_pAppStateManager = new AppStateManager();

	// Create states
	MenuState::create(m_pAppStateManager, MENU_STATE);

	// Start entry state
	m_pAppStateManager->start(m_pAppStateManager->findByName(MENU_STATE));

	Log::getSingletonPtr()->logMessage("App initialized!");
}

// ================================================ //

App::~App(void)
{
	Log::getSingletonPtr()->logMessage("Closing app...");
	delete Engine::getSingletonPtr();
	delete m_pAppStateManager;
}

// ================================================ //