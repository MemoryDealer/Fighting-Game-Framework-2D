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

	// Wraps parseValue(), converts the std::string to a SDL_Color.
	virtual SDL_Color parseColor(const std::string& section, const std::string& value);

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