cmake_minimum_required(VERSION 3.0)
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(rl VERSION 1.0.0)
add_subdirectory(src)

configure_file(${CMAKE_SOURCE_DIR}/data/terminal_8x8.png ${CMAKE_BINARY_DIR}/bin/terminal_8x8.png COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/data/Hack-Regular.ttf ${CMAKE_BINARY_DIR}/bin/Hack-Regular.ttf COPYONLY)

if(WIN32)
configure_file(${CMAKE_SOURCE_DIR}/lib/BearLibTerminal.dll ${CMAKE_BINARY_DIR}/bin/BearLibTerminal.dll COPYONLY)
endif()

