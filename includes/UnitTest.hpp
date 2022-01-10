#ifndef UNIT_TEST_HPP
# define UNIT_TEST_HPP

# include <iostream>
# include <sstream>

# include <sys/types.h> //	waitpid, fork
# include <sys/wait.h>	//	waitpid
# include <unistd.h> 	//	fork
# include <stdlib.h>	// exit

# define FRAMEWORK_NAMESPACE std
 // SHOULD USE MY VERSION!!! ******IMPORTANT******

# ifdef FT_REAL_VERSION
#  include <map>
#  include <stack>
#  include <vector>
#  define FT std
# else
// #  "map.hpp"
	// #include "stack.hpp"
 #  include "vector.hpp"
 # include <vector>
 # define FT ft
# endif

extern bool VERBOSE;

# define ADD_TEST(testlist, func)	load_test(testlist, func, #func)
# define RUN_ALL_TESTS(testlist) launch_all_tests(testlist)
# define ASSERT_EQUAL(a, b) assertEqual(a, b, #a, #b)
# define ASSERT_ERROR(operation) {try {operation; throw std::runtime_error("Error: no exception thrown");} catch(const std::exception& e) {std::cerr << e.what() << std::endl;}}
# define ASSERT_NO_ERROR(operation) {try {operation;} catch(const std::exception& e) {std::cerr << e.what() << std::endl; throw std::runtime_error("Error: exception occurred");}}

typedef int	(*TestFunction2)(void);
struct Test2
{
	std::string	desc;
	int			id;
	TestFunction2	func;
	int			status;
};

template < typename T, typename U >
bool		assertEqual(T a, U b, std::string aName, std::string bName)
{
	if (VERBOSE)
		std::cout << std::endl << "checking: " << aName << "[ " << a << " ] == " << bName << "[ " << b << " ]";
	if (a != b)
	{
		exit(-1);
	}
	else
		return true;
}

void	load_test(FRAMEWORK_NAMESPACE::vector<Test2> *testlist, TestFunction2 function, std::string description);
int		launch_all_tests(FRAMEWORK_NAMESPACE::vector<Test2> *testlist);

#endif
