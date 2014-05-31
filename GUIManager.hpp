// ================================================ //

#ifndef __GUIMANAGER_HPP__
#define __GUIMANAGER_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

class GUI;

// ================================================ //

class GUIManager : public Singleton<GUIManager>
{
public:
	GUIManager(void);
	~GUIManager(void);

	void reloadAll(void);

	GUI* getMenuState(void) const;
	GUI* getLobbyState(void) const;
	GUI* getGameState(void) const;

private:
	std::shared_ptr<GUI> m_pGUIMenuState;
	std::shared_ptr<GUI> m_pGUILobbyState;
	std::shared_ptr<GUI> m_pGUIGameState;

	std::string m_GUIMenuStateFile;
	std::string m_GUILobbyStateFile;
	std::string m_GUIGameStateFile;
};

// ================================================ //

inline GUI* GUIManager::getMenuState(void) const{
	return m_pGUIMenuState.get();
}

inline GUI* GUIManager::getLobbyState(void) const{
	return m_pGUILobbyState.get();
}

inline GUI* GUIManager::getGameState(void) const{
	return m_pGUIGameState.get();
}

// ================================================ //

#endif

// ================================================ //