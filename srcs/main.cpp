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

int	main()
{
	// std::string	output;
	UnitTest	test(false);
	double		score;

	// test.stdout_redirect();
	// std::cout << "Runni5ng" << std::endl;
	// output = test.stdout_restore();

	// std::cout << "Output was: " << output;
	// test.assertEqual(output, std::string("Running\n"));
	// if (output.compare("Running\n") == 0)
	// 	std::cout << "as expected!" << std::endl;

	// test.verbose = true;

	test.run(example);
	test.run(example2);
	test.run(example3);
	score = test.report();
	// example(&test);
	std::cout << "Score: " << score << "%" << std::endl;

	return (0);
}
