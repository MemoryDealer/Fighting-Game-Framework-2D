// ================================================ //

#include "PlayerImpl.hpp"
#include "Player.hpp"
#include "FSM.hpp"
#include "MessageRouter.hpp"
#include "Move.hpp"
#include "FighterMetadata.hpp"
#include "Timer.hpp"
#include "Input.hpp"
#include "Camera.hpp"
#include "PlayerManager.hpp"
#include "Input.hpp"

// ================================================ //

const int MAX_HITBOXES = 7;

// ================================================ //

PlayerImpl::PlayerImpl(const std::string& fighterFile, const int inputType)
	:	ObjectImpl(),
		m_xAccel(0),
		m_yAccel(0),
		m_xVel(0), 
		m_yVel(0),
		m_xMax(0),
		m_yMax(0),
		m_currentAction(PlayerAction::NONE),
		m_playerSide(PlayerSide::LEFT),
		m_pInput(new Input()),
		m_moves(),
		m_pCurrentMove(nullptr),
		m_pMoveTimer(new Timer()),
		m_hitboxes(),
		m_colliding(false),
		m_drawHitboxes(false)
{
	// Load configuration settings
	this->loadFighterData(fighterFile);

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
	state->addTransition(PlayerAction::WALK_BACK, PlayerState::WALKING_BACK);
	m_pFSM->addState(state);

	// State Blocking
	state = new FState(PlayerState::WALKING_BACK);
	state->addTransition(PlayerAction::NONE, PlayerState::IDLE);
	state->addTransition(PlayerAction::WALK_BACK, PlayerState::WALKING_BACK);
	state->addTransition(PlayerAction::WALK_FORWARD, PlayerState::WALKING_FORWARD);
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

void PlayerImpl::loadFighterData(const std::string& fighterFile)
{
	FighterMetadata m(fighterFile);

	//! Add a fighter data file integrity check here?

	if (!m.isLoaded()){
		throw std::exception((std::string("Failed to load fighter file ") + std::string(fighterFile)).c_str());
	}

	// Load spritesheet
	this->setTextureFile(m.parseValue("core", "spriteSheet"));

	// Get player rendering size
	m_dst.w = m.parseIntValue("size", "w");
	m_dst.h = m.parseIntValue("size", "h");

	// Movement
	m_xAccel = m.parseIntValue("movement", "xAccel");
	m_yAccel = m.parseIntValue("movement", "yAccel");
	m_xMax = m.parseIntValue("movement", "xMax");
	m_yMax = m.parseIntValue("movement", "yMax");

	// Set player Y position 26 units from bottom, adjusting for player height
	m_dst.y = Engine::getSingletonPtr()->getLogicalWindowHeight() - m_dst.h - 26;

	// Load move set
	this->loadMoves(m);

	// Default the source rect to the first frame of IDLE
	m_src = m_moves[MoveID::IDLE]->frames[0].toSDLRect();
	m_pCurrentMove = m_moves[MoveID::IDLE];
}

// ================================================ //

void PlayerImpl::loadMoves(FighterMetadata& m)
{
	for(int i=0; i<MoveID::END_MOVES; ++i){
		Log::getSingletonPtr()->logMessage("Parsing move \"" + std::string(MoveID::Name[i]) + "\" for " + m_name);

		m_moves.push_back(m.parseMove(MoveID::Name[i]));
		if (m_moves.back() == nullptr){
			std::string exc = "Unable to load move \"" + std::string(MoveID::Name[i]) + 
				"\" for fighter " + m_name;
			throw std::exception(exc.c_str());
		}
	}

	// Reserve four normal hitboxes
	for(int i=0; i<4; ++i){
		m_hitboxes.push_back(Hitbox(HitboxType::NORMAL));
	}
	// Reserve one throw hitbox
	m_hitboxes.push_back(Hitbox(HitboxType::THROW));
	// Reserve two damage hitboxes
	m_hitboxes.push_back(Hitbox(HitboxType::DAMAGE));
	m_hitboxes.push_back(Hitbox(HitboxType::DAMAGE));
	// Reserve two counter hitboxes
	m_hitboxes.push_back(Hitbox(HitboxType::COUNTER));
	m_hitboxes.push_back(Hitbox(HitboxType::COUNTER));

	m_pMoveTimer->restart();
}

// ================================================ //

void PlayerImpl::updateLocalInput(void)
{
	m_currentAction = PlayerAction::NONE;

	// Movement
	// Checking both right now will force the player to cancel out movement if both are held
	// thus preventing the character from sliding when holding both down
	if (m_pInput->getButton(Input::BUTTON_LEFT) && 
		!m_pInput->getButton(Input::BUTTON_RIGHT)){
		m_xVel -= m_xAccel;
		if (m_xVel < -m_xMax)
			m_xVel = -m_xMax;

		m_currentAction = (m_playerSide == PlayerSide::LEFT) ? 
			PlayerAction::WALK_BACK : PlayerAction::WALK_FORWARD;
	}
	else if (m_pInput->getButton(Input::BUTTON_RIGHT) &&
		!m_pInput->getButton(Input::BUTTON_LEFT)){
		m_xVel += m_xAccel;
		if (m_xVel > m_xMax)
			m_xVel = m_xMax;

		m_currentAction = (m_playerSide == PlayerSide::RIGHT) ?
			PlayerAction::WALK_BACK : PlayerAction::WALK_FORWARD;
	}
	else{
		// Zero out left/right movement
		if (m_xVel < 0)
			m_xVel += m_xAccel;
		else if (m_xVel > 0)
			m_xVel -= m_xAccel;
	}

	m_pFSM->stateTransition(m_currentAction);
}

// ================================================ //

void PlayerImpl::updateMove(double dt)
{
	// Force the current animation to stop instantly if it has changed to a new one
	if (m_pCurrentMove != m_moves[m_pFSM->getCurrentStateID()]){
		m_pCurrentMove->currentFrame = m_pCurrentMove->repeatFrame;
		m_pMoveTimer->setStartTicks(0);
	}

	switch (m_pFSM->getCurrentStateID()){
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
			m_xVel = static_cast<int>(m_xVel * 0.90);
			break;

		case PlayerState::BLOCKING:
			printf("BLOCKING\n");
			break;
	}

	// Update frame
	if (m_pMoveTimer->getTicks() > m_pCurrentMove->frameGap){
		m_src = m_pCurrentMove->frames[m_pCurrentMove->currentFrame].toSDLRect();

		if (m_pCurrentMove->reverse){
			static bool dir = true;

			if (dir){
				if (++m_pCurrentMove->currentFrame >= m_pCurrentMove->numFrames){
					--m_pCurrentMove->currentFrame;
					dir = false;
				}
			}
			else{
				if (--m_pCurrentMove->currentFrame < m_pCurrentMove->repeatFrame){
					++m_pCurrentMove->currentFrame;
					dir = true;
				}
			}
		}
		else if (++m_pCurrentMove->currentFrame >= m_pCurrentMove->numFrames){
			if (m_pCurrentMove->repeat){
				m_pCurrentMove->currentFrame = m_pCurrentMove->repeatFrame;
			}
		}

		m_pMoveTimer->restart();
	}

	this->updateHitboxes();
}

// ================================================ //

void PlayerImpl::updateHitboxes(void)
{
	// Assign each hitbox to originate from the character's center
	// So a hitbox of (50, 0, 50, 50) will be 50x50 and 50 units to the right
	// of the character's center

	for(unsigned int i=0; i<m_hitboxes.size(); ++i){
		SDL_Rect offset = {0, 0, 0, 0};
		offset = m_pCurrentMove->frames[m_pCurrentMove->currentFrame].hitboxes[i];

		int xCenter = m_dst.x + (m_dst.w / 2);
		int yCenter = m_dst.y + (m_dst.h / 2);

		if (m_playerSide == PlayerSide::RIGHT)
			offset.x = -offset.x;

		m_hitboxes[i].setRect( (xCenter - (offset.w / 2) + offset.x), (yCenter - (offset.h / 2) + offset.y),
			offset.w, offset.h);
	}
}

// ================================================ //

void PlayerImpl::sendMessage(const Message& msg)
{
	printf("Received message %d\n", msg.type);
	if (msg.type == MessageType::TYPE_ACTIVATE)
		m_dead = true;
}

// ================================================ //

void PlayerImpl::setColliding(const bool colliding)
{
	m_colliding = colliding;

	if (m_colliding){
		if (m_pFSM->getCurrentStateID() == PlayerState::IDLE){
			m_pFSM->setCurrentState(PlayerState::WALKING_BACK);
			m_xVel = (m_playerSide == PlayerSide::LEFT) ? -m_xMax : m_xMax;
		}
	}
}

// ================================================ //

void PlayerImpl::update(double dt)
{
	//if (m_inputType == PlayerInputType::LOCAL){
	if (true){
		this->updateLocalInput();
	}

	this->updateMove(dt);

	if (m_colliding){
		// Move player back upon collision
		if (m_playerSide == PlayerSide::LEFT){
			m_dst.x = m_dst.x - static_cast<int>(m_xMax * dt);
		}
		else{
			m_dst.x = m_dst.x + static_cast<int>(m_xMax * dt);
		}
	}

	m_dst.x += static_cast<int>(m_xVel * dt);

	this->render();

	// Render hitboxes
	if (m_drawHitboxes){
		for (unsigned int i = 0; i < m_hitboxes.size(); ++i){
			m_hitboxes[i].render();
		}
	}
}

// ================================================ //