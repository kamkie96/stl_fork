#include <doubly_linked_list.h>
#include <ctest.h>
#include <assert.h>

static int compare_ints(const void *a, const void *b)
{
    assert(a && b);
    const int* ia = (const int*)a;
    const int* ib = (const int*)b;
    if (*ia > *ib) return 1;
    if (*ia == *ib) return 0;
    return -1;
}

static void test_init_and_clear_function(void)
{
    doubly_linked_list_t *dll = init(sizeof(int), compare_ints);
    assert(dll);
    assert(dll->__head__ == NULL && dll->__tail__ == NULL);
    assert(dll->__compare__ == compare_ints);

    size_t size = 0;

    EQUALS_SIZE_T(dll->__element_size__, sizeof(int));
    EQUALS_SIZE_T(dll->__size__, size);
    clear(dll);
}

static void test_insert_function(void)
{
    doubly_linked_list_t *dll = init(sizeof(int), compare_ints);
    assert(dll);

    int example_value[] = { 11, 22, 33, 44, 55,
                            66, 77, 88, 99, 101 };

    for (size_t i = 0; i < 10; ++i)
    {
        insert(dll, &example_value[i]);
        EQUALS_SIZE_T(dll->__size__, i + 1);
    }

    clear(dll);
}

static void test_get_function(void)
{
    doubly_linked_list_t *dll = init(sizeof(int), compare_ints);
    assert(dll);

    int first_value = 127;
    int second_value = 13;
    int third_value = 399;

    int get_value = 0;

    insert(dll, &first_value);
    insert(dll, &second_value);
    insert(dll, &third_value);

    get(dll, &get_value, 2);
    EQUALS_INT(get_value, third_value);
    get(dll, &get_value, 1);
    EQUALS_INT(get_value, first_value);
    get(dll, &get_value, 0);
    EQUALS_INT(get_value, second_value);

    clear(dll);
}

static void test_erase_function(void)
{
    doubly_linked_list_t *dll = init(sizeof(int), compare_ints);
    assert(dll);

    int example_value[] = { 1, 2, 3, 4, 5 };

    for (size_t i = 0; i < 5; ++i)
    {
        insert(dll, &example_value[i]);
    }

    size_t size_of_list = 0;

    erase(dll, NULL, 4);
    size_of_list = 4;
    EQUALS_SIZE_T(size(dll), size_of_list);

    erase(dll, NULL, 0);
    size_of_list = 3;
    EQUALS_SIZE_T(size(dll), size_of_list);

    erase(dll, NULL, 1);
    size_of_list = 2;
    EQUALS_SIZE_T(size(dll), size_of_list);

    erase(dll, NULL, 1);
    size_of_list = 1;
    EQUALS_SIZE_T(size(dll), size_of_list);

    erase(dll, NULL, 0);
    size_of_list = 0;
    EQUALS_SIZE_T(size(dll), size_of_list);

    clear(dll);
}

static void test_search_function(void)
{
    doubly_linked_list_t *dll = init(sizeof(int), compare_ints);
    assert(dll);

    int example_value[] = { 11, 17, 29, 37, 101 };

    for (size_t i = 0; i < 5; ++i)
    {
        insert(dll, &example_value[i]);
    }

    for (size_t i = 0; i < 5; ++i)
    {
        EQUALS_INT(search(dll, &example_value[i]), 0);
    }

    clear(dll);
}

static void test_size_function(void)
{
    doubly_linked_list_t *dll = init(sizeof(int), compare_ints);
    assert(dll);

    EQUALS_SIZE_T(size(dll), dll->__size__);

    int example_value = 0;

    for (size_t i = 0; i < 5; ++i)
    {
        insert(dll, &example_value);
        EQUALS_SIZE_T(size(dll), i + 1);
    }

    clear(dll);
}

int main(void)
{
    BEGIN();
    TEST(test_init_and_clear_function());
    TEST(test_insert_function());
    TEST(test_get_function());
    TEST(test_erase_function());
    TEST(test_search_function());
    TEST(test_size_function());
    SUMMARY();
    return 0;
}
