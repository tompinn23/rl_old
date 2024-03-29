set(CMAKE_CXX_STANDARD ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src)

include_directories(${CMAKE_SOURCE_DIR}/src/fmt)
include_directories(${CMAKE_SOURCE_DIR}/src/whereami)
include_directories(${CMAKE_BINARY_DIR})
#Config Section
include (CheckIncludeFileCXX)
include (CheckCXXSymbolExists)

check_include_file_cxx("experimental/filesystem" HAVE_FS_EXP_H)
check_include_file_cxx("filesystem" HAVE_FS_H)
if(HAVE_FS_H)
check_cxx_symbol_exists("std::filesystem::absolute" "filesystem" FS_STD)
check_cxx_symbol_exists("std::experimental::filesystem::absolute" "filesystem" FS_EXP)
endif()
if(HAVE_FS_EXP_H)
check_cxx_symbol_exists("std::filesystem::absolute" "experimental/filesystem" FS_STD)
check_cxx_symbol_exists("std::experimental::filesystem::absolute" "experimental/filesystem" FS_EXP)
endif()
configure_file(config.h.in ${CMAKE_BINARY_DIR}/config.h)


find_package(PythonLibs REQUIRED)

include_directories(${PYTHON_INCLUDE_DIRS})

add_library(bearlib SHARED IMPORTED)
if(WIN32)
set_target_properties(bearlib PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/BearLibTerminal.dll)
set_target_properties(bearlib PROPERTIES IMPORTED_IMPLIB ${CMAKE_SOURCE_DIR}/lib/BearLibTerminal.lib)
else()
set_target_properties(bearlib PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/libBearLibTerminal.so)
endif()

add_subdirectory(fmt)
add_subdirectory(whereami)
#add_subdirectory(screen)

add_executable(rl main.cc generate.cc player.cc interface.cc portability.cc registry.cc)
target_link_libraries(rl bearlib fmt whereami ${PYTHON_LIBRARIES})

add_custom_command(
 TARGET ${PROJECT_NAME} POST_BUILD
 COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/data/lib ${CMAKE_BINARY_DIR}/bin/lib 
 DEPENDS ${destination}
 COMMENT "copy data folder from  ${CMAKE_SOURCE_DIR}/data/lib => ${CMAKE_BINARY_DIR}/bin/lib"
)
