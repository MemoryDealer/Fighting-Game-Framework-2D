// ================================================ //

#ifndef __PLAYERMANAGER_HPP__
#define __PLAYERMANAGER_HPP__

// ================================================ //

#include "stdafx.hpp"
#include "Player.hpp"

// ================================================ //
// This is used as a singleton to hold both player's objects
// ================================================ //

class PlayerManager : public Singleton<PlayerManager>
{
public:
	explicit PlayerManager(unsigned int redFighter, unsigned int blueFighter);
	~PlayerManager(void);

	Player* getRedPlayer(void) const;
	Player* getBluePlayer(void) const;

	void update(double dt);

private:
	std::tr1::shared_ptr<Player> m_pRedPlayer;
	std::tr1::shared_ptr<Player> m_pBluePlayer;
};

// ================================================ //

inline Player* PlayerManager::getRedPlayer(void) const
{ return m_pRedPlayer.get(); }

inline Player* PlayerManager::getBluePlayer(void) const
{ return m_pBluePlayer.get(); }

// ================================================ //

#endif

// ================================================ //