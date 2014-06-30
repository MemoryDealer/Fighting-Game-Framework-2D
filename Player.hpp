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
#include "PlayerData.hpp"

// ================================================ //

class Hitbox;
class Input;
struct Move;
class FighterMetadata;
class Timer;

typedef std::vector<std::shared_ptr<Move>> MoveList;
typedef std::vector<std::shared_ptr<Hitbox>> HitboxList;

// ================================================ //

// A Player is a fighter that can be controlled by human input, AI, or 
// a networked human or AI.
class Player : public Object
{
public:
	// Allocates the Input object, which loads the button map from the specified file.
	// Loads all fighter data and moves. Builds the FSM.
	explicit Player(const std::string& fighterFile, const std::string& buttomMapFile = "", const int mode = PlayerMode::LOCAL);

	// Empty destructor.
	virtual ~Player(void);

	// Getters

	// Returns the side the Player is on (e.g., LEFT or RIGHT).
	const int getSide(void) const;

	// Returns the Hitbox at the specified index.
	Hitbox* getHitbox(const int index);

	// Returns the current state ID.
	const int getCurrentState(void) const;

	// Returns true if the Player is colliding with the other Player (redundant...).
	const bool isColliding(void) const;

	// Returns the X-velocity.
	const int getVelocityX(void) const;

	// Returns the Y-velocity.
	const int getVelocityY(void) const;

	// Returns the mode (e.g., LOCAL, NET, or AI).
	const int getMode(void) const;

	// Returns the internal Input object.
	Input* getInput(void) const;

	// Setters

	// Sets the side value of the Player (e.g., LEFT or RIGHT).
	void setSide(const int side);

	// Sets the colliding value of the Player.
	void setColliding(const bool colliding);

	// Switches the state of drawing the debug hitboxes.
	void toggleDrawHitboxes(void);

	// Sets the mode (e.g., LOCAL, NET, or AI).
	void setMode(const int mode);

	// --- //

	// Handles Messages.
	virtual void sendMessage(const Message& msg);

	// Updates the current Move, handles collision, and renders the Player.
	virtual void update(double dt);

private:
	// Loads texture file(s), all fighter data, and calls loadMoves().
	void loadFighterData(const std::string& fighterFile);

	// Parses all Moves in .fighter file.
	void loadMoves(FighterMetadata& c);

	// Handles Player movement and actions according to the local input status.
	void updateLocalInput(void);

	// Updates the current Move according to the current state. Updates the current
	// frame of the move, and calls updateHitboxes().
	void updateMove(double dt);

	// Adjust each Hitbox according to its offset (from the Player's center).
	void updateHitboxes(void);

	// --- //

	int	m_xAccel, m_yAccel;
	int	m_xVel, m_yVel;
	int	m_xMax, m_yMax;
	int	m_currentAction;
	int	m_playerSide;

	std::shared_ptr<Input> m_pInput;
	int	m_mode;

	MoveList m_moves;
	std::shared_ptr<Move> m_pCurrentMove;
	std::shared_ptr<Timer> m_pMoveTimer;

	HitboxList m_hitboxes;
	bool m_colliding;
	bool m_drawHitboxes;
};

// ================================================ //

// Getters

inline const int Player::getSide(void) const{
	return m_playerSide;
}

inline Hitbox* Player::getHitbox(const int index){
	return m_hitboxes[index].get();
}

inline const bool Player::isColliding(void) const{
	return m_colliding;
}

inline const int Player::getVelocityX(void) const{
	return m_xVel;
}

inline const int Player::getVelocityY(void) const{
	return m_yVel;
}

inline const int Player::getMode(void) const{
	return m_mode;
}

inline Input* Player::getInput(void) const{
	return m_pInput.get();
}

// Setters

inline void Player::setSide(const int side){
	m_playerSide = side;
	m_flip = (side == PlayerSide::LEFT) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
}

inline void Player::toggleDrawHitboxes(void){
	m_drawHitboxes = !m_drawHitboxes;
}

inline void Player::setMode(const int mode){
	m_mode = mode;
}

// ================================================ //

#endif

// ================================================ //