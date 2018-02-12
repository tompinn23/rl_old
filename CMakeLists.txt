cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(rl VERSION 1.0.0)

math(EXPR BITNESS "8*${CMAKE_SIZEOF_VOID_P}")

add_subdirectory(rl)

configure_file(${CMAKE_SOURCE_DIR}/data/terminal_8x8.png ${CMAKE_BINARY_DIR}/terminal_8x8.png COPYONLY)

if(WIN32)
configure_file(${CMAKE_SOURCE_DIR}/rl/deps/bearlibterminal/Windows${BITNESS}/BearLibTerminal.dll ${CMAKE_BINARY_DIR}/BearLibTerminal.dll COPYONLY)
endif()

