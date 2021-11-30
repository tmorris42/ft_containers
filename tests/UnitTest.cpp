#include "UnitTest.hpp"

UnitTest::UnitTest() : stdout_buffer(NULL), buffer(), verbose(false), testsRun(), testsFailed(), testsPassed()
{
	return ;
}

UnitTest::UnitTest(bool verbosity) : stdout_buffer(NULL), buffer(), verbose(verbosity), testsRun(), testsFailed(), testsPassed()
{
	return ;
}

UnitTest::UnitTest(UnitTest const & src) : stdout_buffer(NULL), buffer(NULL), verbose(src.verbose), testsRun(), testsFailed(), testsPassed()
{
	*this = src;
	return ;
}

UnitTest::~UnitTest()
{
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

void	UnitTest::run(void (*f)(UnitTest *self))
{
	++testsRun;
	std::cout << "Running test #" << this->testsRun << ": ";
	try
	{
		f(this);
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

double	UnitTest::report()
{
	std::cout << std::endl << "Ran " << this->testsRun << " test";
	if (this->testsRun == 0 || this->testsRun > 1)
		std::cout << "s";
	std::cout << std::endl;
	std::cout << "Passed: \x1B[32m" << this->testsPassed << "\x1B[m" << std::endl;
	std::cout << "Failed: \x1B[31m" << this->testsFailed << "\x1B[m" << std::endl;
	return (static_cast<double>(this->testsPassed) / static_cast<double>(this->testsRun));
}
