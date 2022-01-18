#include "tests.hpp"

int	test_map_void_constructor()
{
	FT::map<int, int> m;

	ASSERT_EQUAL(m.empty(), true);
	return (0);
}

int test_map_empty()
{
	FT::map<char, int> m;

	FT::pair<const char, int>	p1; //('a', 10);
	FT::pair<const char, int>	p2('b', 20);

	ASSERT_EQUAL(m.empty(), true);
	m.insert( p1 );
	m.insert( p2 );
	ASSERT_EQUAL(m.empty(), false);
	return (0);
}

int test_map_size()
{
	FT::map<char, int> m;

	FT::pair<const char, int>	p1('a', 10);
	FT::pair<const char, int>	p2('b', 20);
	
	ASSERT_EQUAL(m.size(), (unsigned int)0);
	m.insert(p1);
	ASSERT_EQUAL(m.size(), (unsigned int)1);
	m.insert(p2);
	ASSERT_EQUAL(m.size(), (unsigned int)2);
	return (0);
}

void	add_test_map_suite(FRAMEWORK_NAMESPACE::vector<Test2> *testlist)
{
	ADD_TEST(testlist, test_map_void_constructor);
	ADD_TEST(testlist, test_map_empty);
	ADD_TEST(testlist, test_map_size);
}
