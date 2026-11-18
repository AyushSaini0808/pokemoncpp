include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(pokemon_tests
        move_test.cpp
        pokemon_test.cpp
        typechart_test.cpp
        damage_test.cpp
        battle_test.cpp
)
target_link_libraries(pokemon_tests PRIVATE pokemon_core GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(pokemon_tests)