// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
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
	int frameGap;	
	int startupFrames, hitFrames, recoveryFrames;
	int damage;
	int knockback;
	bool repeat, reverse;
	int repeatFrame;
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