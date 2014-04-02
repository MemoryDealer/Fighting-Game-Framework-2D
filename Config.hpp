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
		META
	};

	explicit Config(ConfigType type = INI);
	explicit Config(const char* file, ConfigType type = INI);
	~Config(void);

	void loadFile(const char* file);
	std::string& parseValue(const char* section, const char* value);
	const int parseIntValue(const char* section, const char* value);

	// Getter functions
	const bool isLoaded(void) const;

	// Setter functions

private:
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