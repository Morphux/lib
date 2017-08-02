#include "test.h"

int		list_str_free(void *member) {
	char		*str = member;
	if (str != NULL)
		free(str);
	return 1;
}

TEST(list_add_null) {
	mlist_t	*ptr = NULL;
	void	*null = NULL;

	list_add(ptr, null, 0);
	TEST_ASSERT((ptr == NULL), "Returned pointer is not null.");
	return TEST_SUCCESS;
}

TEST(list_add_member) {
	mlist_t	*ptr = NULL;
	char	test[] = "Hello !\n";

	list_add(ptr, test, sizeof(test));
	TEST_ASSERT(!strcmp(ptr->member, "Hello !\n"), "Member have an unexpected value.");
	TEST_ASSERT((ptr->size == sizeof(test)), "Size is wrong");
	list_free(ptr, NULL);
	return TEST_SUCCESS;
}

TEST(list_add_member_head_list) {
	mlist_t	*ptr = NULL;
	char	test[] = "Hello !\n";
	char	test2[] = "Hello2 !\n";

	list_add(ptr, test, sizeof(test));
	list_add(ptr, test2, sizeof(test2));
	TEST_ASSERT(!strcmp(ptr->member, "Hello !\n"), "Head of the list is a wrong pointer.");
	TEST_ASSERT(!ptr->prev, "Head of the list prev pointer is not null");
	list_free(ptr, NULL);
	return TEST_SUCCESS;
}

TEST(list_add_member_test_multiples) {
	mlist_t	*ptr = NULL;
	char	test[] = "Hello !\n";
	char	test2[] = "Hello2 !\n";

	list_add(ptr, test, sizeof(test));
	list_add(ptr, test2, sizeof(test2));
	TEST_ASSERT(!strcmp(ptr->next->member, "Hello2 !\n"), "Member have an unexpected value.");
	TEST_ASSERT(!strcmp(ptr->next->prev->member, "Hello !\n"), "Member have an unexpected value.");
	TEST_ASSERT((ptr->next->head == ptr), "Head pointer is not right");
	list_free(ptr, NULL);
	return TEST_SUCCESS;
}

TEST(list_for_each) {
	mlist_t	*ptr = NULL, *tmp;
	char	test[] = "Hello !\n";
	char	test2[] = "Hello2 !\n";
	char	test3[] = "Hello3 !\n";
	char	*s_tmp;
	size_t	i = 0;

	list_add(ptr, test, sizeof(test));
	list_add(ptr, test2, sizeof(test2));
	list_add(ptr, test3, sizeof(test3));
	list_for_each(ptr, tmp, s_tmp) {
		switch (i) {
			case 0: TEST_ASSERT(s_tmp, "Hello !\n"); break;
			case 1: TEST_ASSERT(s_tmp, "Hello2 !\n"); break;
			case 2: TEST_ASSERT(s_tmp, "Hello3 !\n"); break;
			case 3: TEST_ASSERT(0, "list_for_each too many iterations.");
		}
	}
	list_free(ptr, NULL);
	return TEST_SUCCESS;
}

TEST(list_tail) {
	mlist_t	*ptr = NULL, *tmp;
	char	test[] = "Hello !\n";
	char	test2[] = "Hello2 !\n";
	char	test3[] = "Hello3 !\n";

	tmp = list_tail(ptr);
	TEST_ASSERT(!tmp, "Pointer is not null.");
	list_add(ptr, test, sizeof(test));
	list_add(ptr, test2, sizeof(test2));
	list_add(ptr, test3, sizeof(test3));
	tmp = list_tail(ptr);
	TEST_ASSERT(!strcmp(tmp->member, "Hello3 !\n"), "Tail is wrong.");
	list_free(ptr, NULL);
	return TEST_SUCCESS;
}

TEST(list_add_after) {
	mlist_t	*ptr = NULL, *tmp;
	char	test[] = "Hello !\n";
	char	test2[] = "Hello2 !\n";
	char	test3[] = "Hello3 !\n";
	char	test4[] = "Hello2.5 !\n";
	char	test5[] = "Hello4 !\n";

	list_add(ptr, test, sizeof(test));
	list_add(ptr, test2, sizeof(test2));
	list_add(ptr, test3, sizeof(test3));
	list_add_after(ptr, ptr->next, test4, sizeof(test4));
	TEST_ASSERT(!strcmp(ptr->member, "Hello !\n"), "Head is wrong.");
	TEST_ASSERT(!strcmp(ptr->next->member, "Hello2 !\n"), "Order is wrong.");
	TEST_ASSERT(!strcmp(ptr->next->next->member, "Hello2.5 !\n"), "Order is wrong.");
	TEST_ASSERT(!strcmp(ptr->next->next->next->member, "Hello3 !\n"), "Order is wrong.");
	tmp = list_tail(ptr);
	list_add_after(ptr, tmp, test5, sizeof(test5));
	tmp = list_tail(ptr);
	TEST_ASSERT(!strcmp(tmp->member, "Hello4 !\n"), "Order is wrong.");
	TEST_ASSERT(!tmp->next, "Next pointer is wrong.");
	list_free(ptr, NULL);
	ptr = NULL;
	list_add_after(ptr, NULL, test, sizeof(test));
	TEST_ASSERT(!strcmp(ptr->member, "Hello !\n"), "Head is wrong.");
	list_free(ptr, NULL);
	return TEST_SUCCESS;
}

TEST(list_add_before) {
	mlist_t	*ptr = NULL, *tmp;
	char	test[] = "Hello !\n";
	char	test2[] = "Hello2 !\n";
	char	test3[] = "Hello3 !\n";
	char	test4[] = "Hello2.5 !\n";
	char	test5[] = "Hello4 !\n";

	list_add(ptr, test, sizeof(test));
	list_add(ptr, test2, sizeof(test2));
	list_add(ptr, test3, sizeof(test3));
	list_add_before(ptr, ptr->next, test4, sizeof(test4));
	TEST_ASSERT(!strcmp(ptr->member, "Hello !\n"), "Head is wrong.");
	TEST_ASSERT(!strcmp(ptr->next->member, "Hello2.5 !\n"), "Order is wrong.");
	TEST_ASSERT(!strcmp(ptr->next->next->member, "Hello2 !\n"), "Order is wrong.");
	TEST_ASSERT(!strcmp(ptr->next->next->next->member, "Hello3 !\n"), "Order is wrong.");
	list_add_before(ptr, ptr, test5, sizeof(test5));
	tmp = ptr->head;
	TEST_ASSERT(!strcmp(tmp->member, "Hello4 !\n"), "Order is wrong.");
	TEST_ASSERT(!tmp->prev, "Next pointer is wrong.");
	list_free(ptr, NULL);
        ptr = NULL;

        list_add_before(ptr, NULL, test, sizeof(test));
        list_add_before(ptr, ptr, test2, sizeof(test2));
        list_add_before(ptr, ptr, test2, sizeof(test2));
	list_free(ptr, NULL);
	return TEST_SUCCESS;
}

TEST(list_for_each_rev) {
	mlist_t	*ptr = NULL, *tmp;
	char	test[] = "Hello !\n";
	char	test2[] = "Hello2 !\n";
	char	test3[] = "Hello3 !\n";
	char	*s_tmp;
	size_t	i = 0;

	list_add(ptr, test, sizeof(test));
	list_add(ptr, test2, sizeof(test2));
	list_add(ptr, test3, sizeof(test3));
	list_for_each_rev(ptr, tmp, s_tmp) {
		switch (i) {
			case 0: TEST_ASSERT(s_tmp, "Hello3 !\n"); break;
			case 1: TEST_ASSERT(s_tmp, "Hello2 !\n"); break;
			case 2: TEST_ASSERT(s_tmp, "Hello !\n"); break;
			case 3: TEST_ASSERT(0, "list_for_each too many iterations.");
		}
	}
	list_free(ptr, NULL);
	return TEST_SUCCESS;
}

TEST(list_size) {
	mlist_t	*ptr = NULL;
	char	test[] = "Hello !\n";
	char	test2[] = "Hello2 !\n";
	char	test3[] = "Hello3 !\n";

	list_add(ptr, test, sizeof(test));
	list_add(ptr, test2, sizeof(test2));
	list_add(ptr, test3, sizeof(test3));
	TEST_ASSERT((list_size(ptr) == 3), "Size is wrong.");
	list_free(ptr, NULL);
	ptr = NULL;
	TEST_ASSERT(list_size(ptr) == 0, "Size is wrong.");
	return TEST_SUCCESS;
}

int		callback_list_free(void *ptr) {
	static bool		passed = false;

	(void)ptr;
	if (!passed) {
		passed = true;
		return 0;
	}
	return 1;
}

TEST(list_free) {
	mlist_t		*ptr = NULL;
	char		test[] = "Toto";

	list_add(ptr, test, sizeof(test));
	list_add(ptr, test, sizeof(test));
	list_add(ptr, test, sizeof(test));
	list_add(ptr, test, sizeof(test));
	list_add(ptr, test, sizeof(test));
	list_free(ptr, &callback_list_free);
	list_free(ptr, &callback_list_free);
	return TEST_SUCCESS;
}

int		callback_list_free_2(void *ptr) {
	free(ptr);
	return 1;
}

TEST(list_remove) {
	mlist_t	*ptr = NULL;
	char	test[] = "Hello !\n";
	char	test2[] = "Hello2 !\n";
	char	test3[] = "Hello3 !\n";
	char	test4[] = "Hello4 !\n";

	list_add(ptr, test, sizeof(test));
	list_add(ptr, test2, sizeof(test2));
	list_add(ptr, test3, sizeof(test3));

	list_del(ptr, test2, sizeof(test2), NULL);
	TEST_ASSERT(strcmp(ptr->next->member, test3) == 0, "List order is wrong");
	list_add(ptr, test3, sizeof(test3));

	list_del(ptr, test, sizeof(test), &callback_list_free_2);
	TEST_ASSERT(strcmp(ptr->member, test3) == 0, "List order is wrong");
	
	list_del(ptr, test4, sizeof(test4), NULL);
	TEST_ASSERT(strcmp(ptr->member, test3) == 0, "List order is wrong");

	list_free(ptr, NULL);
	ptr = NULL;
	list_del(ptr, test, sizeof(test), NULL);
	return TEST_SUCCESS;
}

TEST(vector_string_init) {
    const char  *s1 = "Hello";
    const char  *s2 = "World !\n";
    vector_string_t     *tmp = NULL;

    set_malloc_fail(0);
    TEST_ASSERT(vector_string_init(s1, s2) == NULL, "Malloc failed did not raise an error");

    set_strdup_fail(0);
    TEST_ASSERT(vector_string_init(s1, s2) == NULL, "strdup failed did not raise an error");

    set_strdup_fail(1);
    TEST_ASSERT(vector_string_init(s1, s2) == NULL, "strdup failed did not raise an error");


    tmp = vector_string_init(s1, s2);
    TEST_ASSERT(tmp != NULL, "An error hapenned");
    TEST_ASSERT(strcmp(tmp->str1, s1) == 0, "Strings are not the same");
    TEST_ASSERT(strcmp(tmp->str2, s2) == 0, "Strings are not the same");
    vector_string_free(tmp);
    free(tmp);

    return TEST_SUCCESS;
}

void	register_list_tests(void) {
	reg_test("mlist", list_add_null);
	reg_test("mlist", list_add_member);
	reg_test("mlist", list_add_member_head_list);
	reg_test("mlist", list_add_member_test_multiples);
	reg_test("mlist", list_for_each);
	reg_test("mlist", list_tail);
	reg_test("mlist", list_add_after);
	reg_test("mlist", list_add_before);
	reg_test("mlist", list_for_each_rev);
	reg_test("mlist", list_size);
	reg_test("mlist", list_free);
	reg_test("mlist", list_remove);
        reg_test("mlist", vector_string_init);
}
