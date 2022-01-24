#include "tests.hpp"


template <class T, class C>
static void	print_stack(FT::stack<T, C> & s)
{
	if (!VERBOSE)
		return ;
	std::cout << "size: " << s.size() << std::endl;
	std::cout << "empty: " << s.empty() << std::endl;
	std::cout << "top: " << s.top() << std::endl;
}

int	test_stack_basic()
{
	FT::stack< int, FT::vector<int> > s;

	ASSERT_EQUAL(s.empty(), true);
	ASSERT_EQUAL(s.size(), (size_t)0);
	s.push(5);
	ASSERT_EQUAL(s.empty(), false);
	ASSERT_EQUAL(s.size(), (size_t)1);
	s.push(8);
	ASSERT_EQUAL(s.empty(), false);
	ASSERT_EQUAL(s.size(), (size_t)2);
	ASSERT_EQUAL(s.top(), 8);
	s.pop();
	ASSERT_EQUAL(s.empty(), false);
	ASSERT_EQUAL(s.size(), (size_t)1);
	ASSERT_EQUAL(s.top(), 5);
	// s.pop();
	// ASSERT_EQUAL(s.top(), 0);
	// ASSERT_EQUAL(s.size(), (size_t)0);
	// ASSERT_EQUAL(s.empty(), true);

	return (0);
}

int	test_stack_basic_cmp()
{
	FT::stack< int, FT::vector<int> > s1;
	FT::stack< int, FT::vector<int> > s2;
	FT::stack< int, FT::vector<int> > s3;
	s1.push(5);
	s1.push(8);
	s2.push(5);
	s2.push(8);
	s3.push(5);
	s3.push(7);
	ASSERT_EQUALQ(s1, s2);
	ASSERT_EQUAL(s1 == s2, true);
	ASSERT_EQUAL(s1 != s2, false);
	ASSERT_EQUAL(s1 <= s2, true);
	ASSERT_EQUAL(s1 >= s2, true);
	ASSERT_EQUAL(s1 < s2, false);
	ASSERT_EQUAL(s1 > s2, false);

	ASSERT_EQUAL(s1 == s3, false);
	ASSERT_EQUAL(s1 != s3, true);
	ASSERT_EQUAL(s1 <= s3, false);
	ASSERT_EQUAL(s1 >= s3, true);
	ASSERT_EQUAL(s1 < s3, false);
	ASSERT_EQUAL(s1 > s3, true);

	return (0);
}

int             test_stack_default_copy(void)
{
	typedef FT::vector<int> container_type_used;
	typedef FT::stack<int, container_type_used> stack_type;
	typedef stack_type::container_type container_type;
	container_type  ctnr;
	ctnr.push_back(21);
	ctnr.push_back(42);
	ctnr.push_back(1337);
	ctnr.push_back(19);
	ctnr.push_back(0);
	ctnr.push_back(183792);

	stack_type             stck(ctnr);
	print_stack(stck);
	stck.push(1);
	stck.push(2);
	stck.push(3);
	stck.push(4);
	stck.push(5);
	stck.push(6);
	print_stack(stck);

	return (0);
}

void	add_test_stack_suite(FRAMEWORK_NAMESPACE::vector<Test2> *testlist)
{
	ADD_TEST(testlist, test_stack_basic);
	ADD_TEST(testlist, test_stack_basic_cmp);
	ADD_TEST(testlist, test_stack_default_copy);
}
