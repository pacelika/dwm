cmake_minimum_required(VERSION "3.30")
project(dwm)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/bin/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_DIR}/lib")

add_executable(${PROJECT_NAME} source/config.c source/drw.c source/dwm.c source/transient.c source/util.c source/main.c)
set_source_files_properties(${CMAKE_BINARY_DIR}/CMakeFiles/CompilerIdC/CMakeCCompilerId.c PROPERTIES HEADER_FILE_ONLY TRUE)
add_definitions(-D_DEFAULT_SOURCE -D_BSD_SOURCE -D_XOPEN_SOURCE=700L)
target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC VERSION="1")
include_directories(/usr/X11R6/include /usr/include/freetype2 ${CMAKE_SOURCE_DIR}/headers ${CMAKE_CURRENT_SOURCE_DIR}/source/)
link_directories(/usr/X11R6/lib)
target_link_libraries(${PROJECT_NAME} PRIVATE -lXinerama -lfontconfig -lXft -lX11 -lm)
