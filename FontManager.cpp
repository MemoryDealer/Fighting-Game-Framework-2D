// ================================================ //

#include "FontManager.hpp"
#include "Config.hpp"

// ================================================ //

template<> FontManager* Singleton<FontManager>::msSingleton = nullptr;

// ================================================ //

FontManager::FontManager(void) :
m_pMainFont(nullptr)
{

}

// ================================================ //

FontManager::~FontManager(void)
{

}

// ================================================ //

void FontManager::loadMainFont(const std::string& file, const int size)
{
	m_pMainFont.reset(new Font(file, size));
}

// ================================================ //

void FontManager::reloadAll(void)
{
	Config e("ExtMF.cfg");
	Config theme(e.parseValue("GUI", "theme"));
	if (theme.isLoaded()){
		m_pMainFont.reset(new Font(theme.parseValue("font.main", "file"), 
			theme.parseIntValue("font.main", "size")));
	}
}

// ================================================ //