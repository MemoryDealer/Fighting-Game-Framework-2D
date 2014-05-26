// ================================================ //

#ifndef __GAMESTATE_HPP__
#define __GAMESTATE_HPP__

// ================================================ //

#include "AppState.hpp"

// ================================================ //

class GameStateImpl;

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
	std::tr1::shared_ptr<GameStateImpl> m_pImpl;
};

// ================================================ //

#endif

// ================================================ //