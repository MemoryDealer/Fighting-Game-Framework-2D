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
	explicit Player(unsigned int fighter);
	virtual ~Player(void);

	void loadFighterData(void);
	void processInput(const int input = 0);

	// Getter functions
	const int getSide(void) const;

	// Setter functions
	void setSide(const int side);

	virtual void update(double dt);

private:
	std::tr1::shared_ptr<PlayerImpl> m_pImpl;
};

// ================================================ //

#endif

// ================================================ //