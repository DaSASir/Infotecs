cmake_minimum_required(VERSION 3.16)

add_library(my_library SHARED
    library.cpp
    library.h
)

target_include_directories(my_library PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

set_target_properties(my_library PROPERTIES
    WINDOWS_EXPORT_ALL_SYMBOLS ON
)