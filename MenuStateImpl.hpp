// ================================================ //

#ifndef __MENUSTATEIMPL_HPP__
#define __MENUSTATEIMPL_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

class AppState;

// ================================================ //

class MenuStateImpl
{
public:
	explicit MenuStateImpl(AppState* pMenuState);
	~MenuStateImpl(void);

	void enter(void);
	void exit(void);
	bool pause(void);
	void resume(void);
	void handleInput(SDL_Event& e);
	void processGUIAction(void);
	void update(double dt);

private:
	bool	m_bQuit;
	AppState* m_pMenuState;
};

// ================================================ //

#endif

// ================================================ //