// ================================================ //

#include "stdafx.hpp"
#include "Engine.hpp"

// ================================================ //

#ifdef __cplusplus
	extern "C" {
#endif

// ================================================ //

int SDL_main(int argc, char** argv)
{
	try{
		// Initialize application log
		new Log();
		new Engine();
	} 
	catch(std::exception& e){
		printf("ERROR: %s\n", e.what());
		return 1;
	}

	return 0;
}

// ================================================ //

#ifdef __cplusplus
}
#endif