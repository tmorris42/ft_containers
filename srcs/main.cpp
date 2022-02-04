#include <algorithm>

#include "main.hpp"

bool VERBOSE;

static bool checkArgument(char **begin, char **end, std::string const & option)
{
	return (std::find(begin, end, option) != end);
}

int	main(int argc, char **argv)
{
	if (!argc || !argv)
		return (0);
	VERBOSE = false;
	FRAMEWORK_NAMESPACE::vector<Test2> tests;

	if (checkArgument(argv, argv + argc, "-v"))
	{
		std::cout << "VERBOSE MODE" << std::endl;
		VERBOSE = true;
	}
	bool		runAll = true;

	add_test_vector_int_suite(&tests);
	add_test_iterator_suite(&tests);
	add_test_vector_string_suite(&tests);
	add_test_vector_struct_suite(&tests);
	add_test_vector_class_suite(&tests);

	add_test_stack_suite(&tests);

	add_test_map_suite(&tests);

	#ifndef FT_REAL_VERSION
		if (checkArgument(argv, argv + argc, "-s"))
	{	
		std::cout << "INCLUDING SPECIAL TESTS" << std::endl;
		add_test_rb_tree_suite(&tests);
	}
	#endif

	if (argc > 1)
	{
		int argNumber = 1;
		while (argNumber < argc)
		{
			std::stringstream intValue(argv[argNumber]);
			unsigned int i;
			intValue >> i;
			if (i > 0 && (unsigned int)i <= tests.size())
			{
				RUN_TEST(tests, i - 1);
				runAll = false;
			}
			++argNumber;
		}
	}
	if (!runAll)
		return(0);

	RUN_ALL_TESTS(&tests);
	return (0);
}
