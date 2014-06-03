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
		GUI::ButtonTexture = theme.parseValue("button", "tex");
	}

	// Add layers
	std::vector<std::string> names;

	/* Root layer */
	std::shared_ptr<GUILayer> layer(new GUIMenuStateLayer::Root());
	
	// Buttons
	names = std::vector<std::string>{ "campaign", "arcade", "options", "quit" };
	layer->parse<Button>(c, Widget::Type::BUTTON, names);

	// Add the layer to the GUI
	this->addLayer(layer);

	/* Options layer */
	layer.reset(new GUIMenuStateLayer::Options());

	// Buttons
	names = std::vector<std::string>{ "back" };
	layer->parse<Button>(c, Widget::Type::BUTTON, names);
	
	this->addLayer(layer);

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
		this->setID(GUIMenuState::Layer::ROOT);
		this->setLayerName("root");
	}

	// ================================================ //

	void Root::update(double dt)
	{
		
	}

	// ================================================ //
	// Options
	// ================================================ //

	Options::Options(void)
	{
		this->setID(GUIMenuState::Layer::OPTIONS);
		this->setLayerName("options");
	}

	// ================================================ //

	void Options::update(double dt)
	{

	}

	// ================================================ //
}

// ================================================ //