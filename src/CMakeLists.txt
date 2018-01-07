project(rl VERSION 1.0.0)

set(CMAKE_CXX_STANDARD ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src)



add_library(bearlib SHARED IMPORTED)
set_target_properties(bearlib PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/libBearLibTerminal.so)

add_subdirectory(fmt)
#add_subdirectory(screen)

add_executable(rl main.cc)
target_link_libraries(rl bearlib fmt)