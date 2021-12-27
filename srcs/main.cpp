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

void	test_vector_count_value_constructor(UnitTest *test)
{
	ft::vector<int> Vec(5, 42);

	test->assertEqual(Vec.size(), (unsigned long)5);
	test->assertEqual(Vec.empty(), false);
	test->assertEqual(Vec.capacity(), (unsigned long)5);
	test->assertEqual(Vec[0], 42);
	test->assertEqual(Vec[1], 42);
	test->assertEqual(Vec[2], 42);
	test->assertEqual(Vec[3], 42);
	test->assertEqual(Vec[4], 42);
}

void	test_vector_copy_constructor(UnitTest *test)
{
	ft::vector<int> original(5, 42);
	ft::vector<int> Vec(original);

	test->assertEqual(Vec.size(), (unsigned long)5);
	test->assertEqual(Vec.empty(), false);
	test->assertEqual(Vec.capacity(), (unsigned long)5);
	test->assertEqual(Vec[0], 42);
	test->assertEqual(Vec[1], 42);
	test->assertEqual(Vec[2], 42);
	test->assertEqual(Vec[3], 42);
	test->assertEqual(Vec[4], 42);
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

void	test_vector_insert(UnitTest *test)
{
	ft::vector<int> Vec;
	Vec.push_back(5);
	Vec.push_back(6);
	Vec.push_back(7);
	Vec.push_back(8);
	Vec.push_back(9);
	ft::vector<int>::iterator it = Vec.insert(Vec.begin() + 2, 42);
	test->assertEqual(*it, 42);
	test->assertEqual(Vec.size(), static_cast<unsigned int>(6));
	test->assertEqual(Vec.front(), 5);
	test->assertEqual(Vec.back(), 9);
	test->assertEqual(Vec[0], 5);
	test->assertEqual(Vec[1], 6);
	test->assertEqual(Vec[2], 42);
	test->assertEqual(Vec[3], 7);
	test->assertEqual(Vec[4], 8);
	test->assertEqual(Vec[5], 9);
	it = Vec.insert(Vec.end(), 21);
	test->assertEqual(*it, 21);
	test->assertEqual(Vec.size(), static_cast<unsigned int>(7));
	test->assertEqual(Vec[6], 21);
	test->assertEqual(Vec.capacity(), static_cast<unsigned int>(8));
	it = Vec.insert(Vec.end(), 21);
	it = Vec.insert(Vec.end(), 21);
	test->assertEqual(Vec.capacity(), static_cast<unsigned int>(16));
	test->assertEqual(Vec[0], 5);
	test->assertEqual(Vec[1], 6);
	test->assertEqual(Vec[2], 42);
	test->assertEqual(Vec[3], 7);
	test->assertEqual(Vec[4], 8);
	test->assertEqual(Vec[5], 9);
	test->assertEqual(Vec[6], 21);
	test->assertEqual(Vec[7], 21);
	test->assertEqual(Vec[8], 21);
}

void	test_vector_insert_count(UnitTest *test)
{
	ft::vector<int> Vec;
	Vec.push_back(5);
	Vec.push_back(6);
	Vec.push_back(7);
	Vec.push_back(8);
	Vec.push_back(9);
	Vec.insert(Vec.begin() + 2, (std::size_t)10, 42);
	test->assertEqual(Vec.size(), static_cast<unsigned int>(15));
	test->assertEqual(Vec.front(), 5);
	test->assertEqual(Vec.back(), 9);
	test->assertEqual(Vec[0], 5);
	test->assertEqual(Vec[1], 6);
	test->assertEqual(Vec[2], 42);
	test->assertEqual(Vec[3], 42);
	test->assertEqual(Vec[4], 42);
	test->assertEqual(Vec[5], 42);
	test->assertEqual(Vec[6], 42);
	test->assertEqual(Vec[7], 42);
	test->assertEqual(Vec[8], 42);
	test->assertEqual(Vec[9], 42);
	test->assertEqual(Vec[10], 42);
	test->assertEqual(Vec[11], 42);
	test->assertEqual(Vec[12], 7);
	test->assertEqual(Vec[13], 8);
	test->assertEqual(Vec[14], 9);
	Vec.insert(Vec.begin(), (std::size_t)10, 500);
	test->assertEqual(Vec.size(), static_cast<unsigned int>(25));
	test->assertEqual(Vec[0], 500);
	test->assertEqual(Vec[1], 500);
	test->assertEqual(Vec[2], 500);
	test->assertEqual(Vec[3], 500);
	test->assertEqual(Vec[4], 500);
	test->assertEqual(Vec[5], 500);
	test->assertEqual(Vec[6], 500);
	test->assertEqual(Vec[7], 500);
	test->assertEqual(Vec[8], 500);
	test->assertEqual(Vec[9], 500);
	test->assertEqual(Vec[10], 5);
	test->assertEqual(Vec[11], 6);
	test->assertEqual(Vec[12], 42);
	test->assertEqual(Vec[13], 42);
	test->assertEqual(Vec[14], 42);
	test->assertEqual(Vec[15], 42);
	test->assertEqual(Vec[16], 42);
	test->assertEqual(Vec[17], 42);
	test->assertEqual(Vec[18], 42);
	test->assertEqual(Vec[19], 42);
	test->assertEqual(Vec[20], 42);
	test->assertEqual(Vec[21], 42);
	test->assertEqual(Vec[22], 7);
	test->assertEqual(Vec[23], 8);
	test->assertEqual(Vec[24], 9);
	Vec.insert(Vec.end(), (std::size_t)10, 1000);
	test->assertEqual(Vec.size(), static_cast<unsigned int>(35));
	test->assertEqual(Vec[0], 500);
	test->assertEqual(Vec[1], 500);
	test->assertEqual(Vec[2], 500);
	test->assertEqual(Vec[3], 500);
	test->assertEqual(Vec[4], 500);
	test->assertEqual(Vec[5], 500);
	test->assertEqual(Vec[6], 500);
	test->assertEqual(Vec[7], 500);
	test->assertEqual(Vec[8], 500);
	test->assertEqual(Vec[9], 500);
	test->assertEqual(Vec[10], 5);
	test->assertEqual(Vec[11], 6);
	test->assertEqual(Vec[12], 42);
	test->assertEqual(Vec[13], 42);
	test->assertEqual(Vec[14], 42);
	test->assertEqual(Vec[15], 42);
	test->assertEqual(Vec[16], 42);
	test->assertEqual(Vec[17], 42);
	test->assertEqual(Vec[18], 42);
	test->assertEqual(Vec[19], 42);
	test->assertEqual(Vec[20], 42);
	test->assertEqual(Vec[21], 42);
	test->assertEqual(Vec[22], 7);
	test->assertEqual(Vec[23], 8);
	test->assertEqual(Vec[24], 9);
	test->assertEqual(Vec[25], 1000);
	test->assertEqual(Vec[26], 1000);
	test->assertEqual(Vec[27], 1000);
	test->assertEqual(Vec[28], 1000);
	test->assertEqual(Vec[29], 1000);
	test->assertEqual(Vec[30], 1000);
	test->assertEqual(Vec[31], 1000);
	test->assertEqual(Vec[32], 1000);
	test->assertEqual(Vec[33], 1000);
	test->assertEqual(Vec[34], 1000);
}

void	test_vector_insert_iter(UnitTest *test)
{
	ft::vector<int> Vec;
	ft::vector<int> vec2;

	Vec.push_back(5);
	Vec.push_back(6);
	Vec.push_back(7);
	Vec.push_back(8);
	Vec.push_back(9);
	Vec.insert(Vec.begin() + 2, (std::size_t)10, 42);
	test->assertEqual(Vec.size(), static_cast<unsigned int>(15));
	test->assertEqual(Vec.front(), 5);
	test->assertEqual(Vec.back(), 9);
	test->assertEqual(Vec[0], 5);
	test->assertEqual(Vec[1], 6);
	test->assertEqual(Vec[2], 42);
	test->assertEqual(Vec[3], 42);
	test->assertEqual(Vec[4], 42);
	test->assertEqual(Vec[5], 42);
	test->assertEqual(Vec[6], 42);
	test->assertEqual(Vec[7], 42);
	test->assertEqual(Vec[8], 42);
	test->assertEqual(Vec[9], 42);
	test->assertEqual(Vec[10], 42);
	test->assertEqual(Vec[11], 42);
	test->assertEqual(Vec[12], 7);
	test->assertEqual(Vec[13], 8);
	test->assertEqual(Vec[14], 9);
	Vec.insert(Vec.begin(), (std::size_t)10, 500);
	test->assertEqual(Vec.size(), static_cast<unsigned int>(25));
	test->assertEqual(Vec[0], 500);
	test->assertEqual(Vec[1], 500);
	test->assertEqual(Vec[2], 500);
	test->assertEqual(Vec[3], 500);
	test->assertEqual(Vec[4], 500);
	test->assertEqual(Vec[5], 500);
	test->assertEqual(Vec[6], 500);
	test->assertEqual(Vec[7], 500);
	test->assertEqual(Vec[8], 500);
	test->assertEqual(Vec[9], 500);
	test->assertEqual(Vec[10], 5);
	test->assertEqual(Vec[11], 6);
	test->assertEqual(Vec[12], 42);
	test->assertEqual(Vec[13], 42);
	test->assertEqual(Vec[14], 42);
	test->assertEqual(Vec[15], 42);
	test->assertEqual(Vec[16], 42);
	test->assertEqual(Vec[17], 42);
	test->assertEqual(Vec[18], 42);
	test->assertEqual(Vec[19], 42);
	test->assertEqual(Vec[20], 42);
	test->assertEqual(Vec[21], 42);
	test->assertEqual(Vec[22], 7);
	test->assertEqual(Vec[23], 8);
	test->assertEqual(Vec[24], 9);
	Vec.insert(Vec.end(), (std::size_t)10, 1000);
	test->assertEqual(Vec.size(), static_cast<unsigned int>(35));
	test->assertEqual(Vec[0], 500);
	test->assertEqual(Vec[1], 500);
	test->assertEqual(Vec[2], 500);
	test->assertEqual(Vec[3], 500);
	test->assertEqual(Vec[4], 500);
	test->assertEqual(Vec[5], 500);
	test->assertEqual(Vec[6], 500);
	test->assertEqual(Vec[7], 500);
	test->assertEqual(Vec[8], 500);
	test->assertEqual(Vec[9], 500);
	test->assertEqual(Vec[10], 5);
	test->assertEqual(Vec[11], 6);
	test->assertEqual(Vec[12], 42);
	test->assertEqual(Vec[13], 42);
	test->assertEqual(Vec[14], 42);
	test->assertEqual(Vec[15], 42);
	test->assertEqual(Vec[16], 42);
	test->assertEqual(Vec[17], 42);
	test->assertEqual(Vec[18], 42);
	test->assertEqual(Vec[19], 42);
	test->assertEqual(Vec[20], 42);
	test->assertEqual(Vec[21], 42);
	test->assertEqual(Vec[22], 7);
	test->assertEqual(Vec[23], 8);
	test->assertEqual(Vec[24], 9);
	test->assertEqual(Vec[25], 1000);
	test->assertEqual(Vec[26], 1000);
	test->assertEqual(Vec[27], 1000);
	test->assertEqual(Vec[28], 1000);
	test->assertEqual(Vec[29], 1000);
	test->assertEqual(Vec[30], 1000);
	test->assertEqual(Vec[31], 1000);
	test->assertEqual(Vec[32], 1000);
	test->assertEqual(Vec[33], 1000);
	test->assertEqual(Vec[34], 1000);

	// vec2.push_back(-1);
	vec2.insert(vec2.begin(), Vec.begin(), Vec.end());
	// test->assertEqual(vec2, Vec); // == not implemented yet
	test->assertEqual(vec2.size(), Vec.size());
	test->assertEqual(*(vec2.begin()), *(Vec.begin()));
	test->assertEqual(*(vec2.end() - 1), *(Vec.end() - 1));
}

void	test_vector_clear(UnitTest *test)
{
	ft::vector<int> vec(5, 42);

	test->assertEqual(vec.size(), static_cast<unsigned int>(5));
	unsigned long original_cap = vec.capacity();
	vec.clear();
	test->assertEqual(vec.capacity(), original_cap);
	test->assertEqual(vec.size(), static_cast<unsigned int>(0));
}

void	test_vector_erase_one(UnitTest *test)
{
	ft::vector<int> vec(5, 42);

	test->assertEqual(vec.size(), static_cast<unsigned int>(5));
	unsigned long original_cap = vec.capacity();
	vec.erase(vec.begin()+2);
	test->assertEqual(vec.capacity(), original_cap);
	test->assertEqual(vec.size(), static_cast<unsigned int>(4));
}

void	test_vector_erase_range(UnitTest *test)
{
	ft::vector<int> vec;

	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	vec.push_back(5);
	vec.push_back(6);
	vec.push_back(7);
	vec.push_back(8);
	vec.push_back(9);
	vec.push_back(10);

	test->assertEqual(vec.size(), static_cast<unsigned int>(10));
	unsigned long original_cap = vec.capacity();
	vec.erase(vec.begin()+2, vec.begin()+6);
	test->assertEqual(vec.capacity(), original_cap);
	test->assertEqual(vec.size(), static_cast<unsigned int>(6));
	test->assertEqual(vec.at(1), 2);
	test->assertEqual(vec.at(2), 7);
	test->assertEqual(vec.at(3), 8);
	test->assertEqual(vec.at(4), 9);
	test->assertEqual(vec.at(5), 10);
}

void	test_vector_pop_back(UnitTest *test)
{
	ft::vector<int> vec;

	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	vec.push_back(5);
	vec.push_back(6);
	vec.push_back(7);
	vec.push_back(8);
	vec.push_back(9);
	vec.push_back(10);

	test->assertEqual(vec.size(), static_cast<unsigned int>(10));
	unsigned long original_cap = vec.capacity();
	ft::vector<int>::iterator end = vec.end();
	int count = 0;
	for (ft::vector<int>::iterator it = vec.begin(); it != end; ++it)
	{
		test->assertEqual(*it, count + 1);
		++count;
	}
	test->assertEqual(count, 10);
	vec.pop_back();
	vec.pop_back();
	end = vec.end();
	count = 0;
	for (ft::vector<int>::iterator it = vec.begin(); it != end; ++it)
	{
		test->assertEqual(*it, count + 1);
		++count;
	}
	test->assertEqual(count, 8);
	test->assertEqual(vec.capacity(), original_cap);
	test->assertEqual(vec.size(), static_cast<unsigned int>(8));
}

void	test_vector_resize(UnitTest *test)
{
	ft::vector<int> vec;

	vec.push_back(0);
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	vec.push_back(5);
	vec.push_back(6);
	vec.push_back(7);
	vec.push_back(8);
	vec.push_back(9);

	test->assertEqual(vec.size(), static_cast<unsigned int>(10));
	unsigned long original_cap = vec.capacity();
	ft::vector<int>::iterator end = vec.end();
	int count = 0;
	for (ft::vector<int>::iterator it = vec.begin(); it != end; ++it)
	{
		test->assertEqual(*it, count);
		++count;
	}
	test->assertEqual(count, 10);
	vec.resize(8);
	end = vec.end();
	count = 0;
	for (ft::vector<int>::iterator it = vec.begin(); it != end; ++it)
	{
		test->assertEqual(*it, count);
		++count;
	}
	test->assertEqual(count, 8);
	test->assertEqual(vec.capacity(), original_cap);
	test->assertEqual(vec.size(), static_cast<unsigned int>(8));
	vec.resize(15, 42);
	end = vec.end();
	count = 0;
	for (ft::vector<int>::iterator it = vec.begin(); it != end; ++it)
	{
		if (count < 8)
			test->assertEqual(*it, count);
		else
			test->assertEqual(*it, 42);
		++count;
	}
	test->assertEqual(count, 15);
	test->assertEqual(vec.capacity(), original_cap);
	test->assertEqual(vec.size(), static_cast<unsigned int>(15));
	
}


int	main(int argc, char **argv)
{
	if (!argc || !argv)
		return (0);

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
		// test_vector_at,	// Causes differences in allocations due to stringstream use in vector::at()
		test_vector_operater_bracket,
		test_vector_capacity,
		test_vector_capacity_cppref,
		// test_vector_max_size,	// Difference in allocations and max_size
		test_vector_reserve,
		test_vector_count_value_constructor,	
		test_vector_copy_constructor,	// Segfault
		// test_vector_insert,
		// test_vector_insert_count,
		// test_vector_insert_iter,
		test_vector_clear,
		test_vector_erase_one,
		test_vector_erase_range,
		test_vector_pop_back,
		test_vector_resize,
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
		// "test_vector_at",
		"test_vector_operater_bracket",
		"test_vector_capacity",
		"test_vector_capacity_cppref",
		// "test_vector_max_size",
		"test_vector_reserve",
		"test_vector_count_value_constructor",
		"test_vector_copy_constructor",
		// "test_vector_insert",
		// "test_vector_insert_count",
		// "test_vector_insert_iter",
		"test_vector_clear",
		"test_vector_erase_one",
		"test_vector_erase_range",
		"test_vector_pop_back",
		"test_vector_resize",
	};

	UnitTest	test(false);
	bool		runAll(true);

	if (argc > 1)
	{
		int argNumber = 1;
		while (argNumber < argc)
		{
			std::stringstream intValue(argv[argNumber]);
			int i;
			intValue >> i;
			if (i > 0)
			{
				test.run(tests[i - 1], desc[i - 1]);
				runAll = false;
			}
			else
			{
				std::cout << "VERBOSE MODE" << std::endl;
				test.set_verbosity(true);
			}
			++argNumber;
		}
	}
	if (!runAll)
		return(0);

	

	for (int i = 0; tests[i]; ++i)
	{
		test.run(tests[i], desc[i]);
	}

	test.report();
	return (0);
}
