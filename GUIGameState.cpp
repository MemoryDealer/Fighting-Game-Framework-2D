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
	names = StringList{ "red.fighter", "blue.fighter", "red.wins", "blue.wins", "countdown" };
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