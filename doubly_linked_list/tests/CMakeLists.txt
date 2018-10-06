cmake_minimum_required(VERSION 3.11)

project(doubly_linked_list_tests)
add_compile_options("-Wall" "-Wextra" "-pedantic" "-Wcast-align"
"-Winit-self" "-Wmissing-include-dirs" "-Wredundant-decls" "-Wshadow" "-Wstrict-overflow=5" "-Wundef" "-Wwrite-strings" "-Wpointer-arith" "-Wmissing-declarations"
"-Wuninitialized" "-Wold-style-definition" "-Wstrict-prototypes"
"-Wmissing-prototypes" "-Wswitch-default" "-Wbad-function-cast"
"-Wnested-externs" "-Wconversion" "-Wunreachable-code")

set (DOUBLY_LINKED_LIST_TESTS_SOURCE_FILES
    ${CMAKE_CURRENT_LIST_DIR}/doubly_linked_list_tests.c
    )

add_executable(${PROJECT_NAME} ${DOUBLY_LINKED_LIST_TESTS_SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ../inc)
#target_include_directories(${PROJECT_NAME} PRIVATE ../../ctest/inc)

target_link_libraries(${PROJECT_NAME} doubly_linked_list_lib)

