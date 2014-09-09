// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: Config.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements Config class.
// ================================================ //

#include "Config.hpp"
#include "Engine.hpp"

// ================================================ //

Config::Config(const ConfigType type) :	
m_file(),
m_type(type),
m_loaded(false)
{

}

// ================================================ //

Config::Config(const std::string& file, const ConfigType type) :	
m_file(),
m_type(type),
m_loaded(false)
{
	this->loadFile(file);
}

// ================================================ //

Config::~Config(void)
{
	m_file.close();
}

// ================================================ //

void Config::loadFile(const std::string& file)
{
	Log::getSingletonPtr()->logMessage("Opening file \"" + std::string(file) + "\"");
	if (m_loaded){
		m_file.close();
		m_loaded = false;
	}

	m_file.open(file);

	if (m_file.is_open()){
		m_loaded = true;
		Log::getSingletonPtr()->logMessage("File loaded!");
		
	}
	else{
		Log::getSingletonPtr()->logMessage("ERROR: Failed to load file!");
	}
}

// ================================================ //

void Config::resetFilePointer(void)
{
	m_file.clear();
	m_file.seekg(0, m_file.beg);
}

// ================================================ //

std::string& Config::parseValue(const std::string& section, const std::string& value, const bool quotations)
{
	if (!m_loaded){
		m_buffer.clear();
		return m_buffer;
	}

	// Always start scanning from the first line.
	this->resetFilePointer();

	while(!m_file.eof()){
		std::getline(m_file, m_buffer);
		// Find the right section first.
		if (m_buffer[0] == '[' && m_buffer[m_buffer.size() - 1] == ']'){
			std::string compare(section);
			if (m_buffer.compare(1, m_buffer.size() - 2, compare) == 0){
				// Section found, now find the value.
				std::getline(m_file, m_buffer);
				while(m_buffer[0] != '[' && !m_file.eof()){ // TODO: There must always be a \n at the end of a config file with !m_file.eof().
					
					// Skip comments.
					if (m_buffer[0] != '#'){
						// Find location of assignment operator.
						size_t assign = m_buffer.find_first_of('=');

						// See if pos 0 to the assignment operator matches value name.
						if (m_buffer.compare(0, assign, value) == 0){
							// Trim string to only contain the value.
							if (quotations){
								m_buffer = m_buffer.substr(assign + 2, m_buffer.size() - value.size() - 3);
							}
							else{
								m_buffer = m_buffer.substr(assign + 1, m_buffer.size() - value.size() - 1);
							}

							return m_buffer;
						}
					}

					std::getline(m_file, m_buffer);
				} 
			}
		}
	}

	// Value not found.
	m_buffer.clear();
	return m_buffer;
}

// ================================================ //

const int Config::parseIntValue(const std::string& section, const std::string& value)
{
	std::string str = this->parseValue(section, value);
	if (!str.empty()){
		return std::stoi(str);
	}

	return 0;
}

// ================================================ //

const double Config::parseDoubleValue(const std::string& section, const std::string& value)
{
	std::string str = this->parseValue(section, value);
	if (!str.empty()){
		return std::stod(str);
	}

	return 0.0;
}

// ================================================ //

SDL_Rect Config::parseRect(const std::string& section, const std::string& value)
{
	SDL_Rect rc;
	memset(&rc, 0, sizeof(rc));

	std::string str = this->parseValue(section, value);

	if (!str.empty()){
		// str should look like "(0,0,100,100)".
		char c;
		std::istringstream parse(str);
		parse >> c; // eat "(".
		parse >> rc.x;
		parse >> c; // eat ",".
		parse >> rc.y;
		parse >> c; // eat ",".
		parse >> rc.w;
		parse >> c; // eat ",".
		parse >> rc.h;
	}

	return rc;
}

// ================================================ //

SDL_Color Config::parseColor(const std::string& section, const std::string& value)
{
	SDL_Color color = { 255, 255, 255, 255 };

	std::string str = this->parseValue(section, value);
	if (!str.empty()){
		// str should look like "(255,255,255,255)"
		char c;
		int i = 0;
		std::istringstream parse(str);
		parse >> c; // eat "(".
		parse >> i;
		color.r = static_cast<Uint8>(i);
		parse >> c; // eat ",".
		parse >> i;
		color.g = static_cast<Uint8>(i);
		parse >> c; // eat ",".
		parse >> i;
		color.b = static_cast<Uint8>(i);
		parse >> c; // eat ",".
		parse >> i;
		color.a = static_cast<Uint8>(i);
	}

	return color;
}

// ================================================ //