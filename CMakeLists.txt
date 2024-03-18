add_executable(aplusb_tests aplusb_tests.cpp)
target_link_libraries(aplusb_tests PRIVATE aplusb_i aplusb src gtest gtest_main)

add_test(
        NAME aplusb
        COMMAND $<TARGET_FILE:aplusb_tests>
)

add_executable(stat_arr_tests stat_arr_tests.cpp)
target_link_libraries(stat_arr_tests PRIVATE array static_array src gtest gtest_main)

add_test(
        NAME stat_arr
        COMMAND $<TARGET_FILE:stat_arr_tests>
)