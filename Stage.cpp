// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
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

		layer.src.w = c.parseIntValue(layerName, "w");
		layer.src.h = c.parseIntValue(layerName, "h");

		// Get texture data.
		SDL_QueryTexture(layer.pTexture, nullptr, nullptr, &layer.w, &layer.h);
		layer.src.x = 0;
		layer.src.y = layer.h - layer.src.h;

		// Set default camera position.
		Camera::getSingletonPtr()->setX((layer.w / 2) - (layer.src.w / 2));

		layer.dst.x = layer.dst.y = 0;
		// Render the texture with virtual width/height by default.
		layer.dst.w = Engine::getSingletonPtr()->getLogicalWindowWidth();
		layer.dst.h = Engine::getSingletonPtr()->getLogicalWindowHeight();

		layer.Effect.scrollX = c.parseIntValue(layerName, "scrollX");
		layer.Effect.scrollY = c.parseIntValue(layerName, "scrollY");

		m_layers.push_back(layer);
	}

	m_rightEdge = m_layers[0].w - m_layers[0].src.w;

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
	/*if (Game::getSingletonPtr()->getMode() == Game::CLIENT){
		this->serverReconciliation();
	}*/

	Camera::getSingletonPtr()->update(dt);

	// Render the stage background.
	for (unsigned int i = 0; i<m_layers.size(); ++i){
		// Render the layer.
		SDL_Rect src = m_layers[i].src;
		src.x += Camera::getSingletonPtr()->getX();
		if (src.x < 0){
			src.x = 0;
		}
		else if (src.x > m_rightEdge){
			src.x = m_rightEdge;
		}
		else{
			//src.x /= static_cast<int>(static_cast<double>(src.w) * 100.0);
			printf("Stage: %d => %d\n", Camera::getSingletonPtr()->getX(), src.x);
		}
		SDL_RenderCopyEx(Engine::getSingletonPtr()->getRenderer(),
			m_layers[i].pTexture, &src, &m_layers[i].dst, 0, nullptr, SDL_FLIP_NONE);

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
			if (dst2.x >= 0)
				m_layers[i].dst.x = 0;
		}
	}
}

// ================================================ //