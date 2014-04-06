// ================================================ //

#ifndef __FIGHTERMETADATA_HPP__
#define __FIGHTERMETADATA_HPP__

// ================================================ //

#include "Config.hpp"
#include "Move.hpp"

// ================================================ //

class FighterMetadata : public Config
{
public:
	explicit FighterMetadata(void);
	virtual ~FighterMetadata(void);

	virtual Move* parseMove(const char* name);
	

private:
	// This function will obtain a basic string value from within a move
	//  used by parseMove() in case data is out of order 
	virtual std::string parseMoveValue(const char* section, const char* value);
	virtual const int parseMoveIntValue(const char* section, const char* value);
	virtual const bool parseMoveBoolValue(const char* section, const char* value);

	std::streampos m_moveBeg;
};

// ================================================ //

#endif

// ================================================ //