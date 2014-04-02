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
};

// ================================================ //

namespace PlayerState{
	enum{
		IDLE = 0,
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
		MOVE_LEFT, MOVE_RIGHT,
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