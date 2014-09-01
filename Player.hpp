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
		BLOCKING,
		ATTACKING,
		SPECIAL_OPENER,
		SPECIAL_NONOPENER,
		AUTO_DOUBLE,
		LINKER,
		ENDER
	};

	enum Action{
		NONE = 0,
		WALK_BACK, WALK_FORWARD,
		CROUCH,
		JUMP,
		LIGHT_PUNCH, MEDIUM_PUNCH, HEAVY_PUNCH,
		LIGHT_KICK, MEDIUM_KICK, HEAVY_KICK,
		SPECIAL1,
		SPECIAL2,
		SPECIAL3,
		SPECIAL4,
		SPECIAL5
	};

	// Allocates the Input object, which loads the button map from the specified file.
	// Loads all fighter data and moves. Builds the FSM.
	explicit Player(const std::string& fighterFile, const std::string& buttomMapFile = "", const int mode = Player::Mode::LOCAL);

	// Empty destructor.
	virtual ~Player(void);

	// Determines whether or not to snap player to the new position, depending
	// on the distance, otherwise it graudally slides the player. Used when
	// receiving a network update on the client.
	void updateFromServer(const Server::PlayerUpdate& update);

	// Processes local input for player, adjusting its state.
	void processInput(void);

	// Applies movement to the player based on key presses.
	void applyInput(double dt);

	// Updates the current Move, handles collision.
	virtual void update(double dt);

	// Renders the Player sprite.
	virtual void render(void);

	// Getters

	// Returns the Input object.
	Input* getInput(void) const;

	// Returns the mode the player is currently in.
	const Uint32 getMode(void) const;

	// Setters

	// Sets the side of player, e.g., LEFT or RIGHT.
	void setSide(const Uint32 side);

	// Sets the mode of the player, e.g., LOCAL, NET, or AI.
	void setMode(const Uint32 mode);

public: // Currently public for debugging purposes.
	int32_t m_xAccel, m_yAccel;
	int32_t m_xVel, m_yVel;
	int32_t m_xMax, m_yMax;

	Uint32 m_side;

	Uint32 m_mode;

	std::shared_ptr<Input> m_pInput;
	std::queue<Server::PlayerUpdate> m_playerUpdates;
};

// ================================================ //

// Getters

inline Input* Player::getInput(void) const{
	return m_pInput.get();
}

inline const Uint32 Player::getMode(void) const{
	return m_mode;
}

// Getters

inline void Player::setSide(const Uint32 side){
	m_side = side;
}

inline void Player::setMode(const Uint32 mode){
	m_mode = mode;
}

// ================================================ //

#endif

// ================================================ //