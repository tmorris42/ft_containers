#include "tests.hpp"

template <class T, class C>
static void	print_set(FT::set<T, C> & s)
{
	if (!VERBOSE)
		return ;
	std::cout << "size: " << s.size() << std::endl;
	std::cout << "empty: " << s.empty() << std::endl;
	typename FT::set<T, C>::const_iterator ite = s.end();
	typename FT::set<T, C>::const_iterator it = s.begin();
	while (it != ite)
	{
		std::cout << *it << " ";
		++it;
	}
	std::cout << std::endl;
}

int	test_set_basic()
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

struct classcomp {
	bool operator() (const int & lhs, const int & rhs) const {
		return (lhs < rhs);
	}
};

bool fncmp(int lhs, int rhs) {
	return lhs < rhs;
}

int	test_set_constructors()
{
	FT::set<int> first; // Void constructor
	print_set(first);

	int ints[] = {10, 20, 30, 40, 50};
	FT::set<int> second (ints, ints + 5); // Range constructor
	print_set(second);
	ASSERT_EQUAL(second.count(10), true);
	ASSERT_EQUAL(second.count(50), true);
	ASSERT_EQUAL(second.count(14), false);

	FT::set<int> third(second); // Copy constructor
	print_set(third);
	ASSERT_EQUAL(second.count(10), true);
	ASSERT_EQUAL(second.count(50), true);
	ASSERT_EQUAL(second.count(14), false);

	FT::set<int> fourth(second.begin(), second.end()); // Iterator constructor
	print_set(fourth);
	ASSERT_EQUAL(fourth.count(10), true);
	ASSERT_EQUAL(fourth.count(50), true);
	ASSERT_EQUAL(fourth.count(14), false);

	FT::set<int, classcomp> fifth; // Using class as Compare
	print_set(fifth);

	bool (*fncmp_ptr)(int, int) = fncmp;
	FT::set<int,  bool(*)(int, int)> sixth(fncmp_ptr); // Using function as Compare
	print_set(sixth);
	return (0);
}

int	test_set_operator_assign()
{
	int myints[]={ 12,82,37,64,15 };
	FT::set<int> first (myints, myints+5);
	FT::set<int> second;

	second = first;
	first = FT::set<int>();

	print_set(first);
	print_set(second);
	ASSERT_EQUAL(first.size(), (unsigned)0);
	ASSERT_EQUAL(second.size(), (unsigned)5);
	
	return (0);
}

void add_test_set_suite(FRAMEWORK_NAMESPACE::vector<Test2> *testlist)
{
	ADD_TEST(testlist, test_set_basic);
	ADD_TEST(testlist, test_set_stress_basic);
	ADD_TEST(testlist, test_set_constructors);
	ADD_TEST(testlist, test_set_operator_assign);
}
