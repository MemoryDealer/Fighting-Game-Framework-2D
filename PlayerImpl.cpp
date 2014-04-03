// ================================================ //

#include "PlayerImpl.hpp"
#include "Engine.hpp"
#include "Input.hpp"

// ================================================ //

PlayerImpl::PlayerImpl(unsigned int fighter)
	:	ObjectImpl(fighter),
		m_fighter(fighter),
		m_xAccel(0),
		m_yAccel(0),
		m_xVel(0), 
		m_yVel(0),
		m_xMax(0),
		m_yMax(0),
		m_currentAction(PlayerAction::NONE),
		m_playerSide(PlayerSide::LEFT),
		m_animations(),
		m_pCurrentAnimation(nullptr),
		m_animationTimer()
{
	// Load configuration settings
	this->loadFighterData();

	// Add states to core FSM
	FState* state = new FState(PlayerState::IDLE);

	// State Idle
	state->addTransition(PlayerAction::NONE, PlayerState::IDLE);
	state->addTransition(PlayerAction::WALK_FORWARD, PlayerState::WALKING_FORWARD);
	state->addTransition(PlayerAction::WALK_BACK, PlayerState::WALKING_BACK);
	state->addTransition(PlayerAction::LIGHT_PUNCH, PlayerState::ATTACKING);
	state->addTransition(PlayerAction::MEDIUM_PUNCH, PlayerState::ATTACKING);
	state->addTransition(PlayerAction::HEAVY_PUNCH, PlayerState::ATTACKING);
	state->addTransition(PlayerAction::LIGHT_KICK, PlayerState::ATTACKING);
	state->addTransition(PlayerAction::MEDIUM_KICK, PlayerState::ATTACKING);
	state->addTransition(PlayerAction::HEAVY_KICK, PlayerState::ATTACKING);
	m_pFSM->addState(state);

	// State Walking
	state = new FState(PlayerState::WALKING_FORWARD);
	state->addTransition(PlayerAction::NONE, PlayerState::IDLE);
	state->addTransition(PlayerAction::WALK_FORWARD, PlayerState::WALKING_FORWARD);
	m_pFSM->addState(state);

	// State Blocking
	state = new FState(PlayerState::WALKING_BACK);
	state->addTransition(PlayerAction::NONE, PlayerState::IDLE);
	state->addTransition(PlayerAction::WALK_BACK, PlayerState::WALKING_BACK);
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
	Log::getSingletonPtr()->logMessage("Clearing animation list for \"" + m_name + "\"");
	for(AnimationList::iterator itr = m_animations.begin();
		itr != m_animations.end();
		++itr){
		delete *itr;
	}

	m_animations.clear();
}

// ================================================ //

void PlayerImpl::loadFighterData(void)
{
	Config c(Config::FIGHTER), e;

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
	m_xAccel = c.parseIntValue("movement", "xAccel");
	m_yAccel = c.parseIntValue("movement", "yAccel");
	m_xMax = c.parseIntValue("movement", "xMax");
	m_yMax = c.parseIntValue("movement", "yMax");

	// set floor (temporary)
	e.loadFile("Data/Config/game.cfg");
	m_dst.y = e.parseIntValue("game", "floor");

	this->loadAnimations(c);
}

// ================================================ //

void PlayerImpl::loadAnimations(Config& c)
{
	for(int i=0; i<AnimationID::END_ANIMATIONS; ++i){
		m_animations.push_back(c.parseAnimation(i));
	}

	m_animationTimer.restart();
}

// ================================================ //

void PlayerImpl::processInput(const int input)
{
	m_currentAction = PlayerAction::NONE;

	switch(input){
	default:
		break;

	case Input::NONE:
		// This is currently blocked by PlayerManager::update()
		break;

	case Input::BUTTON_LEFT_PUSHED:
		m_xVel -= m_xAccel;
		if(m_xVel < -m_xMax)
			m_xVel = -m_xMax;

		m_currentAction = (m_playerSide == PlayerSide::LEFT) ?
			PlayerAction::WALK_BACK : PlayerAction::WALK_FORWARD;
		break;

	case Input::BUTTON_LEFT_RELEASED:
		if(m_xVel < 0)
			m_xVel += m_xAccel;
		break;

	case Input::BUTTON_RIGHT_PUSHED:
		m_xVel += m_xAccel;
		if(m_xVel > m_xMax)
			m_xVel = m_xMax;

		m_currentAction = (m_playerSide == PlayerSide::RIGHT) ?
			PlayerAction::WALK_BACK : PlayerAction::WALK_FORWARD;
		break;

	case Input::BUTTON_RIGHT_RELEASED:
		if(m_xVel > 0)
			m_xVel -= m_xAccel;
		break;
	}

	m_pFSM->stateTransition(m_currentAction);
}

// ================================================ //

void PlayerImpl::updateAnimation(double dt)
{
	switch(m_pFSM->getCurrentStateID()){
		default:
			break;

		case PlayerState::IDLE:
			m_pCurrentAnimation = m_animations[AnimationID::IDLE];
			break;

		case PlayerState::WALKING_FORWARD:
			m_pCurrentAnimation = m_animations[AnimationID::WALKING_FORWARD];
			break;

		case PlayerState::WALKING_BACK:
			m_pCurrentAnimation = m_animations[AnimationID::WALKING_BACK];
			break;

		case PlayerState::BLOCKING:
			printf("BLOCKING\n");
			break;
	}

	// Update frame
	if(m_animationTimer.getTicks() > 250){
		m_src.x = m_src.w * (m_pCurrentAnimation->x1 + m_pCurrentAnimation->currentXFrame);
		m_src.y = m_src.h * (m_pCurrentAnimation->y1 + m_pCurrentAnimation->currentYFrame) - m_src.h;
		if((++m_pCurrentAnimation->currentXFrame) >= m_pCurrentAnimation->numXFrames){
			m_pCurrentAnimation->currentXFrame = 0;
		}
		if((++m_pCurrentAnimation->currentYFrame) >= m_pCurrentAnimation->numYFrames){
			m_pCurrentAnimation->currentYFrame = 0;
		}

		m_animationTimer.restart();
	}
}

// ================================================ //

void PlayerImpl::update(double dt)
{
	m_dst.x += static_cast<int>(m_xVel * dt);

	this->updateAnimation(dt);
	this->render();
}

// ================================================ //