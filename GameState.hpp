// ================================================ //

#ifndef __GAMESTATE_HPP__
#define __GAMESTATE_HPP__

// ================================================ //

#include "AppState.hpp"

// ================================================ //

class ObjectManager;

// ================================================ //

class GameState : public AppState
{
public:
	explicit GameState(void);
	~GameState(void);

	DECLARE_APPSTATE_CLASS(GameState);

	void enter(void);
	void exit(void);
	bool pause(void);
	void resume(void);
	void handleInput(SDL_Event& e);
	void update(double dt);

private:
	bool	m_bQuit;
	std::shared_ptr<ObjectManager> m_pObjectManager;
};

// ================================================ //

#endif

// ================================================ //