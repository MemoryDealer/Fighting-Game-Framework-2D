// ================================================ //

#include "PlayerImpl.hpp"
#include "PlayerStates.hpp"
#include "Config.hpp"
#include "Engine.hpp"
#include "Input.hpp"

// ================================================ //

PlayerImpl::PlayerImpl(unsigned int fighter)
	:	ObjectImpl(fighter),
		m_fighter(fighter),
		m_xVel(0), 
		m_yVel(0),
		m_maxXVel(0),
		m_maxYVel(0),
		m_currentXVel(0),
		m_currentYVel(0)
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
	Config c, e;

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
	m_src.x = c.parseIntValue("cell", "x");
	m_src.y = c.parseIntValue("cell", "y");
	m_src.w = c.parseIntValue("cell", "w");
	m_src.h = c.parseIntValue("cell", "h");

	// Load size
	m_dst.w = c.parseIntValue("size", "w");
	m_dst.h = c.parseIntValue("size", "h");

	// Movement
	m_xVel = c.parseIntValue("movement", "xVel");
	m_yVel = c.parseIntValue("movement", "yVel");
	m_maxXVel = c.parseIntValue("movement", "xMax");
	m_maxYVel = c.parseIntValue("movement", "yMax");

	// set floor (temporary)
	e.loadFile("Data/Config/game.cfg");
	m_dst.y = e.parseIntValue("game", "floor");
}

// ================================================ //

void PlayerImpl::processInput(const int input)
{
	switch(input){
	default:
		break;

	case Input::EPSILON:
		m_currentXVel = 0;
		printf("EPSILON!!!\n");
		break;

	case Input::BUTTON_LEFT_PUSHED:
		m_currentXVel -= m_xVel;
		if(std::abs(m_currentXVel) > m_maxXVel)
			m_currentXVel = -m_maxXVel;
		break;

	case Input::BUTTON_LEFT_RELEASED:
		if(m_currentXVel < 0)
			m_currentXVel += m_xVel;
		break;

	case Input::BUTTON_RIGHT_PUSHED:
		m_currentXVel += m_xVel;
		if(m_currentXVel > m_maxXVel)
			m_currentXVel = m_maxXVel;
		break;

	case Input::BUTTON_RIGHT_RELEASED:
		if(m_currentXVel > 0)
			m_currentXVel -= m_xVel;
		break;
	}
}

// ================================================ //

void PlayerImpl::update(double dt)
{
	m_dst.x += static_cast<int>(m_currentXVel * dt);
	printf("Vel: %d\n", m_currentXVel);

	this->render();
}

// ================================================ //