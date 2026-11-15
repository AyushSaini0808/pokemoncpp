cmake_minimum_required(VERSION 4.3)
project(pokemon)

set(CMAKE_CXX_STANDARD 20)

add_executable(pokemon src/main.cpp
        src/Move.cpp
        src/Move.h
        src/Pokemon.cpp
        src/Pokemon.h
        src/Type.h
        src/TypeChart.cpp
        src/TypeChart.h
        src/Damage.cpp
        src/Damage.h
        src/Battle.cpp
        src/Battle.h
        src/BattleUI.cpp
        src/BattleUI.h
)
target_compile_options(pokemon PRIVATE -Wall -Wextra -Wpedantic)
