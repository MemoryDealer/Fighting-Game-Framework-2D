// ================================================ //

#ifndef __OBJECTIMPL_HPP__
#define __OBJECTIMPL_HPP__

// ================================================ //

#include "stdafx.hpp"
#include "FSM.hpp"

// ================================================ //

class ObjectImpl
{
public:
	explicit ObjectImpl(const char* textureFilename);
	virtual ~ObjectImpl(void);

	// Setter functions
	virtual bool setTextureFile(const char* filename);
	virtual void setTextureCoordinates(int x, int y, int w = 0, int h = 0);

	virtual void setPosition(const int x, const int y);
	virtual void setPosition(const SDL_Rect& pos);

	// Getter functions
	virtual SDL_Texture* getTexturePtr(void) const;
	virtual const SDL_Rect& getPosition(void) const;
	virtual const std::string& getName(void) const;

	virtual void render(void);
	virtual void update(double dt) = 0;

protected:
	// SDL components
	SDL_Texture*		m_pTexture;
	SDL_Rect			m_src;
	SDL_Rect			m_dst;
	SDL_RendererFlip	m_flip;

	std::string			m_name;

	std::tr1::shared_ptr<FSM> m_pFSM; // the core state machine
};

// ================================================ //

// Setters
inline void ObjectImpl::setPosition(const int x, const int y)
{ m_dst.x = x; m_dst.y = y; }

inline void ObjectImpl::setPosition(const SDL_Rect& pos)
{ m_dst = pos; }

// Getters
inline SDL_Texture* ObjectImpl::getTexturePtr(void) const
{ return m_pTexture; }

inline const SDL_Rect& ObjectImpl::getPosition(void) const
{ return m_dst; }

inline const std::string& ObjectImpl::getName(void) const
{ return m_name; }

// ================================================ //

#endif

// ================================================ //