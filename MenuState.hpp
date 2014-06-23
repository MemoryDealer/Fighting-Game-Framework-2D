// ================================================ //

#ifndef __MENUSTATE_HPP__
#define __MENUSTATE_HPP__

// ================================================ //

#include "AppState.hpp"

// ================================================ //

class GUIMenuState;
class Stage;

// ================================================ //

class MenuState : public AppState
{
public:
	explicit MenuState(void);
	~MenuState(void);

	DECLARE_APPSTATE_CLASS(MenuState);

	void enter(void);
	void exit(void);
	bool pause(void);
	void resume(void);
	void handleInput(SDL_Event& e);
	void update(double dt);

private:
	void processGUIAction(const int type);

	bool m_bQuit;
	std::shared_ptr<GUIMenuState> m_pGUI;
	std::shared_ptr<Stage> m_pBackground;
};

// ================================================ //

#endif

// ================================================ //