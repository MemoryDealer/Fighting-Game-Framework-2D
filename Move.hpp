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
// File: Move.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines Move struct.
// ================================================ //

#ifndef __MOVE_HPP__
#define __MOVE_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

// All core moves for each fighter.
namespace MoveID{
	enum{
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
		STUNNED_BLOCK,

		END_MOVES
	};

	extern const char* Name[];
}

// ================================================ //

typedef std::vector<SDL_Rect> HitboxRectList;

// A single frame of animation during a move.
struct Frame{
	int x;
	int y;
	int w;
	int h;

	// Render width/height.
	int rw;
	int rh;

	// Frame gap.
	Uint32 gap;

	// Converts this frames coordinates to a SDL_Rect.
	SDL_Rect toSDLRect(void){
		SDL_Rect r;
		r.x = this->x;
		r.y = this->y;
		r.w = this->w;
		r.h = this->h;
		return r;
	}

	// All hitboxes for a frame.
	HitboxRectList hitboxes;
};

typedef std::vector<Frame> FrameList;

// ================================================ //

// A move that can be performed by a Player(e.g., move forward, light punch, etc.).
struct Move
{
	// Initializes all data to zero or false.
	explicit Move(void);

	// Empty destructor.
	virtual ~Move(void);

	int id;
	std::string name;
	int numFrames;
	// How long to wait between frames(ms).
	Uint32 frameGap;	
	int startupFrames, hitFrames, recoveryFrames;
	int damage;
	int hitstun, blockstun;
	int knockback;
	// How the attacking player is moved back upon landing a hit.
	int recoil;
	bool repeat, reverse;
	int repeatFrame;
	// The MoveID the player will transition to upon this move completing its frames.
	int transition;
	// List of moves this move cancels into.
	std::vector<int> cancels; 
	int xVel, yVel;

	// Active frame from the frame list.
	int currentFrame;
	FrameList frames;
};

// ================================================ //

#endif

// ================================================ //