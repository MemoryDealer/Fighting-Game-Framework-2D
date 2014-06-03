// ================================================ //

#ifndef __MENUSTATEIMPL_HPP__
#define __MENUSTATEIMPL_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

class AppState;
class GUIMenuState;
class Stage;

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
	void processGUIAction(const int type);
	void update(double dt);

private:
	bool	m_bQuit;
	AppState* m_pMenuState;
	std::shared_ptr<GUIMenuState> m_pGUI;
	std::shared_ptr<Stage> m_pBackground;
};

// ================================================ //

#endif

// ================================================ //