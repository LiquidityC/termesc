cmake_minimum_required (VERSION 3.2.0)

SET(CMAKE_COLOR_MAKEFILE ON)

project(termesc C)

set(hdrfiles
	include/termesc.h
	)

set(srcfiles
	src/termesc.c
	)

include_directories(include)

add_library(termesc
	${srcfiles}
	${hdrfiles}
	)

add_executable(demo
	src/main
	)

target_link_libraries(demo termesc)
