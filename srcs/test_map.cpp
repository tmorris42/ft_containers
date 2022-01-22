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

int test_map_brackets_write()
{
	FT::map<char, int> m;

	m['a'] = 10;
	m['c'] = 30;	
	m['b'] = 20;
	int count = 10;

	FT::map<char, int>::iterator it = m.begin();
	FT::map<char, int>::iterator ite = m.end();
	while (it != ite)
	{
		ASSERT_EQUAL(it->second, count);
		count += 10;
		++it;
	}
	ASSERT_EQUAL(m.size(), (unsigned int)3);
	ASSERT_EQUAL((m.begin())->second, 10);
	ASSERT_EQUAL((++m.begin())->second, 20);
	ASSERT_EQUAL((--m.end())->second, 30);
	return (0);
}

int test_map_brackets_read()
{
	FT::map<char, int> m;

	m['a'] = 10;
	m['c'] = 30;	
	m['b'] = 20;
	ASSERT_EQUAL(m['a'], 10);
	ASSERT_EQUAL(m['b'], 20);
	ASSERT_EQUAL(m['c'], 30);
	return (0);
}

int test_map_brackets_overwrite()
{
	FT::map<char, int> m;

	m['a'] = 10;
	m['c'] = 30;	
	m['b'] = 20;
	m['a'] = 40;
	m['b'] = 50;
	m['c'] = 60;	
	int count = 40;

	FT::map<char, int>::iterator it = m.begin();
	FT::map<char, int>::iterator ite = m.end();
	while (it != ite)
	{
		ASSERT_EQUAL(it->second, count);
		count += 10;
		++it;
	}
	ASSERT_EQUAL(m.size(), (unsigned int)3);
	ASSERT_EQUAL((m.begin())->second, 40);
	ASSERT_EQUAL((++m.begin())->second, 50);
	ASSERT_EQUAL((--m.end())->second, 60);
	return (0);
}

int test_map_insert_duplicate()
{
	FT::map<char, int> m;

	FT::pair<const char, int>	p1('a', 10);
	FT::pair<const char, int>	p2('a', 20);
	
	ASSERT_EQUAL(m.size(), (unsigned int)0);
	m.insert(p1);
	ASSERT_EQUAL(m.size(), (unsigned int)1);
	m.insert(p1);
	ASSERT_EQUAL(m.size(), (unsigned int)1);
	m.insert(p2);
	ASSERT_EQUAL(m.size(), (unsigned int)1);
	ASSERT_EQUAL(m.begin()->second, 10);
	return (0);
}

int test_map_reverse_iterator()
{
	FT::map<char, int> m;

	m['a'] = 10;
	m['c'] = 30;	
	m['b'] = 20;
	int count = 30;

	FT::map<char, int>::reverse_iterator rit = m.rbegin();
	FT::map<char, int>::reverse_iterator rite = m.rend();
	while (rit != rite)
	{
		ASSERT_EQUAL(rit->second, count);
		count -= 10;
		++rit;
	}
	ASSERT_EQUAL(m.size(), (unsigned int)3);
	ASSERT_EQUAL((m.rbegin())->second, 30);
	ASSERT_EQUAL((++m.rbegin())->second, 20);
	ASSERT_EQUAL((--m.rend())->second, 10);
	return (0);
}

int test_map_find()
{
	FT::map<char, int> m;

	m['a'] = 10;
	m['k'] = 20;

	ASSERT_EQUALQ((m.find('a')), m.begin());
	ASSERT_EQUALQ((m.find('b')), m.end());
	ASSERT_EQUALQ((m.find('k')), (++m.begin()));
	return (0);
}

int test_map_count()
{
	FT::map<char, int> m;

	m['a'] = 10;
	m['k'] = 20;

	ASSERT_EQUALQ((m.count('a')), (unsigned long)1);
	ASSERT_EQUALQ((m.count('b')), (unsigned long)0);
	ASSERT_EQUALQ((m.count('k')), (unsigned long)1);
	return (0);
}

void	add_test_map_suite(FRAMEWORK_NAMESPACE::vector<Test2> *testlist)
{
	ADD_TEST(testlist, test_map_void_constructor);
	ADD_TEST(testlist, test_map_empty);
	ADD_TEST(testlist, test_map_size);
	ADD_TEST(testlist, test_map_brackets_write);
	ADD_TEST(testlist, test_map_brackets_overwrite);
	ADD_TEST(testlist, test_map_brackets_read);
	ADD_TEST(testlist, test_map_insert_duplicate);
	ADD_TEST(testlist, test_map_reverse_iterator);
	ADD_TEST(testlist, test_map_find);
	ADD_TEST(testlist, test_map_count);
}
