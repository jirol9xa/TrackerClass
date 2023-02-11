cmake_minimum_required(VERSION 3.2)

project(TrackerClass)

add_compile_options (-fno-elide-constructors
  -fsanitize=address,leak,undefined
  -Wall
  -Wextra
  -Wpedantic
  )

# Add option to force ANSI-colors (useful for building with Ninja)
option(FORCE_COLORED_OUTPUT "Always produce ANSI-colored output (GNU/Clang only)." TRUE)

if (${FORCE_COLORED_OUTPUT})
  if     ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options (-fdiagnostics-color=always)
  elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options (-fcolor-diagnostics)
  endif ()
endif ()

set(MAIN_FILE main.cpp)

include_directories(include)  # Src headers

add_executable(main ${MAIN_FILE})

add_subdirectory(src)

target_link_libraries(main src)
