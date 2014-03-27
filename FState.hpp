// ================================================ //

#ifndef __FSTATE_HPP__
#define __FSTATE_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

typedef unsigned int StateID;

// ================================================ //

class FState
{
public:
	explicit FState(const StateID id);
	~FState(void);

	void addTransition(const int input, const StateID outputID);
	void deleteTransition(const int outputID);

	// Getter functions
	const StateID getID(void) const;
	const StateID getOutput(const int input);

private:
	std::vector<StateID>	m_inputs;
	std::vector<StateID>	m_outputs;
	StateID					m_stateID;
};

// ================================================ //

inline const StateID FState::getID(void) const
{ return m_stateID; }

// ================================================ //

#endif

// ================================================ //