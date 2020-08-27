cmake_minimum_required(VERSION 3.0)
cmake_policy(SET CMP0048 NEW)

project(gitz LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../cmake)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR
   CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

set(CMAKE_AUTORCC ON)

set(HEADERS
    ../Commit.h
    ../Repository.h
)

set(SOURCES
    ../Commit.cpp
    ../Repository.cpp
    gitz.cpp
    gitz.qrc
)

set(RESOURCES
    ../icons/git-icon.ico
    ../icons/git-icon.png
)

qt5_add_resources(EMBEDDED_RESOURCES gitz.qrc)

add_executable(gitz
    ${HEADERS}
    ${SOURCES}
    ${RESORUCES}
    ${EMBEDDED_RESOURCES}
)

target_link_libraries(gitz
    Qt5::Core
    Qt5::Widgets
)

if(WIN32)
    if(MSVC)
        set_property(TARGET gitz APPEND_STRING PROPERTY
                     LINK_FLAGS " /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
    elseif(MINGW)
        set_property(TARGET gitz APPEND_STRING PROPERTY
                     LINK_FLAGS " -Wl,-subsystem,windows")
    endif()
endif()
