// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: PlayerManager.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines PlayerManager singleton class.
// ================================================ //

#ifndef __PLAYERMANAGER_HPP__
#define __PLAYERMANAGER_HPP__

// ================================================ //

#include "stdafx.hpp"
#include "Player.hpp"

// ================================================ //

// An entry for each fighter available for gameplay.
struct FighterEntry{
	std::string name;
	std::string file;
	SDL_Texture* portrait;
};

typedef std::vector<FighterEntry> FighterEntryList;

// ================================================ //

// Holds both Red and Blue Player Object's and updates them. Performs calculations
// needed for Camera movement and such.
class PlayerManager : public Singleton<PlayerManager>
{
public:
	// Loads fighters.cfg and parses all fighter entries.
	explicit PlayerManager(void);

	// Empty destructor.
	~PlayerManager(void);

	// Returns pointer to Red Player.
	Player* getRedPlayer(void) const;

	// Returns pointer to Blue Player.
	Player* getBluePlayer(void) const;

	// Returns pointer to Red Player Input.
	Input* getRedPlayerInput(void) const;

	// Returns pointer to Blue Player Input.
	Input* getBluePlayerInput(void) const;


	bool load(const std::string& redFighterFile, const std::string& blueFighterFile);
	bool reload(void);

	// Allocates both Player objects with empty fighter files and default 
	// button maps and gamepads.
	bool reset(void);

	void updateCamera(double dt);
	void update(double dt);

private:
	std::shared_ptr<Player> m_pRedPlayer;
	std::shared_ptr<Player> m_pBluePlayer;
	std::string m_redFighterFile, m_blueFighterFile;

	int m_redMax, m_blueMax; // the right edge of the screen minus player width (pixels)

	FighterEntryList m_fighters;
};

// ================================================ //

inline Player* PlayerManager::getRedPlayer(void) const{
	return m_pRedPlayer.get(); 
}

inline Player* PlayerManager::getBluePlayer(void) const{
	return m_pBluePlayer.get(); 
}

inline Input* PlayerManager::getRedPlayerInput(void) const{
	return m_pRedPlayer->getInput();
}

inline Input* PlayerManager::getBluePlayerInput(void) const{
	return m_pBluePlayer->getInput();
}

// ================================================ //

#endif

// ================================================ //