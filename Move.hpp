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

typedef SDL_Rect Frame;
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
	std::vector<int> cancels; // list of moves this move cancels into
	int xVel, yVel;

	int currentFrame;
	FrameList frames;
};

// ================================================ //

#endif

// ================================================ //