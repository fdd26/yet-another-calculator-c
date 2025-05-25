cmake_minimum_required(VERSION 3.10)
project(yet-another-calculator-c)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (MSVC)
	add_compile_options(/W4 /Zi)
else()
	add_compile_options(-Wall -Wextra -Wshadow -Wconversion -pedantic -ggdb3 -Wmaybe-uninitialized -std=gnu11)
	
	add_compile_options(-fsanitize=address -fsanitize=undefined)
	add_link_options(-fsanitize=address -fsanitize=undefined)
endif()

add_executable (calc
	./src/main.c
	./src/tokenize.c
)
target_include_directories(calc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

set_target_properties(calc PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
