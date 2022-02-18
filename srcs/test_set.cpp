#include "tests.hpp"

int	test_set_everything()
{
	typedef FT::set<int>::iterator iterator;
	FT::set<int> s;

	for (int i = 0; i < 10; ++i)
		s.insert(i);
	iterator it = s.begin();

	ASSERT_EQUAL(*it, 0);
	return (0);
}

int test_set_stress_basic()
{
	FT::vector<int>		v1;
	FT::set<int>	s;

	for (int c = 0; c <= 10000; ++c)
	{
		v1.push_back(c);
	}

	size_t size = v1.size();
	for (size_t N = 0; N < size; ++N)
	{
		s.insert(v1[N]);
	}

	return (0);
}

void add_test_set_suite(FRAMEWORK_NAMESPACE::vector<Test2> *testlist)
{
	ADD_TEST(testlist, test_set_everything);
	ADD_TEST(testlist, test_set_stress_basic);	
}
