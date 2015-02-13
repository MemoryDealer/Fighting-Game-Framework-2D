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
// File: FState.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements FState class.
// ================================================ //

#include "FState.hpp"
#include "Engine.hpp"

// ================================================ //

FState::FState(const StateID id) :
m_inputs(),
m_outputs(),
m_stateID(id)
{

}

// ================================================ //

FState::~FState(void)
{
	
}

// ================================================ //

void FState::addTransition(const int input, const StateID outputID)
{
	Assert(m_inputs.size() == m_outputs.size(), "Inputs and outputs not equal");

	m_inputs.push_back(input);
	m_outputs.push_back(outputID);
}

// ================================================ //

const StateID FState::getOutput(const int input)
{
	StateID outputID = m_stateID;

	for(size_t i=0; i<m_inputs.size(); ++i){
		if (m_inputs[i] == input){
			outputID = m_outputs[i];
		}
	}

	return outputID;
}

// ================================================ //