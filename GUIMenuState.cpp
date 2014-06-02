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
		buttonTexture = theme.parseValue("button", "tex");
	}

	// Add layers
	/* Root layer */
	std::shared_ptr<GUILayer> root(new GUIMenuStateLayer::Root());
	
	// Buttons
	// Campaign button
	std::shared_ptr<Button> button(new Button(GUIMenuStateLayer::Root::BUTTON_CAMPAIGN));
	button->setTextureFile(buttonTexture);
	button->setPosition(c.parseRect("layer.root", "button.campaign:pos"));
	button->setLabel(c.parseValue("layer.root", "button.campaign:label"), c.parseIntValue("layer.root", "button.campaign:labeloffset"));
	button->setEnabled(false);
	button->parseLinks(c.parseValue("layer.root", "button.campaign:links"));
	root->addWidget(button);
	
	// Arcade button
	button.reset(new Button(GUIMenuStateLayer::Root::BUTTON_ARCADE));
	button->setTextureFile(buttonTexture);
	button->setPosition(c.parseRect("layer.root", "button.arcade:pos"));
	button->setLabel(c.parseValue("layer.root", "button.arcade:label"), c.parseIntValue("layer.root", "button.arcade:labeloffset"));
	button->parseLinks(c.parseValue("layer.root", "button.arcade:links"));
	root->addWidget(button);

	// Options button
	button.reset(new Button(GUIMenuStateLayer::Root::BUTTON_OPTIONS));
	button->setTextureFile(buttonTexture);
	button->setPosition(c.parseRect("layer.root", "button.options:pos"));
	button->setLabel(c.parseValue("layer.root", "button.options:label"), c.parseIntValue("layer.root", "button.options:labeloffset"));
	button->parseLinks(c.parseValue("layer.root", "button.options:links"));
	root->addWidget(button);

	// Quit button
	button.reset(new Button(GUIMenuStateLayer::Root::BUTTON_QUIT));
	button->setTextureFile(buttonTexture);
	button->setPosition(c.parseRect("layer.root", "button.quit:pos"));
	button->setLabel(c.parseValue("layer.root", "button.quit:label"), c.parseIntValue("layer.root", "button.quit:labeloffset"));
	button->parseLinks(c.parseValue("layer.root", "button.quit:links"));
	root->addWidget(button);

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

	void Root::update(double dt)
	{
		
	}

	// ================================================ //
}

// ================================================ //