// ================================================ //

#include "Move.hpp"

// ================================================ //

namespace MoveID{
	const char* Name[] = {
		"IDLE", "WALKING_FORWARD", "WALKING_BACK"
	};
}

// ================================================ //

Move::Move(void)
	:	id(0),
		numFrames(0),
		startupFrames(0),
		hitFrames(0),
		recoveryFrames(0),
		damage(0),
		knockback(0),
		repeat(false),
		reverse(false),
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
	cancels.clear();
	frames.clear();
}

// ================================================ //

// ================================================ //