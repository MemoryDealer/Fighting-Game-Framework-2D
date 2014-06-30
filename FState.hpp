// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: FState.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines FState class.
// ================================================ //

#ifndef __FSTATE_HPP__
#define __FSTATE_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

typedef unsigned int StateID;

// ================================================ //

// A state for use by the FSM (Finite State Machine) class.
class FState
{
public:
	// Sets the state ID for the state.
	explicit FState(const StateID id);

	// Empty destructor.
	~FState(void);

	// Adds a new transition for this state. When this state is active 
	// in the FSM, the given input will make the FSM transition to the outputID
	// state.
	void addTransition(const int input, const StateID outputID);

	// Getters

	// Returns the ID of the state.
	const StateID getID(void) const;

	// Returns the ID of the state transition the input produces. Returns 
	// its own ID if one doesn't exist.
	const StateID getOutput(const int input);

private:
	std::vector<StateID>	m_inputs;
	std::vector<StateID>	m_outputs;
	StateID					m_stateID;
};

// ================================================ //

inline const StateID FState::getID(void) const{ 
	return m_stateID;
}

// ================================================ //

#endif

// ================================================ //