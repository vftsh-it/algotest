add_executable(aplusb_tests aplusb_tests.cpp)
target_link_libraries(aplusb_tests PRIVATE aplusb_i aplusb src gtest gtest_main)

add_test(
        NAME aplusb
        COMMAND aplusb_tests.cpp
)