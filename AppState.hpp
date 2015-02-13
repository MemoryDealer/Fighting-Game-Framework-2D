// ========================================================================= //
// Fighting game framework (2D) with online multiplayer.
// Copyright(C) 2014 Jordan Sparks <unixunited@live.com>
//
// This program is free software; you can redistribute it and / or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 3
// of the License, or(at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
// ========================================================================= //
// File: AppState.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines AppStateListener class, AppState class, 
// and DECLARE_APPSTATE_CLASS macro.
// ================================================ //

#ifndef __APPSTATE_HPP__
#define __APPSTATE_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

class AppState;

// ================================================ //

// Must be defined to be inherited from by AppStateManager.
class AppStateListener
{
public:
	// Empty constructor.
	explicit AppStateListener(void){};

	// Empty destructor.
	virtual ~AppStateListener(void){};

	// Adds a new state to the AppStateManager (defined later).
	virtual void manageAppState(const std::string& stateName, AppState* pState) = 0;

	// Returns the AppState with the corresponding name, if found.
	// Parameters:
	// stateName - name of state defined by user when it's created
	virtual AppState* findByName(const std::string& stateName) = 0;

	// Exits the current AppState and starts pState.
	virtual void changeAppState(AppState* pState) = 0;

	// Pauses the current states, push pState onto state stack and starts it.
	virtual bool pushAppState(AppState* pState) = 0;

	// Removes current state from state stack and resumes next one. If there are 
	// no more states, the App is shutdown.
	virtual void popAppState(void) = 0;

	// Pauses execution/updating of current state.
	virtual void pauseAppState(void) = 0;

	// Shuts down the App, eventually closing the program.
	virtual void shutdown(void) = 0;
};

// ================================================ //

// AppState is a blueprint for all states in the game. Each game state
// inherits from this class.
class AppState
{
public:
	// Sets m_quit to false.
	virtual ~AppState(void){ m_quit = false; }

	// Initializes a new AppState for use in the game.
	static void create(AppStateListener* parent, const std::string& name){}

	// Simply frees the AppState from memory.
	void destroy(void){ delete this; }

	// Enters the AppState and begins updating.
	virtual void enter(void) = 0;

	// Exits the AppState.
	virtual void exit(void) = 0;

	// Pauses updating of AppState, can be resumed later.
	virtual bool pause(void){ return true; }

	// Resumes updating of AppState.
	virtual void resume(void){};

	// Function to be overriden by derived states.
	virtual void handleInput(SDL_Event& e) = 0;

	// Should be overriden by derived states, all updating done here.
	virtual void update(double dt) = 0;

	// Returns name of state (defined when they are created).
	const std::string& getName(void){ return m_name; }

	// Returns AppState with name stateName by calling the AppStateManager's findByName().
	AppState* findByName(const std::string& stateName){ return m_pParent->findByName(stateName); }

	// Pushes an AppState by calling the AppStateManager's pushAppState().
	bool pushAppState(AppState* pState){ return m_pParent->pushAppState(pState); }

	// Pops the state stack by calling the AppStateManager's popAppState().
	void popAppState(void){ m_pParent->popAppState(); }

	// Sets m_quit to false.
	void reset(void){ m_quit = false; }

protected:
	// Empty destructor.
	explicit AppState(void){}
	
	// Pauses the current active AppState and starts pState, pushing it on the stack.
	void changeAppState(AppState* pState){ m_pParent->changeAppState(pState); }

	// Shuts down the AppStateManager, eventually terminating the program.
	void shutdown(void){ m_pParent->shutdown(); }

	// Pointer to the AppStateManager, which is derived from AppStateListener.
	AppStateListener* m_pParent;
	std::string m_name;
	bool m_quit;
};

// ================================================ //

// Should be place in definition of each class derived from AppState.
// Allocates the AppState, adds the AppState to the AppStateManager 
// and registers its name.
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