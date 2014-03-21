// ================================================ //

#ifndef __OBJECTIMPL_HPP__
#define __OBJECTIMPL_HPP__

// ================================================ //

#include <SDL.h>
#include <string>

// ================================================ //

class ObjectImpl
{
public:
	explicit ObjectImpl(const char* textureFilename);
	virtual ~ObjectImpl(void);

	// Setter functions
	virtual bool setTextureFile(const char* filename);

	virtual void setPosition(const int x, const int y);
	virtual void setPosition(const SDL_Rect& pos);

	// Getter functions
	virtual SDL_Texture* getTexturePtr(void) const;
	virtual const SDL_Rect& getPosition(void) const;

	virtual void update(double dt) = 0;

protected:
	// SDL components
	SDL_Texture*	m_pTexture;
	SDL_Rect		m_pos, m_bb;

	std::string		m_name;
};

// ================================================ //

// Setters
inline void ObjectImpl::setPosition(const int x, const int y)
{ m_pos.x = x; m_pos.y = y; }

inline void ObjectImpl::setPosition(const SDL_Rect& pos)
{ m_pos = pos; }

// Getters
inline SDL_Texture* ObjectImpl::getTexturePtr(void) const
{ return m_pTexture; }

inline const SDL_Rect& ObjectImpl::getPosition(void) const
{ return m_pos; }

// ================================================ //

#endif

// ================================================ //