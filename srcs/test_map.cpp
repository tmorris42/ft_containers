#include "tests.hpp"

int	test_map_void_constructor()
{
	FT::map<int, int> m;

	ASSERT_EQUAL(m.empty(), true);
	return (0);
}

void	add_test_map_suite(FRAMEWORK_NAMESPACE::vector<Test2> *testlist)
{
	ADD_TEST(testlist, test_map_void_constructor);
}
