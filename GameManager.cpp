// ================================================ //

#include "GameManager.hpp"

// ================================================ //

template<> GameManager* Singleton<GameManager>::msSingleton = nullptr;

// ================================================ //

GameManager::GameManager(void) :
m_mode(GameMode::LOCAL)
{

}

// ================================================ //

GameManager::~GameManager(void)
{

}

// ================================================ //