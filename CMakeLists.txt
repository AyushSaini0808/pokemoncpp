cmake_minimum_required(VERSION 3.20)
project(pokemon)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Everything except main.cpp
add_library(pokemon_core STATIC
        src/Move.cpp
        src/Pokemon.cpp
        src/TypeChart.cpp
        src/Damage.cpp
        src/Battle.cpp
        src/BattleUI.cpp
)
target_include_directories(pokemon_core PUBLIC src)
target_compile_options(pokemon_core PRIVATE -Wall -Wextra -Wpedantic)

# The game
add_executable(pokemon src/main.cpp)
target_link_libraries(pokemon PRIVATE pokemon_core)
target_compile_options(pokemon PRIVATE -Wall -Wextra -Wpedantic)

# Tests
enable_testing()
add_subdirectory(tests)