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
#include "StageImpl.hpp"
#include "Engine.hpp"
#include "Config.hpp"
#include "Camera.hpp"

// ================================================ //

Stage::Stage(const std::string& stageFile) :
Object(),
m_layers()
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

		layer.pTexture = Engine::getSingletonPtr()->loadTexture(c.parseValue(layerName, "texture"));

		layer.src.w = c.parseIntValue(layerName, "w");
		layer.src.h = c.parseIntValue(layerName, "h");

		// Get texture data.
		SDL_QueryTexture(layer.pTexture, nullptr, nullptr, &layer.w, &layer.h);
		layer.src.x = (layer.w / 2) - (layer.src.w / 2); // set starting point to center of stage
		layer.src.y = layer.h - layer.src.h;

		layer.dst.x = layer.dst.y = 0;
		// Render the texture with virtual width/height by default.
		layer.dst.w = Engine::getSingletonPtr()->getLogicalWindowWidth();
		layer.dst.h = Engine::getSingletonPtr()->getLogicalWindowHeight();

		layer.Effect.scrollX = c.parseIntValue(layerName, "scrollX");
		layer.Effect.scrollY = c.parseIntValue(layerName, "scrollY");

		m_layers.push_back(layer);
	}

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

void Stage::update(double dt)
{
	for (unsigned int i = 0; i<m_layers.size(); ++i){
		// Update background source based on camera movement.
		const int rightEdge = m_layers[i].w - m_layers[i].src.w;
		m_layers[i].src.x += Camera::getSingletonPtr()->getMoveX();

		// Don't allow stage view to go out of bounds.
		if (m_layers[i].src.x <= 0){
			m_layers[i].src.x = 0;
			Camera::getSingletonPtr()->lock();
		}
		else if (m_layers[i].src.x >= rightEdge){
			m_layers[i].src.x = rightEdge;
			Camera::getSingletonPtr()->lock();
		}

		// Render the layer.
		SDL_RenderCopyEx(const_cast<SDL_Renderer*>(Engine::getSingletonPtr()->getRenderer()),
			m_layers[i].pTexture, &m_layers[i].src, &m_layers[i].dst, 0, nullptr, SDL_FLIP_NONE);

		// Process stage effects.
		if (m_layers[i].Effect.scrollX || m_layers[i].Effect.scrollY){

			// Scroll the layer.
			m_layers[i].dst.x += static_cast<int>(m_layers[i].Effect.scrollX * dt);
			//m_layers[i].dst.y += static_cast<int>(m_layers[i].Effect.scrollY * dt);

			// Calculate offset for second rendering for seamless scrolling.
			SDL_Rect dst2 = m_layers[i].dst;
			//dst2.x -= dst2.w;
			dst2.x = dst2.x - dst2.w - m_layers[i].src.x + rightEdge;
			//dst2.y = dst2.y - dst2.h - m_layers[i].src.y;

			// Render a second time with offset.
			SDL_RenderCopyEx(const_cast<SDL_Renderer*>(Engine::getSingletonPtr()->getRenderer()),
				m_layers[i].pTexture, &m_layers[i].src, &dst2, 0, nullptr, SDL_FLIP_NONE);

			// Wrap back around to beginning.
			if (dst2.x >= 0)
				m_layers[i].dst.x = 0;
		}
	}
}

// ================================================ //