cmake_minimum_required(VERSION 3.0)

project(gitz)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(wxWidgets REQUIRED)
include(${wxWidgets_USE_FILE})

find_package(Libgit2 REQUIRED)
include_directories(${LIBGIT2_INCLUDE_DIR})

if(WIN32)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

add_executable(gitz WIN32
    src/gitz.cpp
    src/gitz.rc
    src/git-icon.ico
    src/GitzApp.cpp
    src/GitzApp.h
    src/GitzFrame.cpp
    src/GitzFrame.h
    src/wx.h
)
target_link_libraries(gitz ${LIBGIT2_LIBRARIES} ${wxWidgets_LIBRARIES})
