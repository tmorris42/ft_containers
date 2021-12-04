#include "main.hpp"

void	example(UnitTest *self)
{
	int x = 1;

	self->assertEqual(x, 1);
	self->assertEqual(x, 2);
}

void	example2(UnitTest *self)
{
	std::string	output;

	self->stdout_redirect();
	std::cout << "Runni5ng" << std::endl;
	output = self->stdout_restore();

	// std::cout << "Output was: " << output;
	self->assertEqual(output, "Running\n");
}

void	example3(UnitTest *self)
{
	std::string	output;

	self->stdout_redirect();
	std::cout << "Running" << std::endl;
	output = self->stdout_restore();

	// std::cout << "Output was: " << output;
	self->assertEqual(output, "Running\n");
}

int	main()
{
	// std::string	output;
	UnitTest	test;
	double		score;

	// test.stdout_redirect();
	// std::cout << "Runni5ng" << std::endl;
	// output = test.stdout_restore();

	// std::cout << "Output was: " << output;
	// test.assertEqual(output, std::string("Running\n"));
	// if (output.compare("Running\n") == 0)
	// 	std::cout << "as expected!" << std::endl;


	test.run(example);
	test.run(example2);
	test.run(example3);
	score = test.report();
	// example(&test);
	std::cout << "Score: " << score << "%" << std::endl;

	return (0);
}
