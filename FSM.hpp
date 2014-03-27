// ================================================ //

#ifndef __FSM_HPP__
#define __FSM_HPP__

// ================================================ //

#include "FState.hpp"

// ================================================ //

typedef std::map<StateID, FState*, std::less<int>> StateMap;
typedef StateMap::value_type SM_VT;

// ================================================ //
// Finite State Machine
// ================================================ //

class FSM
{
public:
	explicit FSM(const StateID id);
	~FSM(void);

	StateID stateTransition(const int input);

	void addState(FState* pState);
	void deleteState(const StateID id);

	// Getter functions
	const StateID getCurrentStateID(void) const;
	FState* getStatePtr(const StateID id);

	// Setter functions
	void setCurrentState(const StateID id);

private:
	StateMap	m_stateMap;
	StateID		m_currentState;
};

// ================================================ //

inline const StateID FSM::getCurrentStateID(void) const
{ return m_currentState; }

inline void FSM::setCurrentState(const StateID id)
{ m_currentState = id; }

// ================================================ //

#endif

// ================================================ //