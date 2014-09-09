// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: GUIGameState.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements GUIGameState class, the GUI object for the game state.
// ================================================ //

#include "GUIGameState.hpp"
#include "WidgetStatic.hpp"
#include "WidgetButton.hpp"
#include "WidgetHealthBar.hpp"
#include "Config.hpp"
#include "Engine.hpp"

// ================================================ //

GUIGameState::GUIGameState(const std::string& file) :
GUI()
{
	Config c(file);
	if (!c.isLoaded()){
		throw std::exception("Failed to load GUI config file to GameState");
	}

	StringList names;

	// Add each layer to the GUI.
	std::shared_ptr<GUILayer> layer(new GUIGameStateLayer::Root());
	names = StringList{ "red.fighter", "blue.fighter", "red.name", "blue.name",
		"red.wins", "blue.wins", "countdown" };
	layer->parse<WidgetStatic>(c, Widget::Type::STATIC, names);
	names = StringList{ "red", "blue" };
	layer->parse<WidgetHealthBar>(c, Widget::Type::HEALTHBAR, names);
	this->addLayer(layer);

	this->pushLayer(GUIGameState::Layer::ROOT);
}

// ================================================ //

GUIGameState::~GUIGameState(void)
{

}

// ================================================ //

void GUIGameState::update(double dt)
{
	GUI::update(dt);
}

// ================================================ //
// ================================================ //

namespace GUIGameStateLayer{

	// ================================================ //
	// Root
	// ================================================ //

	Root::Root(void)
	{
		this->setID(GUIGameState::Layer::ROOT);
		this->setLayerName("root");
	}

	// ================================================ //

	Pregame::Pregame(void)
	{
		this->setID(GUIGameState::Layer::PREGAME);
		this->setLayerName("pregame");
	}
}

// ================================================ //