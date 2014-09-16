// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: Hitbox.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements Hitbox class.
// ================================================ //

#include "Hitbox.hpp"
#include "Engine.hpp"

// ================================================ //

Hitbox::Hitbox(const int type) :
m_rc(),
m_type(type),
m_active(false),
m_color(),
m_outline()
{
	memset(&m_rc, 0, sizeof(m_rc));

	switch (m_type){
	default:
	case Hitbox::Type::NORMAL:
		m_color.r = m_outline.r = 0;
		m_color.g = m_outline.g = 0;
		m_color.b = 200;
		m_color.a = 50;

		m_outline.b = 255;
		break;

	case Hitbox::Type::DAMAGE:
		m_color.r = m_outline.r = 200;
		m_color.g = m_outline.g = 0;
		m_color.b = m_outline.b = 0;
		m_color.a = 50;

		m_outline.r = 255;
		break;

	case Hitbox::Type::THROW:

		break;

	case Hitbox::Type::COUNTER:
		m_color.r = m_outline.r = 0;
		m_color.g = 255;
		m_color.b = 200;
		m_color.a = 50;

		m_outline.g = 255;
		m_outline.b = 255;
		break;
	}
}

// ================================================ //

Hitbox::~Hitbox(void)
{

}

// ================================================ //

const bool Hitbox::intersects(const Hitbox* b)
{
	return (SDL_HasIntersection(&this->getRect(), &b->getRect()) == SDL_TRUE);
}

// ================================================ //

void Hitbox::render(void)
{
	// Render the inner translucent box.
	SDL_SetRenderDrawBlendMode(Engine::getSingletonPtr()->getRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(Engine::getSingletonPtr()->getRenderer(), m_color.r, m_color.g, m_color.b, m_color.a);
	SDL_RenderFillRect(Engine::getSingletonPtr()->getRenderer(), &m_rc);
	
	// Render the opaque outline.
	SDL_SetRenderDrawColor(Engine::getSingletonPtr()->getRenderer(), m_outline.r, m_outline.g, m_outline.b, 255);
	SDL_RenderDrawRect(Engine::getSingletonPtr()->getRenderer(), &m_rc);
}

// ================================================ //

const bool Hitbox::HitboxIntersect(const Hitbox* a, const Hitbox* b)
{
	return (SDL_HasIntersection(&a->getRect(), &b->getRect()) == SDL_TRUE);
}

// ================================================ //