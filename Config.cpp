// ================================================ //

#include "Config.hpp"
#include "Engine.hpp"

// ================================================ //

Config::Config(const ConfigType type)
	:	m_file(),
		m_type(type),
		m_loaded(false)
{

}

// ================================================ //

Config::Config(const char* file, const ConfigType type)
	:	m_file(),
		m_type(type),
		m_loaded(false)
{
	// Open file
	this->loadFile(file);
}

// ================================================ //

Config::~Config(void)
{
	m_file.close();
}

// ================================================ //

void Config::loadFile(const char* file)
{
	Log::getSingletonPtr()->logMessage("Opening file \"" + std::string(file) + "\"");
	if(m_loaded){
		m_file.close();
		m_loaded = false;
	}

	m_file.open(file);

	if(m_file.is_open()){
		m_loaded = true;
		Log::getSingletonPtr()->logMessage("File loaded!");
	}
}

// ================================================ //

void Config::resetFilePointer(void)
{
	m_file.clear();
	m_file.seekg(0, m_file.beg);
}

// ================================================ //

std::string& Config::parseValue(const char* section, const char* value)
{
	if(!m_loaded){
		m_buffer.clear();
		return m_buffer;
	}

	// Reset file pointer to beginning
	this->resetFilePointer();

	while(!m_file.eof()){
		m_file >> m_buffer;

		// Find the right section first
		if(m_buffer[0] == '[' && m_buffer[m_buffer.size() - 1] == ']'){
			std::string compare(section);

			// Compare the section name inside the brackets
			if(m_buffer.compare(1, m_buffer.size() - 2, compare) == 0){
				
				// Section found, now find the value
				m_file >> m_buffer;
				while(m_buffer[0] != '[' && !m_file.eof()){ // NOTE: There must always be a \n at the end of a config file
					
					// Skip comments
					if(m_buffer[0] != '#'){
						// Find location of assignment operator
						size_t assign = m_buffer.find_first_of('=');

						// See if pos 0 to the assignment operator matches value name
						if(m_buffer.compare(0, assign, value) == 0){
							m_buffer = m_buffer.substr(assign + 1, m_buffer.size());

							return m_buffer;
						}
					}

					m_file >> m_buffer;
				} 
			}
		}
	}

	// Value not found, return empty string
	m_buffer.clear();
	return m_buffer;
}

// ================================================ //

const int Config::parseIntValue(const char* section, const char* value)
{
	std::string str = this->parseValue(section, value);
	if(!str.empty()){
		return std::stoi(str);
	}

	return 0;
}

// ================================================ //