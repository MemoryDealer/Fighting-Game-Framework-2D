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

private:
	std::shared_ptr<GUI> m_pGUIMenuState;

	std::string m_GUIMenuStateFile;
	std::string m_GUILobbyStateFile;
	std::string m_GUIGameStateFile;
};

// ================================================ //

inline GUI* GUIManager::getMenuState(void) const{
	return m_pGUIMenuState.get();
}

// ================================================ //

#endif

// ================================================ //