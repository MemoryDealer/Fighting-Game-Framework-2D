// ================================================ //

#ifndef __ANIMATION_HPP__
#define __ANIMATION_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

namespace MoveID{
	enum{
		IDLE = 0,
		WALKING_FORWARD,
		WALKING_BACK,

		END_MOVES
	};

	extern const char* Name[];
}

// ================================================ //

typedef std::vector<SDL_Rect> HitboxRectList;

struct Frame{
	int x;
	int y;
	int w;
	int h;

	SDL_Rect toSDLRect(void){
		SDL_Rect r;
		r.x = this->x;
		r.y = this->y;
		r.w = this->w;
		r.h = this->h;
		return r;
	}

	// Holds each hitbox for a single frame
	HitboxRectList hitboxes;
};

typedef std::vector<Frame> FrameList;

// ================================================ //

struct Move
{
	explicit Move(void);
	virtual ~Move(void);

	int id;
	std::string name;
	int numFrames;
	int frameGap;	// how long to wait between frames (ms)
	int startupFrames, hitFrames, recoveryFrames;
	int damage;
	int knockback;
	bool repeat, reverse;
	int repeatFrame;
	std::vector<int> cancels; // list of moves this move cancels into
	int xVel, yVel;

	int currentFrame;
	FrameList frames;
};

// ================================================ //

#endif

// ================================================ //