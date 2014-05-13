// ================================================ //

#ifndef __FIGHTERMETADATA_HPP__
#define __FIGHTERMETADATA_HPP__

// ================================================ //

#include "Config.hpp"

// ================================================ //

struct Move;

// ================================================ //

class FighterMetadata : public Config
{
public:
	explicit FighterMetadata(const char* file);
	explicit FighterMetadata(void);
	virtual ~FighterMetadata(void);

	// Currently this is shit, probably O(n^3) or something
	virtual Move* parseMove(const char* name);
	

private:
	// This function will obtain a basic string value from within a move
	//  used by parseMove() in case data is out of order 
	virtual std::string parseMoveValue(const char* section, const char* value);
	virtual const int parseMoveIntValue(const char* section, const char* value);
	virtual const bool parseMoveBoolValue(const char* section, const char* value);
	virtual void parseHitboxes(Move* pMove, const char* frame);
	virtual SDL_Rect FighterMetadata::parseRect(const std::string& str);

	std::streampos m_moveBeg;
};

// ================================================ //

#endif

// ================================================ //