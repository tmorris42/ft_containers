#include "UnitTest.hpp"

UnitTest::UnitTest() : stdout_buffer(NULL), buffer(), verbose(false), testsRun(), testsFailed(), testsPassed(), tests()
{
	return ;
}

UnitTest::UnitTest(bool verbosity) : stdout_buffer(NULL), buffer(), verbose(verbosity), testsRun(), testsFailed(), testsPassed(), tests()
{
	return ;
}

UnitTest::UnitTest(UnitTest const & src) : stdout_buffer(NULL), buffer(NULL), verbose(src.verbose), testsRun(), testsFailed(), testsPassed(), tests()
{
	*this = src;
	return ;
}

UnitTest::~UnitTest()
{
	// this->tests.resize(0);
	return ;
}

UnitTest const &	UnitTest::operator=(UnitTest const & rhs)
{
	if (this != &rhs)
	{
		this->stdout_buffer = rhs.stdout_buffer;
	}
	return (*this);
}

void	UnitTest::stdout_redirect()
{
    this->stdout_buffer = std::cout.rdbuf(this->buffer.rdbuf());
}

std::string UnitTest::stdout_restore()
{
    std::cout.rdbuf( this->stdout_buffer );
    std::string output = this->buffer.str();
    buffer.str("");
    buffer.clear();
    if (this->verbose)
        std::cout << output << std::endl;
    return (output);
}

void	UnitTest::run(void (*test_case)(UnitTest *self))
{
	++testsRun;
	std::cout << "Running test #" << this->testsRun << ": ";
	try
	{
		test_case(this);
		std::cout << "\x1B[32mPASS\x1B[m";
		++testsPassed;
	}
	catch(const std::exception& e)
	{
		std::cout << "\x1B[31mFAIL\x1B[m";
		if (this->verbose)
			std::cout << " -- " << e.what();
		++testsFailed;
	}	
	std::cout << std::endl;
}

void	UnitTest::run(void (*test_case)(UnitTest *self), std::string const & title)
{
	++testsRun;
	std::cout << "Test #" << this->testsRun << " - " << title << ": ";
	try
	{
		test_case(this);
		std::cout << "\x1B[32mPASS\x1B[m";
		++testsPassed;
	}
	catch(const std::exception& e)
	{
		std::cout << "\x1B[31mFAIL\x1B[m";
		if (this->verbose)
			std::cout << " -- " << e.what();
		++testsFailed;
	}	
	std::cout << std::endl;
}

void	UnitTest::run(Test test)
{
	++testsRun;
	std::cout << "Test #" << test.id << "(" << this->testsRun << "/\?\?) - " << test.desc << " : ";
	try
	{
		test.func(this);
		if (this->verbose)
			std::cout << std::endl;
		std::cout << "\x1B[32mPASS\x1B[m";
		++testsPassed;
	}
	catch(const std::exception& e)
	{
		if (this->verbose)
			std::cout << std::endl;
		std::cout << "\x1B[31mFAIL\x1B[m";
		if (this->verbose)
			std::cout << " -- " << e.what();
		++testsFailed;
	}	
	std::cout << std::endl;
}

void	UnitTest::run(unsigned int id)
{
	if (id < this->tests.size())
	{
		this->run(this->tests[id]);
	}
	else
	{
		std::cout << "No test with id == " << id + 1 << std::endl;
	}
}

double	UnitTest::report()
{
	double	score;

	std::cout << std::endl << "Ran " << this->testsRun << " test";
	if (this->testsRun == 0 || this->testsRun > 1)
		std::cout << "s";
	std::cout << std::endl;
	std::cout << "Passed: \x1B[32m" << this->testsPassed << "\x1B[m" << std::endl;
	std::cout << "Failed: \x1B[31m" << this->testsFailed << "\x1B[m" << std::endl;
	score = static_cast<double>(this->testsPassed) / static_cast<double>(this->testsRun);
	std::cout << "Score: " << score * 100.0 << "%" << std::endl;
	return (score);
}

void		UnitTest::set_verbosity(bool verbosity)
{
	this->verbose = verbosity;
}

bool		UnitTest::get_verbosity()
{
	return (this->verbose);
}

bool		UnitTest::add_test(TestFunction function, std::string description)
{
	Test newTest;
	newTest.desc = description;
	newTest.func = function;
	newTest.id = this->tests.size() + 1;
	this->tests.push_back(newTest);
	return (true);
}

void		UnitTest::run_all_tests()
{
	for (ft::vector<Test>::iterator it = this->tests.begin(); it != this->tests.end(); ++it)
	{
		this->run(*it);
	}
}
