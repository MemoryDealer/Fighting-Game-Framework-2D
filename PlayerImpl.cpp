// ================================================ //

#include "PlayerImpl.hpp"
#include "PlayerStates.hpp"
#include "Config.hpp"

// ================================================ //

PlayerImpl::PlayerImpl(unsigned int fighter)
	:	ObjectImpl(fighter),
		m_fighter(fighter)
{
	// Load configuration settings
	this->loadFighterData();

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

void PlayerImpl::loadFighterData(void)
{
	Config c;

	//! Add a fighter data file integrity check here?

	switch(m_fighter){
	default:
		break;

	case Fighter::LORD_GRISHNAKH:
		c.loadFile("Data/Config/varg.fighter");
		break;
	}

	if(!c.isLoaded()){
		throw std::exception("Failed to load fighter file!");
	}

	// Load spritesheet
	this->setTextureFile(c.parseValue("core", "spriteSheet").c_str());

	// Load src rect
	m_src.x = c.parseIntValue("src", "x");
	m_src.y = c.parseIntValue("src", "y");
	m_src.w = m_dst.w = c.parseIntValue("src", "w");
	m_src.h = m_dst.h = c.parseIntValue("src", "h");
}

// ================================================ //

void PlayerImpl::update(double dt)
{
	//printf("PlayerState: %d\n", m_pFSM->getCurrentStateID());
	this->setTextureCoordinates(m_src.x + 1, m_src.y);
	this->render();
}

// ================================================ //