// ================================================ //

#ifndef __PLAYERMANAGER_HPP__
#define __PLAYERMANAGER_HPP__

// ================================================ //

#include "stdafx.hpp"
#include "Player.hpp"

// ================================================ //

struct FighterEntry{
	std::string name;
	std::string file;
	SDL_Texture* portrait;
};

typedef std::vector<FighterEntry> FighterEntryList;

// ================================================ //
// This is used as a singleton to hold both player's objects
// ================================================ //

class PlayerManager : public Singleton<PlayerManager>
{
public:
	explicit PlayerManager(void);
	~PlayerManager(void);

	Player* getRedPlayer(void) const;
	Player* getBluePlayer(void) const;

	bool load(const char* redFighterFile, const char* blueFighterFile);

	void update(double dt);

private:
	std::tr1::shared_ptr<Player> m_pRedPlayer;
	std::tr1::shared_ptr<Player> m_pBluePlayer;

	FighterEntryList m_fighters;
};

// ================================================ //

inline Player* PlayerManager::getRedPlayer(void) const
{ return m_pRedPlayer.get(); }

inline Player* PlayerManager::getBluePlayer(void) const
{ return m_pBluePlayer.get(); }

// ================================================ //

#endif

// ================================================ //