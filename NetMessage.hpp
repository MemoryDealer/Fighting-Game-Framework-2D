// ========================================================================= //
// Fighting game framework (2D) with online multiplayer.
// Copyright(C) 2014 Jordan Sparks <unixunited@live.com>
//
// This program is free software; you can redistribute it and / or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 3
// of the License, or(at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
// ========================================================================= //
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
		PAN_CAMERA,
		CLIENT_INPUT,
		LAST_PROCESSED_INPUT_SEQUENCE,
		RED_TAKE_HIT,
		BLUE_TAKE_HIT,
		RED_TAKE_HIT_BLOCK,
		BLUE_TAKE_HIT_BLOCK,
		MATCH_OVER,

		END
	};
}

// ================================================ //