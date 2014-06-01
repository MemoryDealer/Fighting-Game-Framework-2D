// ================================================ //

#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

class Config
{
public:
	enum ConfigType{
		INI = 0,
		FIGHTER_METADATA
	};

	explicit Config(const ConfigType type = INI);
	explicit Config(const std::string& file, const ConfigType type = INI);
	virtual ~Config(void);

	virtual void loadFile(const std::string& file);
	virtual void resetFilePointer(void);
	virtual std::string& parseValue(const std::string& section, const std::string& value);
	virtual const int parseIntValue(const std::string& section, const std::string& value);
	virtual SDL_Rect parseRect(const std::string& section, const std::string& value);

	// Getter functions
	const bool isLoaded(void) const;

	// Setter functions


protected:
	std::ifstream	m_file;
	ConfigType		m_type;
	bool			m_loaded;
	std::string		m_buffer;
};

// ================================================ //

inline const bool Config::isLoaded(void) const
{ return m_loaded; }

// ================================================ //

#endif

// ================================================ //