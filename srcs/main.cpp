#include "main.hpp"

bool VERBOSE;

int	main(int argc, char **argv)
{
	if (!argc || !argv)
		return (0);
	if (argc > 1)
		VERBOSE = true;
	else
		VERBOSE = false;

	FRAMEWORK_NAMESPACE::vector<Test2> tests;
	add_test_vector_suite(&tests);
	add_test_iterator_suite(&tests);

	RUN_ALL_TESTS(&tests);
	return (0);
}
