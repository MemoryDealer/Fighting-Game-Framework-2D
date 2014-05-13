// ================================================ //

#include "stdafx.hpp"
#include "StageImpl.hpp"
#include "Engine.hpp"
#include "Config.hpp"
#include "Log.hpp"

// ================================================ //

StageImpl::StageImpl(const char* stageFile)
	:	ObjectImpl(0),
		m_layers(),
		m_stageWidth(0),
		m_stageHeight(0)
{
	Config c(stageFile);

	Log::getSingletonPtr()->logMessage("Loading stage from file \"" + std::string(stageFile) + "\"");

	// Load the stage configuration file
	const int numLayers = c.parseIntValue("core", "layers");
	m_stageWidth = c.parseIntValue("core", "stageWidth");
	m_stageHeight = c.parseIntValue("core", "stageHeight");

	// Parse layer data one by one
	for(int i=1; i<=numLayers; ++i){
		StageLayer layer;
		std::string layerName = (std::string("layer") + Engine::toString(i));
		
		// TODO: Change all functions to use std::string or const char*
		layer.pTexture = Engine::getSingletonPtr()->loadTexture(c.parseValue(layerName.c_str(), "texture").c_str());

		// Set up default rect values
		layer.src.x = layer.src.y = 0;
		SDL_QueryTexture(layer.pTexture, nullptr, nullptr, &layer.src.w, &layer.src.h);
		layer.dst.x = layer.dst.y = 0;
		layer.dst.w = Engine::getSingletonPtr()->getWindowWidth();
		layer.dst.h = Engine::getSingletonPtr()->getWindowHeight();

		layer.Effect.scrollX = c.parseIntValue(layerName.c_str(), "scrollX");
		layer.Effect.scrollY = c.parseIntValue(layerName.c_str(), "scrollY");

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
	for(int i=0; i<m_layers.size(); ++i){

		SDL_RenderCopyEx(const_cast<SDL_Renderer*>(Engine::getSingletonPtr()->getRenderer()),
			m_layers[i].pTexture, &m_layers[i].src, &m_layers[i].dst, 0, nullptr, SDL_FLIP_NONE);

		if(m_layers[i].Effect.scrollX){

			m_layers[i].dst.x += static_cast<int>(m_layers[i].Effect.scrollX * dt);
			SDL_Rect dst = m_layers[i].dst;
			dst.x -= dst.w;

			SDL_RenderCopyEx(const_cast<SDL_Renderer*>(Engine::getSingletonPtr()->getRenderer()),
				m_layers[i].pTexture, &m_layers[i].src, &dst, 0, nullptr, SDL_FLIP_NONE);

			if(dst.x == 0)
				m_layers[i].dst.x = 0;
		}
	}
}

// ================================================ //