// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
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