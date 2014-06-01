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
	std::shared_ptr<Button> buttonCampaign(new Button(GUIMenuStateLayer::Root::BUTTON_CAMPAIGN));
	buttonCampaign->setTextureFile(buttonTexture);
	buttonCampaign->setPosition(c.parseRect("layer.root", "button.campaign:pos"));
	buttonCampaign->setLabel(c.parseValue("layer.root", "button.campaign:label"));
	root->addWidget(buttonCampaign);

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
	printf("Updating menu state...\n");

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
		printf("Updating root...\n");
	}

	// ================================================ //
}

// ================================================ //