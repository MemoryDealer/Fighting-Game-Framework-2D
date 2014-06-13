// ================================================ //

#ifndef __PLAYERIMPL_HPP__
#define __PLAYERIMPL_HPP__

// ================================================ //

#include "ObjectImpl.hpp"
#include "PlayerData.hpp"
#include "Hitbox.hpp"
#include "Engine.hpp"
#include "FSM.hpp"

// ================================================ //

struct Move;
class FighterMetadata;
class Timer;
class Input;

// ================================================ //

typedef std::vector<Move*> MoveList;
typedef std::vector<Hitbox> HitboxList;

// ================================================ //

class PlayerImpl : public ObjectImpl
{
public:
	explicit PlayerImpl(const std::string& fighterFile, const int inputType);
	virtual ~PlayerImpl(void);

	void loadFighterData(const std::string& fighterFile);
	void loadMoves(FighterMetadata& c);
	

	// Getter functions
	const int getSide(void) const;
	Hitbox& getHitbox(const int index = 0);
	const int getCurrentState(void) const;
	const bool isColliding(void) const;
	const int getVelocityX(void) const;
	const int getVelocityY(void) const;
	Input* getInput(void) const;

	// Setter functions
	void setSide(const int side);
	void setColliding(const bool colliding);
	void toggleDrawHitboxes(void);

	// Other functions
	virtual void sendMessage(const Message& msg);
	virtual void update(double dt);

private:
	void updateLocalInput(void);
	void updateMove(double dt);
	void updateHitboxes(void);

	int		m_xAccel, m_yAccel;
	int		m_xVel, m_yVel;
	int		m_xMax, m_yMax;
	int		m_currentAction;
	int		m_playerSide;

	std::shared_ptr<Input> m_pInput;

	MoveList		m_moves;
	Move*			m_pCurrentMove;
	std::shared_ptr<Timer> m_pMoveTimer;

	HitboxList	m_hitboxes;
	bool		m_colliding; // control for x-axis movement
	bool		m_drawHitboxes;
};

// ================================================ //

// Getter functions
inline const int PlayerImpl::getSide(void) const{ 
	return m_playerSide; 
}

inline Hitbox& PlayerImpl::getHitbox(const int index){ 
	Assert(static_cast<size_t>(index) <= m_hitboxes.size(), "Index out of bounds"); 
	return m_hitboxes[index]; 
}

inline const int PlayerImpl::getCurrentState(void) const{ 
	return m_pFSM->getCurrentStateID(); 
}

inline const bool PlayerImpl::isColliding(void) const{
	return m_colliding;
}

inline const int PlayerImpl::getVelocityX(void) const{
	return m_xVel;
}

inline const int PlayerImpl::getVelocityY(void) const{
	return m_yVel;
}

inline Input* PlayerImpl::getInput(void) const{
	return m_pInput.get();
}

// Setter functions
inline void PlayerImpl::setSide(const int side){ 
	m_playerSide = side; 
	m_flip = (side == PlayerSide::LEFT) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
}

inline void PlayerImpl::toggleDrawHitboxes(void){
	m_drawHitboxes = !m_drawHitboxes;
}

// ================================================ //

#endif

// ================================================ //