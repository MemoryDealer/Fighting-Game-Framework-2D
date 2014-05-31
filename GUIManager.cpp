// ================================================ //

#include "GUIManager.hpp"
#include "GUIMenuState.hpp"
#include "Config.hpp"

// ================================================ //

template<> GUIManager* Singleton<GUIManager>::msSingleton = nullptr;

// ================================================ //

GUIManager::GUIManager(void) :
m_pGUIMenuState(nullptr),
m_pGUILobbyState(nullptr),
m_pGUIGameState(nullptr),
m_GUIMenuStateFile(),
m_GUILobbyStateFile(),
m_GUIGameStateFile()
{
	// Load location of GUI configuration files
	Config c("ExtMF.cfg");

	m_GUIMenuStateFile = c.parseValue("GUI", "menustate");
	m_GUILobbyStateFile = c.parseValue("GUI", "lobbystate");
	m_GUIGameStateFile = c.parseValue("GUI", "gamestate");

	this->reloadAll();
}

// ================================================ //

GUIManager::~GUIManager(void)
{

}

// ================================================ //

void GUIManager::reloadAll(void)
{
	m_pGUIMenuState.reset(new GUIMenuState(m_GUIMenuStateFile));
}

// ================================================ //