// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: Move.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements Move struct.
// ================================================ //

#include "Move.hpp"

// ================================================ //

namespace MoveID{
	const char* Name[] = {
		"IDLE", "WALKING_FORWARD", "WALKING_BACK", "JUMPING", 
		"CROUCHING", "CROUCHED", "UNCROUCHING",
		"ATTACK_LP",
		"STUNNED_JUMP", "STUNNED_HIT", "STUNNED_BLOCK"
	};
}

// ================================================ //

Move::Move(void) :
id(0),
numFrames(0),
startupFrames(0),
hitFrames(0),
recoveryFrames(0),
damage(0),
hitstun(0),
blockstun(0),
knockback(0),
recoil(0),
repeat(false),
reverse(false),
repeatFrame(0),
transition(-1),
cancels(),
xVel(0),
yVel(0),
currentFrame(0),
frames()
{

}

// ================================================ //

Move::~Move(void)
{
	
}

// ================================================ //

