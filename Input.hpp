// ================================================ //

#ifndef __INPUT_HPP__
#define __INPUT_HPP__

// ================================================ //

namespace Input{

	static const int NUM_INPUTS = 64;

	enum{
		NONE = 0,
		BUTTON_LEFT_PUSHED,
		BUTTON_LEFT_RELEASED,
		BUTTON_DOWN_PUSHED,
		BUTTON_DOWN_RELEASED,
		BUTTON_RIGHT_PUSHED,
		BUTTON_RIGHT_RELEASED,
		BUTTON_UP_PUSHED,
		BUTTON_UP_RELEASED,

		END_INPUT
	};
}

// ================================================ //

#endif

// ================================================ //