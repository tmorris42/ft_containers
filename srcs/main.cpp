#include <algorithm>

#include "main.hpp"

bool VERBOSE;

static bool checkArgument(char **begin, char **end, std::string const &option)
{
	return (std::find(begin, end, option) != end);
}

int main(int argc, char **argv)
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
	bool runAll = true;
	bool addAll = true;

	if (checkArgument(argv, argv + argc, "vector") ||
		checkArgument(argv, argv + argc, "stack") ||
		checkArgument(argv, argv + argc, "map") ||
		checkArgument(argv, argv + argc, "set") ||
		checkArgument(argv, argv + argc, "rb"))
	{
		addAll = false;
	}

	if (checkArgument(argv, argv + argc, "vector") || addAll)
	{
		add_test_vector_int_suite(&tests);
		add_test_iterator_suite(&tests);
		add_test_vector_string_suite(&tests);
		add_test_vector_struct_suite(&tests);
		add_test_vector_class_suite(&tests);
	}

	if (checkArgument(argv, argv + argc, "stack") || addAll)
	{
		add_test_stack_suite(&tests);
	}

	if (checkArgument(argv, argv + argc, "map") || addAll)
	{
		add_test_map_suite(&tests);
	}

	if (checkArgument(argv, argv + argc, "set") || addAll)
	{
		add_test_set_suite(&tests);
	}

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
		return (0);

	RUN_ALL_TESTS(&tests);
	return (0);
}
