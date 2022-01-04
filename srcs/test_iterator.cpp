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

void	test_enable_if(UnitTest *test)
{
	test->ASSERT_EQUAL(false, true);
}

void	test_lexicographical_compare(UnitTest *test)
{
	bool	ret;
	ft::vector<char> v1;
	v1.push_back('a');
	v1.push_back('b');
	v1.push_back('c');
	v1.push_back('d');
	ft::vector<char> v2(v1);
	ret = ft::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end());
	test->ASSERT_EQUAL(ret, false);
	v1.pop_back();
	ret = ft::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end());
	test->ASSERT_EQUAL(ret, true);
	v1.push_back('c');
	ret = ft::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end());
	test->ASSERT_EQUAL(ret, true);
}

void	test_pair(UnitTest *test)
{
	int n = 1;
	char c = 'a';
	int a[5] = {1, 2, 3, 4, 5};
	int & r = n;
	ft::pair<int, char>	p = ft::make_pair(n, c);
	test->ASSERT_EQUAL(p.first, 1);
	test->ASSERT_EQUAL(p.second, 'a');

	ft::pair<int*, int*>	p2 = ft::make_pair(&r, a);
	n = 7;
	test->ASSERT_EQUAL(p.first, 1);
	test->ASSERT_EQUAL(*p2.first, 7);
	test->ASSERT_EQUAL(*(p2.second + 2), 3);

	// Test comparisons
	ft::pair<int, char> p3 = p;
	p3.second = 'b';
	test->ASSERT_EQUAL(p == p3, false);
	test->ASSERT_EQUAL(p != p3, true);
	test->ASSERT_EQUAL(p < p3, true);
	test->ASSERT_EQUAL(p <= p3, true);
	test->ASSERT_EQUAL(p > p3, false);
	test->ASSERT_EQUAL(p >= p3, false);
	test->ASSERT_EQUAL(p3 < p, false);
	test->ASSERT_EQUAL(p3 <= p, false);
	test->ASSERT_EQUAL(p3 > p, true);
	test->ASSERT_EQUAL(p3 >= p, true);
	p3.second = 'a';
	test->ASSERT_EQUAL(p == p3, true);
	test->ASSERT_EQUAL(p != p3, false);
	test->ASSERT_EQUAL(p < p3, false);
	test->ASSERT_EQUAL(p <= p3, true);
	test->ASSERT_EQUAL(p > p3, false);
	test->ASSERT_EQUAL(p >= p3, true);
	test->ASSERT_EQUAL(p3 < p, false);
	test->ASSERT_EQUAL(p3 <= p, true);
	test->ASSERT_EQUAL(p3 > p, false);
	test->ASSERT_EQUAL(p3 >= p, true);
	p3.first = 0;
	test->ASSERT_EQUAL(p == p3, false);
	test->ASSERT_EQUAL(p != p3, true);
	test->ASSERT_EQUAL(p < p3, false);
	test->ASSERT_EQUAL(p <= p3, false);
	test->ASSERT_EQUAL(p > p3, true);
	test->ASSERT_EQUAL(p >= p3, true);
	test->ASSERT_EQUAL(p3 < p, true);
	test->ASSERT_EQUAL(p3 <= p, true);
	test->ASSERT_EQUAL(p3 > p, false);
	test->ASSERT_EQUAL(p3 >= p, false);

}

void	add_test_iterator_suite(UnitTest & ut_test)
{
	ADD_TEST(test_random_access_iterator_tag_int);
	ADD_TEST(test_random_access_iterator_tag_vector);
	ADD_TEST(test_reverse_iterator_vector);
	ADD_TEST(test_enable_if);
	ADD_TEST(test_lexicographical_compare);
	ADD_TEST(test_pair);
}
