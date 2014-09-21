// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: NetMessage.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines NetMessage enumerations.
// ================================================ //

#include "stdafx.hpp"

// ================================================ //

namespace NetMessage{
	enum{
		BEGIN = ID_USER_PACKET_ENUM,

		SYSTEM_MESSAGE,
		SET_USERNAME,
		USERNAME_IN_USE,
		CLIENT_DISCONNECTED,
		CLIENT_LOST_CONNECTION,
		PLAYER_LIST,
		CHAT,
		READY,
		PLAYING_RED, // Let's a client know they are playing next match.
		PLAYING_BLUE,
		SERVER_STARTING_GAME,
		UPDATE_RED_PLAYER,
		UPDATE_BLUE_PLAYER,
		UPDATE_PLAYERS,
		STAGE_SHIFT,
		CLIENT_INPUT,
		LAST_PROCESSED_INPUT_SEQUENCE,
		RED_TAKE_DAMAGE,
		BLUE_TAKE_DAMAGE,
		MATCH_OVER,

		END
	};
}

// ================================================ //