#include "UnitTest.hpp"

void	stdout_redirect(std::streambuf **stdout_buffer, std::stringstream *buffer )
{
    *stdout_buffer = std::cout.rdbuf(buffer->rdbuf());
}

std::string stdout_restore( std::streambuf * stdout_buffer, std::stringstream *buffer, bool verbose )
{
    std::cout.rdbuf( stdout_buffer );
    std::string output = buffer->str();
    buffer->str("");
    buffer->clear();
    if (verbose)
        std::cout << output;
    return (output);
}

void	stderr_redirect(std::streambuf **stderr_buffer, std::stringstream *buffer )
{
    *stderr_buffer = std::cerr.rdbuf(buffer->rdbuf());
}

std::string stderr_restore( std::streambuf * stderr_buffer, std::stringstream *buffer, bool verbose )
{
    std::cerr.rdbuf( stderr_buffer );
    std::string output = buffer->str();
    buffer->str("");
    buffer->clear();
    if (verbose)
        std::cerr << output;
    return (output);
}

void load_test(FRAMEWORK_NAMESPACE::vector<Test2> *testlist,
			   TestFunction2 function, std::string description)
{
	// std::cout << "Adding test (" << description << ")" << std::endl;
	Test2 newTest;
	newTest.desc = description;
	newTest.func = function;
	newTest.id = testlist->size() + 1;
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

int launch_test(FRAMEWORK_NAMESPACE::vector<Test2> *testlist, Test2 *test, bool verbose)
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
		int	ret;
		std::streambuf *stdout_buffer = NULL;
		std::stringstream	buffer;
		std::string			output;
		std::streambuf *stderr_buffer = NULL;
		std::stringstream	err_buffer;
		std::string			errput;
		#ifdef FT_REAL_VERSION
		std::ofstream outfile(("logs/" + test->desc + ".std.out.log").c_str());
		std::ofstream errfile(("logs/" + test->desc + ".std.err.log").c_str());
		#else
		std::ofstream outfile(("logs/" + test->desc + ".ft.out.log").c_str());
		std::ofstream errfile(("logs/" + test->desc + ".ft.err.log").c_str());
		#endif
		testlist->~vector();
		try
		{
			stdout_redirect(&stdout_buffer, &buffer);
			stderr_redirect(&stderr_buffer, &err_buffer);
			ret = func();
			output = stdout_restore(stdout_buffer, &buffer, verbose);
			errput = stderr_restore(stderr_buffer, &err_buffer, verbose);
			outfile << output;
			errfile << errput;
			outfile.close();
			errfile.close();
			// delete stdout_buffer;
			exit(ret);
		}
		catch (std::exception & e)
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

int launch_all_tests(FRAMEWORK_NAMESPACE::vector<Test2> *testlist, bool verbose)
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
		success += (launch_test(testlist, &(*it), verbose) == 0);
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
