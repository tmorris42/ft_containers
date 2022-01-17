#include "tests.hpp"

int	test_map_void_constructor()
{
	FT::map<int, int> m;

	ASSERT_EQUAL(m.empty(), true);
	return (0);
}

// int test_map_empty()
// {
// 	FT::map<char, int> m;

// 	ASSERT_EQUAL(m.empty(), true);
// 	m.insert( FT::pair<char, int>('a', 100));
// 	m.insert( FT::pair<char, int>('b', 200));
// 	ASSERT_EQUAL(m.empty(), false);
// 	return (0);
// }

int test_map_size()
{
	FT::map<const char, int> m;

	ASSERT_EQUAL(m.size(), (unsigned int)0);
	m.insert( FT::make_pair<const char, int>('a', 100));
	ASSERT_EQUAL(m.size(), (unsigned int)1);
	m.insert( FT::make_pair<const char, int>('b', 200));
	ASSERT_EQUAL(m.size(), (unsigned int)2);
	return (0);
}

void	add_test_map_suite(FRAMEWORK_NAMESPACE::vector<Test2> *testlist)
{
	ADD_TEST(testlist, test_map_void_constructor);
	// ADD_TEST(testlist, test_map_empty);
	ADD_TEST(testlist, test_map_size);
}
