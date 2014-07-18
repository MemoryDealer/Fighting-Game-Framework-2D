// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: GUIMenuState.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements GUIMenuState class.
// ================================================ //

#include "GUIMenuState.hpp"
#include "Config.hpp"
#include "WidgetStatic.hpp"
#include "WidgetButton.hpp"
#include "WidgetTextbox.hpp"
#include "Engine.hpp"

// ================================================ //

GUIMenuState::GUIMenuState(const std::string& file) :
GUI()
{
	Config c(file);
	if (!c.isLoaded()){
		throw std::exception("Failed to load GUI config file for MenuState");
	}

	// List of names of each widget for each layer.
	StringList names;

	// Add each layer to the GUI.
	std::shared_ptr<GUILayer> layer(new GUIMenuStateLayer::Root());
	names = StringList{ "campaign", "arcade", "options", "quit" };
	layer->parse<WidgetButton>(c, Widget::Type::BUTTON, names);
	this->addLayer(layer);

	layer.reset(new GUIMenuStateLayer::Campaign());
	names = StringList{ "new", "load", "back" };
	layer->parse<WidgetButton>(c, Widget::Type::BUTTON, names);
	this->addLayer(layer);

	layer.reset(new GUIMenuStateLayer::Arcade());
	names = StringList{ "local", "online", "back" };
	layer->parse<WidgetButton>(c, Widget::Type::BUTTON, names);
	this->addLayer(layer);

	layer.reset(new GUIMenuStateLayer::Online());
	names = StringList{ "host", "join", "dedicated", "back" };
	layer->parse<WidgetButton>(c, Widget::Type::BUTTON, names);
	this->addLayer(layer);

	layer.reset(new GUIMenuStateLayer::Host());
	names = StringList{ "port" };
	layer->parse<WidgetTextbox>(c, Widget::Type::TEXTBOX, names);
	names = StringList{ "port" };
	layer->parse<WidgetStatic>(c, Widget::Type::STATIC, names);
	names = StringList{ "host", "back" };
	layer->parse<WidgetButton>(c, Widget::Type::BUTTON, names);
	this->addLayer(layer);

	layer.reset(new GUIMenuStateLayer::Join());
	names = StringList{ "" };
	this->addLayer(layer);
	
	layer.reset(new GUIMenuStateLayer::Options());
	names = StringList{ "back" };
	layer->parse<WidgetButton>(c, Widget::Type::BUTTON, names);
	this->addLayer(layer);

	// Set starting layer to Root.
	this->pushLayer(GUIMenuState::Layer::ROOT);
}

// ================================================ //

GUIMenuState::~GUIMenuState(void)
{

}

// ================================================ //

void GUIMenuState::update(double dt)
{
	GUI::update(dt);
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
	// Campaign
	// ================================================ //

	Campaign::Campaign(void)
	{
		this->setID(GUIMenuState::Layer::CAMPAIGN);
		this->setLayerName("campaign");
	}

	// ================================================ //
	// Arcade
	// ================================================ //

	Arcade::Arcade(void)
	{
		this->setID(GUIMenuState::Layer::ARCADE);
		this->setLayerName("arcade");
	}

	// ================================================ //
	// Online
	// ================================================ //

	Online::Online(void)
	{
		this->setID(GUIMenuState::Layer::ONLINE);
		this->setLayerName("online");
	}

	// ================================================ //
	// Host
	// ================================================ //

	Host::Host(void)
	{
		this->setID(GUIMenuState::Layer::HOST);
		this->setLayerName("host");
	}

	// ================================================ //
	// Join
	// ================================================ //

	Join::Join(void)
	{
		this->setID(GUIMenuState::Layer::JOIN);
		this->setLayerName("join");
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
}

// ================================================ //