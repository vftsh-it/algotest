#include <gtest/gtest.h>

extern "C"
{
    #include "algo.h"
    #include "stat_arr.h"
}

///////////////////////////////////////////////////////////////////////////////

TEST(allocation, all_available)
{
    stat_arr_t *arr = init_sa (3);
    ASSERT_EQ(0, arr->head[0]);
    ASSERT_EQ(0, arr->head[1]);
    ASSERT_EQ(0, arr->head[2]);
    std::cout << "Test passed: + 0.2 point\n";
}

///////////////////////////////////////////////////////////////////////////////

TEST(basic, get)
{
    stat_arr_t *arr = init_sa (3);
    output_t out = get_sa (arr, 1);
    ASSERT_EQ(0, out.code);
    ASSERT_EQ(0, *(out.value));

    TYPE correct;

    #if INTEGER
        correct = 21;      
    #elif STR
        correct = "fikus";
    #endif

    arr->head[1] = correct;

    out = get_sa (arr, 1);

    ASSERT_EQ(correct, *(out.value));
    ASSERT_EQ(0, out.code);
    std::cout << "Test passed: + 0.3 point\n";
}

TEST(basic, set)
{
    stat_arr_t *arr = init_sa (3);
    ASSERT_EQ(0, arr->head[1]);

    TYPE correct;

    #if INTEGER
        correct = 42;      
    #elif STR
        correct = "fikus";
    #endif

    output_t out = set_sa (arr, 1, &correct);

    ASSERT_EQ(0, out.code);
    ASSERT_EQ(correct, arr->head[1]);
    std::cout << "Test passed: + 0.3 point\n";
}

TEST(basic, size)
{
    stat_arr_t *arr = init_sa (3);
    ASSERT_EQ(3, size_sa (arr));
    std::cout << "Test passed: + 0.2 point\n";
}

///////////////////////////////////////////////////////////////////////////////

TEST(over_bounds, get)
{
    stat_arr_t *arr = init_sa (3);
    output_t out = get_sa (arr, 4);
    ASSERT_EQ(1, out.code);
    std::cout << "Test passed: + 0.3 point\n";
}

TEST(over_bounds, set)
{
    stat_arr_t *arr = init_sa (3);

    TYPE val;

    #if INTEGER
        val = 42;
    #elif STR
        val = "fikus";
    #endif

    output_t out = set_sa (arr, 4, &val);
    ASSERT_EQ(1, out.code);
    std::cout << "Test passed: + 0.3 point\n";
}

///////////////////////////////////////////////////////////////////////////////


#if INTEGER
TEST(stress, stress)
{
    output_t out;
    stat_arr_t *arr = init_sa (111);
    for (int i = 0; i < 420'000; ++i) {
        out = get_sa (arr, i % 111);

        ASSERT_EQ(0, out.code);

        TYPE prev = *(out.value);
        TYPE arg = prev + 1;
        out = set_sa (arr, i % 111, &arg);
        ASSERT_EQ(prev, i / 111);
        ASSERT_EQ(0, out.code);
    }
    std::cout << "Test passed: + 0.3 point\n";
}

TEST(fuzz, fuzz)
{
    output_t out;
    TYPE arg = 0;
    stat_arr_t *arr = init_sa (420'000);
    std::srand(std::time(nullptr));

    for (int i = 0; i < 420'000; ++i) {
        out = get_sa (arr, i);

        ASSERT_EQ(0, out.code);
        ASSERT_EQ(0, *(out.value));

        if (i != 0) {
            out = get_sa (arr, i - 1);

            ASSERT_EQ(0, out.code);
            ASSERT_EQ(arg, *(out.value));
        }

        arg = (1 + std::rand()) % 10'000'000;
        out = set_sa (arr, i, &arg);
        ASSERT_EQ(0, out.code);
    }
    std::cout << "Test passed: + 0.4 point\n";
}
#endif
