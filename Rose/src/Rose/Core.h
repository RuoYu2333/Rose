#pragma once

#ifdef RS_PLATFORM_WINDOWS
	#ifdef RS_BUILD_DLL
		#define ROSE_API __declspec(dllexport)
	#else 
		#define ROSE_API __declspec(dllimport)
	#endif
#else
    #error Rose only supports Windows!

#endif