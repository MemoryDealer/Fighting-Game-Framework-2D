// ================================================ //

#include "Config.hpp"

// ================================================ //

Config::Config(const char* file, ConfigType type)
	:	m_file(),
		m_type(type),
		m_loaded(false)
{
	// Open file
	m_file.open(file);

	if(m_file.is_open()){
		m_loaded = true;

	}
}

// ================================================ //

Config::~Config(void)
{
	m_file.close();
}

// ================================================ //

std::string& Config::parseValue(const char* section, const char* value)
{
	// Reset file pointer to beginning
	m_file.seekg(0, m_file.beg);

	while(!m_file.eof()){
		m_file >> m_buffer;

		// Find the right section first
		if(m_buffer[0] == '[' && m_buffer[m_buffer.size() - 1] == ']'){
			std::string compare(section);

			// Compare the section name inside the brackets
			if(m_buffer.compare(1, m_buffer.size() - 2, compare) == 0){
				
				// Section found, now find the value
				m_file >> m_buffer;
				while(m_buffer[0] != '['){
					
					// Find location of assignment operator
					size_t assign = m_buffer.find_first_of('=');

					// See if pos 0 to the assignment operator matches value name
					if(m_buffer.compare(0, assign, value) == 0){
						m_buffer = m_buffer.substr(assign + 1, m_buffer.size());

						return m_buffer;
					}

					m_file >> m_buffer;
				} 
			}
		}
	}

	// Value not found, return empty string
	m_buffer.erase();
	return m_buffer;
}

// ================================================ //