// ================================================ //

#include "GUI.hpp"

// ================================================ //

GUI::GUI(const std::string& file) :
m_guifile(file)
{
	// Attempt to load the GUI configuration file
	if (!m_guifile.empty()){
		if (this->load(m_guifile)){
			Log::getSingletonPtr()->logMessage("GUI file \"" + m_guifile + "\" loaded!");
		}
		else{
			std::string exc = "Failed to load GUI file \"" + m_guifile + "\"";
			throw std::exception(exc.c_str());
		}
	}
}

// ================================================ //

GUI::~GUI(void)
{

}

// ================================================ //

bool GUI::load(const std::string& file)
{
	m_guifile.assign(file);
}

// ================================================ //