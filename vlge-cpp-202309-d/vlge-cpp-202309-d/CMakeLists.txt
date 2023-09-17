cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(vlge-cpp-202309-d)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 4.5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()

#--Define Your Custom Project Here--

add_executable(${PROJECT_NAME} main.cpp "GameEngine/GEVector3.h" "GameProgram/GPManager.cpp" "GameProgram/GPManager.h" "AppProgram/APManager.h" "AppProgram/APManager.cpp" "GameEngine/GENetwork.h" "GameEngine/GETransform.h" "GameProgram/GameProgram.cpp" "AppProgram/AppProgram.cpp" "GameEngine/GELogger.h" "AppEngine/AELogger.h" "LauncherProgram/LPManager.h"   "Constant/KExitCode.h" "Constant/KFpsTarget.h" "ArgumentException/ArgumentException.h" "AppProgram/AppProgram.h")

#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()