cmake_minimum_required(VERSION 3.0)

project(gitz)

if(WIN32)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

add_executable(gitz WIN32
    gitz.cpp
    gitz.rc
    git-icon.ico
    GitzApp.cpp
    GitzApp.h
    GitzFrame.cpp
    GitzFrame.h
    wx.h
)