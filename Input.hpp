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

		BUTTON_START,
		BUTTON_SELECT, // such as A button, for menus (will be a duplicate)

		NUM_BUTTONS
	};

	void loadButtonMap(const std::string& file);
	void resetAllButtons(void);

	// Getter functions
	const bool getButton(const int button) const;
	const ButtonValue getMappedButton(const int button, const bool gamepad = false) const;
	SDL_GameController* getPad(void) const;
	const int getPadID(void) const;
	const int getPadDeadzone(void) const;

	// Setter functions
	void setButton(const int button, const bool state);
	void setPad(SDL_GameController* pad);
	void setPadDeadzone(const int deadzone);
	
private:
	bool m_buttons[NUM_BUTTONS];
	ButtonValue m_keyboardMap[NUM_BUTTONS];
	ButtonValue m_gamepadMap[NUM_BUTTONS];
	SDL_GameController* m_pad;
	int m_padDeadzone;
};

// ================================================ //

// Getters
inline const bool Input::getButton(const int button) const{
	return m_buttons[button];
}

inline SDL_GameController* Input::getPad(void) const{
	return m_pad;
}

inline const ButtonValue Input::getMappedButton(const int button, const bool gamepad) const{
	return (gamepad == true) ? m_gamepadMap[button] : m_keyboardMap[button];
}

inline const int Input::getPadDeadzone(void) const{
	return m_padDeadzone;
}

// Setters
inline void Input::setButton(const int button, const bool state){
	m_buttons[button] = state;
}

inline void Input::setPad(SDL_GameController* pad){
	m_pad = pad;
}

inline void Input::setPadDeadzone(const int deadzone){
	m_padDeadzone = deadzone;
}

// ================================================ //

#endif

// ================================================ //