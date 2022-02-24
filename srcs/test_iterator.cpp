#include "tests.hpp"

int test_random_access_iterator_tag_int()
{

	typedef FT::iterator_traits<int *> traits;
	if (typeid(traits::iterator_category) == typeid(FT::random_access_iterator_tag))
		ASSERT_EQUAL(true, true);
	else
		ASSERT_EQUAL(true, false);
	return (0);
}

int test_random_access_iterator_tag_vector()
{

	typedef FT::iterator_traits<FT::vector<int>::iterator> traits;
	if (typeid(traits::iterator_category) == typeid(FT::random_access_iterator_tag))
		ASSERT_EQUAL(true, true);
	else
		ASSERT_EQUAL(true, false);
	return (0);
}

int test_bidirectional_iterator_tag_map()
{

	typedef FT::iterator_traits<FT::map<int, int>::iterator> traits;
	if (typeid(traits::iterator_category) == typeid(FT::bidirectional_iterator_tag))
		ASSERT_EQUAL(true, true);
	else
		ASSERT_EQUAL(true, false);
	return (0);
}

int test_reverse_iterator_vector()
{
	FT::vector<int> v;
	for (int x = 0; x < 10; ++x)
	{
		v.push_back(x);
	}

	FT::vector<int>::reverse_iterator rit;
	FT::vector<int>::reverse_iterator rite;
	rit = v.rbegin();
	rite = v.rend();
	int expected = v.size() - 1;
	ASSERT_EQUAL(expected, 9);
	ASSERT_EQUAL(*rit, 9);
	int i = 0;
	while (rit != rite)
	{
		ASSERT_EQUAL(*rit, expected);			// Test iterator incrementation and access through operator*
		ASSERT_EQUAL(v.rbegin()[i], 9 - i);		// Test random access through operator[]
		ASSERT_EQUAL(*(i + v.rbegin()), 9 - i); // Test operator+
		ASSERT_EQUAL(rit - v.rbegin(), i);		// Test operator-
		++rit;
		--expected;
		++i;
	}
	rit = v.rbegin();
	ASSERT_EQUAL(rit[2], 7);
	return (0);
}

int test_reverse_iterator_map()
{
	FT::map<int, int> m;
	for (int x = 0; x < 10; ++x)
	{
		m[x] = x * 10;
	}

	FT::map<int, int>::reverse_iterator rit;
	FT::map<int, int>::reverse_iterator rite;
	rit = m.rbegin();
	rite = m.rend();
	int expected = m.size() - 1;
	ASSERT_EQUAL(expected, 9);
	ASSERT_EQUAL(rit->first, expected);
	int i = 0;
	while (rit != rite)
	{
		ASSERT_EQUAL(rit->first, expected);			// Test iterator incrementation and access through operator*
		ASSERT_EQUAL(rit->second, expected * 10);
		// ASSERT_EQUALQ(m.rbegin()[i].first, 9 - i);		// Test random access through operator[]
		// ASSERT_EQUAL((i + m.rbegin())->first, 9 - i); // Test operator+
		// ASSERT_EQUAL((rit - m.rbegin())->first, i);		// Test operator-
		++rit;
		--expected;
		++i;
	}
	return (0);
}

int test_lexicographical_compare()
{
	bool ret;
	FT::vector<char> v1;
	v1.push_back('a');
	v1.push_back('b');
	v1.push_back('c');
	v1.push_back('d');
	FT::vector<char> v2(v1);
	ret = FT::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end());
	ASSERT_EQUAL(ret, false);
	v1.pop_back();
	ret = FT::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end());
	ASSERT_EQUAL(ret, true);
	v1.push_back('c');
	ret = FT::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end());
	ASSERT_EQUAL(ret, true);
	return (0);
}

int test_pair()
{
	int n = 1;
	char c = 'a';
	int a[5] = {1, 2, 3, 4, 5};
	int &r = n;
	FT::pair<int, char> p = FT::make_pair(n, c);
	ASSERT_EQUAL(p.first, 1);
	ASSERT_EQUAL(p.second, 'a');

	FT::pair<int *, int *> p2 = FT::make_pair(&r, a);
	n = 7;
	ASSERT_EQUAL(p.first, 1);
	ASSERT_EQUAL(*p2.first, 7);
	ASSERT_EQUAL(*(p2.second + 2), 3);

	// Test comparisons
	FT::pair<int, char> p3 = p;
	p3.second = 'b';
	ASSERT_EQUAL(p == p3, false);
	ASSERT_EQUAL(p != p3, true);
	ASSERT_EQUAL(p < p3, true);
	ASSERT_EQUAL(p <= p3, true);
	ASSERT_EQUAL(p > p3, false);
	ASSERT_EQUAL(p >= p3, false);
	ASSERT_EQUAL(p3 < p, false);
	ASSERT_EQUAL(p3 <= p, false);
	ASSERT_EQUAL(p3 > p, true);
	ASSERT_EQUAL(p3 >= p, true);
	p3.second = 'a';
	ASSERT_EQUAL(p == p3, true);
	ASSERT_EQUAL(p != p3, false);
	ASSERT_EQUAL(p < p3, false);
	ASSERT_EQUAL(p <= p3, true);
	ASSERT_EQUAL(p > p3, false);
	ASSERT_EQUAL(p >= p3, true);
	ASSERT_EQUAL(p3 < p, false);
	ASSERT_EQUAL(p3 <= p, true);
	ASSERT_EQUAL(p3 > p, false);
	ASSERT_EQUAL(p3 >= p, true);
	p3.first = 0;
	ASSERT_EQUAL(p == p3, false);
	ASSERT_EQUAL(p != p3, true);
	ASSERT_EQUAL(p < p3, false);
	ASSERT_EQUAL(p <= p3, false);
	ASSERT_EQUAL(p > p3, true);
	ASSERT_EQUAL(p >= p3, true);
	ASSERT_EQUAL(p3 < p, true);
	ASSERT_EQUAL(p3 <= p, true);
	ASSERT_EQUAL(p3 > p, false);
	ASSERT_EQUAL(p3 >= p, false);

	return (0);
}

void add_test_iterator_suite(FRAMEWORK_NAMESPACE::vector<Test2> *testlist)
{
	ADD_TEST(testlist, test_random_access_iterator_tag_int);
	ADD_TEST(testlist, test_random_access_iterator_tag_vector);
	ADD_TEST(testlist, test_bidirectional_iterator_tag_map);
	ADD_TEST(testlist, test_reverse_iterator_vector);
	ADD_TEST(testlist, test_reverse_iterator_map);
	ADD_TEST(testlist, test_lexicographical_compare);
	ADD_TEST(testlist, test_pair);
}
