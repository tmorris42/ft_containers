#ifndef UNIT_TEST_HPP
# define UNIT_TEST_HPP

# include <iostream>
# include <sstream>

class UnitTest
{
	private:
		std::streambuf		*stdout_buffer;
		std::stringstream	buffer;
		bool				verbose;
		unsigned int		testsRun;
		unsigned int		testsFailed;
		unsigned int		testsPassed;

	public:
		UnitTest();
		UnitTest(bool verbosity);
		UnitTest(UnitTest const & src);
		virtual ~UnitTest();
		UnitTest const &	operator=(UnitTest const & rhs);
		void		run(void (*f)(UnitTest *self));
		void		run(void (*f)(UnitTest *self), std::string const & title);
		double		report();
		void		stdout_redirect();
		std::string	stdout_restore();
		
		
		template < typename T, typename U >
		bool		assertEqual(T a, U b)
		{
			if (this->verbose)
				std::cout << "checking: " << a << " = " << b << std::endl;
			if (a != b)
				throw std::runtime_error("Error: arguments are not equal");
			else
				return true;
		}
};

#endif
