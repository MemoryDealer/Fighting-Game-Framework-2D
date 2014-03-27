// ================================================ //

#include "FSM.hpp"
#include "Engine.hpp"

// ================================================ //

FSM::FSM(StateID id)
	:	m_stateMap(),
		m_currentState(id)
{

}

// ================================================ //

FSM::~FSM(void)
{
	// Free any pointers in the map
	FState* pState = nullptr;
	StateMap::iterator itr;

	if(!m_stateMap.empty()){
		for(itr = m_stateMap.begin();
			itr != m_stateMap.end();
			++itr){
			pState = static_cast<FState*>(itr->second);
			if(pState != nullptr)
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

	// See if this state already exists
	existingState = this->getStatePtr(pState->getID());

	if(existingState != nullptr)
		return;

	m_stateMap.insert(SM_VT(pState->getID(), pState));
}

// ================================================ //

void FSM::deleteState(const StateID id)
{
	FState* pState = nullptr;
	StateMap::iterator itr;

	pState = this->getStatePtr(id);

	if(pState != nullptr){
		if(pState->getID() == id){
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

	if(!m_stateMap.empty()){
		itr = m_stateMap.find(id);
		if(itr != m_stateMap.end()){
			pState = static_cast<FState*>(itr->second);
		}
	}

	return pState;
}

// ================================================ //