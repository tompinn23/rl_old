set(CMAKE_CXX_STANDARD ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
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


#lua

include_directories (${CMAKE_SOURCE_DIR}/src/lua-5.3.4/src)
set (LUA_SRC_CORE lua-5.3.4/src/lapi.c lua-5.3.4/src/lcode.c lua-5.3.4/src/lctype.c lua-5.3.4/src/ldebug.c lua-5.3.4/src/ldo.c lua-5.3.4/src/ldump.c lua-5.3.4/src/lfunc.c lua-5.3.4/src/lgc.c lua-5.3.4/src/llex.c
  lua-5.3.4/src/lmem.c lua-5.3.4/src/lobject.c lua-5.3.4/src/lopcodes.c lua-5.3.4/src/lparser.c lua-5.3.4/src/lstate.c lua-5.3.4/src/lstring.c lua-5.3.4/src/ltable.c
  lua-5.3.4/src/ltm.c lua-5.3.4/src/lundump.c lua-5.3.4/src/lvm.c lua-5.3.4/src/lzio.c)
set (LUA_SRC_LIB lua-5.3.4/src/lauxlib.c lua-5.3.4/src/lbaselib.c lua-5.3.4/src/lbitlib.c lua-5.3.4/src/lcorolib.c lua-5.3.4/src/ldblib.c lua-5.3.4/src/liolib.c
  lua-5.3.4/src/lmathlib.c lua-5.3.4/src/loslib.c lua-5.3.4/src/lstrlib.c lua-5.3.4/src/ltablib.c lua-5.3.4/src/lutf8lib.c lua-5.3.4/src/loadlib.c lua-5.3.4/src/linit.c)

add_library (libluadll SHARED ${LUA_SRC_CORE} ${LUA_SRC_LIB})
target_compile_definitions ( libluadll PRIVATE _CRT_SECURE_NO_WARNINGS LUA_BUILD_AS_DLL )
set_target_properties ( libluadll PROPERTIES OUTPUT_NAME lua53 LINKER_LANGUAGE C)

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
target_link_libraries(rl bearlib fmt whereami libluadll)

add_custom_command(
 TARGET ${PROJECT_NAME} POST_BUILD
 COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/data/lib ${CMAKE_BINARY_DIR}/lib 
 DEPENDS ${destination}
 COMMENT "copy data folder from  ${CMAKE_SOURCE_DIR}/data/lib => ${CMAKE_BINARY_DIR}/lib"
)
