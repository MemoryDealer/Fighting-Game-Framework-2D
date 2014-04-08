// ================================================ //

#ifndef __PLAYERSTATES_HPP__
#define __PLAYERSTATES_HPP__

// ================================================ //

namespace Fighter{
	enum{
		DUMMY = 50,
		LORD_GRISHNAKH,
		CORPSE_EXPLOSION
	};
}

// ================================================ //

namespace PlayerSide{
	enum{
		LEFT = 0,
		RIGHT
	};
}

// ================================================ //

namespace PlayerInputType{
	enum{
		LOCAL = 0,
		AI,
		NET
	};
}

// ================================================ //

namespace PlayerState{
	// These along with PlayerAction may seem redundant, but they may be needed for AI/network player input
	enum{
		IDLE = 0,
		WALKING_FORWARD,
		WALKING_BACK,
		BLOCKING,
		ATTACKING,
		SPECIAL_OPENER,
		SPECIAL_NONOPENER,
		AUTO_DOUBLE,
		LINKER,
		ENDER,

		_
	};
}

// ================================================ //

namespace PlayerAction{
	enum{
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
		SPECIAL5,
		
		__
	};
}

// ================================================ //

#endif

// ================================================ //