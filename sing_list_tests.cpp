#include "gtest/gtest.h"
#include <vector>

extern "C"
{
    #include "algo.h"
    #include "sing_list.h"    
}

///////////////////////////////////////////////////////////////////////////////

TEST(basic, init)
{
    list_t *list = init_sll();
    ASSERT_EQ(list->head, (node_t *)NULL);
    ASSERT_EQ(list->tail, (node_t *)NULL);
    ASSERT_EQ(list->size, 0);

    std::cout << "Test passed: + 0.3 point\n";
}

///////////////////////////////////////////////////////////////////////////////

TEST(insert, single)
{
    list_t *list = init_sll();

    TYPE val;

    #if INTEGER
        val = 3;
    #elif STRING
        val = "magnolia";
    #endif

    int res = insert_sll (list, 0, &val);
    ASSERT_EQ(0, res);

    ASSERT_EQ(list->size, 1);

    ASSERT_EQ(list->head->value, &val);
    ASSERT_EQ(list->tail->value, &val);

    ASSERT_EQ(list->head->next, (node_t *)NULL);
    ASSERT_EQ(list->head->prev, (node_t *)NULL);

    ASSERT_EQ(list->tail->next, (node_t *)NULL);
    ASSERT_EQ(list->tail->prev, (node_t *)NULL);

    std::cout << "Test passed: + 0.3 point\n";
}

TEST(insert, double)
{
    TYPE fst;
    TYPE snd;

    #if INTEGER
        fst = 3;
        snd = 2;
    #elif STRING
        fst = "magnolia";
        snd = "tulip";
    #endif

    list_t *list = init_sll();
    int res = insert_sll (list, 0, &fst);

    ASSERT_EQ(0, res);

    res = insert_sll (list, 0, &snd);

    ASSERT_EQ(0, res);

    ASSERT_EQ(list->size, 2);

    ASSERT_EQ(list->head->value, &snd);
    ASSERT_EQ(list->head->next->value, &fst);

    ASSERT_EQ(list->tail->value, &fst);
    ASSERT_EQ(list->tail->prev->value, &snd);

    ASSERT_EQ(list->head->next->next, (node_t *)NULL);
    ASSERT_EQ(list->head->prev, (node_t *)NULL);

    ASSERT_EQ(list->tail->next, (node_t *)NULL);
    ASSERT_EQ(list->tail->prev->prev, (node_t *)NULL);

    ASSERT_EQ(list->head->next, list->tail);
    ASSERT_EQ(list->tail->prev, list->head);

    std::cout << "Test passed: + 0.3 point\n";
}

TEST(insert, triple)
{
    TYPE fst;
    TYPE snd;
    TYPE trd;

    #if INTEGER
        fst = 3;
        snd = 2;
        trd = 1;
    #elif STRING
        fst = "magnolia";
        snd = "tulip";
        trd = "dundelion";
    #endif

    list_t *list = init_sll();
    int res = insert_sll (list, 0, &fst);
    ASSERT_EQ(0, res);
    res = insert_sll (list, 1, &snd);
    ASSERT_EQ(0, res);
    res = insert_sll (list, 2, &trd);
    ASSERT_EQ(0, res);

    ASSERT_EQ(list->size, 3);

    ASSERT_EQ(list->head->value, &fst);
    ASSERT_EQ(list->head->next->value, &snd);
    ASSERT_EQ(list->head->next->next->value, &trd);

    ASSERT_EQ(list->tail->value, &trd);
    ASSERT_EQ(list->tail->prev->value, &snd);
    ASSERT_EQ(list->tail->prev->prev->value, &fst);

    ASSERT_EQ(list->head->next->next->next, (node_t *)NULL);
    ASSERT_EQ(list->head->prev, (node_t *)NULL);

    ASSERT_EQ(list->tail->next, (node_t *)NULL);
    ASSERT_EQ(list->tail->prev->prev->prev, (node_t *)NULL);

    ASSERT_EQ(list->head->next, list->tail->prev);

    std::cout << "Test passed: + 0.4 point\n";
}

///////////////////////////////////////////////////////////////////////////////

TEST(basic, get)
{
    TYPE fst;
    TYPE snd;
    TYPE trd;

    #if INTEGER
        fst = 3;
        snd = 2;
        trd = 1;
    #elif STRING
        fst = "magnolia";
        snd = "tulip";
        trd = "dundelion";
    #endif

    list_t *list = init_sll();
    int res = insert_sll (list, 0, &fst);
    ASSERT_EQ(0, res);
    res = insert_sll (list, 1, &snd);
    ASSERT_EQ(0, res);
    res = insert_sll (list, 2, &trd);
    ASSERT_EQ(0, res);

    output_t out;

    out = get_sll (list, 0);
    ASSERT_EQ(0, out.code);
    ASSERT_EQ(&fst, out.value);

    out = get_sll (list, 1);
    ASSERT_EQ(0, out.code);
    ASSERT_EQ(&snd, out.value);

    out = get_sll (list, 2);
    ASSERT_EQ(0, out.code);
    ASSERT_EQ(&trd, out.value);

    out = get_sll (list, 3);
    ASSERT_EQ(1, out.code);

    std::cout << "Test passed: + 0.3 point\n";
}

TEST(basic, set)
{
    TYPE fst;
    TYPE snd;
    TYPE trd;
    TYPE frh;
    TYPE ffh;
    TYPE sxh;

    #if INTEGER
        fst = 3;
        snd = 2;
        trd = 1;

        frh = 4;
        ffh = 5;
        sxh = 6;
    #elif STRING
        fst = "magnolia";
        snd = "tulip";
        trd = "dundelion";

        frh = "lily";
        ffh = "daisy";
        sxh = "rose";
    #endif

    list_t *list = init_sll();
    int res = insert_sll (list, 0, &fst);
    ASSERT_EQ(0, res);
    res = insert_sll (list, 1, &snd);
    ASSERT_EQ(0, res);
    res = insert_sll (list, 2, &trd);
    ASSERT_EQ(0, res);

    ASSERT_EQ(0, set_sll (list, 0, &frh));
    ASSERT_EQ(0, set_sll (list, 1, &ffh));
    ASSERT_EQ(0, set_sll (list, 2, &sxh));
    ASSERT_EQ(1, set_sll (list, 3, &sxh));

    output_t out;

    out = get_sll (list, 0);
    ASSERT_EQ(0, out.code);
    ASSERT_EQ(&frh, out.value);

    out = get_sll (list, 1);
    ASSERT_EQ(0, out.code);
    ASSERT_EQ(&ffh, out.value);

    out = get_sll (list, 2);
    ASSERT_EQ(0, out.code);
    ASSERT_EQ(&sxh, out.value);
    
    std::cout << "Test passed: + 0.3 point\n";
}

TEST(basic, size)
{
    list_t *list = init_sll();
    list->size = 121;

    ASSERT_EQ(121, size_sll (list));
    
    std::cout << "Test passed: + 0.3 point\n";
}

///////////////////////////////////////////////////////////////////////////////

TEST(delete, single)
{
    TYPE val;

    #if INTEGER
        val = 3;
    #elif STRING
        val = "magnolia";
    #endif

    list_t *list = init_sll();
    insert_sll (list, 0, &val);

    delete_sll (list, 0);

    ASSERT_EQ(NULL, list->head);
    ASSERT_EQ(NULL, list->tail);
    ASSERT_EQ(0, list->size);

    std::cout << "Test passed: + 0.3 point\n";
}

TEST(delete, double)
{
    TYPE fst;
    TYPE snd;

    #if INTEGER
        fst = 3;
        snd = 2;
    #elif STRING
        fst = "magnolia";
        snd = "tulip";
    #endif

    list_t *list = init_sll();
    insert_sll (list, 0, &fst);
    insert_sll (list, 0, &snd);

    delete_sll (list, 0);

    ASSERT_EQ(list->size, 1);

    ASSERT_EQ(list->head->value, &fst);
    ASSERT_EQ(list->tail->value, &fst);

    ASSERT_EQ(list->head->next, (node_t *)NULL);
    ASSERT_EQ(list->head->prev, (node_t *)NULL);

    ASSERT_EQ(list->tail->next, (node_t *)NULL);
    ASSERT_EQ(list->tail->prev, (node_t *)NULL);

    ASSERT_EQ(list->head, list->tail);

    std::cout << "Test passed: + 0.3 point\n";
}

TEST(delete, triple)
{
    TYPE fst;
    TYPE snd;
    TYPE trd;

    #if INTEGER
        fst = 3;
        snd = 2;
        trd = 1;
    #elif STRING
        fst = "magnolia";
        snd = "tulip";
        trd = "dundelion";
    #endif

    list_t *list = init_sll();
    insert_sll (list, 0, &fst);
    insert_sll (list, 1, &snd);
    insert_sll (list, 2, &trd);

    delete_sll (list, 2);

    ASSERT_EQ(list->size, 2);

    ASSERT_EQ(list->head->value, &fst);
    ASSERT_EQ(list->tail->value, &snd);

    ASSERT_EQ(list->head->next->value, &snd);
    ASSERT_EQ(list->tail->prev->value, &fst);

    ASSERT_EQ(list->head->prev, (node_t *)NULL);
    ASSERT_EQ(list->tail->next, (node_t *)NULL);

    ASSERT_EQ(list->head->next, list->tail);
    ASSERT_EQ(list->head, list->tail->prev);

    std::cout << "Test passed: + 0.4 point\n";
}

///////////////////////////////////////////////////////////////////////////////

#if INTEGER
TEST(stress, insert)
{
    list_t *list = init_sll();
    node_t *prev;
    int val = 1;

    for (int i = 0; i < 4'200'000; ++i) {
        prev = list->head;

        insert_sll (list, 0, &val);

        ASSERT_EQ(&val, list->head->value);
        ASSERT_EQ(prev, list->head->next);
        ASSERT_EQ(list->head->prev, (node_t *)NULL);
        val++;
    }

    std::cout << "Test passed: + 1.0 point\n";
}

TEST(fuzz, fuzz)
{
    list_t *list = init_sll();
    node_t *prev;
    int val;
    output_t out;
    std::vector<int *> data;

    std::srand(std::time(nullptr));

    for (int i = 0; i < 4'200'000; ++i) {
        prev = list->head;

        val = (1 + std::rand()) % 10'000'000;
        data.push_back(&val);

        ASSERT_EQ(0, insert_sll (list, 0, &val));
        out = get_sll (list, 0);

        ASSERT_EQ(0, out.code);
        ASSERT_EQ(&val, out.value);
    }

    for (int i = 0; i < 4'200'000; ++i) {
        out = delete_sll(list, 0);

        ASSERT_EQ(0, out.code);
        ASSERT_EQ(data.back(), out.value);
        data.pop_back();
    }

    std::cout << "Test passed: + 1.0 point\n";
}
#endif

///////////////////////////////////////////////////////////////////////////////
