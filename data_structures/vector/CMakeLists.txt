cmake_minimum_required(VERSION 3.11)

project(vector)
add_compile_options("-Wall" "-g3" "-Wextra" "-pedantic" "-Wcast-align"
"-Winit-self" "-Wmissing-include-dirs" "-Wredundant-decls" "-Wshadow"
"-Wstrict-overflow=5" "-Wundef" "-Wwrite-strings" "-Wpointer-arith"
"-Wmissing-declarations" "-Wuninitialized" "-Wold-style-definition"
"-Wstrict-prototypes" "-Wmissing-prototypes" "-Wswitch-default"
"-Wbad-function-cast" "-Wnested-externs" "-Wconversion" "-Wunreachable-code")

set(VECTOR_HEADER_FILES
    ${CMAKE_CURRENT_LIST_DIR}/inc/vector.h
    )

set(VECTOR_SOURCE_FILES
    ${CMAKE_CURRENT_LIST_DIR}/src/vector.c
    )

add_library(${PROJECT_NAME}_lib
	    ${VECTOR_HEADER_FILES}
	    ${VECTOR_SOURCE_FILES}
    )
target_include_directories(${PROJECT_NAME}_lib PUBLIC inc)
target_include_directories(${PROJECT_NAME}_lib PUBLIC ../../common/)

add_executable(${PROJECT_NAME} src/main.c)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_lib)

add_subdirectory(tests)
