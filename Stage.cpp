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
// File: Stage.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements Stage class.
// ================================================ //

#include "Stage.hpp"
#include "Engine.hpp"
#include "Config.hpp"
#include "Client.hpp"
#include "Game.hpp"
#include "PlayerManager.hpp"
#include "Camera.hpp"

// ================================================ //

Stage::Stage(const std::string& stageFile) :
Object(),
m_layers(),
m_rightEdge(0),
m_shiftUpdates()
{
	Config c(stageFile);
	if (!c.isLoaded()){
		Log::getSingletonPtr()->logMessage("Failed to load stage file \"" + stageFile + "\"");
		return;
	}

	Log::getSingletonPtr()->logMessage("Loading stage from file \"" + std::string(stageFile) + "\"");

	const int numLayers = c.parseIntValue("core", "layers");

	// Parse layer data one by one.
	for (int i = 1; i <= numLayers; ++i){
		StageLayer layer;
		std::string layerName = (std::string("layer") + Engine::toString(i));

		layer.pTexture = Engine::getSingletonPtr()->loadTexture(
			Engine::getSingletonPtr()->getDataDirectory() + "/" + c.parseValue(layerName, "texture"));
		///f: re-organize the layer struct to be more understandable
		layer.src.w = c.parseIntValue(layerName, "w");
		layer.src.h = c.parseIntValue(layerName, "h");

		// Get texture data.
		SDL_QueryTexture(layer.pTexture, nullptr, nullptr, &layer.w, &layer.h);
		layer.src.x = 0;
		layer.src.y = layer.h - layer.src.h;

		// Set default camera position.
		Camera::getSingletonPtr()->panX((layer.w / 2) - (layer.src.w / 2));

		layer.dst.x = layer.dst.y = 0;
		// Render the texture with virtual width/height by default.
		layer.dst.w = Engine::getSingletonPtr()->getLogicalWindowWidth();
		layer.dst.h = Engine::getSingletonPtr()->getLogicalWindowHeight();

		layer.Effect.scrollX = c.parseIntValue(layerName, "scrollX");
		layer.Effect.scrollY = c.parseIntValue(layerName, "scrollY");

		m_layers.push_back(layer);
	}

	m_rightEdge = m_layers[0].w - m_layers[0].src.w;
	Camera::getSingletonPtr()->setRightBound(m_rightEdge);

	Log::getSingletonPtr()->logMessage("Stage loaded with " + Engine::toString(numLayers) + " layer(s)!");
}

// ================================================ //

Stage::~Stage(void)
{
	for (StageLayerList::iterator itr = m_layers.begin();
		itr != m_layers.end();
		++itr){
		Engine::getSingletonPtr()->destroyTexture(itr->pTexture);
	}
}

// ================================================ //

void Stage::shift(const int x)
{
	m_layers[0].src.x += x;
	if (m_layers[0].src.x < 0){
		m_layers[0].src.x = 0;
	}
	else if (m_layers[0].src.x > m_rightEdge){
		m_layers[0].src.x = m_rightEdge;
	}
}

// ================================================ //

void Stage::setShift(const int x)
{
	m_layers[0].src.x = x;
	if (m_layers[0].src.x < 0){
		m_layers[0].src.x = 0;
	}
	else if (m_layers[0].src.x > m_rightEdge){
		m_layers[0].src.x = m_rightEdge;
	}
}


// ================================================ //

void Stage::updateShiftFromServer(const Stage::ShiftUpdate& update)
{
	if (Game::getSingletonPtr()->getMode() == Game::CLIENT){
		m_shiftUpdates.push(update);
	}
}

// ================================================ //

void Stage::serverReconciliation(void)
{
	while (!m_shiftUpdates.empty()){
		ShiftUpdate update = m_shiftUpdates.front();

		this->setShift(update.shift);

		for (std::list<Client::StageShift>::iterator itr = Client::getSingletonPtr()->m_pendingStageShifts.begin();
			 itr != Client::getSingletonPtr()->m_pendingStageShifts.end();){
			if (itr->seq <= update.lastProcessedShift){
				itr = Client::getSingletonPtr()->m_pendingStageShifts.erase(itr);
			}
			else{
				printf("reapplying stage shift %d/%d\n", itr->shift, itr->seq);
				this->shift(itr->shift);
				if (Game::getSingletonPtr()->getPlaying() == Game::PLAYING_RED){
					//PlayerManager::getSingletonPtr()->getBluePlayer()->
				}
				++itr;
			}
		}

		m_shiftUpdates.pop();
	}
}

// ================================================ //

void Stage::update(double dt)
{
	Camera::getSingletonPtr()->update(dt);

	// Render the stage background.
	for (unsigned int i = 0; i<m_layers.size(); ++i){
		// Render the layer.
		SDL_Rect src = m_layers[i].src;

		m_layers[i].src.x = Camera::getSingletonPtr()->getX();
		if (m_layers[i].src.x < 0){
			m_layers[i].src.x = 0;
		}
		else if (m_layers[i].src.x > m_rightEdge){
			m_layers[i].src.x = m_rightEdge;
		}

		SDL_RenderCopyEx(Engine::getSingletonPtr()->getRenderer(),
			m_layers[i].pTexture, &m_layers[i].src, &m_layers[i].dst, 0, nullptr, SDL_FLIP_NONE);

		// Process stage effects.
		if (m_layers[i].Effect.scrollX || m_layers[i].Effect.scrollY){

			// Scroll the layer.
			m_layers[i].dst.x += static_cast<int>(m_layers[i].Effect.scrollX * dt);
			//m_layers[i].dst.y += static_cast<int>(m_layers[i].Effect.scrollY * dt);

			// Calculate offset for second rendering for seamless scrolling.
			SDL_Rect dst2 = m_layers[i].dst;
			//dst2.x -= dst2.w;
			dst2.x = dst2.x - dst2.w - m_layers[i].src.x + m_rightEdge;
			//dst2.y = dst2.y - dst2.h - m_layers[i].src.y;

			// Render a second time with offset.
			SDL_RenderCopyEx(Engine::getSingletonPtr()->getRenderer(),
				m_layers[i].pTexture, &m_layers[i].src, &dst2, 0, nullptr, SDL_FLIP_NONE);

			// Wrap back around to beginning.
			if (dst2.x >= 0){
				m_layers[i].dst.x = 0;
			}
		}
	}
}

// ================================================ //