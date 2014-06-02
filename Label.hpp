// ================================================ //

#ifndef __LABEL_HPP__
#define __LABEL_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

class Label
{
public:
	explicit Label(void);
	virtual ~Label(void);

	void create(const std::string& label);

	// Getter functions
	SDL_Texture* getTexturePtr(void) const;
	const int getOffset(void) const;

	// Setter functions
	void setOffset(const int offset);

private:
	SDL_Texture* m_pTexture;
	std::string m_label;
	int m_offset; // space between both left/right sides of Object's dst
};

// ================================================ //

// Getters
inline SDL_Texture* Label::getTexturePtr(void) const{
	return m_pTexture;
}

inline const int Label::getOffset(void) const{
	return m_offset;
}

// Setters
inline void Label::setOffset(const int offset){
	m_offset = offset;
}

// ================================================ //

#endif

// ================================================ //