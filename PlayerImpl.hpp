// ================================================ //

#ifndef __PLAYERIMPL_HPP__
#define __PLAYERIMPL_HPP__

// ================================================ //

#include "ObjectImpl.hpp"
#include "PlayerData.hpp"
#include "Hitbox.hpp"

// ================================================ //

struct Move;
class FighterMetadata;
class Timer;

// ================================================ //

typedef std::vector<Move*> MoveList;
typedef std::vector<Hitbox> HitboxList;

// ================================================ //

class PlayerImpl : public ObjectImpl
{
public:
	explicit PlayerImpl(const int fighter, const int inputType);
	virtual ~PlayerImpl(void);

	void loadFighterData(void);
	void loadMoves(FighterMetadata& c);
	

	// Getter functions
	const int getSide(void) const;

	// Setter functions
	void setSide(const int side);
	void setInput(const int input, const bool down);

	// Other functions
	virtual void sendMessage(const Message& msg);
	virtual void update(double dt);

private:
	void updateLocalInput(void);
	void updateMove(double dt);
	void updateHitboxes(void);

	int		m_fighter;
	int		m_xAccel, m_yAccel;
	int		m_xVel, m_yVel;
	int		m_xMax, m_yMax;
	int		m_currentAction;
	int		m_playerSide;

	int		m_inputType;
	bool*	m_input; // dynamically allocated array of current inputs

	MoveList		m_moves;
	Move*			m_pCurrentMove;
	std::tr1::shared_ptr<Timer> m_pMoveTimer;

	HitboxList	m_hitboxes;
};

// ================================================ //

// Getter functions
inline const int PlayerImpl::getSide(void) const
{ return m_playerSide; }

// Setter functions
inline void PlayerImpl::setSide(const int side)
{ 
	m_playerSide = side; 
	m_flip = (side == PlayerSide::LEFT) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL; 
}

inline void PlayerImpl::setInput(const int input, const bool down)
{ m_input[input] = down; }

// ================================================ //

#endif

// ================================================ //