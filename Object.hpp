// ================================================ //

#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

class ObjectImpl;
struct Message;

// ================================================ //

class Object
{
public:
	/** \brief An Object is *anything* that can be rendered and/or interacted with.
		An abstract class to derive from for any new object in the game. */
	explicit Object(void);
	virtual ~Object(void);

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
	/** \brief This should be called in the constructor of any child class of Object,
		passing the local m_pImpl of the child class as the argument. This basically
		allows "pointer to implementation" polymorphism. */
	virtual void setPImpl(std::shared_ptr<ObjectImpl> pImpl);

private:
	std::shared_ptr<ObjectImpl> m_pImpl;
};

// ================================================ //

inline void Object::setPImpl(std::shared_ptr<ObjectImpl> pImpl)
{ m_pImpl = pImpl; }

// ================================================ //

#endif

// ================================================ //