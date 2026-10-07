cmake_minimum_required(VERSION 3.16)

# Nom du projet
project(simulator CXX)

# Utilisation du standard C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Export de compile_commands.json pour autocomplétion/LSP (VS Code, CLion, clangd)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Placer les exécutables compilés dans project_root/bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

# ------------------------------------------------------------------------------
# Recherche des fichiers sources et en-têtes
# ------------------------------------------------------------------------------

# Découverte automatique des fichiers .cpp dans src/
file(GLOB_RECURSE SIMULATOR_SOURCES CONFIGURE_DEPENDS src/*.cpp)

set(MAIN_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

# Filtrer main.cpp pour isoler les autres fichiers sources (.cpp)
set(LIB_SOURCES ${SIMULATOR_SOURCES})
list(REMOVE_ITEM LIB_SOURCES "${MAIN_SOURCE}")

# Options de compilation / Warnings
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(DEFAULT_COMPILE_OPTIONS -Wall -Wextra -Wpedantic)
elseif(MSVC)
    set(DEFAULT_COMPILE_OPTIONS /W4)
endif()

# ------------------------------------------------------------------------------
# Création de la bibliothèque et de l'exécutable
# ------------------------------------------------------------------------------

# Création de la bibliothèque statique si des sources existent dans src/
if(LIB_SOURCES)
    add_library(simulator_lib STATIC ${LIB_SOURCES})
    # Inclusion des dossiers headers/ et src/
    target_include_directories(simulator_lib PUBLIC headers src)
    target_compile_options(simulator_lib PRIVATE ${DEFAULT_COMPILE_OPTIONS})
    message(STATUS "Building simulator_lib avec le dossier headers/ et src/.")
else()
    message(STATUS "Aucun fichier source secondaire dans src/.")
endif()

# Création de l'exécutable principal
add_executable(simulator "${MAIN_SOURCE}")
target_include_directories(simulator PRIVATE headers src)
target_compile_options(simulator PRIVATE ${DEFAULT_COMPILE_OPTIONS})

if(TARGET simulator_lib)
    target_link_libraries(simulator PRIVATE simulator_lib)
endif()

# ------------------------------------------------------------------------------
# Cibles personnalisées (Clean Build)
# ------------------------------------------------------------------------------

add_custom_target(cleanbuild
    COMMAND ${CMAKE_COMMAND} --build "${CMAKE_BINARY_DIR}" --clean-first
    COMMENT "Nettoyage et re-compilation complète..."
)