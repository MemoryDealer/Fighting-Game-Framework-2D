// ================================================ //

#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

// ================================================ //

#include "Object.hpp"
#include "PlayerData.hpp"

// ================================================ //

class PlayerImpl;
class Hitbox;

// ================================================ //

class Player : public Object
{
public:
	explicit Player(const std::string& fighterFile, const int inputType = PlayerInputType::LOCAL);
	virtual ~Player(void);

	// Hitbox indices
	enum{
		HBOX_LOWER = 0,
		HBOX_MIDDLE,
		HBOX_UPPER,
		HBOX_HEAD,
		TBOX,
		DBOX1,
		DBOX2,
		CBOX1,
		CBOX2,
	};

	// Getter functions
	const int getSide(void) const;
	Hitbox& getHitbox(const int index);
	const int getCurrentState(void) const;
	const bool isColliding(void) const;
	const int getVelocityX(void) const;
	const int getVelocityY(void) const;

	// Setter functions
	void setSide(const int side);
	void setInput(const int input, const bool down);
	void setColliding(const bool colliding = true);

	virtual void update(double dt);

private:
	std::shared_ptr<PlayerImpl> m_pImpl;
};

// ================================================ //

#endif

// ================================================ //