#include "main.hpp"

bool VERBOSE;

int	main(int argc, char **argv)
{
	if (!argc || !argv)
		return (0);

	VERBOSE = false;
	bool		runAll(true);

	FRAMEWORK_NAMESPACE::vector<Test2> tests;
	add_test_vector_int_suite(&tests);
	add_test_iterator_suite(&tests);
	add_test_vector_string_suite(&tests);

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
				RUN_TEST(tests, i);
				runAll = false;
			}
			else
			{
				if (!VERBOSE)
				{
					std::cout << "VERBOSE MODE" << std::endl;
					VERBOSE = true;
				}
			}
			++argNumber;
		}
	}
	if (!runAll)
		return(0);

	RUN_ALL_TESTS(&tests);
	return (0);
}
