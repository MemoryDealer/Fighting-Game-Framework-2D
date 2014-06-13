// ================================================ //

#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

// ================================================ //

#include "Object.hpp"
#include "PlayerData.hpp"

// ================================================ //

class PlayerImpl;
class Hitbox;
class Input;

// ================================================ //

class Player : public Object
{
public:
	explicit Player(const std::string& fighterFile, const std::string& buttomMapFile = "", const int mode = PlayerMode::LOCAL);
	virtual ~Player(void);

	// Getter functions
	const int getSide(void) const;
	Hitbox& getHitbox(const int index);
	const int getCurrentState(void) const;
	const bool isColliding(void) const;
	const int getVelocityX(void) const;
	const int getVelocityY(void) const;
	const int getMode(void) const;
	Input* getInput(void) const;

	// Setter functions
	void setSide(const int side);
	void setColliding(const bool colliding);
	void toggleDrawHitboxes(void);
	void setMode(const int mode);

	virtual void update(double dt);

private:
	std::shared_ptr<PlayerImpl> m_pImpl;
};

// ================================================ //

#endif

// ================================================ //