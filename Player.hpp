// ================================================ //

#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

// ================================================ //

#include "Object.hpp"
#include "PlayerData.hpp"

// ================================================ //

class PlayerImpl;

// ================================================ //

class Player : public Object
{
public:
	explicit Player(const int fighter, const int inputType = PlayerInputType::LOCAL);
	virtual ~Player(void);

	void loadFighterData(void);

	// Getter functions
	const int getSide(void) const;

	// Setter functions
	void setSide(const int side);
	void setInput(const int input, const bool down = true);

	virtual void update(double dt);

private:
	std::tr1::shared_ptr<PlayerImpl> m_pImpl;
};

// ================================================ //

#endif

// ================================================ //