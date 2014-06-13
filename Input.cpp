// ================================================ //

#include "Input.hpp"

// ================================================ //

Input::Input(void) :
m_type(0)
{
	// Set all button states to false
	std::fill_n(m_buttons, static_cast<int>(Input::NUM_BUTTONS), false);
}

// ================================================ //

Input::~Input(void)
{

}

// ================================================ //