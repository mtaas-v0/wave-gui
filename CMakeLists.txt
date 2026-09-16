cmake_minimum_required (VERSION 2.8)
project (wave-gui)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RELEASE)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

if(NOT MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -W -Wall -Wno-long-long -pedantic")

endif()

if(MINGW)
    # Forces GCC to link the C, C++, and thread runtimes statically
    if(NOT BUILD_SHARED_LIBS)
        message(STATUS "🔒 Building project as STATIC libraries.")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++ -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,-Bdynamic,--no-whole-archive")
    else()
        add_compile_definitions(MAKE_DLL)
    
    endif()
endif()

if(MINGW)
    message(STATUS "🟢 SUCCESS: CMake detected MINGW toolchain!")
    message(STATUS "   Compiler: ${CMAKE_CXX_COMPILER_ID} version ${CMAKE_CXX_COMPILER_VERSION}")
else()
    message(WARNING "🔴 FAILURE: MINGW was NOT detected by CMake.")
    message(STATUS "   Active Toolchain ID: ${CMAKE_CXX_COMPILER_ID}")
endif()


if(WIN32)
    # This forces BOTH the compiler and IDEs to recognize the definition
    add_compile_definitions(_WIN32)
endif()


#
## Dependencies
find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(SDL2 REQUIRED)

# Replace the pkg_search_module(glfw3 REQUIRED glfw3) block with this:
find_package(glfw3 CONFIG REQUIRED)

include_directories(SYSTEM ${GLFW_INCLUDE_DIRS})

find_package(FFTW)
if (FFTW_FOUND)
    message(STATUS "FFTW support enabled.")
    include_directories(SYSTEM ${FFTW_INCLUDE_DIRS})
else()
    message(WARNING "Cannot find FFTW. Not using/building FFTW stuff")
endif()

#
## Logging parameters
if (CG_LOGGING) # Verbosity
    add_definitions(-DCG_LOGGING=${CG_LOGGING})
else (CG_LOGGING)
    add_definitions(-DCG_LOGGING=10)
endif (CG_LOGGING)

#mingw adjust
include_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/external/mingw-std-threads)



option(CG_OUTPUT "Use cg-output" ON)
if (CG_OUTPUT)
    add_definitions(-DCG_OUTPUT -DCOLOR_OUTPUT)
endif()




add_definitions(-DCG_COLOR_OUTPUT) # Colored log messages

## Libs
set(CG_CORE_LIB cg_core)
set(CG_IMGUI_LIB ImGui)

include_directories(src)
include_directories(external)

add_subdirectory(src)
add_subdirectory(external)
add_subdirectory(main)
