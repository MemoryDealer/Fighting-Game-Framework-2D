// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: Player.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines Player class.
// ================================================ //

#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

// ================================================ //

#include "Object.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "FSM.hpp"

// ================================================ //

class Hitbox;
class Input;
struct Move;
class FighterMetadata;
class Timer;
class Widget;

typedef std::vector<std::shared_ptr<Move>> MoveList;
typedef std::vector<std::shared_ptr<Hitbox>> HitboxList;

// ================================================ //

// A Player is a fighter that can be controlled by human input, AI, or 
// a networked human or AI.
class Player : public Object
{
public:
	// Enumerations

	enum Side{
		LEFT = 0,
		RIGHT
	};

	enum Mode{
		LOCAL = 0,
		AI,
		NET
	};

	enum State{
		IDLE = 0,
		WALKING_FORWARD,
		WALKING_BACK,
		JUMPING,

		CROUCHING,
		CROUCHED,
		UNCROUCHING,

		ATTACK_LP,

		STUNNED_JUMP,
		STUNNED_HIT,
		STUNNED_BLOCK
	};

	// Allocates the Input object, which loads the button map from the specified file.
	// Loads all fighter data and moves. Builds the FSM.
	explicit Player(const std::string& fighterFile, const std::string& buttomMapFile = "", const int mode = Player::Mode::LOCAL);

	// Empty destructor.
	virtual ~Player(void);

	// Adds net input from client to processing queue.
	void enqueueClientInput(const Client::NetInput& input);

	// Determines whether or not to snap player to the new position, depending
	// on the distance, otherwise it graudally slides the player. Used when
	// receiving a network update on the client.
	void updateFromServer(const Server::PlayerUpdate& update);

	// Rewinds player state to last server update and replays unprocessed inputs.
	void serverReconciliation(void);

	// Processes pending input that is being replayed as part of server reconciliation.
	void processReplayedInput(double dt = 0);

	// Processes local input for player, adjusting its state.
	void processInput(double dt = 0);

	// Applies movement to the player based on key presses.
	void applyInput(double dt);

	// Updates the current Move, handles collision.
	virtual void update(double dt);

	// Renders the Player sprite.
	virtual void render(void);

	// Process animation updates for the current move.
	void updateMove(void);

	// Loads textures, moves, etc.
	void loadFighterData(const std::string& file);

	// Applies a hit from a move performed by the other player.
	// Returns true if the player was hit.
	bool takeHit(const Move* pMove);

	// Getters

	// Returns the Input object.
	Input* getInput(void) const;

	// Returns the mode the player is currently in.
	const Uint32 getMode(void) const;

	// Returns X velocity.
	const int32_t getXVelocity(void) const;

	// Returns X jump velocity.
	const int32_t getXJumpVelocity(void) const;

	// Returns pointer to player's health bar.
	Widget* getHealthBarPtr(void) const;

	// Returns the side the player is on (e.g., LEFT or RIGHT).
	const int getSide(void) const;

	// Returns current state ID.
	const Uint32 getCurrentState(void) const;

	// Returns HP (hit points).
	const Uint32 getCurrentHP(void) const;

	// Returns hitbox pointer at index n.
	Hitbox* getHitbox(const int n) const;

	// Returns maximum position X at which the player can be.
	const int getMaxXPos(void) const;

	// Returns pointer to current move.
	Move* getCurrentMove(void) const;

	// Setters

	// Sets the side of player, e.g., LEFT or RIGHT.
	void setSide(const Uint32 side);

	// Sets the mode of the player, e.g., LOCAL, NET, or AI.
	void setMode(const Uint32 mode);

	// Points the internal Widget pointer to the player's health bar.
	void setHealthBarPtr(Widget* pHealthBar);

	// Sets the side the player is on. Also sets the rendering flip variable 
	// accordingly.
	void setSide(const int side);

	// Sets current state.
	void setCurrentState(const Uint32 state);

	// Sets the Player's HP directly.
	void setCurrentHP(const Uint32 hp);

	// Sets the player object to draw hitboxes if true.
	void setDrawHitboxes(const bool draw);

	// Toggles the state of whether or not the player will draw hitboxes.
	void toggleDrawHitboxes(void);

	// Sets the player to colliding if true.
	void setColliding(const bool colliding);

	// Sets the current stun of the Player.
	void setStun(const Uint32 stun);

	bool hitboxesActive = false;

private:
	// Physics.

	int32_t m_xAccel;
	int32_t m_xVel;
	int32_t m_xMax;
	Uint32 m_jumpStrength;
	Uint32 m_jumpSpeed;
	int m_xJumpVel;
	double m_jump;

	int jumpCtr;

	// Render width and height (default dst rect).
	int m_rW, m_rH;

	// Game.

	// The y position at which player will appear 26 units from bottom of screen.
	int m_floor;
	Uint32 m_side;
	Uint32 m_mode;
	int m_maxHP;
	int m_currentHP;
	Uint32 m_currentStun;
	Widget* m_pHealthBar;
	std::shared_ptr<Input> m_pInput;
	MoveList m_moves;
	HitboxList m_hitboxes;
	std::shared_ptr<Move> m_pCurrentMove;
	std::shared_ptr<Timer> m_pMoveTimer;
	bool m_drawHitboxes;
	int m_maxXPos;
	bool m_colliding;

	// Net stuff.

	std::queue<Client::NetInput> m_clientInputs;
	std::queue<Server::PlayerUpdate> m_serverUpdates;
};

// ================================================ //

// Getters

inline Input* Player::getInput(void) const{
	return m_pInput.get();
}

inline const Uint32 Player::getMode(void) const{
	return m_mode;
}

inline const int32_t Player::getXVelocity(void) const{
	return (m_pFSM->getCurrentStateID() == Player::State::JUMPING) 
		? m_xJumpVel : m_xVel;
}

inline const int32_t Player::getXJumpVelocity(void) const{
	return m_xJumpVel;
}

inline Widget* Player::getHealthBarPtr(void) const{
	return m_pHealthBar;
}

inline const int Player::getSide(void) const{
	return m_side;
}

inline const Uint32 Player::getCurrentState(void) const{
	return m_pFSM->getCurrentStateID();
}

inline const Uint32 Player::getCurrentHP(void) const{
	return m_currentHP;
}

inline Hitbox* Player::getHitbox(const int n) const{
	return m_hitboxes[n].get();
}

inline const int Player::getMaxXPos(void) const{
	return m_maxXPos;
}

inline Move* Player::getCurrentMove(void) const{
	return m_pCurrentMove.get();
}

// Setters

inline void Player::setSide(const Uint32 side){
	m_side = side;
}

inline void Player::setMode(const Uint32 mode){
	m_mode = mode;
}

inline void Player::setHealthBarPtr(Widget* pHealthBar){
	m_pHealthBar = pHealthBar;
}

inline void Player::setSide(const int side){
	m_side = side;
	m_flip = (side == Player::Side::LEFT) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
}

inline void Player::setCurrentState(const Uint32 state){
	m_pFSM->setCurrentState(state);
}

inline void Player::setCurrentHP(const Uint32 hp){
	m_currentHP = hp;
}

inline void Player::setDrawHitboxes(const bool draw){
	m_drawHitboxes = draw;
}

inline void Player::toggleDrawHitboxes(void){
	m_drawHitboxes = !m_drawHitboxes;
}

inline void Player::setColliding(const bool colliding){
	m_colliding = colliding;
}

inline void Player::setStun(const Uint32 stun){
	m_currentStun = stun;
}

// ================================================ //

#endif

// ================================================ //