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
	names = StringList{ "ready", "start", "send", "exit" };
	layer->parse<WidgetButton>(c, Widget::Type::BUTTON, names);
	names = StringList{ "send" };
	layer->parse<WidgetTextbox>(c, Widget::Type::TEXTBOX, names);
	names = StringList{ "players", "chat" };
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

