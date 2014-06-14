// ================================================ //

#ifndef __GAMEPADMANAGER_HPP__
#define __GAMEPADMANAGER_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

typedef struct{
	SDL_GameController* pad;
	int id;
} Gamepad;

typedef std::vector<Gamepad> GamepadList;

// ================================================ //

class GamepadManager : public Singleton<GamepadManager>
{
public:
	GamepadManager(void);
	~GamepadManager(void);

	bool addPad(const int id);
	void removePad(const int id);

	void addAllConnectedPads(void);

	// Getter functions
	SDL_GameController* getPad(const int id);

	// Setter functions

private:
	GamepadList m_gamepads;
};

// ================================================ //

// Getters
inline SDL_GameController* GamepadManager::getPad(const int id){
	for (GamepadList::iterator itr = m_gamepads.begin();
		itr != m_gamepads.end();
		++itr){
		if (itr->id == id){
			return itr->pad;
		}
	}
}

// Setters

// ================================================ //

#endif

// ================================================ //