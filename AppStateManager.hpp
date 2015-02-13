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
// File: AppStateManager.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines AppStateManager class.
// ================================================ //

#ifndef __APPSTATEMANAGER_HPP__
#define __APPSTATEMANAGER_HPP__

// ================================================ //

#include "AppState.hpp"

// ================================================ //

// Holds a list of AppStates and the active stack of AppStates. Used to enter
// or exit these states by pushing, popping, changing, and pausing.
class AppStateManager : public AppStateListener
{
public:
	// Record to keep track of all AppStates.
	typedef struct{
		std::string name;
		AppState* pState;
	} STATE_INFO;

	// Sets m_bShutdown to false.
	explicit AppStateManager(void);

	// Exits all states on the active state stack. Destroys all states
	// in the list of states and clears the list.
	~AppStateManager(void);

	// Adds a new entry of STATE_INFO to the state list, pointing to pState.
	void manageAppState(const std::string& name, AppState* pState);

	// Searchs the state list (linear) and returns when the names match.
	AppState* findByName(const std::string& stateName);

	// Calls changeAppState() with pState. Creates a game clock and enters the 
	// main loop of the program. The MessageRouter and active AppState are updated
	// if the window is in focus.
	void start(AppState* pState);

	// Exits the active state, initializes pState and enters it, 
	// adding it to the stack.
	void changeAppState(AppState* pState);

	// Pauses active state, initializes and enters pState, 
	// adding it to the stack.
	bool pushAppState(AppState* pState);

	// Exits the current state and removes it from the active state stack. If there
	// is another state on the active state stack left, it is resumed. If not,
	// shutdown() is called.
	void popAppState(void);

	// Pauses active state and resumes the state in the stack below.
	void pauseAppState(void);

	// Sets m_bShutdown to true, forcing the main loop in start() to quit.
	void shutdown(void);

protected:
	// Empty here, can be overriden in game states.
	virtual void init(AppState* pState);

	std::vector<AppState*>	m_activeStateStack;
	std::vector<STATE_INFO> m_states;
	bool					m_bShutdown;
};

// ================================================ //

#endif

// ================================================ //