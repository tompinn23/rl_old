set(CMAKE_CXX_STANDARD ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/deps/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/deps/bearlibterminal)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/deps/lua/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/deps/fmt)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/deps/whereami)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_BINARY_DIR})

add_subdirectory(deps)

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
configure_file(src/config.h.in ${CMAKE_BINARY_DIR}/config.h)

set(RL_SRC src/main.cc src/generate.cc src/player.cc src/interface.cc src/portability.cc src/registry.cc)

add_executable(rl ${RL_SRC})
target_link_libraries(rl bearlib fmt whereami libluadll)

add_custom_command(
 TARGET ${PROJECT_NAME} POST_BUILD
 COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/data/lib ${CMAKE_BINARY_DIR}/lib 
 DEPENDS ${destination}
 COMMENT "copy data folder from  ${CMAKE_SOURCE_DIR}/data/lib => ${CMAKE_BINARY_DIR}/lib"
)

