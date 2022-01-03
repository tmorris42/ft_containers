#include "test_iterator.hpp"

void	test_random_access_iterator_tag_int(UnitTest *test)
{
		
	typedef ft::iterator_traits<int*> traits;
	if (typeid(traits::iterator_category) == typeid(ft::random_access_iterator_tag))
		test->ASSERT_EQUAL(true, true);
	else
		test->ASSERT_EQUAL(true, false);
}

void	test_random_access_iterator_tag_vector(UnitTest *test)
{
		
	typedef ft::iterator_traits<ft::vector<int>::iterator> traits;
	if (typeid(traits::iterator_category) == typeid(ft::random_access_iterator_tag))
		test->ASSERT_EQUAL(true, true);
	else
		test->ASSERT_EQUAL(true, false);
}

void	test_reverse_iterator_vector(UnitTest *test)
{
	ft::vector<int>	v;
	for (int x = 0; x < 10; ++x)
	{
		v.push_back(x);
	}

	ft::vector<int>::reverse_iterator	rit;
	ft::vector<int>::reverse_iterator	rite;
	rit = v.rbegin();
	rite = v.rend();
	int	expected = v.size() - 1;
	test->ASSERT_EQUAL(expected,9);
	test->ASSERT_EQUAL(*rit, 9);
	int i = 0;
	while (rit != rite)
	{
		test->ASSERT_EQUAL(*rit, expected); // Test iterator incrementation and access through operator*
		test->ASSERT_EQUAL(v.rbegin()[i], 9 - i); // Test random access through operator[]
		test->ASSERT_EQUAL(*(i + v.rbegin()), 9 - i); // Test operator+
		test->ASSERT_EQUAL(rit - v.rbegin(), i); // Test operator-
		++rit;
		--expected;
		++i;
	}
}

void	add_test_iterator_suite(UnitTest & ut_test)
{
	ADD_TEST(test_random_access_iterator_tag_int);
	ADD_TEST(test_random_access_iterator_tag_vector);
	ADD_TEST(test_reverse_iterator_vector);
}
