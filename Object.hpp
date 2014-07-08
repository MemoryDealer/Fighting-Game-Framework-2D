// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: Object.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines Object class.
// ================================================ //

#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

struct Message;
class Label;
class FSM;

// ================================================ //

// An Object is *anything* that can be rendered and/or interacted with.
// An abstract class to derive from for any new object in the game.
class Object
{
public:
	// Gives the Object an ID using a static counter. Adds Object to the
	// MessageRouter.
	explicit Object(void);

	// Destroys the Object's main texture if it's allocated.
	virtual ~Object(void);

	// Getters

	// Returns a pointer to the Object's main SDL_Texture.
	virtual SDL_Texture* getTexturePtr(void) const;

	// Returns the Object's position as an SDL_Rect.
	virtual const SDL_Rect& getPosition(void) const;

	// Returns the Object's name.
	virtual const std::string& getName(void) const;

	// Returns the Object's ID.
	virtual const int getID(void) const;

	// Returns true if the Object is dead.
	virtual const bool isDead(void) const;

	// Returns a pointer to the Object's Label.
	virtual Label* getLabel(void) const;

	// Setters

	// Sets the main SDL_Texture's pointer directly.
	virtual void setTexture(SDL_Texture* pTex);

	// Sets the main SDL_Texture's pointer directly.
	virtual void setTexture(std::shared_ptr<SDL_Texture> pTex);

	// Loads the main SDL_Texture's by loading it from the specified filename.
	virtual bool setTextureFile(const std::string& filename);

	// Sets the main SDL_Texture's source(clipping) coordinates.
	virtual void setTextureCoordinates(const int x, const int y, const int w = 0, const int h = 0);

	// Calls Label::create() on the internal Label.
	virtual void setLabel(const std::string& label, const int offset = 0);

	// Sets the destination SDL_Rect coordinates (where in the viewport it's rendered).
	virtual void setPosition(const int x, const int y);

	// Sets the destination SDL_Rect coordinates (where in the viewport it's rendered).
	virtual void setPosition(const int x, const int y, const int w, const int h);

	// Sets the destination SDL_Rect coordinates (where in the viewport it's rendered).
	virtual void setPosition(const SDL_Rect& pos);

	// --- //

	// Processes the Message (should be overriden by children who want to handle messages).
	virtual void sendMessage(const Message& msg);

	// Renders the main SDL_Texture and Label if m_renderLabel is true.
	virtual void render(void);

	// Ticks the Object.
	virtual void update(double dt) = 0;

protected:
	SDL_Texture*		m_pTexture;
	SDL_Rect			m_src;
	SDL_Rect			m_dst;
	SDL_RendererFlip	m_flip;

	std::string			m_name;
	std::shared_ptr<Label> m_pLabel;
	bool				m_renderLabel;
	int					m_id;

	bool				m_dead;

	// The core state machine.
	std::shared_ptr<FSM> m_pFSM;
};

// ================================================ //

// Getters

inline SDL_Texture* Object::getTexturePtr(void) const{
	return m_pTexture;
}

inline const SDL_Rect& Object::getPosition(void) const{
	return m_dst;
}

inline const std::string& Object::getName(void) const{
	return m_name;
}

inline const int Object::getID(void) const{
	return m_id;
}

inline const bool Object::isDead(void) const{
	return m_dead;
}

inline Label* Object::getLabel(void) const{
	return m_pLabel.get();
}

// Setters

inline void Object::setTexture(std::shared_ptr<SDL_Texture> pTex){
	return this->setTexture(pTex.get());
}

inline void Object::setPosition(const int x, const int y){
	m_dst.x = x; m_dst.y = y;
}

inline void Object::setPosition(const int x, const int y, const int w, const int h){
	m_dst.x = x; m_dst.y = y; m_dst.w = w; m_dst.h = h;
}

inline void Object::setPosition(const SDL_Rect& pos){
	m_dst = pos;
}

// ================================================ //

#endif

// ================================================ //