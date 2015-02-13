// ========================================================================= //
// Fighting game framework (2D) with online multiplayer.
// Copyright(C) 2014 Jordan Sparks <unixunited@live.com>
//
// This program is free software; you can redistribute it and / or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 3
// of the License, or(at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
// ========================================================================= //
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

