// ================================================ //

#ifndef __INPUT_HPP__
#define __INPUT_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

class Input
{
public:
	Input(void);
	~Input(void);

	enum{
		BUTTON_LEFT = 0,
		BUTTON_DOWN,
		BUTTON_RIGHT,
		BUTTON_UP,

		NUM_BUTTONS
	};

	// Getter functions
	const bool getButton(const int button) const;

	// Setter functions
	void setButton(const int button, const bool state);

private:
	int m_type;
	bool m_buttons[NUM_BUTTONS];
};

// ================================================ //

// Getters
inline const bool Input::getButton(const int button) const{
	return m_buttons[button];
}

// Setters
inline void Input::setButton(const int button, const bool state){
	m_buttons[button] = state;
}

// ================================================ //

#endif

// ================================================ //