// ================================================ //

#include "FighterMetadata.hpp"
#include "Engine.hpp"

// ================================================ //

FighterMetadata::FighterMetadata(void)
	:	Config(Config::FIGHTER_METADATA),
		m_moveBeg()
{

}

// ================================================ //

FighterMetadata::~FighterMetadata(void)
{

}

// ================================================ //

Move* FighterMetadata::parseMove(const char* name)
{
	this->resetFilePointer();

	while(!m_file.eof()){
		m_file >> m_buffer;

		// Look for moves section
		if(m_buffer[0] == '[' && m_buffer[m_buffer.size() - 1] == ']'){
			if(m_buffer.compare(1, m_buffer.size() - 2, "moves") == 0){

				// In the moves section, now find the move
				while(!m_file.eof()){
					m_file >> m_buffer;

					if(m_buffer[0] == '+'){
						// Found a move, see if it's the right one (example buffer: "+(IDLE){")
						if(m_buffer.compare(2, m_buffer.size() - 4, name) == 0){

							// Allocate Move object for this move
							Move* pMove = new Move();

							// Store beginning of this move's data
							m_moveBeg = m_file.tellg();

							// Get the main data for the move
							pMove->numFrames = this->parseMoveIntValue("core", "numFrames");
							pMove->frameGap = this->parseMoveIntValue("core", "frameGap");

							// frame data
							m_buffer = this->parseMoveValue("core", "frameData");
							char c;
							std::istringstream parse(m_buffer);
							parse >> pMove->startupFrames;
							parse >> c;
							parse >> pMove->hitFrames;
							parse >> c;
							parse >> pMove->recoveryFrames;

							pMove->damage = this->parseMoveIntValue("core", "damage");
							pMove->knockback = this->parseMoveIntValue("core", "knockback");
							pMove->repeat = this->parseMoveBoolValue("core", "repeat");
							if(pMove->repeat)
								pMove->repeatFrame = this->parseMoveIntValue("core", "repeatFrame");
							pMove->reverse = this->parseMoveBoolValue("core", "reverse");

							// Parse any cancels
							// ...

							// Locomotion
							pMove->xVel = this->parseMoveIntValue("locomotion", "xVel");
							pMove->yVel = this->parseMoveIntValue("locomotion", "yVel");

							// Parse initial frame
							Frame frame1;
							frame1.x = this->parseMoveIntValue("frame1", "x");
							frame1.y = this->parseMoveIntValue("frame1", "y");
							frame1.w = this->parseMoveIntValue("frame1", "w");
							frame1.h = this->parseMoveIntValue("frame1", "h");
							pMove->frames.push_back(frame1);

							// Parse the rest of the frames
							for(int i=2; i<=pMove->numFrames; ++i){
								Frame frame;
								std::string frameSection = "frame" + Engine::toString(i);
								frame.x = this->parseMoveIntValue(frameSection.c_str(), "x");
								frame.y = this->parseMoveIntValue(frameSection.c_str(), "y");
								frame.w = this->parseMoveIntValue(frameSection.c_str(), "w");
								frame.h = this->parseMoveIntValue(frameSection.c_str(), "h");

								// See if any values should be inherited
								if(frame.x == -1)
									frame.x = pMove->frames.back().x;
								if(frame.y == -1)
									frame.y = pMove->frames.back().y;
								if(frame.w == -1)
									frame.w = pMove->frames.back().w;
								if(frame.h == -1)
									frame.h = pMove->frames.back().h;

								pMove->frames.push_back(frame);
							}

							// Finished parsing move
							return pMove;
						}
					}
				}
			}
		}
	}

	return nullptr;
}

// ================================================ //

std::string FighterMetadata::parseMoveValue(const char* section, const char* value)
{
	// Reset file pointer to beginning of this move
	m_file.clear();
	m_file.seekg(m_moveBeg);

	while(!m_file.eof()){
		// Find the section
		m_file >> m_buffer;

		if(m_buffer[0] == '[' && m_buffer[m_buffer.size() - 2] == ']'){
			
			// Does the section name match? 
			if(m_buffer.compare(1, m_buffer.size() - 3, section) == 0){
				while(m_buffer[0] != '}'){
					m_file >> m_buffer;

					// Skip comments
					if(m_buffer[0] != '#'){
						// Find location of assignment operator
						size_t assign = m_buffer.find_first_of('=');

						// See if this is the value
						if(m_buffer.compare(0, assign, value) == 0){
							m_buffer = m_buffer.substr(assign + 1, m_buffer.size());

							return m_buffer;
						}
					}
				}
			}
		}
	}

	m_file.clear();
	return std::string("");
}

// ================================================ //

const int FighterMetadata::parseMoveIntValue(const char* section, const char* value)
{
	std::string str = this->parseMoveValue(section, value);
	if(!str.empty()){
		return std::stoi(str);
	}

	return -1;
}

// ================================================ //

const bool FighterMetadata::parseMoveBoolValue(const char* section, const char* value)
{
	return (this->parseMoveIntValue(section, value) >= 1);
}

// ================================================ //