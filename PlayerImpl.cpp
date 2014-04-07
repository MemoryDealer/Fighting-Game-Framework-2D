// ================================================ //

#include "PlayerImpl.hpp"
#include "Engine.hpp"
#include "FSM.hpp"
#include "MessageRouter.hpp"
#include "Move.hpp"
#include "FighterMetadata.hpp"
#include "Timer.hpp"

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
		m_input(),
		m_moves(),
		m_pCurrentMove(nullptr),
		m_pMoveTimer(new Timer())
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
	Log::getSingletonPtr()->logMessage("Clearing move list for \"" + m_name + "\"");
	for(MoveList::iterator itr = m_moves.begin();
		itr != m_moves.end();
		++itr){
		delete *itr;
	}

	m_moves.clear();
}

// ================================================ //

void PlayerImpl::loadFighterData(void)
{
	FighterMetadata m;
	Config e;

	//! Add a fighter data file integrity check here?

	switch(m_fighter){
	default:
		break;

	case Fighter::LORD_GRISHNAKH:
		m.loadFile("Data/Config/varg.fighter");
		break;

	case Fighter::CORPSE_EXPLOSION:
		m.loadFile("Data/Config/corpse-explosion.fighter");
		break;
	}

	if(!m.isLoaded()){
		throw std::exception("Failed to load fighter file!");
	}

	// Load spritesheet
	this->setTextureFile(m.parseValue("core", "spriteSheet").c_str());

	// Size
	m_dst.w = m.parseIntValue("size", "w");
	m_dst.h = m.parseIntValue("size", "h");

	// Movement
	m_xAccel = m.parseIntValue("movement", "xAccel");
	m_yAccel = m.parseIntValue("movement", "yAccel");
	m_xMax = m.parseIntValue("movement", "xMax");
	m_yMax = m.parseIntValue("movement", "yMax");

	// set floor (temporary)
	e.loadFile("Data/Config/game.cfg");
	m_dst.y = e.parseIntValue("game", "floor");

	this->loadMoves(m);

	// Default the source rect to the first frame of IDLE
	m_src = m_moves[MoveID::IDLE]->frames[0];
	m_pCurrentMove = m_moves[MoveID::IDLE];
}

// ================================================ //

void PlayerImpl::loadMoves(FighterMetadata& m)
{
	for(int i=0; i<MoveID::END_MOVES; ++i){
		Log::getSingletonPtr()->logMessage("Parsing move \"" + std::string(MoveID::Name[i]) + "\" for " + m_name);

		m_moves.push_back(m.parseMove(MoveID::Name[i]));
		if(m_moves.back() == nullptr){
			std::string exc = "Unable to load move \"" + std::string(MoveID::Name[i]) + 
				"\" for fighter " + Engine::toString(m_fighter);
			throw std::exception(exc.c_str());
		}
	}

	m_pMoveTimer->restart();
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

void PlayerImpl::updateMove(double dt)
{
	static StateID lastState = 0;

	// Force the current animation to stop instantly if it has changed to a new one
	if(m_pCurrentMove != m_moves[m_pFSM->getCurrentStateID()]){
		m_pCurrentMove->currentFrame = m_pCurrentMove->repeatFrame;
		m_pMoveTimer->setStartTicks(0);
	}

	switch(m_pFSM->getCurrentStateID()){
		default:
			break;

		case PlayerState::IDLE:
			m_pCurrentMove = m_moves[MoveID::IDLE];
			break;

		case PlayerState::WALKING_FORWARD:
			m_pCurrentMove = m_moves[MoveID::WALKING_FORWARD];
			break;

		case PlayerState::WALKING_BACK:
			m_pCurrentMove = m_moves[MoveID::WALKING_BACK];
			break;

		case PlayerState::BLOCKING:
			printf("BLOCKING\n");
			break;
	}

	// Update frame
	if(m_pMoveTimer->getTicks() > m_pCurrentMove->frameGap){
		m_src = m_pCurrentMove->frames[m_pCurrentMove->currentFrame];
		/*m_dst.w = m_src.w * 2;
		m_dst.h = m_src.h * 2;*/
		if(m_name == "Object1")
			printf("Frame: %d\n", m_pCurrentMove->currentFrame);

		if(m_pCurrentMove->reverse){
			static bool dir = true;

			if(dir){
				if(++m_pCurrentMove->currentFrame >= m_pCurrentMove->numFrames){
					--m_pCurrentMove->currentFrame;
					dir = false;
				}
			}
			else{
				if(--m_pCurrentMove->currentFrame < m_pCurrentMove->repeatFrame){
					++m_pCurrentMove->currentFrame;
					dir = true;
				}
			}
		}
		else if(++m_pCurrentMove->currentFrame >= m_pCurrentMove->numFrames){
			if(m_pCurrentMove->repeat){
				m_pCurrentMove->currentFrame = m_pCurrentMove->repeatFrame;
			}
		}

		m_pMoveTimer->restart();
	}
}

// ================================================ //

void PlayerImpl::sendMessage(const Message& msg)
{
	printf("Received message %d\n", msg.type);
	if(msg.type == MessageType::TYPE_ACTIVATE)
		m_dead = true;
}

// ================================================ //

void PlayerImpl::update(double dt)
{
	this->updateMove(dt);

	m_dst.x += static_cast<int>(m_xVel * dt);

	this->render();
}

// ================================================ //