cmake_minimum_required(VERSION 3.10)

project(sm LANGUAGES C)

add_compile_definitions(_POSIX_C_SOURCE=200809L)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -D_DEBUG")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_library(sm STATIC)
add_subdirectory(../threading ${CMAKE_BINARY_DIR}/threading_from_sm)
add_subdirectory(../api ${CMAKE_BINARY_DIR}/api_from_sm)

target_sources(sm PRIVATE
    sm.c
)

target_include_directories(sm PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(sm
	PUBLIC
    	threading
    	api
)
