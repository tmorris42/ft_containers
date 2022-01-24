#include "tests.hpp"

template<class T1, class T2>
static void print_map(FT::map<T1, T2> m)
{
	typedef typename FT::map<T1, T2>	map_type;
	typedef typename map_type::iterator			iterator;
	if (!VERBOSE)
		return ;
	std::cout << "size: " << m.size() << std::endl;
	// std::cout << "max_size: " << m.max_size() << std::endl; Not handled the same as std

	iterator ite = m.end();
	for (iterator it = m.begin(); it != ite; ++it)
	{
		std::cout << "-- m[" << it->first << "] = " << it->second << std::endl;
	}
}

int	test_map_void_constructor()
{
	FT::map<int, int> m;

	ASSERT_EQUAL(m.empty(), true);
	print_map(m);
	return (0);
}

int test_map_copy_constructor()
{
	FT::map<int, int> m;

	m[5] = 1;
	m[6] = 2;
	m[3] = 4;
	FT::map<int, int> m2(m);
	ASSERT_EQUAL(m2.size(), (unsigned long)3);
	ASSERT_EQUAL(m2.empty(), false);
	FT::map<int, int>::iterator it1 = m.begin();
	FT::map<int, int>::iterator ite1 = m.end();
	FT::map<int, int>::iterator it2 = m2.begin();
	FT::map<int, int>::iterator ite2 = m2.end();
	while (it1 != ite1 && it2 != ite2)
	{
		ASSERT_EQUALQ(*it1, *it2);
		++it1;
		++it2;
	}
	print_map(m);
	print_map(m2);
	return (0);
}

int test_map_iterator_constructor()
{
	FT::map<int, int> m;

	m[5] = 1;
	m[6] = 2;
	m[3] = 4;

	FT::map<int, int>::iterator it1 = m.begin();
	FT::map<int, int>::iterator ite1 = m.end();
	FT::map<int, int> m2(it1, ite1);
	ASSERT_EQUAL(m2.size(), (unsigned long)3);
	ASSERT_EQUAL(m2.empty(), false);
	FT::map<int, int>::iterator it2 = m2.begin();
	FT::map<int, int>::iterator ite2 = m2.end();
	while (it1 != ite1 && it2 != ite2)
	{
		ASSERT_EQUALQ(*it1, *it2);
		++it1;
		++it2;
	}
	print_map(m);
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
	print_map(m);
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
	print_map(m);
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
	print_map(m);
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
	print_map(m);
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
	print_map(m);
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
	print_map(m);
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
	print_map(m);
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
	print_map(m);
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
	print_map(m);
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
	print_map(m);
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
	print_map(m);
	return (0);
}

int test_map_erase_by_range()
{
	FT::map<char, int> m;
	FT::map<char, int>::iterator it;

	m['a'] = 1;
	m['b'] = 2;
	m['c'] = 3;
	m['d'] = 4;
	m['e'] = 5;

	ASSERT_EQUAL(m.size(), (unsigned long)5);
	it = (++m.begin());
	m.erase(++it, m.end());
	ASSERT_EQUAL(m.size(), (unsigned long)2);
	ASSERT_EQUAL(m.begin()->first, 'a');
	ASSERT_EQUAL((++m.begin())->first, 'b');
	print_map(m);
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
	print_map(m);
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
	print_map(m1);
	print_map(m2);
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
	print_map(m1);
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
	print_map(m1);
	return (0);
}

int test_map_lower_bound()
{
	FT::map<char, int> m1;

	m1['b'] = 1;
	m1['c'] = 2;
	m1['e'] = 4;

	ASSERT_EQUAL(m1.lower_bound('a')->second, 1);
	ASSERT_EQUAL(m1.lower_bound('b')->second, 1);
	ASSERT_EQUAL(m1.lower_bound('c')->second, 2);
	ASSERT_EQUAL(m1.lower_bound('d')->second, 4);
	ASSERT_EQUAL(m1.lower_bound('e')->second, 4);
	ASSERT_EQUALQ(m1.lower_bound('f'), m1.end());
	print_map(m1);
	return (0);
}


int test_map_upper_bound()
{
	FT::map<char, int> m1;

	m1['b'] = 1;
	m1['c'] = 2;
	m1['e'] = 4;

	ASSERT_EQUAL(m1.upper_bound('a')->second, 1);
	ASSERT_EQUAL(m1.upper_bound('b')->second, 2);
	ASSERT_EQUAL(m1.upper_bound('c')->second, 4);
	ASSERT_EQUAL(m1.upper_bound('d')->second, 4);
	ASSERT_EQUALQ(m1.upper_bound('e'), m1.end());
	ASSERT_EQUALQ(m1.upper_bound('f'), m1.end());
	print_map(m1);
	return (0);
}

int test_map_equal_range()
{
	typedef FT::map<char, int>::iterator iterator;
	FT::map<char, int> m1;
	FT::pair<iterator, iterator> p;

	m1['b'] = 1;
	m1['c'] = 2;
	m1['e'] = 4;

	ASSERT_EQUAL(m1.equal_range('a').first->first, 'b');
	ASSERT_EQUAL(m1.equal_range('a').second->first, 'b');
	ASSERT_EQUAL(m1.equal_range('a').first->second, 1);
	ASSERT_EQUAL(m1.equal_range('a').second->second, 1);
	ASSERT_EQUAL(m1.equal_range('b').first->first, 'b');
	ASSERT_EQUAL(m1.equal_range('b').second->first, 'c');	
	ASSERT_EQUAL(m1.equal_range('b').first->second, 1);
	ASSERT_EQUAL(m1.equal_range('b').second->second, 2);
	ASSERT_EQUAL(m1.equal_range('c').first->first, 'c');
	ASSERT_EQUAL(m1.equal_range('c').second->first, 'e');
	ASSERT_EQUAL(m1.equal_range('c').first->second, 2);
	ASSERT_EQUAL(m1.equal_range('c').second->second, 4);
	ASSERT_EQUAL(m1.equal_range('d').first->first, 'e');
	ASSERT_EQUAL(m1.equal_range('d').second->first, 'e');
	ASSERT_EQUAL(m1.equal_range('d').first->second, 4);
	ASSERT_EQUAL(m1.equal_range('d').second->second, 4);
	ASSERT_EQUAL(m1.equal_range('e').first->first, 'e');
	ASSERT_EQUAL(m1.equal_range('e').first->second, 4);
	ASSERT_EQUALQ(m1.equal_range('e').second, m1.end());
	ASSERT_EQUALQ(m1.equal_range('f').first, m1.end());
	ASSERT_EQUALQ(m1.equal_range('f').second, m1.end());
	print_map(m1);
	return (0);
}

void	add_test_map_suite(FRAMEWORK_NAMESPACE::vector<Test2> *testlist)
{
	ADD_TEST(testlist, test_map_void_constructor);
	ADD_TEST(testlist, test_map_copy_constructor);
	ADD_TEST(testlist, test_map_iterator_constructor);
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
	ADD_TEST(testlist, test_map_erase_by_range);
	ADD_TEST(testlist, test_map_clear);
	ADD_TEST(testlist, test_map_four_values);
	ADD_TEST(testlist, test_map_four_values_descending);
	ADD_TEST(testlist, test_map_swap);
	ADD_TEST(testlist, test_map_lower_bound);
	ADD_TEST(testlist, test_map_upper_bound);
	ADD_TEST(testlist, test_map_equal_range);
}
