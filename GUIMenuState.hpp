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
		explicit Root(void);

		enum Widget{
			BUTTON_CAMPAIGN = 0,
			BUTTON_ARCADE,
			BUTTON_OPTIONS,
			BUTTON_QUIT
		};

		virtual void update(double dt);
	};

	// ================================================ //
	// ================================================ //

	class Options : public GUILayer
	{
	public:
		explicit Options(void);

		enum Widget{
			BUTTON_BACK = 0
		};

		virtual void update(double dt);
	};

}

// ================================================ //

#endif

// ================================================ //