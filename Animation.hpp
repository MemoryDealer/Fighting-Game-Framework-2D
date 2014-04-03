// ================================================ //

#ifndef __ANIMATION_HPP__
#define __ANIMATION_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

namespace AnimationID{
	enum{
		IDLE = 0,
		WALKING_FORWARD,
		WALKING_BACK,

		END_ANIMATIONS
	};
}

// ================================================ //

class Animation
{
public:
	explicit Animation(void){}
	virtual ~Animation(void){}

//private:
	int id;
	int x1, y1;
	int x2, y2;
};

// ================================================ //

#endif

// ================================================ //