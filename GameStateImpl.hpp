// ================================================ //

#ifndef __GAMESTATEIMPL_HPP__
#define __GAMESTATEIMPL_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

class ObjectManager;

// ================================================ //

class GameStateImpl
{
public:
	explicit GameStateImpl(void);
	~GameStateImpl(void);

	void enter(void);
	void exit(void);
	bool pause(void);
	void resume(void);
	void handleInput(SDL_Event& e);
	void update(double dt);

	const bool shouldPop(void) const;

private:
	bool	m_bQuit;

	std::shared_ptr<ObjectManager> m_pObjectManager;
};

// ================================================ //

inline const bool GameStateImpl::shouldPop(void) const
{ return m_bQuit; }

// ================================================ //

#endif

// ================================================ //