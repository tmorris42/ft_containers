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
	FT::map<char, int>::iterator it;
	char	tmp_c;

	m['a'] = 10;
	m['k'] = 20;

	it = m.find('a');
	tmp_c = it->first;
	ASSERT_EQUAL(tmp_c, 'a');
	ASSERT_EQUAL((m.find('k'))->first, 'k');
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
	m.erase('k');
	ASSERT_EQUALQ((m.count('k')), (unsigned long)0);
	return (0);
}

int test_map_erase_by_iterator()
{
	FT::map<char, int> m;
	FT::map<char, int>::iterator it;

	m['a'] = 1;
	m['b'] = 2;
	m['c'] = 3;

	ASSERT_EQUAL(m.size(), (unsigned long)3);
	it = (++m.begin());
	m.erase(it);
	ASSERT_EQUAL(m.size(), (unsigned long)2);
	ASSERT_EQUAL(m.begin()->first, 'a');
	ASSERT_EQUAL((++m.begin())->first, 'c');

	return (0);
}

int test_map_erase_by_key()
{
	FT::map<char, int> m;
	FT::map<char, int>::iterator it;

	m['a'] = 1;
	m['b'] = 2;
	m['c'] = 3;

	ASSERT_EQUAL(m.size(), (unsigned long)3);
	it = (++m.begin());
	m.erase('c');
	ASSERT_EQUAL(m.size(), (unsigned long)2);
	ASSERT_EQUAL(m.begin()->first, 'a');
	ASSERT_EQUAL((++m.begin())->first, 'b');
	return (0);
}

int test_map_clear()
{
	FT::map<char, int> m;

	m['a'] = 1;
	m['b'] = 2;
	m['c'] = 3;

	ASSERT_EQUAL(m.size(), (unsigned long)3);
	m.clear();
	ASSERT_EQUAL(m.size(), (unsigned long)0);
	return (0);
}

int test_map_swap()
{
	FT::map<char, int> m1;
	FT::map<char, int> m2;

	m1['a'] = 1;
	m1['b'] = 2;
	m1['c'] = 3;
	m2['d'] = 11;
	m2['e'] = 12;
	m2['f'] = 13;
	m2['g'] = 14;

	m1.size();
	ASSERT_EQUAL(m1.size(), (unsigned long)3);
	ASSERT_EQUAL(m2.size(), (unsigned long)4);
	m1.swap(m2);
	ASSERT_EQUAL(m1.size(), (unsigned long)4);
	ASSERT_EQUAL(m2.size(), (unsigned long)3);
	ASSERT_EQUAL(m2.begin()->first, 'a');
	ASSERT_EQUAL(m2.begin()->second, 1);
	ASSERT_EQUAL(m1.begin()->first, 'd');
	ASSERT_EQUAL(m1.begin()->second, 11);

	return (0);
}

int test_map_four_values()
{
	FT::map<char, int> m1;

	m1['a'] = 1;
	m1['b'] = 2;
	m1['c'] = 3;
	m1['d'] = 11;


	m1.size();
	ASSERT_EQUAL(m1.size(), (unsigned long)4);

	return (0);
}

int test_map_four_values_descending()
{
	FT::map<char, int> m1;

	m1['d'] = 5;
	m1['c'] = 4;
	m1['b'] = 3;
	m1['a'] = 2;


	m1.size();
	ASSERT_EQUAL(m1.size(), (unsigned long)4);

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
	ADD_TEST(testlist, test_map_erase_by_iterator);
	ADD_TEST(testlist, test_map_erase_by_key);
	ADD_TEST(testlist, test_map_clear);
	ADD_TEST(testlist, test_map_four_values);
	ADD_TEST(testlist, test_map_four_values_descending);
	ADD_TEST(testlist, test_map_swap);
}
