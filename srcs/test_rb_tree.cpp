#include "tests.hpp"

template <class T>
void printBT(const std::string& prefix, const ft::Node<T>* node, bool isLeft)
{
    if(node)
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

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
	printBT(&rb);
	return (0);
}

void	add_test_rb_tree_suite(FRAMEWORK_NAMESPACE::vector<Test2> *testlist)
{
	ADD_TEST(testlist, test_rb_tree_void_constructor);
	ADD_TEST(testlist, test_rb_tree_insert);
}
