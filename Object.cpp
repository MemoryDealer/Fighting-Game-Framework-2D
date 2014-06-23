// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: Object.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements Object class.
// ================================================ //

#include "Object.hpp"
#include "Engine.hpp"
#include "MessageRouter.hpp"
#include "FSM.hpp"
#include "Label.hpp"

// ================================================ //

Object::Object(void) :
m_pTexture(nullptr),
m_src(),
m_dst(),
m_flip(SDL_FLIP_NONE),
m_name("ObjectID "),
m_pLabel(nullptr),
m_renderLabel(false),
m_dead(false),
m_pFSM(new FSM(0))
{
	static int nameCtr = 0;
	m_id = nameCtr++;
	m_name += std::to_string(static_cast<long long>(m_id));

	m_src.x = m_src.y = m_dst.x = m_dst.y = 0;

	Log::getSingletonPtr()->logMessage("Object \"" + m_name + "\" created!");

	MessageRouter::getSingletonPtr()->addObject(static_cast<Object*>(this));
}

// ================================================ //

Object::~Object(void)
{
	if (m_pTexture != nullptr)
		Engine::getSingletonPtr()->destroyTexture(m_pTexture);

	Log::getSingletonPtr()->logMessage("Destroyed Object \"" + m_name + "\"");
}

// ================================================ //

void Object::setTexture(SDL_Texture* pTex)
{
	m_pTexture = pTex;

	// Get texture width/height
	SDL_QueryTexture(m_pTexture, nullptr, nullptr, &m_src.w, &m_src.h);
	m_dst.w = m_src.w;
	m_dst.h = m_src.h;
}

// ================================================ //

bool Object::setTextureFile(const std::string& filename)
{
	if (m_pTexture != nullptr)
		Engine::getSingletonPtr()->destroyTexture(m_pTexture);

	Log::getSingletonPtr()->logMessage("Setting texture \"" + std::string(filename) +
		"\" for Object \"" + m_name + "\"");
	m_pTexture = Engine::getSingletonPtr()->loadTexture(filename);

	// Get texture width/height
	SDL_QueryTexture(m_pTexture, nullptr, nullptr, &m_src.w, &m_src.h);
	m_dst.w = m_src.w;
	m_dst.h = m_src.h;

	return (m_pTexture != nullptr);
}

// ================================================ //

void Object::setTextureCoordinates(const int x, const int y, const int w, const int h)
{
	m_src.x = x; m_src.y = y;
	if (w != 0)
		m_src.w = m_dst.w = w;
	if (h != 0)
		m_src.h = m_dst.h = h;
}

// ================================================ //

inline void Object::setLabel(const std::string& label, const int offset)
{
	m_pLabel->create(label); m_pLabel->setOffset(offset);
}

// ================================================ //

void Object::sendMessage(const Message& msg)
{

}

// ================================================ //

void Object::render(void)
{
	//! I hope it's safe to const_cast the renderer pointer
	SDL_RenderCopyEx(const_cast<SDL_Renderer*>(Engine::getSingletonPtr()->getRenderer()),
		m_pTexture, &m_src, &m_dst, 0, nullptr, m_flip);

	if (m_renderLabel){
		SDL_Rect dst = m_dst;
		dst.x += m_pLabel->getOffset();
		dst.w -= m_pLabel->getOffset() * 2;

		SDL_RenderCopyEx(const_cast<SDL_Renderer*>(Engine::getSingletonPtr()->getRenderer()), m_pLabel->getTexturePtr(),
			&m_src, &dst, 0, nullptr, m_flip);
	}
}

// ================================================ //