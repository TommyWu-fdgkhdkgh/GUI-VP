file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_library(rv64-spike
		iss.cpp
		syscall.cpp
        ${HEADERS})

target_link_libraries(rv64-spike core-common ${SoftFloat_LIBRARIES})


if(COLOR_THEME STREQUAL "LIGHT")
	message("> using color theme LIGHT")
	target_compile_definitions(rv64-spike PRIVATE COLOR_THEME_LIGHT)
elseif(COLOR_THEME STREQUAL "DARK")
	message("> using color theme DARK")
	target_compile_definitions(rv64-spike PRIVATE COLOR_THEME_DARK)
endif()


target_include_directories(rv64-spike PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
