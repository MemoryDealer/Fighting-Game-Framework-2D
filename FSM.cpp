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
// File: FSM.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements FSM class.
// ================================================ //

#include "FSM.hpp"
#include "Engine.hpp"

// ================================================ //

FSM::FSM(StateID id) :
m_stateMap(),
m_currentState(id)
{

}

// ================================================ //

FSM::~FSM(void)
{
	FState* pState = nullptr;
	StateMap::iterator itr;

	if (!m_stateMap.empty()){
		for(itr = m_stateMap.begin();
			itr != m_stateMap.end();
			++itr){
			pState = static_cast<FState*>(itr->second);
			if (pState != nullptr)
				delete pState;
		}
	}
}

// ================================================ //

StateID FSM::stateTransition(const int input)
{
	FState* pState = this->getStatePtr(m_currentState);

	Assert(static_cast<int>(pState != nullptr), "FState is nullptr in FSM");

	m_currentState = pState->getOutput(input);
	return m_currentState;
}

// ================================================ //

void FSM::addState(FState* pState)
{
	FState* existingState = nullptr;
	StateMap::iterator itr;

	// See if this state already exists. Return if it does.
	existingState = this->getStatePtr(pState->getID());

	if (existingState != nullptr){
		return;
	}

	m_stateMap.insert(SM_VT(pState->getID(), pState));
}

// ================================================ //

void FSM::deleteState(const StateID id)
{
	FState* pState = nullptr;
	StateMap::iterator itr;

	pState = this->getStatePtr(id);

	if (pState != nullptr){
		if (pState->getID() == id){
			m_stateMap.erase(itr);
			delete pState;
		}
	}
}

// ================================================ //

FState* FSM::getStatePtr(const StateID id)
{
	FState* pState = nullptr;
	StateMap::iterator itr;

	if (!m_stateMap.empty()){
		itr = m_stateMap.find(id);
		if (itr != m_stateMap.end()){
			pState = static_cast<FState*>(itr->second);
		}
	}

	return pState;
}

// ================================================ //