// ================================================ //

#ifndef __OBJECTIMPL_HPP__
#define __OBJECTIMPL_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

class FSM;
struct Message;

// ================================================ //

class ObjectImpl
{
public:
	explicit ObjectImpl(void);
	virtual ~ObjectImpl(void);

	// Setter functions
	virtual bool setTextureFile(const std::string& filename);
	virtual void setTextureCoordinates(const int x, const int y, const int w = 0, const int h = 0);

	virtual void setPosition(const int x, const int y);
	virtual void setPosition(const SDL_Rect& pos);

	// Getter functions
	virtual SDL_Texture* getTexturePtr(void) const;
	virtual const SDL_Rect& getPosition(void) const;
	virtual const std::string& getName(void) const;
	virtual const int getID(void) const;
	virtual const bool isDead(void) const;

	// Other functions
	virtual void sendMessage(const Message& msg);
	virtual void render(void);
	virtual void update(double dt) = 0;

protected:
	// SDL components
	SDL_Texture*		m_pTexture;
	SDL_Rect			m_src;
	SDL_Rect			m_dst;
	SDL_RendererFlip	m_flip;

	std::string			m_name;
	int					m_id;

	bool				m_dead;

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

inline const int ObjectImpl::getID(void) const
{ return m_id; }

inline const bool ObjectImpl::isDead(void) const
{ return m_dead; }

// ================================================ //

#endif

// ================================================ //