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
		CHAT,

		END
	};
}

// ================================================ //