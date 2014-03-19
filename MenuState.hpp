// ================================================ //

#ifndef __MENUSTATE_HPP__
#define __MENUSTATE_HPP__

// ================================================ //

#include "AppState.hpp"

// ================================================ //

class MenuStateImpl;

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
	void update(double dt);

private:
	std::tr1::shared_ptr<MenuStateImpl> m_pImpl;
};

// ================================================ //

#endif

// ================================================ //