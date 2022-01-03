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

void	add_test_iterator_suite(UnitTest & ut_test)
{
	ADD_TEST(test_random_access_iterator_tag_int);
	ADD_TEST(test_random_access_iterator_tag_vector);
}
