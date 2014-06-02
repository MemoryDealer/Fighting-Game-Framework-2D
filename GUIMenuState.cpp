// ================================================ //

#include "GUIMenuState.hpp"
#include "Config.hpp"
#include "Button.hpp"

// ================================================ //

GUIMenuState::GUIMenuState(const std::string& file) :
GUI()
{
	// Load config file
	Config c(file);
	if (!c.isLoaded()){
		throw std::exception("Failed to load GUI config file for MenuState");
	}

	// Get theme textures
	std::string buttonTexture;
	Config e("ExtMF.cfg");
	Config theme(e.parseValue("GUI", "theme"));
	if (theme.isLoaded()){
		GUI::m_buttonTheme = theme.parseValue("button", "tex");
	}

	// Add layers
	std::vector<std::string> names;

	/* Root layer */
	std::shared_ptr<GUILayer> root(new GUIMenuStateLayer::Root());
	
	// Buttons
	names = std::vector<std::string>{ "campaign", "arcade", "options", "quit" };
	root->parse<Button>(c, Widget::Type::BUTTON, names);


	this->addLayer(root);

	// Set starting layer
	this->setCurrentLayer(GUIMenuState::Layer::ROOT);
}

// ================================================ //

GUIMenuState::~GUIMenuState(void)
{

}

// ================================================ //

void GUIMenuState::update(double dt)
{
	GUI::update(dt);

	// Update the current layer
	this->getCurrentLayer()->update(dt);
	this->getCurrentLayer()->render();
}

// ================================================ //
// ================================================ //

namespace GUIMenuStateLayer{

	// ================================================ //
	// Root
	// ================================================ //

	Root::Root(void)
	{
		this->setLayerName("root");
	}

	// ================================================ //

	void Root::update(double dt)
	{
		
	}

	// ================================================ //
}

// ================================================ //