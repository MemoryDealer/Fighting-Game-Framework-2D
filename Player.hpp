// ================================================ //

#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

// ================================================ //

#include "Object.hpp"

// ================================================ //

class PlayerImpl;

// ================================================ //

class Player : public Object
{
public:
	explicit Player(const char* textureFilename);
	virtual ~Player(void);

	// Getter functions
	

	virtual void update(double dt);

private:
	std::tr1::shared_ptr<PlayerImpl> m_pImpl;
};

// ================================================ //

#endif

// ================================================ //