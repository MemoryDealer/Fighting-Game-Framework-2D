// ================================================ //

#include "FState.hpp"
#include "Engine.hpp"

// ================================================ //

FState::FState(const StateID id)
	:	m_inputs(),
		m_outputs(),
		m_stateID(id)
{

}

// ================================================ //

FState::~FState(void)
{
	m_inputs.clear();
	m_outputs.clear();
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

	// Find the input
	for(size_t i=0; i<m_inputs.size(); ++i){
		if (m_inputs[i] == input){
			outputID = m_outputs[i];
		}
	}

	return outputID;
}

// ================================================ //