#pragma once

// Platform checking 
#if defined(_WIN64)
    #define WINDOWS 1
#elif defined(__unix__) || !defined(__APPLE__) && defined(__MACH__)
    #define LINUX 1
#elif defined(__APPLE__) && defined(__MACH__)
    #define OSX 1
#endif
