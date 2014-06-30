// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: FighterMetadata.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines FighterMetadata class.
// ================================================ //

#ifndef __FIGHTERMETADATA_HPP__
#define __FIGHTERMETADATA_HPP__

// ================================================ //

#include "Config.hpp"

// ================================================ //

struct Move;

// ================================================ //

// A specialized config file parser for reading/writing fighter data
// from a .fighter file.
class FighterMetadata : public Config
{
public:
	// Sets the type to FIGHTER_METADATA.
	explicit FighterMetadata(void);

	// Sets the type to FIGHTER_METADATA and opens the file handle.
	explicit FighterMetadata(const std::string& file);

	// Empty destructor, parent destructor close the file handle.
	virtual ~FighterMetadata(void);

	// Allocates a Move object and parses all data for it. 
	// A Move is formatted like so:
	// +(MOVE_NAME)
	// ... (all data)
	// -(MOVE_NAME)
	virtual std::shared_ptr<Move> parseMove(const std::string& name);
	
private:
	// Obtains a basic string value from within a move.
	// Used by parseMove() in case data is out of order.
	virtual std::string parseMoveValue(const std::string& section, const std::string& value);

	// Wraps parseMoveValue() and converts the std::string to an int. Returns -1 
	// on failure is to let FighterMetadata::parseMove() know if a frame of 
	// animation should be inherited from the previous frame, rather than 
	// assigning its corresponding value(s) to zero. This will no longer be 
	// necessary once a tool is developed to visually edit fighter data.
	virtual const int parseMoveIntValue(const std::string& section, const std::string& value);

	// Wraps parseMoveValue() and converts the std::string to a bool.
	virtual const bool parseMoveBoolValue(const std::string& section, const std::string& value);

	// Parses all hitboxes for a Move's particular frame.
	virtual void parseHitboxes(std::shared_ptr<Move> pMove, const std::string& frame);

	// Same as Config::parseRect(), but directly operates on the str parameter.
	virtual SDL_Rect FighterMetadata::parseRect(const std::string& str);

	// Holds the beginning line of a move for going back to parse more.
	std::streampos m_moveBeg;
};

// ================================================ //

#endif

// ================================================ //