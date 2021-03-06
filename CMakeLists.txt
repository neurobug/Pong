cmake_minimum_required(VERSION 3.9)
project(pong)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "-mwindows")
endif(MINGW)

# Using Jackbengine library
add_subdirectory(${PROJECT_SOURCE_DIR}/external/jackbengine)
include_directories(${PROJECT_SOURCE_DIR}/external/jackbengine/include)
include_directories(${PROJECT_SOURCE_DIR}/external/jackbengine/src)
include_directories(${PROJECT_SOURCE_DIR}/external/jackbengine/external)

include_directories(${PROJECT_SOURCE_DIR}/src)

# Using Resource generator tool
add_executable(
    resourceGenerator
    ${PROJECT_SOURCE_DIR}/external/resourceGenerator/resourceGenerator.c
)

# Creating resources C representations
add_custom_command(
    OUTPUT resources.cpp
    COMMAND resourceGenerator
        resources.cpp
        -b${PROJECT_SOURCE_DIR}/resources/left.wav
        -b${PROJECT_SOURCE_DIR}/resources/right.wav
        -b${PROJECT_SOURCE_DIR}/resources/wall.wav
        -t${PROJECT_SOURCE_DIR}/resources/menu.tmx
        -t${PROJECT_SOURCE_DIR}/resources/wall.tmx
        -t${PROJECT_SOURCE_DIR}/resources/two_players.tmx
        -t${PROJECT_SOURCE_DIR}/resources/one_player.tmx
        -b${PROJECT_SOURCE_DIR}/resources/tileset.png
        -b${PROJECT_SOURCE_DIR}/resources/pong32x32.png
    DEPENDS
        resources/left.wav
        resources/right.wav
        resources/wall.wav
        resources/menu.tmx
        resources/wall.tmx
        resources/two_players.tmx
        resources/one_player.tmx
        resources/tileset.png
        resources/pong32x32.png
)

# Tell CMake to create an app bundle on MacOS
if(APPLE)
    set(CMAKE_MACOSX_BUNDLE true)
    set(ICON_FILE ${PROJECT_SOURCE_DIR}/resources/${CMAKE_PROJECT_NAME}.icns)
    set_source_files_properties(
        ${ICON_FILE}
        PROPERTIES
        MACOSX_PACKAGE_LOCATION
        Resources
    )
endif(APPLE)

if(MINGW)
    set(ICON_FILE ${PROJECT_SOURCE_DIR}/resources/win_icon.rc)
endif(MINGW)

# Defining source files
set(
    SOURCE_FILES
    src/main.cpp
    src/app.cpp
    src/scene/menu/menuScene.cpp
    src/scene/wall/wallScene.cpp
    src/scene/wall/state/wallServiceState.cpp
    src/scene/wall/state/wallGameState.cpp
    src/scene/wall/state/wallGameOverState.cpp
    src/scene/2players/2playersScene.cpp
    src/scene/2players/state/2playersServiceState.cpp
    src/scene/2players/state/2playersGameState.cpp
    src/scene/2players/state/2playersGameOverState.cpp
    src/scene/1player/1playerScene.cpp
    src/scene/1player/state/1playerServiceState.cpp
    src/scene/1player/state/1playerGameState.cpp
    src/scene/1player/state/1playerGameOverState.cpp
    resources.cpp
    ${ICON_FILE}
)

# Compiling final executable
add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${CMAKE_PROJECT_NAME} jackbengine)

# Post build operations
if(APPLE)
    set_target_properties(
        ${CMAKE_PROJECT_NAME}
        PROPERTIES
        MACOSX_BUNDLE_INFO_PLIST
        ${PROJECT_SOURCE_DIR}/resources/${CMAKE_PROJECT_NAME}.plist
    )
endif(APPLE)
