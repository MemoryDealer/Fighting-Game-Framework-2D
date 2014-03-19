// ================================================ //

#ifndef __APP_HPP__
#define __APP_HPP__

// ================================================ //

#include "AppStateManager.hpp"

// ================================================ //

const std::string MENU_STATE = "MenuState";
const std::string LOBBY_STATE = "LobbyState";
const std::string GAME_STATE = "GameState";

// ================================================ //

class App
{
public:
	explicit App(void);
	~App(void);

private:
	AppStateManager* m_pAppStateManager; // the Big Dog
};

// ================================================ //

#endif

// ================================================ //