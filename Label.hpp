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

private:
	SDL_Texture* m_pTexture;
	std::string m_label;
};

// ================================================ //

inline SDL_Texture* Label::getTexturePtr(void) const{
	return m_pTexture;
}

// ================================================ //

#endif

// ================================================ //