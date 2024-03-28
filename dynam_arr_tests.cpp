#include <gtest/gtest.h>

extern "C"
{
    #include "algo.h"
    #include "dynam_arr.h"    
}

///////////////////////////////////////////////////////////////////////////////

TEST(basic, init)
{
    dyn_arr_t *arr = init_da (3);
    ASSERT_EQ(0, arr->capacity);
    ASSERT_EQ(3, arr->size);
    ASSERT_EQ(3, arr->array->size);
    std::cout << "Test passed: + 0.2 point\n";
}

TEST(basic, basic_init)
{
    dyn_arr_t *arr = basic_init_da ();
    ASSERT_NE(0, arr->size);
    ASSERT_EQ(0, arr->capacity);
    ASSERT_EQ(arr->size, arr->array->size);
    std::cout << "Test passed: + 0.2 point\n";
}

TEST(basic, get)
{
    dyn_arr_t *arr = init_da (3);
    output_t out = get_da (arr, 1);
    ASSERT_EQ(0, out.code);
    ASSERT_EQ(0, *(out.value));

    TYPE correct;

    #if INTEGER
        correct = 21;      
    #elif STR
        correct = "fikus";
    #endif

    arr->array->head[1] = correct;
    out = get_da (arr, 1);
    ASSERT_EQ(correct, *(out.value));
    ASSERT_EQ(0, out.code);
    std::cout << "Test passed: + 0.2 point\n";
}

TEST(basic, set)
{
    dyn_arr_t *arr = init_da (3);

    ASSERT_EQ(0, arr->array->head[1]);

    TYPE correct;

    #if INTEGER
        correct = 21;      
    #elif STR
        correct = "fikus";
    #endif

    set_da (arr, 1, &correct);
    ASSERT_EQ(correct, arr->array->head[1]);
    std::cout << "Test passed: + 0.2 point\n";
}

TEST(basic, size)
{
    dyn_arr_t *arr = init_da (3);
    ASSERT_EQ(3, size_da (arr));
    std::cout << "Test passed: + 0.2 point\n";
}

TEST(basic, is_empty)
{
    dyn_arr_t *arr = init_da (3);
    ASSERT_EQ(0, is_empty_da (arr));

    arr = init_da (0);
    ASSERT_NE(0, is_empty_da (arr));

    arr = basic_init_da ();
    ASSERT_NE(0, is_empty_da (arr));
    std::cout << "Test passed: + 0.2 point\n";
}

TEST(basic, pop_back)
{
    dyn_arr_t *arr = init_da (4);

    TYPE correct3;

    #if INTEGER
        correct3 = 21;      
    #elif STR
        correct3 = "fikus";
    #endif

    TYPE correct2;

    #if INTEGER
        correct2 = 42;      
    #elif STR
        correct2 = "magnolia";
    #endif

    TYPE correct1;

    #if INTEGER
        correct1 = 11;      
    #elif STR
        correct1 = "dodo";
    #endif

    TYPE correct0;
    
    #if INTEGER
        correct0 = 0;      
    #elif STR
        correct0 = "";
    #endif

    arr->array->head[3] = correct3;
    arr->array->head[2] = correct2;
    arr->array->head[1] = correct1;
    arr->array->head[0] = correct0;

    output_t out;

    out = pop_back_da (arr);
    ASSERT_EQ(correct3, *(out.value));
    ASSERT_EQ(0, out.code);
    ASSERT_EQ(3, arr->size);
    ASSERT_EQ(4, arr->capacity);

    out = pop_back_da (arr);
    ASSERT_EQ(correct2, *(out.value));
    ASSERT_EQ(0, out.code);
    ASSERT_EQ(2, arr->size);
    ASSERT_EQ(4, arr->capacity);

    out = pop_back_da (arr);
    ASSERT_EQ(correct1, *(out.value));
    ASSERT_EQ(0, out.code);
    ASSERT_EQ(1, arr->size);
    ASSERT_EQ(4, arr->capacity);

    out = pop_back_da (arr);
    ASSERT_EQ(correct0, *(out.value));
    ASSERT_EQ(0, out.code);
    ASSERT_EQ(0, arr->size);
    ASSERT_EQ(2, arr->capacity);
    std::cout << "Test passed: + 0.2 point\n";
}

TEST(basic, push_back)
{
    dyn_arr_t *arr = init_da (2);

    TYPE correct1;

    #if INTEGER
        correct1 = 21;      
    #elif STR
        correct1 = "fikus";
    #endif

    TYPE correct2;

    #if INTEGER
        correct2 = 42;      
    #elif STR
        correct2 = "magnolia";
    #endif

    push_back_da (arr, &correct1);
    ASSERT_EQ(correct1, arr->array->head[2]);
    ASSERT_EQ(3, arr->size);
    ASSERT_EQ(4, arr->capacity);

    push_back_da (arr, &correct2);
    ASSERT_EQ(correct2, arr->array->head[3]);
    ASSERT_EQ(4, arr->size);
    ASSERT_EQ(4, arr->capacity);
    std::cout << "Test passed: + 0.2 point\n";
}

///////////////////////////////////////////////////////////////////////////////

#if INTEGER
TEST(stress, stress)
{
    output_t out;
    dyn_arr_t *arr = init_da (111);
    for (int i = 0; i < 420'000; ++i) {
        out = get_da (arr, i % 111);

        ASSERT_EQ(0, out.code);

        TYPE prev = *(out.value);
        TYPE arg = prev + 1;
        out = set_da (arr, i % 111, &arg);
        ASSERT_EQ(prev, i / 111);
        ASSERT_EQ(0, out.code);
    }
    std::cout << "Test passed: + 0.7 point\n";
}

TEST(fuzz, fuzz)
{
    output_t out;
    TYPE arg = 0;
    dyn_arr_t *arr = init_da (4'200'000);
    std::srand(std::time(nullptr));

    for (int i = 0; i < 4'200'000; ++i) {
        out = get_da (arr, i);

        ASSERT_EQ(0, out.code);
        ASSERT_EQ(0, *(out.value));

        if (i != 0) {
            out = get_da (arr, i - 1);

            ASSERT_EQ(0, out.code);
            ASSERT_EQ(arg, *(out.value));
        }

        arg = (1 + std::rand()) % 10'000'000;
        out = set_da (arr, i, &arg);
        ASSERT_EQ(0, out.code);
    }
    std::cout << "Test passed: + 1.0 point\n";
}
#endif

///////////////////////////////////////////////////////////////////////////////
