#ifndef UNIT_TEST_HPP
# define UNIT_TEST_HPP

# include <iostream>
# include <sstream>

# define NAMESPACE std
 // SHOULD USE MY VERSION!!! ******IMPORTANT******

# ifdef FT_REAL_VERSION
#  include <map>
#  include <stack>
#  include <vector>
   namespace ft = std;
# else
// #  "map.hpp"
	// #include "stack.hpp"
 #  include "vector.hpp"
 # include <vector>
# endif

# define INIT UnitTest	ut_test(false)
# define ADD_TEST(func) ut_test.add_test(func, #func)
# define SET_VERBOSITY(verbosity) ut_test.set_verbosity(verbosity)
# define RUN_TEST(index) ut_test.run(index)
# define RUN_ALL_TESTS ut_test.run_all_tests
# define REPORT ut_test.report
# define ASSERT_EQUAL(a, b) assertEqual(a, b, #a, #b)
# define ASSERT_ERROR(operation) {try {operation; throw std::runtime_error("Error: no exception thrown");} catch(const std::exception& e) {std::cerr << e.what() << std::endl;}}
# define ASSERT_NO_ERROR(operation) {try {operation;} catch(const std::exception& e) {std::cerr << e.what() << std::endl; throw std::runtime_error("Error: exception occurred");}}

class UnitTest;
typedef void (*TestFunction)(UnitTest*);

struct Test
{
	std::string	desc;
	int			id;
	TestFunction	func;
};

class UnitTest
{
	private:
		std::streambuf		*stdout_buffer;
		std::stringstream	buffer;
		bool				verbose;
		unsigned int		testsRun;
		unsigned int		testsFailed;
		unsigned int		testsPassed;
		NAMESPACE::vector<Test>	tests;

	public:
		UnitTest();
		UnitTest(bool verbosity);
		UnitTest(UnitTest const & src);
		virtual ~UnitTest();
		UnitTest const &	operator=(UnitTest const & rhs);
		void		run(void (*f)(UnitTest *self));
		void		run(Test test);
		void		run(void (*f)(UnitTest *self), std::string const & title);
		void		run(unsigned int id);
		double		report();
		void		stdout_redirect();
		std::string	stdout_restore();
		void		set_verbosity(bool verbosity);
		bool		get_verbosity();
		bool		add_test(TestFunction function, std::string description);
		void		run_all_tests();
		
		
		template < typename T, typename U >
		bool		assertEqual(T a, U b)
		{
			if (this->verbose)
				std::cout << "checking: " << a << " == " << b << std::endl;
			if (a != b)
				throw std::runtime_error("Error: arguments are not equal");
			else
				return true;
		}

		template < typename T, typename U >
		bool		assertEqual(T a, U b, std::string aName, std::string bName)
		{
			if (this->verbose)
				std::cout << std::endl << "checking: " << aName << "[ " << a << " ] == " << bName << "[ " << b << " ]";
			if (a != b)
				throw std::runtime_error("Error: arguments are not equal");
			else
				return true;
		}
};

#endif
