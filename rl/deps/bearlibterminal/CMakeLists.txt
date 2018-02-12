add_library(bearlib SHARED IMPORTED GLOBAL)

if(WIN32)
set_target_properties(bearlib PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/Windows${BITNESS}/BearLibTerminal.dll)
set_target_properties(bearlib PROPERTIES IMPORTED_IMPLIB ${CMAKE_CURRENT_SOURCE_DIR}/Windows${BITNESS}/BearLibTerminal.lib)
else()
set_target_properties(bearlib PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/Linux${BITNESS}/libBearLibTerminal.so)
endif()
