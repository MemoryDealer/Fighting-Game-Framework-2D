// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: Game.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines Game singleton class.
// ================================================ //

// ================================================ //

#ifndef __GAME_HPP__
#define __GAME_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

// A singleton class to hold information for use between
// game states (e.g., should the lobby state start a server
// or a client). 
class Game : public Singleton<Game>
{
public:
	// Initializes mode to IDLE.
	explicit Game(void);

	// Empty destructor.
	~Game(void);

	// Game modes.
	enum Mode{
		IDLE = 0,
		CAMPAIGN,
		SERVER,
		CLIENT
	};

	// Some playing states.
	enum Playing{
		NIL = 1000,
		PLAYING_RED,
		PLAYING_BLUE,
		SPECTATING
	};

	// Getters

	// Returns the game mode.
	const int getMode(void) const;

	// Returns the username.
	const std::string getUsername(void) const;

	// Returns state.
	const int getPlaying(void) const;

	// Returns name of red player.
	const std::string getRedPlayerName(void) const;

	// Returns name of blue player.
	const std::string getBluePlayerName(void) const;

	// Returns true if the network simulator should be used.
	const bool useNetSimulator(void) const;

	// Returns simulated ping.
	const Uint32 getNetSimulatedPing(void) const;

	// Returns simulated packet loss.
	const float getNetSimulatedPacketLoss(void) const;

	// Returns last error.
	const int getError(void) const;

	// Setters

	// Sets the game mode.
	void setMode(const int mode);

	// Sets the username.
	void setUsername(const std::string& username);

	// Sets state.
	void setPlaying(const int playing);

	// Sets name of red player.
	void setRedPlayerName(const std::string& name);

	// Sets name of blue player.
	void setBluePlayerName(const std::string& name);

	// Sets error.
	void setError(const int error);

	// --- //

	static const int MAX_USERNAME_LENGTH = 16;

private:
	// Game mode for use across game states.
	int m_mode;

	// Playing state of game, e.g., PLAYING_RED, PLAYING_BLUE, or SPECTATOR.
	int m_playing;

	// Error messages to be passed between game states.
	int m_error;

	// The local username of the player.
	std::string m_username;

	// The usernames of active players.
	std::string m_redPlayerName, m_bluePlayerName;

	// Simulated network lag.
	bool m_useSimulator;

	Uint32 m_simulatedPing;

	float m_simulatedPacketLoss;
};

// ================================================ //

// Getters

inline const int Game::getMode(void) const{
	return m_mode;
}

inline const std::string Game::getUsername(void) const{
	return m_username;
}

inline const int Game::getPlaying(void) const{
	return m_playing;
}

inline const std::string Game::getRedPlayerName(void) const{
	return m_redPlayerName;
}

inline const std::string Game::getBluePlayerName(void) const{
	return m_bluePlayerName;
}

inline const bool Game::useNetSimulator(void) const{
	return m_useSimulator;
}

inline const Uint32 Game::getNetSimulatedPing(void) const{
	return m_simulatedPing;
}

inline const float Game::getNetSimulatedPacketLoss(void) const{
	return m_simulatedPacketLoss;
}

inline const int Game::getError(void) const{
	return m_error;
}

// Setters

inline void Game::setMode(const int mode){
	m_mode = mode;
}

inline void Game::setUsername(const std::string& username){
	m_username = username;
}

inline void Game::setRedPlayerName(const std::string& name){
	m_redPlayerName = name;
}

inline void Game::setBluePlayerName(const std::string& name){
	m_bluePlayerName = name;
}

inline void Game::setPlaying(const int playing){
	m_playing = playing;
}

inline void Game::setError(const int error){
	m_error = error;
}

// ================================================ //

#endif

// ================================================ //

