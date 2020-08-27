cmake_minimum_required(VERSION 3.0)

project(gitz LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../cmake)

find_package(wxWidgets 3.1 REQUIRED)
include(${wxWidgets_USE_FILE})

find_package(libgit2 REQUIRED)
include_directories(${LIBGIT2_INCLUDE_DIR})

if(WIN32)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

add_executable(gitz WIN32
    ../icons/git-icon.ico
    gitz.cpp
    gitz.rc
    GitzApp.cpp
    GitzApp.h
    GitzFrame.cpp
    GitzFrame.h
    wx.h
)
target_link_libraries(gitz ${LIBGIT2_LIBRARIES} ${wxWidgets_LIBRARIES})
