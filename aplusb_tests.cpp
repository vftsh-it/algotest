#include <gtest/gtest.h>

extern "C"
{
#include "aplusb.h"
}

////////////////////////////////////////////////////////////////////////////

TEST(public_aplusb_basic, basic)
{
    a_t a = {1};
    b_t b = {1};

    ASSERT_EQ(plus_basic(&a, &b), 2);
}

TEST(public_aplusb_basic, stress)
{
    for (int i = 0; i <= 42'000; ++i) {
        for (int j = 0; j <= 42'000; ++j) {
            a_t a = {i};
            b_t b = {j};

            ASSERT_EQ(plus_basic(&a, &b), i + j);
        }
    }
    
}

TEST(public_aplusb_basic, fuzz)
{
    std::srand(std::time(nullptr));

    for (int i = 0; i < 1'000; ++i) {
        for (int j = 0; j < 1'000; ++j) {
            int fst = (1 + std::rand()) % 10'000'000;
            int snd = (1 + std::rand()) % 10'000'000;
            a_t a = {fst};
            b_t b = {snd};

            ASSERT_EQ(plus_basic(&a, &b), fst + snd);
        }
    }
    
}

////////////////////////////////////////////////////////////////////////////

TEST(public_aplusb_intermediate, basic)
{
    a_t a = {1};
    b_t b = {1};
    c_t c = {1};

    plus_intermediate(&a, &b, &c);

    ASSERT_EQ(c.val, 2);
}

TEST(public_aplusb_intermediate, stress)
{
    for (int i = 0; i <= 42'000; ++i) {
        for (int j = 0; j <= 42'000; ++j) {
            a_t a = {i};
            b_t b = {j};
            c_t c = {0};

            plus_intermediate(&a, &b, &c);

            ASSERT_EQ(c.val, i + j);
        }
    }
    
}

TEST(public_aplusb_intermediate, fuzz)
{
    std::srand(std::time(nullptr));

    for (int i = 0; i < 1'000; ++i) {
        for (int j = 0; j < 1'000; ++j) {
            int fst = (1 + std::rand()) % 10'000'000;
            int snd = (1 + std::rand()) % 10'000'000;
            a_t a = {fst};
            b_t b = {snd};
            c_t c = {0};

            plus_intermediate(&a, &b, &c);

            ASSERT_EQ(c.val, fst + snd);
        }
    }
    
}

////////////////////////////////////////////////////////////////////////////

TEST(public_aplusb_advanced, basic)
{
    a_t a = {1};
    b_t b = {1};
    c_t *c = plus_advanced(&a, &b);

    ASSERT_EQ(c->val, 2);
}

TEST(public_aplusb_advanced, stress)
{
    for (int i = 0; i <= 42'000; ++i) {
        for (int j = 0; j <= 42'000; ++j) {
            a_t a = {i};
            b_t b = {j};
            c_t *c = plus_advanced(&a, &b);

            ASSERT_EQ(c->val, i + j);   
        }
    }
    
}

TEST(public_aplusb_advanced, fuzz)
{
    std::srand(std::time(nullptr));

    for (int i = 0; i < 1'000; ++i) {
        for (int j = 0; j < 1'000; ++j) {
            int fst = (1 + std::rand()) % 10'000'000;
            int snd = (1 + std::rand()) % 10'000'000;
            a_t a = {fst};
            b_t b = {snd};
            c_t *c = plus_advanced(&a, &b);

            ASSERT_EQ(c->val, fst + snd);
        }
    }
    
}