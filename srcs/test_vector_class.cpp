#include "tests.hpp"


int	test_vector_vector_basic()
{
	FT::vector< FT::vector< int > > cvec1;
	FT::vector< FT::vector< int > > cvec2;
	FT::vector<int> ivec1;
	FT::vector<int> ivec2;

	ASSERT_EQUAL(cvec1.size(), (unsigned long)0);
	ASSERT_EQUAL(cvec1.empty(), true);
	ASSERT_EQUAL(cvec1.capacity(), (unsigned long)0);

	ivec1.insert(ivec1.begin(), 8, 42);
	ivec2.insert(ivec2.begin(), 8, 84);
	cvec1.push_back(ivec1);
	cvec1.push_back(ivec2);

	ASSERT_EQUAL(cvec1.size(), (unsigned long)2);
	ASSERT_EQUAL(cvec1.empty(), false);
	ASSERT_EQUAL(cvec1.capacity(), (unsigned long)2);
	FT::vector< FT::vector<int> >::iterator it;
	FT::vector< FT::vector<int> >::iterator ite;
	it = cvec1.begin();
	ite = cvec1.end();
	while (it != ite)
	{
		ASSERT_EQUAL((*it).size(), (unsigned long)8);
		++it;
	}
	cvec2 = cvec1;
	ASSERT_EQUALQ(cvec2, cvec1);
	return (0);
}

int test_vector_stress_basic()
{
	FT::vector<int>	v1;
	FT::vector<int>	v2;
	v1.insert(v1.begin(), 10000, 42);
	v2 = v1;

	return (0);
}

void	add_test_vector_class_suite(FRAMEWORK_NAMESPACE::vector<Test2> *testlist)
{
	ADD_TEST(testlist, test_vector_vector_basic);
	// ADD_TEST(testlist, test_vector_stress_basic); // Takes a long time on MY version

}
