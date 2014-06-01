// ================================================ //

#ifndef __FONT_HPP__
#define __FONT_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

class Font
{
public:
	explicit Font(const std::string& ttfFile, const int size);
	~Font(void);

	TTF_Font* get(void) const;

private:
	TTF_Font* m_pFont;
};

// ================================================ //

inline TTF_Font* Font::get(void) const{
	return m_pFont;
}

// ================================================ //

#endif

// ================================================ //