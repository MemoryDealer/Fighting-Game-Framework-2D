// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: GUILobbyState.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements GUILobbyState class, the GUI object for the menu state.
// ================================================ //

#include "GUILobbyState.hpp"
#include "WidgetStatic.hpp"
#include "WidgetButton.hpp"
#include "WidgetTextbox.hpp"
#include "WidgetListbox.hpp"
#include "Config.hpp"
#include "Engine.hpp"

// ================================================ //

GUILobbyState::GUILobbyState(const std::string& file) :
GUI()
{
	Config c(file);
	if (!c.isLoaded()){
		throw std::exception("Failed to load GUI config file for LobbyState");
	}

	StringList names;

	// Add each layer to the GUI.
	std::shared_ptr<GUILayer> layer(new GUILobbyStateLayer::Root());
	names = StringList{ "ready", "send", "exit" };
	layer->parse<WidgetButton>(c, Widget::Type::BUTTON, names);
	names = StringList{ "send" };
	layer->parse<WidgetTextbox>(c, Widget::Type::TEXTBOX, names);
	names = StringList{ "chat" };
	layer->parse<WidgetListbox>(c, Widget::Type::LISTBOX, names);
	this->addLayer(layer);

	this->pushLayer(GUILobbyState::Layer::ROOT);
}

// ================================================ //

GUILobbyState::~GUILobbyState(void)
{

}

// ================================================ //

void GUILobbyState::update(double dt)
{
	GUI::update(dt);
}

// ================================================ //
// ================================================ //

namespace GUILobbyStateLayer{

	// ================================================ //
	// Root
	// ================================================ //

	Root::Root(void)
	{
		this->setID(GUILobbyState::Layer::ROOT);
		this->setLayerName("root");
	}

	// ================================================ //
}

// ================================================ //

