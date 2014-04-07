// ================================================ //

#ifndef __PLAYERIMPL_HPP__
#define __PLAYERIMPL_HPP__

// ================================================ //

#include "ObjectImpl.hpp"
#include "PlayerData.hpp"
#include "Input.hpp"

// ================================================ //

struct Move;
class FighterMetadata;
class Timer;

// ================================================ //

typedef std::vector<Move*> MoveList;

// ================================================ //

class PlayerImpl : public ObjectImpl
{
public:
	explicit PlayerImpl(unsigned int fighter);
	virtual ~PlayerImpl(void);

	void loadFighterData(void);
	void loadMoves(FighterMetadata& c);
	void processInput(const int input);
	void updateMove(double dt);

	// Getter functions
	const int getSide(void) const;

	// Setter functions
	void setSide(const int side);

	// Other functions
	virtual void sendMessage(const Message& msg);
	virtual void update(double dt);

private:
	int		m_fighter;
	int		m_xAccel, m_yAccel;
	int		m_xVel, m_yVel;
	int		m_xMax, m_yMax;
	int		m_currentAction;
	int		m_playerSide;

	bool	m_input[Input::NUM_INPUTS];

	MoveList		m_moves;
	Move*			m_pCurrentMove;
	std::tr1::shared_ptr<Timer> m_pMoveTimer;
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

// ================================================ //

#endif

// ================================================ //