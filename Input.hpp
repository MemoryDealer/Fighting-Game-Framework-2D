// ================================================ //

#ifndef __INPUT_HPP__
#define __INPUT_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

typedef unsigned long long ButtonValue;

// ================================================ //

class Input
{
public:
	Input(const std::string& bmap);
	~Input(void);

	enum{
		BUTTON_UP = 0,
		BUTTON_DOWN,
		BUTTON_LEFT,
		BUTTON_RIGHT,

		NUM_BUTTONS
	};

	void loadButtonMap(const std::string& file);

	// Getter functions
	const bool getButton(const int button) const;
	const ButtonValue getMappedButton(const int button, const bool gamepad = false) const;

	// Setter functions
	void setButton(const int button, const bool state);
	
private:
	int m_type;
	bool m_buttons[NUM_BUTTONS];
	ButtonValue m_keyboardMap[NUM_BUTTONS];
	ButtonValue m_gamepadMap[NUM_BUTTONS];
};

// ================================================ //

// Getters
inline const bool Input::getButton(const int button) const{
	return m_buttons[button];
}

inline const ButtonValue Input::getMappedButton(const int button, const bool gamepad) const{
	return (gamepad == true) ? m_gamepadMap[button] : m_keyboardMap[button];
}

// Setters
inline void Input::setButton(const int button, const bool state){
	m_buttons[button] = state;
}

// ================================================ //

#endif

// ================================================ //