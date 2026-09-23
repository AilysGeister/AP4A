cmake_minimum_required(VERSION 3.16)

# Project updated to 'simulator' with C++ support
project(simulator CXX)

# Use C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Export compile_commands.json for LSP/tooling (clangd, ccls)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Force executables to be placed in project_root/bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

# ------------------------------------------------------------------------------
# Source Discovery & Library Setup
# ------------------------------------------------------------------------------

# Collect all C++ sources under src/
file(GLOB_RECURSE SIMULATOR_SOURCES CONFIGURE_DEPENDS src/*.cpp)

set(MAIN_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

# Filter out main.cpp to find secondary library sources
set(LIB_SOURCES ${SIMULATOR_SOURCES})
list(REMOVE_ITEM LIB_SOURCES "${MAIN_SOURCE}")

# Compiler warning flags
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(DEFAULT_COMPILE_OPTIONS -Wall -Wextra -Wpedantic)
elseif(MSVC)
    set(DEFAULT_COMPILE_OPTIONS /W4)
endif()

# Build static library only if additional source files exist in src/
if(LIB_SOURCES)
    add_library(simulator_lib STATIC ${LIB_SOURCES})
    target_include_directories(simulator_lib PUBLIC src)
    target_compile_options(simulator_lib PRIVATE ${DEFAULT_COMPILE_OPTIONS})
    message(STATUS "Building simulator_lib with helper sources.")
else()
    message(STATUS "No helper sources found in src/; building executable directly.")
endif()

# ------------------------------------------------------------------------------
# Main Executable
# ------------------------------------------------------------------------------

add_executable(simulator "${MAIN_SOURCE}")
target_include_directories(simulator PRIVATE src)
target_compile_options(simulator PRIVATE ${DEFAULT_COMPILE_OPTIONS})

if(TARGET simulator_lib)
    target_link_libraries(simulator PRIVATE simulator_lib)
endif()

# ------------------------------------------------------------------------------
# Custom Utility Targets (Clean Build & Force Rebuild)
# ------------------------------------------------------------------------------

# 1. Clean build target (`cmake --build build --target cleanbuild`)
add_custom_target(cleanbuild
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_BINARY_DIR}" --clean-first
    COMMENT "Cleaning and rebuilding all targets..."
)

# 2. Force rebuild target (`cmake --build build --target forcebuild`)
add_custom_target(forcebuild
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_BINARY_DIR}" -- --always-make
    COMMENT "Forcing rebuild of all files, including unchanged ones..."
)