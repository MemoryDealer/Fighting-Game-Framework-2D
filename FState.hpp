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

typedef Uint32 StateID;

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