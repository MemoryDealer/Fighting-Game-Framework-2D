// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: Config.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines Config class.
// ================================================ //

#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

// Provides config file reading/writing tools. Has basic INI parsing
// functions, supporting multiple types.
class Config
{
public:
	// Two types of config files.
	enum ConfigType{
		INI = 0,
		FIGHTER_METADATA
	};

	// Initializes type and sets loaded to false.
	explicit Config(const ConfigType type = INI);

	// Same as other constructor, except it opens the file handle.
	explicit Config(const std::string& file, const ConfigType type = INI);

	// Closes the file handle.
	virtual ~Config(void);

	// Opens file handle to specified filename. Closes the handle first if
	// it's already open.
	virtual void loadFile(const std::string& file);

	// Clears the file handle and seeks to position zero.
	virtual void resetFilePointer(void);

	// Resets the file pointer and scans line by line looking for the section 
	// (such as [gamesettings]), then looks in that section for the value. Returns
	// the value in std::string format. The parameter quotations should be true
	// if the value is inside quotation marks.
	virtual std::string& parseValue(const std::string& section, const std::string& value, const bool quotations = false);

	// Wraps parseValue(), converts the std::string to an int.
	virtual const int parseIntValue(const std::string& section, const std::string& value);

	// Wraps parseValue(), converts the std::string to a double.
	virtual const double parseDoubleValue(const std::string& section, const std::string& value);

	// Wraps parseValue(), converts the std::string to a SDL_Rect.
	virtual SDL_Rect parseRect(const std::string& section, const std::string& value);

	// Getters

	// Returns true if the file handle is open.
	const bool isLoaded(void) const;

protected:
	std::ifstream	m_file;
	ConfigType		m_type;
	bool			m_loaded;

	// Used for returning string values.
	std::string		m_buffer;
};

// ================================================ //

// Getters

inline const bool Config::isLoaded(void) const{ 
	return m_loaded; 
}

// ================================================ //

#endif

// ================================================ //