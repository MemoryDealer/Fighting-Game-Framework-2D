// ========================================================================= //
// Fighting game framework (2D) with online multiplayer.
// Copyright(C) 2014 Jordan Sparks <unixunited@live.com>
//
// This program is free software; you can redistribute it and / or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 3
// of the License, or(at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
// ========================================================================= //
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
	names = StringList{ "port", "username" };
	layer->parse<WidgetTextbox>(c, Widget::Type::TEXTBOX, names);
	layer->parse<WidgetStatic>(c, Widget::Type::STATIC, names);
	names = StringList{ "host", "back" };
	layer->parse<WidgetButton>(c, Widget::Type::BUTTON, names);
	this->addLayer(layer);

	layer.reset(new GUIMenuStateLayer::Join());
	names = StringList{ "server", "port", "username", "password" };
	layer->parse<WidgetStatic>(c, Widget::Type::STATIC, names);
	names = StringList{ "join", "back" };
	layer->parse<WidgetButton>(c, Widget::Type::BUTTON, names);
	names = StringList{ "server", "port", "username", "password" };
	layer->parse<WidgetTextbox>(c, Widget::Type::TEXTBOX, names);
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