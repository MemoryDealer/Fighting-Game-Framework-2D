// ================================================ //

#include "stdafx.hpp"
#include "App.hpp"

// ================================================ //

#ifdef __cplusplus
	extern "C" {
#endif

// ================================================ //

int SDL_main(int argc, char** argv)
{
	try{
		// Initialize application log
		App app;
		
	} 
	catch(std::exception& e){
#ifdef __WIN32__
		MessageBoxA(GetForegroundWindow(), e.what(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
		std::cerr << "An exception has occured: " << e.what() << std::endl;
#endif
	}

	return 0;
}

// ================================================ //

#ifdef __cplusplus
}
#endif