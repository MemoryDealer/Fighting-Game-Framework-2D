// ================================================ //

#ifndef __OBJECTIMPL_HPP__
#define __OBJECTIMPL_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

class ObjectImpl
{
public:
	explicit ObjectImpl(void);
	virtual ~ObjectImpl(void);

	bool setTextureFile(const char* filename);

	// Getter functions
	SDL_Texture* getTexturePtr(void) const;

	void update(double dt);

private:
	// SDL components
	SDL_Texture*	m_pTexture;
	SDL_Rect		m_pos, m_bb;

	std::string		m_name;
};

// ================================================ //

inline SDL_Texture* ObjectImpl::getTexturePtr(void) const
{ return m_pTexture; }

// ================================================ //

#endif

// ================================================ //