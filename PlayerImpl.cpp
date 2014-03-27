// ================================================ //

#include "PlayerImpl.hpp"
#include "PlayerStates.hpp"

// ================================================ //

PlayerImpl::PlayerImpl(const char* textureFilename)
	:	ObjectImpl(textureFilename)
{
	// Add states to core FSM
	FState* state = new FState(PlayerState::IDLE);

	// State Idle
	state->addTransition(PlayerAction::NONE, PlayerState::IDLE);
	state->addTransition(PlayerAction::LIGHT_PUNCH, PlayerState::ATTACKING);
	state->addTransition(PlayerAction::MEDIUM_PUNCH, PlayerState::ATTACKING);
	state->addTransition(PlayerAction::HEAVY_PUNCH, PlayerState::ATTACKING);
	state->addTransition(PlayerAction::LIGHT_KICK, PlayerState::ATTACKING);
	state->addTransition(PlayerAction::MEDIUM_KICK, PlayerState::ATTACKING);
	state->addTransition(PlayerAction::HEAVY_KICK, PlayerState::ATTACKING);
	m_pFSM->addState(state);

	// State Attacking
	state = new FState(PlayerState::ATTACKING);
	state->addTransition(PlayerAction::NONE, PlayerState::IDLE);
	state->addTransition(PlayerAction::LIGHT_PUNCH, PlayerState::ATTACKING); // light punch cancels into self
	m_pFSM->addState(state);

	// Set the starting state
	m_pFSM->setCurrentState(PlayerState::IDLE);
}

// ================================================ //

PlayerImpl::~PlayerImpl(void)
{

}

// ================================================ //

void PlayerImpl::update(double dt)
{
	printf("PlayerState: %d\n", m_pFSM->getCurrentStateID());
	this->setTextureCoordinates(m_src.x + 1, m_src.y);
	this->render();
}

// ================================================ //