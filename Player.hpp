// ================================================ //

#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

// ================================================ //

#include "Object.hpp"
#include "PlayerData.hpp"

// ================================================ //

class Hitbox;
class Input;
struct Move;
class FighterMetadata;
class Timer;

typedef std::vector<std::shared_ptr<Move>> MoveList;
typedef std::vector<std::shared_ptr<Hitbox>> HitboxList;

// ================================================ //

class Player : public Object
{
public:
	explicit Player(const std::string& fighterFile, const std::string& buttomMapFile = "", const int mode = PlayerMode::LOCAL);
	virtual ~Player(void);

	// Getter functions
	const int getSide(void) const;
	Hitbox* getHitbox(const int index);
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

	virtual void sendMessage(const Message& msg);
	virtual void update(double dt);

private:
	void loadFighterData(const std::string& fighterFile);
	void loadMoves(FighterMetadata& c);
	void updateLocalInput(void);
	void updateMove(double dt);
	void updateHitboxes(void);

	int		m_xAccel, m_yAccel;
	int		m_xVel, m_yVel;
	int		m_xMax, m_yMax;
	int		m_currentAction;
	int		m_playerSide;

	std::shared_ptr<Input> m_pInput;
	int		m_mode;

	MoveList		m_moves;
	std::shared_ptr<Move>	m_pCurrentMove;
	std::shared_ptr<Timer>	m_pMoveTimer;

	HitboxList	m_hitboxes;
	bool		m_colliding; // control for x-axis movement
	bool		m_drawHitboxes;
};

// ================================================ //

// Getter functions
inline const int Player::getSide(void) const{
	return m_playerSide;
}

inline Hitbox* Player::getHitbox(const int index){
	return m_hitboxes[index].get();
}

inline const bool Player::isColliding(void) const{
	return m_colliding;
}

inline const int Player::getVelocityX(void) const{
	return m_xVel;
}

inline const int Player::getVelocityY(void) const{
	return m_yVel;
}

inline const int Player::getMode(void) const{
	return m_mode;
}

inline Input* Player::getInput(void) const{
	return m_pInput.get();
}

// Setter functions
inline void Player::setSide(const int side){
	m_playerSide = side;
	m_flip = (side == PlayerSide::LEFT) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
}

inline void Player::toggleDrawHitboxes(void){
	m_drawHitboxes = !m_drawHitboxes;
}

inline void Player::setMode(const int mode){
	m_mode = mode;
}

// ================================================ //

#endif

// ================================================ //