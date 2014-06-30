// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
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