// ================================================ //

#ifndef __FONTMANAGER_HPP__
#define __FONTMANAGER_HPP__

// ================================================ //

#include "stdafx.hpp"
#include "Font.hpp"

// ================================================ //

class FontManager : public Singleton<FontManager>
{
public:
	explicit FontManager(void);
	~FontManager(void);

	void loadMainFont(const std::string& file, const int size);

	void reloadAll(void);

	// Getter functions
	Font* getMainFont(void) const;

private:
	std::shared_ptr<Font> m_pMainFont;
};

// ================================================ //

inline Font* FontManager::getMainFont(void) const{
	return m_pMainFont.get();
}

// ================================================ //

#endif

// ================================================ //