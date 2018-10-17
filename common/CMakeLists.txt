cmake_minimum_required(VERSION 3.11)

project(STL)

add_compile_options("-Wall" "-g3" "-Wextra" "-pedantic" "-Wcast-align"
"-Winit-self" "-Wmissing-include-dirs" "-Wredundant-decls" "-Wshadow"
"-Wstrict-overflow=5" "-Wundef" "-Wwrite-strings" "-Wpointer-arith"
"-Wmissing-declarations" "-Wuninitialized" "-Wold-style-definition"
"-Wstrict-prototypes" "-Wmissing-prototypes" "-Wswitch-default"
"-Wbad-function-cast" "-Wnested-externs" "-Wconversion" "-Wunreachable-code")

add_subdirectory(debug_print)
add_subdirectory(ctest)
