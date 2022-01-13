#include "UnitTest.hpp"

void load_test(FRAMEWORK_NAMESPACE::vector<Test2> *testlist,
			   TestFunction2 function, std::string description)
{
	// std::cout << "Adding test (" << description << ")" << std::endl;
	Test2 newTest;
	newTest.desc = description;
	newTest.func = function;
	newTest.id = testlist->size();
	newTest.status = 0;
	testlist->push_back(newTest);
	// std::cout << "Tests added so far: " << testlist->size() << std::endl;
}

void print_test_results(Test2 *test)
{
	std::cout << "#" << test->id << ": " << test->desc << ": ";
	if (WIFEXITED(test->status) && !WEXITSTATUS(test->status))
	{
		std::cout << "\x1B[32mOK\x1B[m";
		// ++ut_tests_passed;
	}
	else
	{
		std::cout << "\x1B[31m";
		if (WIFSIGNALED(test->status))
		{
			switch (WTERMSIG(test->status))
			{
			case SIGSEGV:
				std::cout << "SIGSEGV";
				break;
			default:
				std::cout << "SIGNAL";
			}
		}
		else
			std::cout << "KO";
		std::cout << "\x1B[m";
	}
	std::cout << std::endl;
}

int launch_test(FRAMEWORK_NAMESPACE::vector<Test2> *testlist, Test2 *test)
{
	TestFunction2 func = test->func;
	pid_t pid;

	pid = fork();
	if (pid < 0)
	{
		//error
	}
	else if (!pid)
	{
		//child
		testlist->~vector();
		try
		{
			exit(func());
		}
		catch (std::exception)
		{
			exit(-1);
		}
	}
	else
	{
		//parent
		waitpid(pid, &(test->status), 0);
		print_test_results(test);
		return (-1 * (!WIFEXITED(test->status) || WEXITSTATUS(test->status)));
	}
	return (0);
}

int launch_all_tests(FRAMEWORK_NAMESPACE::vector<Test2> *testlist)
{
	int success;
	int total;
	FRAMEWORK_NAMESPACE::vector<Test2>::iterator it;
	FRAMEWORK_NAMESPACE::vector<Test2>::iterator ite;

	success = 0;
	total = 0;
	it = testlist->begin();
	ite = testlist->end();
	while (it != ite)
	{
		++total;
		success += (launch_test(testlist, &(*it)) == 0);
		++it;
	}
	if (success == total)
		std::cout << "\x1B[32m" << std::endl;
	else
		std::cout << "\x1B[31m" << std::endl;
	std::cout << success << "/" << total << " passed"
			  << "\x1B[m" << std::endl;
	return (0);
}
