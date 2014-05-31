// ================================================ //

#ifndef __GUI_HPP__
#define __GUI_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

class GUI
{
public:
	explicit GUI(const std::string& file = "");
	~GUI(void);

	bool load(const std::string& file);

private:
	std::string m_guifile;
};

// ================================================ //

#endif

// ================================================ //