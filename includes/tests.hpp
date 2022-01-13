#ifndef TESTS_HPP
# define TESTS_HPP

# include <iostream> // std::cout
# include <typeinfo> // typeid

# include "main.hpp"
# include "UnitTest.hpp"
// # include "vector.hpp"

void	add_test_iterator_suite(FRAMEWORK_NAMESPACE::vector<Test2> *testlist);
void	add_test_vector_class_suite(FRAMEWORK_NAMESPACE::vector<Test2> *testlist);
void	add_test_vector_int_suite(FRAMEWORK_NAMESPACE::vector<Test2> *testlist);
void	add_test_vector_string_suite(FRAMEWORK_NAMESPACE::vector<Test2> *testlist);
void	add_test_vector_struct_suite(FRAMEWORK_NAMESPACE::vector<Test2> *testlist);

void	add_test_stack_suite(FRAMEWORK_NAMESPACE::vector<Test2> *testlist);

void	add_test_rb_tree_suite(FRAMEWORK_NAMESPACE::vector<Test2> *testlist);

#endif
