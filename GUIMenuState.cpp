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

	/* Add layers */
	// Root layer
	std::shared_ptr<GUILayer> root(new GUIMenuStateLayer::Root());
	
	// Buttons
	std::shared_ptr<Button> button(new Button(GUIMenuStateLayer::Root::BUTTON_CAMPAIGN));
	button->setTextureFile(buttonTexture);
	button->setPosition(c.parseRect("layer.root", "button.campaign:pos"));
	button->setLabel(c.parseValue("layer.root", "button.campaign:label"));
	root->addWidget(button);

	button.reset(new Button(GUIMenuStateLayer::Root::BUTTON_ARCADE));
	button->setTextureFile(buttonTexture);
	button->setPosition(c.parseRect("layer.root", "button.arcade:pos"));
	button->setLabel(c.parseValue("layer.root", "button.arcade:label"));
	root->addWidget(button);

	this->addLayer(root);

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