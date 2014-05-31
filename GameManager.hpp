// ================================================ //

#ifndef __GAMEMANAGER_HPP__
#define __GAMEMANAGER_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

class Timer;

// ================================================ //

namespace GameMode{
	enum{
		LOCAL = 0,
		CLIENT,
		SERVER
	};
}

// ================================================ //

class GameManager : public Singleton<GameManager>
{
public:
	explicit GameManager(void);
	~GameManager(void);

	// Getter functions
	const int getMode(void) const;

	// Setter functions
	void setMode(const int mode);

private:
	int m_mode;
};

// ================================================ //

inline const int GameManager::getMode(void) const{
	return m_mode;
}

inline void GameManager::setMode(const int mode){
	m_mode = mode;
}

// ================================================ //

#endif

// ================================================ //