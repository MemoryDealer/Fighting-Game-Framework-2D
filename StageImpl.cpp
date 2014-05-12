// ================================================ //

#include "stdafx.hpp"
#include "StageImpl.hpp"
#include "Engine.hpp"
#include "Config.hpp"

// ================================================ //

StageImpl::StageImpl(const char* stageFile)
	:	ObjectImpl(0),
		m_layers(),
		m_stageWidth(0),
		m_stageHeight(0)
{
	Config c(stageFile);

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
		layer.Effect.scrollX = c.parseIntValue(layerName.c_str(), "scrollX");
		layer.Effect.scrollY = c.parseIntValue(layerName.c_str(), "scrollY");

		m_layers.push_back(layer);
	}
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

		m_layers[i].dst.x += static_cast<int>(m_layers[i].Effect.scrollX * dt);

		SDL_RenderCopyEx(const_cast<SDL_Renderer*>(Engine::getSingletonPtr()->getRenderer()),
			m_layers[i].pTexture, nullptr, nullptr, 0, nullptr, SDL_FLIP_NONE);
	}
}

// ================================================ //