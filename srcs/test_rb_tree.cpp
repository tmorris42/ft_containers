#include "tests.hpp"

template <class T1, class T2>
std::ostream & 	operator<<(std::ostream & os, FT::pair<T1, T2> p)
{
	os << "Pair<" << p.first << ", " << p.second << ">" << std::endl;
	return (os);
}

template <class T>
void printBT(const std::string& prefix, const ft::Node<T>* node, bool isLeft)
{
    if(node)
    {
        std::cout << prefix;
        std::cout << (isLeft ? "├──" : "└──" );

		if (node->color == RB_RED)
			std::cout << "R:";
		else
			std::cout << "B:";
        // print the value of the node
        std::cout << node->value << std::endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "│   " : "    "), node->left, true);
        printBT( prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}
template <class T>
void printBT(const ft::RB_Tree<T>* tree)
{
    printBT("", tree->root, false);    
}

int	test_rb_tree_void_constructor()
{
	ft::RB_Tree<int> rb;

	ASSERT_EQUAL(rb.search(5), (ft::Node<int>*)NULL);
	return (0);
}

int test_rb_tree_insert()
{
	ft::RB_Tree<int> rb;

	rb.insert(6);
	rb.insert(5);
	rb.insert(7);
	ASSERT_EQUAL(rb.search(5)->value, 5);
	ASSERT_EQUAL(rb.search(6)->value, 6);
	ASSERT_EQUAL(rb.search(7)->value, 7);
	ASSERT_EQUAL(rb.search(8), (ft::Node<int>*)NULL);
	// printBT(&rb);
	return (0);
}

int test_rb_tree_delete()
{
	ft::RB_Tree<int> rb;

	rb.insert(6);
	rb.insert(5);
	rb.insert(7);
	rb.insert(10);
	rb.insert(9);
	rb.insert(4);
	// printBT(&rb);
	ASSERT_EQUAL(rb.search(7)->value, 7);
	rb.delete_node(rb.root, 7);
	ASSERT_EQUAL(rb.search(7), (ft::Node<int>*)NULL);

	// printBT(&rb);

	rb.delete_tree(rb.root);
	return (0);
}

int test_rb_pair()
{
	ft::RB_Tree< FT::pair<char, int> >	rb;

	FT::pair<char, int>	p1('a', 10);
	FT::pair<char, int>	p2('b', 20);
	rb.insert(p1);
	rb.insert(p2);
	printBT(&rb);
	return (0);
}

int test_rb_pair_const()
{
	ft::RB_Tree< FT::pair<const char, int> >	rb;

	FT::pair<const char, int>	p1('a', 10);
	FT::pair<const char, int>	p2('b', 20);
	rb.insert(p1);
	rb.insert(p2);
	printBT(&rb);
	return (0);
}

int test_rb_playground()
{
	ft::RB_Tree<int> rb;

	rb.insert(6);
	rb.insert(5);
	rb.insert(7);
	rb.insert(10);
	rb.insert(9);
	rb.insert(4);
	printBT(&rb);

	rb.delete_node(rb.root, 7);

	printBT(&rb);

	rb.delete_tree(rb.root);
	return (0);
}

int test_rb_single_element()
{
	ft::RB_Tree<int> rb;

	rb.insert(5);
	ASSERT_EQUAL(rb.root->color, RB_BLACK);
	ASSERT_EQUAL(rb.root->value, 5);
	return (0);
}

int test_rb_two_elements()
{
	ft::RB_Tree<int>	rb;
	void				*nptr = NULL;

	rb.insert(5);
	ASSERT_EQUAL(rb.root->color, RB_BLACK);
	ASSERT_EQUAL(rb.root->value, 5);
	rb.insert(8);
	ASSERT_EQUAL(rb.root->color, RB_BLACK);
	ASSERT_EQUAL(rb.root->value, 5);
	ASSERT_EQUAL(rb.root->left, nptr);
	ASSERT_EQUAL(rb.root->right->color, RB_RED);
	ASSERT_EQUAL(rb.root->right->value, 8);

	return (0);
}

int test_rb_ascending_insert()
{
	ft::RB_Tree<int>	rb;
	void				*nptr = NULL;

	rb.insert(5);
	ASSERT_EQUAL(rb.root->color, RB_BLACK);
	ASSERT_EQUAL(rb.root->value, 5);
	rb.insert(8);
	ASSERT_EQUAL(rb.root->color, RB_BLACK);
	ASSERT_EQUAL(rb.root->value, 5);
	ASSERT_EQUAL(rb.root->left, nptr);
	ASSERT_EQUAL(rb.root->right->color, RB_RED);
	ASSERT_EQUAL(rb.root->right->value, 8);
	rb.insert(10);
	ASSERT_EQUAL(rb.root->color, RB_BLACK);
	ASSERT_EQUAL(rb.root->value, 8);
	ASSERT_EQUAL(rb.root->left->color, RB_RED);
	ASSERT_EQUAL(rb.root->left->value, 5);
	ASSERT_EQUAL(rb.root->right->color, RB_RED);
	ASSERT_EQUAL(rb.root->right->value, 10);
	return (0);
}

int test_rb_recoloring_insert()
{
	ft::RB_Tree<int>	rb;
	void				*nptr = NULL;

	rb.insert(5);
	ASSERT_EQUAL(rb.root->color, RB_BLACK);
	ASSERT_EQUAL(rb.root->value, 5);
	rb.insert(8);
	ASSERT_EQUAL(rb.root->color, RB_BLACK);
	ASSERT_EQUAL(rb.root->value, 5);
	ASSERT_EQUAL(rb.root->left, nptr);
	ASSERT_EQUAL(rb.root->right->color, RB_RED);
	ASSERT_EQUAL(rb.root->right->value, 8);
	rb.insert(4);
	ASSERT_EQUAL(rb.root->color, RB_BLACK);
	ASSERT_EQUAL(rb.root->value, 5);
	ASSERT_EQUAL(rb.root->left->color, RB_RED);
	ASSERT_EQUAL(rb.root->left->value, 4);
	ASSERT_EQUAL(rb.root->right->color, RB_RED);
	ASSERT_EQUAL(rb.root->right->value, 8);
	rb.insert(11);
	ASSERT_EQUAL(rb.root->color, RB_BLACK);
	ASSERT_EQUAL(rb.root->value, 5);
	ASSERT_EQUAL(rb.root->left->color, RB_BLACK);
	ASSERT_EQUAL(rb.root->left->value, 4);
	ASSERT_EQUAL(rb.root->right->color, RB_BLACK);
	ASSERT_EQUAL(rb.root->right->value, 8);
	ASSERT_EQUAL(rb.root->right->right->color, RB_RED);
	ASSERT_EQUAL(rb.root->right->right->value, 11);
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

	// ADD_TEST(testlist, test_rb_playground);
}
