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

void	add_test_rb_tree_suite(FRAMEWORK_NAMESPACE::vector<Test2> *testlist)
{
	ADD_TEST(testlist, test_rb_tree_void_constructor);
	ADD_TEST(testlist, test_rb_tree_insert);
	ADD_TEST(testlist, test_rb_tree_delete);
	ADD_TEST(testlist, test_rb_pair);
	ADD_TEST(testlist, test_rb_pair_const);

	ADD_TEST(testlist, test_rb_playground);
}
