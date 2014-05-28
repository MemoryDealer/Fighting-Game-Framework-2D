// ================================================ //

#include "stdafx.hpp"
#include "StageImpl.hpp"
#include "Camera.hpp"
#include "Engine.hpp"
#include "Config.hpp"
#include "Log.hpp"

// ================================================ //

StageImpl::StageImpl(const std::string& stageFile)
	:	ObjectImpl(),
		m_layers()
{
	Config c(stageFile);

	Log::getSingletonPtr()->logMessage("Loading stage from file \"" + std::string(stageFile) + "\"");

	// Load the stage configuration file
	const int numLayers = c.parseIntValue("core", "layers");

	// Parse layer data one by one
	for(int i=1; i<=numLayers; ++i){
		StageLayer layer;
		std::string layerName = (std::string("layer") + Engine::toString(i));
		
		// TODO: Change all functions to use std::string or const char*
		layer.pTexture = Engine::getSingletonPtr()->loadTexture(c.parseValue(layerName, "texture"));

		// Set up default rect values
		layer.src.w = c.parseIntValue(layerName, "w");
		layer.src.h = c.parseIntValue(layerName, "h");

		SDL_QueryTexture(layer.pTexture, nullptr, nullptr, &layer.w, &layer.h);
		layer.src.x = layer.w - layer.src.w;
		layer.src.y = layer.h - layer.src.h;
		
		layer.dst.x = layer.dst.y = 0;
		layer.dst.w = Engine::getSingletonPtr()->getLogicalWindowWidth();
		layer.dst.h = Engine::getSingletonPtr()->getLogicalWindowHeight();

		layer.Effect.scrollX = c.parseIntValue(layerName, "scrollX");
		layer.Effect.scrollY = c.parseIntValue(layerName, "scrollY");

		m_layers.push_back(layer);
	}

	Log::getSingletonPtr()->logMessage("Stage loaded with " + Engine::toString(numLayers) + " layer(s)!");
}

// ================================================ //

StageImpl::~StageImpl(void)
{
	// Free all texture pointers
	for(StageLayerList::iterator itr = m_layers.begin();
		itr != m_layers.end();
		++itr){
			Engine::getSingletonPtr()->destroyTexture(itr->pTexture);
	}
	m_layers.clear();
}

// ================================================ //

void StageImpl::update(double dt)
{
	for(unsigned int i=0; i<m_layers.size(); ++i){		
		// Update background source based on camera movement
		const int rightEdge = m_layers[i].w - m_layers[i].src.w;
		m_layers[i].src.x += static_cast<int>(Camera::getSingletonPtr()->moveX);
		printf("x: %d\n", m_layers[i].src.x);
		if (m_layers[i].src.x < 0){
			m_layers[i].src.x = 0;
		}
		else if (m_layers[i].src.x > rightEdge){
			m_layers[i].src.x = rightEdge;
		}

		// Render the background
		SDL_RenderCopyEx(const_cast<SDL_Renderer*>(Engine::getSingletonPtr()->getRenderer()),
			m_layers[i].pTexture, &m_layers[i].src, &m_layers[i].dst, 0, nullptr, SDL_FLIP_NONE);

		// Process stage effects
		if (m_layers[i].Effect.scrollX || m_layers[i].Effect.scrollY){

			// Scroll the layer
			m_layers[i].dst.x += static_cast<int>(m_layers[i].Effect.scrollX * dt);
			//m_layers[i].dst.y += static_cast<int>(m_layers[i].Effect.scrollY * dt);

			// Calculate offset for second rendering for seamless scrolling
			SDL_Rect dst2 = m_layers[i].dst;
			//dst2.x -= dst2.w;
			dst2.x = dst2.x - dst2.w - m_layers[i].src.x + rightEdge;
			//dst2.y = dst2.y - dst2.h - m_layers[i].src.y;

			// Render a second time with offset
			SDL_RenderCopyEx(const_cast<SDL_Renderer*>(Engine::getSingletonPtr()->getRenderer()),
				m_layers[i].pTexture, &m_layers[i].src, &dst2, 0, nullptr, SDL_FLIP_NONE);

			// Wrap back around to beginning
			if (dst2.x >= 0)
				m_layers[i].dst.x = 0;
		}
	}
}

// ================================================ //