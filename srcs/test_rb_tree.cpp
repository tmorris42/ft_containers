#ifndef FT_REAL_VERSION
#include "tests.hpp"

template <class T1, class T2>
std::ostream & 	operator<<(std::ostream & os, FT::pair<T1, T2> p)
{
	os << "Pair<" << p.first << ", " << p.second << ">" << std::endl;
	return (os);
}

template <class T, class Compare>
void printBT(const std::string& prefix, const ft::Node<T, Compare>* node, bool isLeft)
{
    if(node)
    {
        std::cout << prefix;
        std::cout << (isLeft ? "├──" : "└──" );

		if (node->color == RB_RED)
			std::cout << "R:";
		else
			std::cout << "B:";
        std::cout << node->value << std::endl;
        printBT<T, Compare>( prefix + (isLeft ? "│   " : "    "), node->left, true);
        printBT<T, Compare>( prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}
template <class T, class Compare>
void printBT(const ft::RB_Tree<T, Compare>* tree)
{
	if (VERBOSE)
	{
		std::cout << "TREE:: h = " << tree->get_black_height() << "; is_rb = " << tree->is_red_black() << std::endl;
    	printBT<T, Compare>("", &tree->stump, false);
	}
}

int	test_rb_tree_void_constructor()
{
	ft::RB_Tree<int> rb((std::less<int>()));

	ASSERT_EQUALQ(rb.search(5), rb.end());
	return (0);
}

int test_rb_tree_insert()
{
	ft::RB_Tree<int> rb((std::less<int>()));

	rb.insert(6);
	rb.insert(5);
	rb.insert(7);
	ASSERT_EQUAL(*rb.search(5), 5);
	ASSERT_EQUAL(*rb.search(6), 6);
	ASSERT_EQUAL(*rb.search(7), 7);
	ASSERT_EQUALQ(rb.search(8), rb.end());
	printBT(&rb);
	return (0);
}

int test_rb_tree_delete()
{
	ft::RB_Tree<int> rb(((std::less<int>())));

	rb.insert(6);
	rb.insert(5);
	rb.insert(7);
	rb.insert(10);
	rb.insert(9);
	rb.insert(4);
	ASSERT_EQUAL(*rb.search(7), 7);
	rb.delete_node(rb.stump.left, 7);
	ASSERT_EQUALQ(rb.search(7), rb.end());
	rb.delete_tree(rb.stump.left);
	return (0);
}

int test_rb_pair()
{
	ft::RB_Tree< FT::pair<char, int> >	rb((std::less<FT::pair<char, int> >()));

	FT::pair<char, int>	p1('a', 10);
	FT::pair<char, int>	p2('b', 20);
	rb.insert(p1);
	rb.insert(p2);
	return (0);
}

int test_rb_pair_const()
{
	ft::RB_Tree< FT::pair<const char, int> >	rb((std::less<FT::pair<const char, int> >()));

	FT::pair<const char, int>	p1('a', 10);
	FT::pair<const char, int>	p2('b', 20);
	rb.insert(p1);
	rb.insert(p2);
	return (0);
}

int test_rb_single_element()
{
	ft::RB_Tree<int> rb((std::less<int>()));

	rb.insert(5);
	ASSERT_EQUAL(rb.stump.left->color, RB_BLACK);
	ASSERT_EQUAL(rb.stump.left->value, 5);
	return (0);
}

int test_rb_two_elements()
{
	ft::RB_Tree<int>	rb((std::less<int>()));
	void				*nptr = NULL;

	rb.insert(5);
	ASSERT_EQUAL(rb.stump.left->color, RB_BLACK);
	ASSERT_EQUAL(rb.stump.left->value, 5);
	rb.insert(8);
	ASSERT_EQUAL(rb.stump.left->color, RB_BLACK);
	ASSERT_EQUAL(rb.stump.left->value, 5);
	ASSERT_EQUAL(rb.stump.left->left, nptr);
	ASSERT_EQUAL(rb.stump.left->right->color, RB_RED);
	ASSERT_EQUAL(rb.stump.left->right->value, 8);

	return (0);
}

int test_rb_ascending_insert()
{
	ft::RB_Tree<int>	rb((std::less<int>()));
	void				*nptr = NULL;

	rb.insert(5);
	ASSERT_EQUAL(rb.stump.left->color, RB_BLACK);
	ASSERT_EQUAL(rb.stump.left->value, 5);
	rb.insert(8);
	ASSERT_EQUAL(rb.stump.left->color, RB_BLACK);
	ASSERT_EQUAL(rb.stump.left->value, 5);
	ASSERT_EQUAL(rb.stump.left->left, nptr);
	ASSERT_EQUAL(rb.stump.left->right->color, RB_RED);
	ASSERT_EQUAL(rb.stump.left->right->value, 8);
	rb.insert(10);
	printBT(&rb);
	ASSERT_EQUAL(rb.stump.left->color, RB_BLACK);
	ASSERT_EQUAL(rb.stump.left->value, 8);
	ASSERT_EQUAL(rb.stump.left->left->color, RB_RED);
	ASSERT_EQUAL(rb.stump.left->left->value, 5);
	ASSERT_EQUAL(rb.stump.left->right->color, RB_RED);
	ASSERT_EQUAL(rb.stump.left->right->value, 10);
	return (0);
}

int test_rb_recoloring_insert()
{
	ft::RB_Tree<int>	rb((std::less<int>()));
	void				*nptr = NULL;

	rb.insert(5);
	ASSERT_EQUAL(rb.stump.left->color, RB_BLACK);
	ASSERT_EQUAL(rb.stump.left->value, 5);
	rb.insert(8);
	ASSERT_EQUAL(rb.stump.left->color, RB_BLACK);
	ASSERT_EQUAL(rb.stump.left->value, 5);
	ASSERT_EQUAL(rb.stump.left->left, nptr);
	ASSERT_EQUAL(rb.stump.left->right->color, RB_RED);
	ASSERT_EQUAL(rb.stump.left->right->value, 8);
	rb.insert(4);
	ASSERT_EQUAL(rb.stump.left->color, RB_BLACK);
	ASSERT_EQUAL(rb.stump.left->value, 5);
	ASSERT_EQUAL(rb.stump.left->left->color, RB_RED);
	ASSERT_EQUAL(rb.stump.left->left->value, 4);
	ASSERT_EQUAL(rb.stump.left->right->color, RB_RED);
	ASSERT_EQUAL(rb.stump.left->right->value, 8);
	rb.insert(11);
	ASSERT_EQUAL(rb.stump.left->color, RB_BLACK);
	ASSERT_EQUAL(rb.stump.left->value, 5);
	ASSERT_EQUAL(rb.stump.left->left->color, RB_BLACK);
	ASSERT_EQUAL(rb.stump.left->left->value, 4);
	ASSERT_EQUAL(rb.stump.left->right->color, RB_BLACK);
	ASSERT_EQUAL(rb.stump.left->right->value, 8);
	ASSERT_EQUAL(rb.stump.left->right->right->color, RB_RED);
	ASSERT_EQUAL(rb.stump.left->right->right->value, 11);
	return (0);
}

int test_rb_begin()
{
	ft::RB_Tree<int> rb((std::less<int>()));
	ft::RB_Tree<int>::iterator	it;

	rb.insert(5);
	rb.insert(6);
	rb.insert(4);
	it = rb.begin();
	ASSERT_EQUAL(*(it++), 4);
	ASSERT_EQUAL(*it, 5);
	ASSERT_EQUAL(*(++it), 6);
	return (0);
}

int test_rb_end()
{
	ft::RB_Tree<int> rb((std::less<int>()));
	ft::RB_Tree<int>::iterator	it;
	ft::RB_Tree<int>::iterator	ite;
	int count;

	rb.insert(5);
	rb.insert(6);
	rb.insert(4);
	it = rb.begin();
	ite = rb.end();
	count = 4;
	while (it != ite)
	{
		ASSERT_EQUAL(*it, count);
		++count;
		++it;
	}
	return (0);
}

int test_rb_dec()
{
	ft::RB_Tree<int> rb((std::less<int>()));
	ft::RB_Tree<int>::iterator	it;
	ft::RB_Tree<int>::iterator	ite;

	rb.insert(5);
	rb.insert(6);
	rb.insert(4);
	it = rb.begin();
	ASSERT_EQUAL(*it, 4);
	++it;
	ASSERT_EQUAL(*it, 5);
	--it;
	ASSERT_EQUAL(*it, 4);
	--it;
	ASSERT_EQUAL(*it, 0);
	return (0);
}

int test_rb_inc()
{
	ft::RB_Tree<int> rb((std::less<int>()));
	ft::RB_Tree<int>::iterator	it;
	ft::RB_Tree<int>::iterator	ite;

	rb.insert(5);
	rb.insert(6);
	rb.insert(4);
	printBT(&rb);
	it = rb.begin();
	ASSERT_EQUAL(*it, 4);
	++it;
	ASSERT_EQUAL(*it, 5);
	++it;
	ASSERT_EQUAL(*it, 6);
	++it;
	ASSERT_EQUAL(*it, 0);
	++it;
	ASSERT_EQUAL(*it, 4);
	return (0);
}

int	test_rb_size()
{
	ft::RB_Tree<int> rb((std::less<int>()));

	ASSERT_EQUAL(rb.size(), static_cast<unsigned long>(0));
	rb.insert(5);
	ASSERT_EQUAL(rb.size(), static_cast<unsigned long>(1));
	rb.insert(6);
	ASSERT_EQUAL(rb.size(), static_cast<unsigned long>(2));
	rb.insert(4);
	ASSERT_EQUAL(rb.size(), static_cast<unsigned long>(3));
	return (0);
}

int	test_rb_size_low_high_med()
{
	ft::RB_Tree<int> rb((std::less<int>()));

	ASSERT_EQUAL(rb.size(), static_cast<unsigned long>(0));
	rb.insert(1);
	ASSERT_EQUAL(rb.size(), static_cast<unsigned long>(1));
	rb.insert(3);
	ASSERT_EQUAL(rb.size(), static_cast<unsigned long>(2));
	rb.insert(2);
	ASSERT_EQUAL(rb.size(), static_cast<unsigned long>(3));
	return (0);
}

int test_rb_four_chars()
{
	ft::RB_Tree<char> rb((std::less<char>()));

	rb.insert('d');
	rb.insert('e');
	rb.insert('f');
	rb.insert('g');
	printBT(&rb);
	rb.delete_tree(rb.stump.left);
	return (0);
}

int test_rb_playground()
{
	ft::RB_Tree<int> rb(((std::less<int>())));

	rb.insert(10);
	rb.insert(20);
	rb.insert(30);
	rb.insert(25);
	rb.insert(35);
	printBT(&rb);

	rb.delete_node(rb.stump.left, 10);

	printBT(&rb);

	rb.delete_tree(rb.stump.left);
	return (0);
}

void	add_test_rb_tree_suite(FRAMEWORK_NAMESPACE::vector<Test2> *testlist)
{
	ADD_TEST(testlist, test_rb_tree_void_constructor);
	ADD_TEST(testlist, test_rb_tree_insert);
	ADD_TEST(testlist, test_rb_tree_delete);
	ADD_TEST(testlist, test_rb_pair);
	ADD_TEST(testlist, test_rb_pair_const);
	ADD_TEST(testlist, test_rb_single_element);
	ADD_TEST(testlist, test_rb_two_elements);
	ADD_TEST(testlist, test_rb_ascending_insert);
	ADD_TEST(testlist, test_rb_recoloring_insert);
	ADD_TEST(testlist, test_rb_begin);
	ADD_TEST(testlist, test_rb_end);
	ADD_TEST(testlist, test_rb_dec);
	ADD_TEST(testlist, test_rb_inc);
	ADD_TEST(testlist, test_rb_size);
	ADD_TEST(testlist, test_rb_size_low_high_med);
	ADD_TEST(testlist, test_rb_four_chars);

	ADD_TEST(testlist, test_rb_playground);
}
#endif
