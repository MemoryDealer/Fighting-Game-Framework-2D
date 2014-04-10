// ================================================ //

#ifndef __HITBOX_HPP__
#define __HITBOX_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

namespace HitboxType{
	enum{
		NORMAL = 0,
		DAMAGE,
		THROW,
		COUNTER
	};
}

// ================================================ //

class Hitbox
{
public:
	explicit Hitbox(const int type);
	virtual ~Hitbox(void);

	const bool intersects(const Hitbox& b);
	void render(void);

	// Getter functions
	virtual const SDL_Rect& getRect(void) const;
	virtual const bool isActive(void) const;

	// Setter functions
	virtual void setActive(const bool active);
	virtual void setRect(const int x, const int y, const int w = 0, const int h = 0);
	virtual void setRect(const SDL_Rect& pos);

	// Static functions
	static const bool HitboxIntersect(const Hitbox& a, const Hitbox& b);

private:
	SDL_Rect	m_rc;
	int			m_type;
	bool		m_active;
	SDL_Color	m_color;
	SDL_Color	m_outline;
};

// ================================================ //

// Getter functions
inline const SDL_Rect& Hitbox::getRect(void) const
{ return m_rc; }

inline const bool Hitbox::isActive(void) const
{ return m_active; }

// Setter functions
inline void Hitbox::setActive(const bool active)
{ m_active = active; }

inline void Hitbox::setRect(const int x, const int y, const int w , const int h)
{ 
	m_rc.x = x; m_rc.y = y; 
	if(w != 0)
		m_rc.w = w;
	if(h != 0)
		m_rc.h = h;
}

inline void Hitbox::setRect(const SDL_Rect& pos)
{ m_rc = pos; }

// ================================================ //

#endif

// ================================================ //