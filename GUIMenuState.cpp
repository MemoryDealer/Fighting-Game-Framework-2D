// ================================================ //

#include "GUIMenuState.hpp"
#include "Config.hpp"

// ================================================ //

GUIMenuState::GUIMenuState(const std::string& file) :
GUI()
{
	// Load config file
	Config c(file);
	if (!c.isLoaded()){
		throw std::exception("Failed to load GUI config file for MenuState");
	}

	// Add layers
	this->addLayer(std::shared_ptr<GUILayer>(new GUIMenuStateLayer::Root()));

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
	if (this->getCurrentLayer() != nullptr){
		this->getCurrentLayer()->update(dt);
	}
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