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

add_executable(dynam_arr_tests dynam_arr_tests.cpp)
target_link_libraries(dynam_arr_tests PRIVATE array dynamic_array static_array src gtest gtest_main)

add_test(
        NAME dynam_arr
        COMMAND $<TARGET_FILE:dynam_arr_tests>
)

add_executable(doub_list_tests doub_list_tests.cpp)
target_link_libraries(doub_list_tests PRIVATE list doub_list src gtest gtest_main)

add_test(
        NAME doub_list
        COMMAND $<TARGET_FILE:doub_list_tests>
)

add_executable(sing_list_tests sing_list_tests.cpp)
target_link_libraries(sing_list_tests PRIVATE list sing_list src gtest gtest_main)

add_test(
        NAME sing_list
        COMMAND $<TARGET_FILE:sing_list_tests>
)