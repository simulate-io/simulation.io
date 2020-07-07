# v3.10 required for C++17 MSVC
cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

if(POLICY CMP0025)
    # compiler id for AppleClang is now 'AppleClang' rather than OLD (default) policy of 'Clang'
    cmake_policy(SET CMP0025 NEW)
endif()

# notably sets the PROJECT_NAME variable, C/CXX as default build-languages, but i'll overwrite it to just target CXX
# https://cmake.org/cmake/help/latest/command/project.html
project(simulate.io LANGUAGES CXX)

# note: if ccache is installed as a wrapper around the compiler, it must have its SLOPPINESS config setting set (ENV vars are the highest priority scope way of doing this)
# otherwise, cotire will complain and not generate the precompiled header (.gch), but it does issue this way of fixing it (thankfully!)
if(${CMAKE_HOST_SYSTEM_NAME} MATCHES "Darwin" OR ${CMAKE_HOST_SYSTEM_NAME} MATCHES "Linux")
    message(STATUS "HOST SYSTEM NAME is Darwin or Linux. Searching for (optional) ccache...")
    find_program(CCACHE_PROGRAM ccache)
    if(CCACHE_PROGRAM)
        message(STATUS "ccache found! Setting ENV variable (CCACHE_SLOPPINESS) so that cotire can build .gch")
        # reference: https://ccache.dev/manual/latest.html#_configuration_settings
        set(ENV{CCACHE_SLOPPINESS} "pch_defines,time_macros")
    else()
        message(STATUS "ccache not found! Nothing changes.")
    endif()
endif()

# use C++17 features (globally, for all subsequent targets)
set(CMAKE_CXX_STANDARD 17) # C++17 MSVC fix in CMake 3.10
set(CMAKE_CXX_STANDARD_REQUIRED ON) # prevent default fallback to an older standard if compiler doesn't support C++17
set(CMAKE_CXX_EXTENSIONS OFF) # only use the official standards (e.g. for g++, -std=c++17 and not -std=gnu++17)

# add cmake/ directory to PATH variable where CMake looks for modules (.cmake files)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
# add path to cotire module
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/deps/cotire/CMake")
# searches module path for a 'cotire.cmake' and includes its defined macros
include(cotire)

# add path to googltest module
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/deps/googletest/googletest/CMake")
add_subdirectory(deps/googletest)
enable_testing()
include_directories(${googletest_SOURCE_DIR}/include)

# for MSVC, switch to multi-threaded static linking of MSVCRT runtime library
if(MSVC)
    # init CompilerFlags variable as a list of these terms found in the cmake cache file
    set(CompilerFlags
        CMAKE_CXX_FLAGS
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_MINSIZEREL
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_RELWITHDEBINFO
    )
    # check each of these cache entries and replace any /MD with /MT and /MDd with /MTd
    # note: since these variables are already in the cache, the pattern set(... CACHE ... FORCE) must be used to overwrite it
    foreach(CompilerFlag ${CompilerFlags})
        if(${CompilerFlag} MATCHES "/MD")
            string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
            set(${CompilerFlag} "${${CompilerFlag}}" CACHE STRING "msvc compiler flags" FORCE)
        endif()
        if(${CompilerFlag} MATCHES "/MDd")
            string(REPLACE "/MDd" "/MTd" ${CompilerFlag} "${${CompilerFlag}}")
            set(${CompilerFlag} "${${CompilerFlag}}" CACHE STRING "msvc compiler flags" FORCE)
        endif()
    endforeach()
endif()

# adds an executable target <simulate.io> to be built from the source files listed <main.cpp>
# the source files can be removed from here and specified later using target_sources()
# https://cmake.org/cmake/help/latest/command/add_executable.html
# warning: use CMAKE_CURRENT_SOURCE_DIR rather than CMAKE_SOURCE_DIR since the the latter points to the src directory of the parent project. So, if my project is a sub-project of another then mine won't build
# https://github.com/KhronosGroup/Vulkan-LoaderAndValidationLayers/issues/1428
# note: according to cotire manual, the pch.cpp file must be the first listed source file for out target
# reference: https://github.com/sakra/cotire/blob/master/MANUAL.md#using-a-manually-maintained-prefix-header-instead-of-the-automatically-generated-one

file(GLOB source_list
"src/*.cpp"
"src/battles/*.cpp"
"src/characters/*.cpp"
"src/game/*.cpp"
"include/*.h"
"include/game/*.h"
"/src/utils/*.hpp")

add_executable(simulate.io  ${source_list})

#YM: As of CMake 3.8 it supports TREE to recursivley search file paths for source structure,
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${source_list})

# reference: https://pabloariasal.github.io/2018/02/19/its-time-to-do-cmake-right/
# SCOPE SPECIFIERS...
# PRVATE - for internal building of target
# INTERFACE - for external users (usage requirements) of target
# PUBLIC = both PRIVATE and INTERFACE
# thus the include/ directory is PUBLIC since it is needed for both internally building target and external users to possess
# and src/ is PRIVATE since only private headers reside here and are only needed for internal building
target_include_directories(simulate.io
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# https://foonathan.net/blog/2018/10/17/cmake-warnings.html
# set the warning flags for the respective compilers using cmake generator expressions
# (removed, since this causes build nightmares when using warning-heavy libs) using -Werror and /WX to treat warnings as compile errors (ensures warnings get either fixed or suppressed right away rather than getting hidden in files that never get compiled again)
# using -Wall + -Wextra and /W4 to provide a sufficient amount of general warnings
# note: /Wall on MSVC is practically unusable due to the enormous amount of warnings generated by the standard library
# note: if additional warning flags are to be added, I believe the project would have to be clean-rebuilt to apply the new warning detection to previously compiled files
# note: for some reason, the cmakecache file doesn't reflect these changes (e.g. still says default of /W3), but they seem to still apply correctly
# DEPRECATED (cotire doesn't work well will some generator expressions, like the ones below...)
#target_compile_options(simulate.io PRIVATE
#    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
#        -Wall -Wextra>
#        # opt. could add -Werror (if your libs don't throw so many warnings or you have good warning policy handling)
#    $<$<CXX_COMPILER_ID:MSVC>:
#        /W4>
#        # opt. could add /WX (if your libs don't throw so many warnings or you have good warning policy handling)
#)

# reference: https://stackoverflow.com/questions/10046114/in-cmake-how-can-i-test-if-the-compiler-is-clang
if(CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(simulate.io PRIVATE -Wall -Wextra)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(simulate.io PRIVATE /W4)
endif()

# reference: https://stackoverflow.com/questions/7304625/how-do-i-change-the-startup-project-of-a-visual-studio-solution-via-cmake
# sets the startup project in the Visual Studio solution (so that user doesn't have to explicitly right click target and set option)
if(MSVC)
    set_property(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" PROPERTY VS_STARTUP_PROJECT simulate.io)
endif()

# cotire stuff (must go below target (simulate.io) configuration above)
# disable automatic UNITY (JUMBO) builds
set_target_properties(simulate.io PROPERTIES COTIRE_ADD_UNITY_BUILD FALSE)
# enable manual prefix header that we must maintain, rather than the automatic one generated by cotire
set_target_properties(simulate.io PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "${CMAKE_CURRENT_SOURCE_DIR}/include/simulate.io/pch.h")
# must call this after setting all target properties of simulate.io
# apply cotire function on our target
cotire(simulate.io)

# YM: adding the assets directory after the build is complete.
add_custom_command(
        TARGET simulate.io POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/assets/main.json
                ${CMAKE_CURRENT_BINARY_DIR}/assets/main.json
)