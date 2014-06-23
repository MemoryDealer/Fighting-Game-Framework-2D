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
	explicit FighterMetadata(const std::string& file);
	explicit FighterMetadata(void);
	virtual ~FighterMetadata(void);

	// Currently this is shit, probably O(n^3) or something
	virtual std::shared_ptr<Move> parseMove(const std::string& name);
	

private:
	// This function will obtain a basic string value from within a move
	//  used by parseMove() in case data is out of order 
	virtual std::string parseMoveValue(const std::string& section, const std::string& value);
	virtual const int parseMoveIntValue(const std::string& section, const std::string& value);
	virtual const bool parseMoveBoolValue(const std::string& section, const std::string& value);
	virtual void parseHitboxes(std::shared_ptr<Move> pMove, const std::string& frame);
	virtual SDL_Rect FighterMetadata::parseRect(const std::string& str);

	std::streampos m_moveBeg;
};

// ================================================ //

#endif

// ================================================ //