#include "main.hpp"

void	example(UnitTest *test)
{
	int x = 1;

	test->assertEqual(x, 1);
	test->assertEqual(x, 2);
}

void	example2(UnitTest *test)
{
	std::string	output;

	test->stdout_redirect();
	std::cout << "Runni5ng" << std::endl;
	output = test->stdout_restore();

	// std::cout << "Output was: " << output;
	test->assertEqual(output, "Running\n");
}

void	example3(UnitTest *test)
{
	std::string	output;

	test->stdout_redirect();
	std::cout << "Running" << std::endl;
	output = test->stdout_restore();

	// std::cout << "Output was: " << output;
	test->assertEqual(output, "Running\n");
}

void	test_vector_void_constructor(UnitTest *test)
{
	// test->assertEqual()
	ft::vector<int> Vec;

	// test->assertEqual(Vec.size(), static_cast<unsigned int>(0));
	test->assertEqual(0, 0);
}

void	test_vector_push_back(UnitTest *test)
{
	// test->assertEqual()
	ft::vector<int> Vec;
	Vec.push_back(5);
	test->assertEqual(Vec.size(), static_cast<unsigned int>(1));
	test->assertEqual(Vec.front(), 5);
}

void	test_vector_push_back_twice(UnitTest *test)
{
	// test->assertEqual()
	ft::vector<int> Vec;
	Vec.push_back(5);
	test->assertEqual(Vec.size(), static_cast<unsigned int>(1));
	Vec.push_back(6);
	test->assertEqual(Vec.size(), static_cast<unsigned int>(2));
	test->assertEqual(Vec.front(), 5);
	test->assertEqual(Vec.back(), 6);
}

int	main(int argc, char **argv)
{
	#ifndef FT_REAL_VERSION//CREATE A REAL STL EXAMPLE
		// #include "map.hpp"
		// #include "stack.hpp"
		// std::cout << "Mine" << std::endl;
	#else
		// std::cout << "Real" << std::endl;
		#include <map>
		#include <stack>
		#include <vector>
		namespace ft = std;
	#endif

	// std::string	output;
	if (!argc || !argv)
		return (0);

	UnitTest	test(false);
	if (argc > 1)
	{
		std::cout << "VERBOSE MODE" << std::endl;
		test.set_verbosity(true);
	}

	// test.stdout_redirect();
	// std::cout << "Runni5ng" << std::endl;
	// output = test.stdout_restore();

	// std::cout << "Output was: " << output;
	// test.assertEqual(output, std::string("Running\n"));
	// if (output.compare("Running\n") == 0)
	// 	std::cout << "as expected!" << std::endl;

	// test.verbose = true;

	test.run(test_vector_void_constructor, "Test vector<int>()");
	test.run(test_vector_push_back, "Test vector<int>.push_back()");
	test.run(test_vector_push_back_twice, "test_vector_push_back_twice");
	
	// test.run(example2);
	// test.run(example3);
	test.report();
	// example(&test);
	return (0);
}
