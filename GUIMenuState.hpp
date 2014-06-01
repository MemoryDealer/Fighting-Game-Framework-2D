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

	// Layers
	enum Layer{
		ROOT = 0,
		OPTIONS
	};

	virtual void update(double dt);

private:

};

// ================================================ //

namespace GUIMenuStateLayer{

	// ================================================ //

	class Root : public GUILayer
	{
	public:

		enum Widget{
			BUTTON_CAMPAIGN = 0,
			BUTTON_ARCADE,
			BUTTON_OPTIONS,
			BUTTON_QUIT
		};

		virtual void update(double dt);
	};

	// ================================================ //

}

// ================================================ //

#endif

// ================================================ //