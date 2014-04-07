// ================================================ //

#include "App.hpp"
#include "Engine.hpp"
#include "MessageRouter.hpp"
#include "MenuState.hpp"

// ================================================ //

App::App(void)
	:	m_pAppStateManager(nullptr)
{
	// Initialize log singleton
	new Log();

	// Initialize message router singleton
	new MessageRouter();

	// Initialize engine singleton
	Log::getSingletonPtr()->logMessage("Initializing engine...");
	new Engine();

	// Create our state manager
	m_pAppStateManager = new AppStateManager();

	// Create states
	MenuState::create(m_pAppStateManager, MENU_STATE);

	Log::getSingletonPtr()->logMessage("App initialized!");

	// Start entry state
	m_pAppStateManager->start(m_pAppStateManager->findByName(MENU_STATE));
}

// ================================================ //

App::~App(void)
{
	delete m_pAppStateManager;
	delete Engine::getSingletonPtr(); // Engine must be available for AppState's destruction (ObjectManager)
	delete MessageRouter::getSingletonPtr();

	Log::getSingletonPtr()->logMessage("Exiting app...");
}

// ================================================ //