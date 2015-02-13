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
// File: FSM.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines FSM class.
// ================================================ //

#ifndef __FSM_HPP__
#define __FSM_HPP__

// ================================================ //

#include "FState.hpp"

// ================================================ //

// Types for managing states.

typedef std::map<StateID, FState*, std::less<int>> StateMap;
typedef StateMap::value_type SM_VT;

// ================================================ //

// FSM (Finite State Machine) class. Holds an arbitrary number of 
// states and performs transitions on them.
class FSM
{
public:
	// Sets current state to id.
	explicit FSM(const StateID id);

	// Frees all FState pointers in the machine.
	~FSM(void);

	// The state machine moves to a new state depending on the current state
	// and the input. Returns the ID of the new state.
	StateID stateTransition(const int input);

	// Adds a new FState to the machine.
	void addState(FState* pState);

	// Removes an FState from the machine.
	void deleteState(const StateID id);

	// Getters

	// Returns the ID of the active state.
	const StateID getCurrentStateID(void) const;

	// Returns a pointer to the specified FState in the machine.
	FState* getStatePtr(const StateID id);

	// Setters

	// Sets the active state, overriding any transitions.
	void setCurrentState(const StateID id);

private:
	StateMap	m_stateMap;
	StateID		m_currentState;
};

// ================================================ //

// Getters

inline const StateID FSM::getCurrentStateID(void) const{ 
	return m_currentState; 
}

// Setters

inline void FSM::setCurrentState(const StateID id){ 
	m_currentState = id; 
}

// ================================================ //

#endif

// ================================================ //