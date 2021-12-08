#include "main.hpp"

void	example3(UnitTest *test)
{
	std::string	output;

	test->stdout_redirect();
	std::cout << "Running" << std::endl;
	output = test->stdout_restore();
	test->assertEqual(output, "Running\n");
}

void	test_vector_void_constructor(UnitTest *test)
{
	ft::vector<int> Vec;

	test->assertEqual(Vec.size(), (unsigned long)0);
	test->assertEqual(Vec.empty(), true);
	test->assertEqual(Vec.capacity(), (unsigned long)0);
}

void	test_vector_push_back(UnitTest *test)
{
	// test->assertEqual()
	ft::vector<int> Vec;
	Vec.push_back(5);
	test->assertEqual(Vec.size(), static_cast<unsigned int>(1));
	test->assertEqual(Vec.front(), 5);
}

void	test_vector_push_back_twice(UnitTest *test)
{
	// test->assertEqual()
	ft::vector<int> Vec;
	Vec.push_back(5);
	test->assertEqual(Vec.size(), static_cast<unsigned int>(1));
	Vec.push_back(6);
	test->assertEqual(Vec.size(), static_cast<unsigned int>(2));
	test->assertEqual(Vec.front(), 5);
	test->assertEqual(Vec.back(), 6);
}

void	test_vector_push_back_thrice(UnitTest *test)
{
	// test->assertEqual()
	ft::vector<int> Vec;
	Vec.push_back(5);
	test->assertEqual(Vec.size(), static_cast<unsigned int>(1));
	Vec.push_back(6);
	test->assertEqual(Vec.size(), static_cast<unsigned int>(2));
	Vec.push_back(7);
	test->assertEqual(Vec.size(), static_cast<unsigned int>(3));
	test->assertEqual(Vec.front(), 5);
	test->assertEqual(Vec.back(), 7);
}

void	test_vector_push_back_x4(UnitTest *test)
{
	ft::vector<int> Vec;
	Vec.push_back(5);
	Vec.push_back(6);
	Vec.push_back(7);
	Vec.push_back(8);
	test->assertEqual(Vec.size(), static_cast<unsigned int>(4));
	test->assertEqual(Vec.front(), 5);
	test->assertEqual(Vec.back(), 8);
}

void	test_vector_push_back_x5(UnitTest *test)
{
	ft::vector<int> Vec;
	Vec.push_back(5);
	Vec.push_back(6);
	Vec.push_back(7);
	Vec.push_back(8);
	Vec.push_back(9);
	test->assertEqual(Vec.size(), static_cast<unsigned int>(5));
	test->assertEqual(Vec.front(), 5);
	test->assertEqual(Vec.back(), 9);
}

void	test_vector_push_back_x15(UnitTest *test)
{
	ft::vector<int> Vec;
	Vec.push_back(5);
	Vec.push_back(6);
	Vec.push_back(7);
	Vec.push_back(8);
	Vec.push_back(9);
	Vec.push_back(5);
	Vec.push_back(6);
	Vec.push_back(7);
	Vec.push_back(8);
	Vec.push_back(9);
	Vec.push_back(5);
	Vec.push_back(6);
	Vec.push_back(7);
	Vec.push_back(8);
	Vec.push_back(42);
	test->assertEqual(Vec.size(), static_cast<unsigned int>(15));
	test->assertEqual(Vec.front(), 5);
	test->assertEqual(Vec.back(), 42);
}

void	test_vector_empty(UnitTest *test)
{
	ft::vector<int> Vec;
	test->assertEqual(Vec.empty(), true);
	Vec.push_back(1);
	test->assertEqual(Vec.empty(), false);
	// Vec.pop_back()
	// test->assertEqual(Vec.empty(), true);
}

void	test_vector_iterator_forward(UnitTest *test)
{
	ft::vector<int> Vec;
	Vec.push_back(0);
	Vec.push_back(1);
	Vec.push_back(2);
	Vec.push_back(3);
	Vec.push_back(4);
	ft::vector<int>::iterator it = Vec.begin();
	ft::vector<int>::iterator ite = Vec.end();
	while (it != ite)
	{
		test->assertEqual((*it), it - Vec.begin());
		++it;
	}
}

void	test_vector_at(UnitTest *test)
{
	ft::vector<int> Vec;
	Vec.push_back(0);
	Vec.push_back(1);
	Vec.push_back(2);
	Vec.push_back(3);
	Vec.push_back(4);
	ft::vector<int>::reference ref = Vec.at(2);
	ft::vector<int>::const_reference cref = Vec.at(4);
	test->assertEqual(ref, 2);
	test->assertEqual(cref, 4);
	try
	{
		Vec.at(9);
		throw std::runtime_error("Expected Exception not thrown");
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	try
	{
		Vec.at(-1);
		throw std::runtime_error("Expected Exception not thrown");
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}	
}

void	test_vector_operater_bracket(UnitTest *test)
{
	ft::vector<int> Vec;
	Vec.push_back(0);
	Vec.push_back(1);
	Vec.push_back(2);
	Vec.push_back(3);
	Vec.push_back(4);
	ft::vector<int>::reference ref = Vec[2];
	ft::vector<int>::const_reference cref = Vec[4];
	test->assertEqual(ref, 2);
	test->assertEqual(cref, 4);
	try
	{
		Vec[9];
		throw std::runtime_error("No exception thrown");
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	try
	{
		Vec[-1];
		throw std::runtime_error("No exception thrown");
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}	
}

void	test_vector_capacity(UnitTest *test)
{
	ft::vector<int> Vec;
	test->assertEqual(Vec.capacity(), (unsigned long)(0));
	Vec.push_back(5);
	test->assertEqual(Vec.capacity(), (unsigned long)1);
	Vec.push_back(6);
	test->assertEqual(Vec.capacity(), (unsigned long)2);
	Vec.push_back(7);
	test->assertEqual(Vec.capacity(), (unsigned long)4);
	Vec.push_back(8);
	test->assertEqual(Vec.capacity(), (unsigned long)4);
	Vec.push_back(9);
	test->assertEqual(Vec.capacity(), (unsigned long)8);
	Vec.push_back(5);
	test->assertEqual(Vec.capacity(), (unsigned long)8);
	Vec.push_back(6);
	test->assertEqual(Vec.capacity(), (unsigned long)8);
	Vec.push_back(7);
	test->assertEqual(Vec.capacity(), (unsigned long)8);
	Vec.push_back(8);
	test->assertEqual(Vec.capacity(), (unsigned long)16);
	Vec.push_back(9);
	test->assertEqual(Vec.capacity(), (unsigned long)16);
	Vec.push_back(5);
	test->assertEqual(Vec.capacity(), (unsigned long)16);
	Vec.push_back(6);
	test->assertEqual(Vec.capacity(), (unsigned long)16);
	Vec.push_back(7);
	test->assertEqual(Vec.capacity(), (unsigned long)16);
	Vec.push_back(8);
	test->assertEqual(Vec.capacity(), (unsigned long)16);
	Vec.push_back(42);
	test->assertEqual(Vec.capacity(), (unsigned long)16);
}

void	test_vector_capacity_cppref(UnitTest *test)
{
	int sz = 200;
    ft::vector<int> v1;
 
 	test->stdout_redirect();

    unsigned long cap = v1.capacity();
    std::cout << "initial capacity=" << cap << '\n';
 
    for (int n = 0; n < sz; ++n) {
        v1.push_back(n);
        if (cap != v1.capacity()) {
            cap = v1.capacity();
            std::cout << "new capacity=" << cap << '\n';
        }
    }
 
    std::cout << "final size=" << v1.size() << '\n';
    std::cout << "final capacity=" << v1.capacity() << '\n';

	std::string output = test->stdout_restore();
	test->assertEqual(output, "initial capacity=0\nnew capacity=1\nnew capacity=2\nnew capacity=4\nnew capacity=8\nnew capacity=16\nnew capacity=32\nnew capacity=64\nnew capacity=128\nnew capacity=256\nfinal size=200\nfinal capacity=256\n");
}

void	test_vector_max_size(UnitTest *test)
{
	ft::vector<int> Vec;
	
	// test->assertEqual(Vec.max_size(), (unsigned long)2305843009213693951);
	test->assertEqual(Vec.max_size(), (unsigned long)9223372036854775807);
}

void	test_vector_reserve(UnitTest *test)
{
	ft::vector<int> Vec;
	
	// test->assertEqual(Vec.max_size(), (unsigned long)2305843009213693951);
	test->assertEqual(Vec.capacity(), (unsigned long)0);
	Vec.reserve(200);
	test->assertEqual(Vec.capacity(), (unsigned long)200);
	Vec.reserve(100);
	test->assertEqual(Vec.capacity(), (unsigned long)200);
	Vec.reserve(2220);
	test->assertEqual(Vec.capacity(), (unsigned long)2220);
}

int	main(int argc, char **argv)
{
	#ifndef FT_REAL_VERSION//CREATE A REAL STL EXAMPLE
		// #include "map.hpp"
		// #include "stack.hpp"
		// std::cout << "Mine" << std::endl;
	#else
		// std::cout << "Real" << std::endl;
		#include <map>
		#include <stack>
		#include <vector>
		namespace ft = std;
	#endif

	if (!argc || !argv)
		return (0);

	UnitTest	test(false);
	if (argc > 1)
	{
		std::cout << "VERBOSE MODE" << std::endl;
		test.set_verbosity(true);
	}

	void (*tests[])(UnitTest*) = {
		test_vector_void_constructor,
		test_vector_push_back,
		test_vector_push_back_twice,
		test_vector_push_back_thrice,
		test_vector_push_back_x4,
		test_vector_push_back_x5,
		test_vector_push_back_x15,
		test_vector_empty,
		test_vector_iterator_forward,
		test_vector_at,
		test_vector_operater_bracket,
		test_vector_capacity,
		test_vector_capacity_cppref,
		// test_vector_max_size,
		test_vector_reserve,
		NULL
		};

	std::string	desc[] = {
		"Test vector<int>()",
		"Test vector<int>.push_back()",
		"test_vector_push_back_twice",
		"test_vector_push_back_thrice",
		"test_vector_push_back_x4",
		"test_vector_push_back_x5",
		"test_vector_push_back_x15",
		"test_vector_empty",
		"test_vector_iterator_forward",
		"test_vector_at",
		"test_vector_operater_bracket",
		"test_vector_capacity",
		"test_vector_capacity_cppref",
		// "test_vector_max_size",
		"test_vector_reserve",
	};

	for (int i = 0; tests[i]; ++i)
	{
		test.run(tests[i], desc[i]);
	}

	test.report();
	return (0);
}
