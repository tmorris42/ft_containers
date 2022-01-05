#include "main.hpp"

void	example3(UnitTest *test)
{
	std::string	output;

	test->stdout_redirect();
	std::cout << "Running" << std::endl;
	output = test->stdout_restore();
	test->ASSERT_EQUAL(output, "Running\n");
}

int	main(int argc, char **argv)
{
	if (!argc || !argv)
		return (0);

	INIT;
	ADD_TEST_SUITE(add_test_vector_suite);
	ADD_TEST_SUITE(add_test_iterator_suite);

	bool		runAll(true);

	if (argc > 1)
	{
		int argNumber = 1;
		while (argNumber < argc)
		{
			std::stringstream intValue(argv[argNumber]);
			int i;
			intValue >> i;
			if (i > 0)
			{
				RUN_TEST(i - 1);
				runAll = false;
			}
			else
			{
				std::cout << "VERBOSE MODE" << std::endl;
				SET_VERBOSITY(true);
			}
			++argNumber;
		}
	}
	if (!runAll)
		return(0);

	RUN_ALL_TESTS();
	REPORT();
	return (0);
}
