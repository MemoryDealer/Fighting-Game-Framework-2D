// ================================================ //

#ifndef __APPSTATE_HPP__
#define __APPSTATE_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

class AppState;

// ================================================ //

class AppStateListener
{
public:
	explicit AppStateListener(void){};
	virtual ~AppStateListener(void){};

	virtual void manageAppState(const std::string& stateName, AppState* pState) = 0;

	virtual AppState*	findByName(const std::string& stateName) = 0;
	virtual void		changeAppState(AppState* pState) = 0;
	virtual bool		pushAppState(AppState* pState) = 0;
	virtual void		popAppState(void) = 0;
	virtual void		pauseAppState(void) = 0;
	virtual void		shutdown(void) = 0;
};

// ================================================ //
// Each game state inherits this class
class AppState
{
public:
	virtual ~AppState(void){}

	static void create(AppStateListener* parent, const std::string& name){}

	void destroy(void){ delete this; }

	virtual void enter(void) = 0;
	virtual void exit(void) = 0;
	virtual bool pause(void){ return true; }
	virtual void resume(void){};
	virtual void handleInput(SDL_Event& e) = 0;
	virtual void update(double dt) = 0;

	const std::string& getName(void){ return m_name; }

	AppState*	findByName(const std::string& stateName){ return m_pParent->findByName(stateName); }
	bool		pushAppState(AppState* pState){ return m_pParent->pushAppState(pState); }
	void		popAppState(void){ m_pParent->popAppState(); }

protected:
	explicit AppState(void){}
	
	void		changeAppState(AppState* pState){ m_pParent->changeAppState(pState); }
	void		shutdown(void){ m_pParent->shutdown(); }

	AppStateListener* m_pParent;
	std::string m_name;
};

// ================================================ //

#define DECLARE_APPSTATE_CLASS(T)\
static void create(AppStateListener* parent, const std::string& name)\
{\
	T* myAppState = new T();\
	myAppState->m_pParent = parent;\
	myAppState->m_name = name;\
	parent->manageAppState(name, myAppState);\
}

// ================================================ //

#endif

// ================================================ //