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
	add_test_vector_struct_suite(&tests);
	add_test_vector_class_suite(&tests);

	add_test_stack_suite(&tests);

	add_test_rb_tree_suite(&tests);

	if (argc > 1)
	{
		int argNumber = 1;
		while (argNumber < argc)
		{
			std::stringstream intValue(argv[argNumber]);
			int i;
			intValue >> i;
			if (i > 0 && (unsigned int)i <= tests.size())
			{
				RUN_TEST(tests, i - 1);
				runAll = false;
			}
			else
			{
				if (!VERBOSE && !std::strcmp(argv[argNumber], "-v"))
				{
					std::cout << "VERBOSE MODE" << std::endl;
					VERBOSE = true;
				}
				else
					std::cout << "ERROR: test #" << i << " not found." << std::endl;
			}
			++argNumber;
		}
	}
	if (!runAll)
		return(0);

	RUN_ALL_TESTS(&tests);
	return (0);
}
