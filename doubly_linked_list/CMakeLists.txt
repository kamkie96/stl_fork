cmake_minimum_required(VERSION 3.11)

project(doubly_linked_list)
add_compile_options("-Wall" "-Wextra" "-pedantic" "-Wcast-align"
"-Winit-self" "-Wmissing-include-dirs" "-Wredundant-decls" "-Wshadow"
"-Wstrict-overflow=5" "-Wundef" "-Wwrite-strings" "-Wpointer-arith"
"-Wmissing-declarations" "-Wuninitialized" "-Wold-style-definition"
"-Wstrict-prototypes" "-Wmissing-prototypes" "-Wswitch-default"
"-Wbad-function-cast" "-Wnested-externs" "-Wconversion" "-Wunreachable-code")

set(DOUBLY_LINKED_LIST_HEADER_FILES
    ${CMAKE_CURRENT_LIST_DIR}/inc/doubly_linked_list.h
    )

set(DOUBLY_LINKED_LIST_SOURCE_FILES
    ${CMAKE_CURRENT_LIST_DIR}/src/doubly_linked_list.c
    )

add_library(${PROJECT_NAME}_lib
    ${DOUBLY_LINKED_LIST_HEADER_FILES}
    ${DOUBLY_LINKED_LIST_SOURCE_FILES}
    )
target_include_directories(${PROJECT_NAME}_lib PUBLIC inc)

add_executable(${PROJECT_NAME} src/main.c)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_lib)

#add_subdirectory(tests)
