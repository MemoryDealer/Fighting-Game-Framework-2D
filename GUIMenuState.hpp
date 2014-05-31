// ================================================ //

#ifndef __GUIMENUSTATE_HPP__
#define __GUIMENUSTATE_HPP__

// ================================================ //

#include "GUI.hpp"

// ================================================ //

class GUIMenuState : public GUI
{
public:
	explicit GUIMenuState(const std::string& file);
	virtual ~GUIMenuState(void);

	virtual void update(double dt);

private:

};

// ================================================ //

#endif

// ================================================ //