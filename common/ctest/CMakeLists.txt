cmake_minimum_required(VERSION 3.11)

project(ctest)

set(DOUBLY_LINKED_LIST_HEADER_FILES
    ${CMAKE_CURRENT_LIST_DIR}/inc/ctest.h
    )

set(DOUBLY_LINKED_LIST_SOURCE_FILES
    ${CMAKE_CURRENT_LIST_DIR}/src/ctest.c
    )

add_library(${PROJECT_NAME}_lib
    ${DOUBLY_LINKED_LIST_HEADER_FILES}
    ${DOUBLY_LINKED_LIST_SOURCE_FILES}
    )
target_include_directories(${PROJECT_NAME}_lib PUBLIC inc)

add_executable(${PROJECT_NAME} src/main.c)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_lib)
