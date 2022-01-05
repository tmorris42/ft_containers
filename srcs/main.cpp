#include "main.hpp"

void	example3(UnitTest *test)
{
	std::string	output;

	test->stdout_redirect();
	std::cout << "Running" << std::endl;
	output = test->stdout_restore();
	test->ASSERT_EQUAL(output, "Running\n");
}

void	test_vector_void_constructor(UnitTest *test)
{
	ft::vector<int> Vec;

	test->ASSERT_EQUAL(Vec.size(), (unsigned long)0);
	test->ASSERT_EQUAL(Vec.empty(), true);
	test->ASSERT_EQUAL(Vec.capacity(), (unsigned long)0);
}

void	test_vector_count_value_constructor(UnitTest *test)
{
	ft::vector<int> Vec(5, 42);

	test->ASSERT_EQUAL(Vec.size(), (unsigned long)5);
	test->ASSERT_EQUAL(Vec.empty(), false);
	test->ASSERT_EQUAL(Vec.capacity(), (unsigned long)5);
	test->ASSERT_EQUAL(Vec[0], 42);
	test->ASSERT_EQUAL(Vec[1], 42);
	test->ASSERT_EQUAL(Vec[2], 42);
	test->ASSERT_EQUAL(Vec[3], 42);
	test->ASSERT_EQUAL(Vec[4], 42);
}

void	test_vector_copy_constructor(UnitTest *test)
{
	ft::vector<int> original(5, 42);
	ft::vector<int> Vec(original);

	test->ASSERT_EQUAL(Vec.size(), original.size());
	test->ASSERT_EQUAL(Vec.empty(), false);
	test->ASSERT_EQUAL(Vec.capacity(), original.capacity());
	test->ASSERT_EQUAL(Vec[0], 42);
	test->ASSERT_EQUAL(Vec[1], 42);
	test->ASSERT_EQUAL(Vec[2], 42);
	test->ASSERT_EQUAL(Vec[3], 42);
	test->ASSERT_EQUAL(Vec[4], 42);
}

void	test_vector_iter_constructor(UnitTest *test)
{
	ft::vector<int> original(5, 42);
	ft::vector<int> Vec(original.begin(), original.end());

	test->ASSERT_EQUAL(Vec.size(), original.size());
	test->ASSERT_EQUAL(Vec.empty(), false);
	test->ASSERT_EQUAL(Vec.capacity(), original.capacity());
	test->ASSERT_EQUAL(Vec[0], 42);
	test->ASSERT_EQUAL(Vec[1], 42);
	test->ASSERT_EQUAL(Vec[2], 42);
	test->ASSERT_EQUAL(Vec[3], 42);
	test->ASSERT_EQUAL(Vec[4], 42);
}

void	test_vector_push_back(UnitTest *test)
{
	// test->ASSERT_EQUAL()
	ft::vector<int> Vec;
	Vec.push_back(5);
	test->ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(1));
	test->ASSERT_EQUAL(Vec.front(), 5);
}

void	test_vector_push_back_twice(UnitTest *test)
{
	// test->ASSERT_EQUAL()
	ft::vector<int> Vec;
	Vec.push_back(5);
	test->ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(1));
	Vec.push_back(6);
	test->ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(2));
	test->ASSERT_EQUAL(Vec.front(), 5);
	test->ASSERT_EQUAL(Vec.back(), 6);
}

void	test_vector_push_back_thrice(UnitTest *test)
{
	// test->ASSERT_EQUAL()
	ft::vector<int> Vec;
	Vec.push_back(5);
	test->ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(1));
	Vec.push_back(6);
	test->ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(2));
	Vec.push_back(7);
	test->ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(3));
	test->ASSERT_EQUAL(Vec.front(), 5);
	test->ASSERT_EQUAL(Vec.back(), 7);
}

void	test_vector_push_back_x4(UnitTest *test)
{
	ft::vector<int> Vec;
	Vec.push_back(5);
	Vec.push_back(6);
	Vec.push_back(7);
	Vec.push_back(8);
	test->ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(4));
	test->ASSERT_EQUAL(Vec.front(), 5);
	test->ASSERT_EQUAL(Vec.back(), 8);
}

void	test_vector_push_back_x5(UnitTest *test)
{
	ft::vector<int> Vec;
	Vec.push_back(5);
	Vec.push_back(6);
	Vec.push_back(7);
	Vec.push_back(8);
	Vec.push_back(9);
	test->ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(5));
	test->ASSERT_EQUAL(Vec.front(), 5);
	test->ASSERT_EQUAL(Vec.back(), 9);
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
	test->ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(15));
	test->ASSERT_EQUAL(Vec.front(), 5);
	test->ASSERT_EQUAL(Vec.back(), 42);
}

void	test_vector_empty(UnitTest *test)
{
	ft::vector<int> Vec;
	test->ASSERT_EQUAL(Vec.empty(), true);
	Vec.push_back(1);
	test->ASSERT_EQUAL(Vec.empty(), false);
	// Vec.pop_back()
	// test->ASSERT_EQUAL(Vec.empty(), true);
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
		test->ASSERT_EQUAL((*it), it - Vec.begin());
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
	test->ASSERT_EQUAL(ref, 2);
	test->ASSERT_EQUAL(cref, 4);
	ASSERT_ERROR(Vec.at(9))
	ASSERT_ERROR(Vec.at(-1))
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
	test->ASSERT_EQUAL(ref, 2);
	test->ASSERT_EQUAL(cref, 4);
	ASSERT_NO_ERROR(Vec[9])
	ASSERT_NO_ERROR(Vec[-1])
}

void	test_vector_capacity(UnitTest *test)
{
	ft::vector<int> Vec;
	test->ASSERT_EQUAL(Vec.capacity(), (unsigned long)(0));
	Vec.push_back(5);
	test->ASSERT_EQUAL(Vec.capacity(), (unsigned long)1);
	Vec.push_back(6);
	test->ASSERT_EQUAL(Vec.capacity(), (unsigned long)2);
	Vec.push_back(7);
	test->ASSERT_EQUAL(Vec.capacity(), (unsigned long)4);
	Vec.push_back(8);
	test->ASSERT_EQUAL(Vec.capacity(), (unsigned long)4);
	Vec.push_back(9);
	test->ASSERT_EQUAL(Vec.capacity(), (unsigned long)8);
	Vec.push_back(5);
	test->ASSERT_EQUAL(Vec.capacity(), (unsigned long)8);
	Vec.push_back(6);
	test->ASSERT_EQUAL(Vec.capacity(), (unsigned long)8);
	Vec.push_back(7);
	test->ASSERT_EQUAL(Vec.capacity(), (unsigned long)8);
	Vec.push_back(8);
	test->ASSERT_EQUAL(Vec.capacity(), (unsigned long)16);
	Vec.push_back(9);
	test->ASSERT_EQUAL(Vec.capacity(), (unsigned long)16);
	Vec.push_back(5);
	test->ASSERT_EQUAL(Vec.capacity(), (unsigned long)16);
	Vec.push_back(6);
	test->ASSERT_EQUAL(Vec.capacity(), (unsigned long)16);
	Vec.push_back(7);
	test->ASSERT_EQUAL(Vec.capacity(), (unsigned long)16);
	Vec.push_back(8);
	test->ASSERT_EQUAL(Vec.capacity(), (unsigned long)16);
	Vec.push_back(42);
	test->ASSERT_EQUAL(Vec.capacity(), (unsigned long)16);
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
	test->ASSERT_EQUAL(output, "initial capacity=0\nnew capacity=1\nnew capacity=2\nnew capacity=4\nnew capacity=8\nnew capacity=16\nnew capacity=32\nnew capacity=64\nnew capacity=128\nnew capacity=256\nfinal size=200\nfinal capacity=256\n");
}

void	test_vector_max_size(UnitTest *test)
{
	ft::vector<int> Vec;
	
	test->ASSERT_EQUAL(Vec.max_size(), (unsigned long)2305843009213693951);
	// test->ASSERT_EQUAL(Vec.max_size(), (unsigned long)9223372036854775807);
}

void	test_vector_reserve(UnitTest *test)
{
	ft::vector<int> Vec;
	
	// test->ASSERT_EQUAL(Vec.max_size(), (unsigned long)2305843009213693951);
	test->ASSERT_EQUAL(Vec.capacity(), (unsigned long)0);
	Vec.reserve(200);
	test->ASSERT_EQUAL(Vec.capacity(), (unsigned long)200);
	Vec.reserve(100);
	test->ASSERT_EQUAL(Vec.capacity(), (unsigned long)200);
	Vec.reserve(2220);
	test->ASSERT_EQUAL(Vec.capacity(), (unsigned long)2220);
}

void	test_vector_reserve_overmax(UnitTest *test)
{
	ft::vector<int> Vec;
	
	// test->ASSERT_EQUAL(Vec.max_size(), (unsigned long)2305843009213693951);
	test->ASSERT_EQUAL(Vec.capacity(), (unsigned long)0);
	ASSERT_ERROR(	Vec.reserve(Vec.max_size() + 1) );
	test->ASSERT_EQUAL(Vec.capacity(), (unsigned long)0);
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
	test->ASSERT_EQUAL(*it, 42);
	test->ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(6));
	test->ASSERT_EQUAL(Vec.front(), 5);
	test->ASSERT_EQUAL(Vec.back(), 9);
	test->ASSERT_EQUAL(Vec[0], 5);
	test->ASSERT_EQUAL(Vec[1], 6);
	test->ASSERT_EQUAL(Vec[2], 42);
	test->ASSERT_EQUAL(Vec[3], 7);
	test->ASSERT_EQUAL(Vec[4], 8);
	test->ASSERT_EQUAL(Vec[5], 9);
	it = Vec.insert(Vec.end(), 21);
	test->ASSERT_EQUAL(*it, 21);
	test->ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(7));
	test->ASSERT_EQUAL(Vec[6], 21);
	test->ASSERT_EQUAL(Vec.capacity(), static_cast<unsigned int>(8));
	it = Vec.insert(Vec.end(), 21);
	it = Vec.insert(Vec.end(), 21);
	test->ASSERT_EQUAL(Vec.capacity(), static_cast<unsigned int>(16));
	test->ASSERT_EQUAL(Vec[0], 5);
	test->ASSERT_EQUAL(Vec[1], 6);
	test->ASSERT_EQUAL(Vec[2], 42);
	test->ASSERT_EQUAL(Vec[3], 7);
	test->ASSERT_EQUAL(Vec[4], 8);
	test->ASSERT_EQUAL(Vec[5], 9);
	test->ASSERT_EQUAL(Vec[6], 21);
	test->ASSERT_EQUAL(Vec[7], 21);
	test->ASSERT_EQUAL(Vec[8], 21);
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
	test->ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(15));
	test->ASSERT_EQUAL(Vec.capacity(), static_cast<unsigned int>(15));
	test->ASSERT_EQUAL(Vec.front(), 5);
	test->ASSERT_EQUAL(Vec.back(), 9);
	test->ASSERT_EQUAL(Vec[0], 5);
	test->ASSERT_EQUAL(Vec[1], 6);
	test->ASSERT_EQUAL(Vec[2], 42);
	test->ASSERT_EQUAL(Vec[3], 42);
	test->ASSERT_EQUAL(Vec[4], 42);
	test->ASSERT_EQUAL(Vec[5], 42);
	test->ASSERT_EQUAL(Vec[6], 42);
	test->ASSERT_EQUAL(Vec[7], 42);
	test->ASSERT_EQUAL(Vec[8], 42);
	test->ASSERT_EQUAL(Vec[9], 42);
	test->ASSERT_EQUAL(Vec[10], 42);
	test->ASSERT_EQUAL(Vec[11], 42);
	test->ASSERT_EQUAL(Vec[12], 7);
	test->ASSERT_EQUAL(Vec[13], 8);
	test->ASSERT_EQUAL(Vec[14], 9);
	Vec.insert(Vec.begin(), (std::size_t)10, 500);
	test->ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(25));
	test->ASSERT_EQUAL(Vec.capacity(), static_cast<unsigned int>(30));
	test->ASSERT_EQUAL(Vec[0], 500);
	test->ASSERT_EQUAL(Vec[1], 500);
	test->ASSERT_EQUAL(Vec[2], 500);
	test->ASSERT_EQUAL(Vec[3], 500);
	test->ASSERT_EQUAL(Vec[4], 500);
	test->ASSERT_EQUAL(Vec[5], 500);
	test->ASSERT_EQUAL(Vec[6], 500);
	test->ASSERT_EQUAL(Vec[7], 500);
	test->ASSERT_EQUAL(Vec[8], 500);
	test->ASSERT_EQUAL(Vec[9], 500);
	test->ASSERT_EQUAL(Vec[10], 5);
	test->ASSERT_EQUAL(Vec[11], 6);
	test->ASSERT_EQUAL(Vec[12], 42);
	test->ASSERT_EQUAL(Vec[13], 42);
	test->ASSERT_EQUAL(Vec[14], 42);
	test->ASSERT_EQUAL(Vec[15], 42);
	test->ASSERT_EQUAL(Vec[16], 42);
	test->ASSERT_EQUAL(Vec[17], 42);
	test->ASSERT_EQUAL(Vec[18], 42);
	test->ASSERT_EQUAL(Vec[19], 42);
	test->ASSERT_EQUAL(Vec[20], 42);
	test->ASSERT_EQUAL(Vec[21], 42);
	test->ASSERT_EQUAL(Vec[22], 7);
	test->ASSERT_EQUAL(Vec[23], 8);
	test->ASSERT_EQUAL(Vec[24], 9);
	Vec.insert(Vec.end(), (std::size_t)10, 1000);
	test->ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(35));
	test->ASSERT_EQUAL(Vec.capacity(), static_cast<unsigned int>(50));
	test->ASSERT_EQUAL(Vec[0], 500);
	test->ASSERT_EQUAL(Vec[1], 500);
	test->ASSERT_EQUAL(Vec[2], 500);
	test->ASSERT_EQUAL(Vec[3], 500);
	test->ASSERT_EQUAL(Vec[4], 500);
	test->ASSERT_EQUAL(Vec[5], 500);
	test->ASSERT_EQUAL(Vec[6], 500);
	test->ASSERT_EQUAL(Vec[7], 500);
	test->ASSERT_EQUAL(Vec[8], 500);
	test->ASSERT_EQUAL(Vec[9], 500);
	test->ASSERT_EQUAL(Vec[10], 5);
	test->ASSERT_EQUAL(Vec[11], 6);
	test->ASSERT_EQUAL(Vec[12], 42);
	test->ASSERT_EQUAL(Vec[13], 42);
	test->ASSERT_EQUAL(Vec[14], 42);
	test->ASSERT_EQUAL(Vec[15], 42);
	test->ASSERT_EQUAL(Vec[16], 42);
	test->ASSERT_EQUAL(Vec[17], 42);
	test->ASSERT_EQUAL(Vec[18], 42);
	test->ASSERT_EQUAL(Vec[19], 42);
	test->ASSERT_EQUAL(Vec[20], 42);
	test->ASSERT_EQUAL(Vec[21], 42);
	test->ASSERT_EQUAL(Vec[22], 7);
	test->ASSERT_EQUAL(Vec[23], 8);
	test->ASSERT_EQUAL(Vec[24], 9);
	test->ASSERT_EQUAL(Vec[25], 1000);
	test->ASSERT_EQUAL(Vec[26], 1000);
	test->ASSERT_EQUAL(Vec[27], 1000);
	test->ASSERT_EQUAL(Vec[28], 1000);
	test->ASSERT_EQUAL(Vec[29], 1000);
	test->ASSERT_EQUAL(Vec[30], 1000);
	test->ASSERT_EQUAL(Vec[31], 1000);
	test->ASSERT_EQUAL(Vec[32], 1000);
	test->ASSERT_EQUAL(Vec[33], 1000);
	test->ASSERT_EQUAL(Vec[34], 1000);
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
	test->ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(15));
	test->ASSERT_EQUAL(Vec.front(), 5);
	test->ASSERT_EQUAL(Vec.back(), 9);
	test->ASSERT_EQUAL(Vec[0], 5);
	test->ASSERT_EQUAL(Vec[1], 6);
	test->ASSERT_EQUAL(Vec[2], 42);
	test->ASSERT_EQUAL(Vec[3], 42);
	test->ASSERT_EQUAL(Vec[4], 42);
	test->ASSERT_EQUAL(Vec[5], 42);
	test->ASSERT_EQUAL(Vec[6], 42);
	test->ASSERT_EQUAL(Vec[7], 42);
	test->ASSERT_EQUAL(Vec[8], 42);
	test->ASSERT_EQUAL(Vec[9], 42);
	test->ASSERT_EQUAL(Vec[10], 42);
	test->ASSERT_EQUAL(Vec[11], 42);
	test->ASSERT_EQUAL(Vec[12], 7);
	test->ASSERT_EQUAL(Vec[13], 8);
	test->ASSERT_EQUAL(Vec[14], 9);
	Vec.insert(Vec.begin(), (std::size_t)10, 500);
	test->ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(25));
	test->ASSERT_EQUAL(Vec[0], 500);
	test->ASSERT_EQUAL(Vec[1], 500);
	test->ASSERT_EQUAL(Vec[2], 500);
	test->ASSERT_EQUAL(Vec[3], 500);
	test->ASSERT_EQUAL(Vec[4], 500);
	test->ASSERT_EQUAL(Vec[5], 500);
	test->ASSERT_EQUAL(Vec[6], 500);
	test->ASSERT_EQUAL(Vec[7], 500);
	test->ASSERT_EQUAL(Vec[8], 500);
	test->ASSERT_EQUAL(Vec[9], 500);
	test->ASSERT_EQUAL(Vec[10], 5);
	test->ASSERT_EQUAL(Vec[11], 6);
	test->ASSERT_EQUAL(Vec[12], 42);
	test->ASSERT_EQUAL(Vec[13], 42);
	test->ASSERT_EQUAL(Vec[14], 42);
	test->ASSERT_EQUAL(Vec[15], 42);
	test->ASSERT_EQUAL(Vec[16], 42);
	test->ASSERT_EQUAL(Vec[17], 42);
	test->ASSERT_EQUAL(Vec[18], 42);
	test->ASSERT_EQUAL(Vec[19], 42);
	test->ASSERT_EQUAL(Vec[20], 42);
	test->ASSERT_EQUAL(Vec[21], 42);
	test->ASSERT_EQUAL(Vec[22], 7);
	test->ASSERT_EQUAL(Vec[23], 8);
	test->ASSERT_EQUAL(Vec[24], 9);
	Vec.insert(Vec.end(), (std::size_t)10, 1000);
	test->ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(35));
	test->ASSERT_EQUAL(Vec[0], 500);
	test->ASSERT_EQUAL(Vec[1], 500);
	test->ASSERT_EQUAL(Vec[2], 500);
	test->ASSERT_EQUAL(Vec[3], 500);
	test->ASSERT_EQUAL(Vec[4], 500);
	test->ASSERT_EQUAL(Vec[5], 500);
	test->ASSERT_EQUAL(Vec[6], 500);
	test->ASSERT_EQUAL(Vec[7], 500);
	test->ASSERT_EQUAL(Vec[8], 500);
	test->ASSERT_EQUAL(Vec[9], 500);
	test->ASSERT_EQUAL(Vec[10], 5);
	test->ASSERT_EQUAL(Vec[11], 6);
	test->ASSERT_EQUAL(Vec[12], 42);
	test->ASSERT_EQUAL(Vec[13], 42);
	test->ASSERT_EQUAL(Vec[14], 42);
	test->ASSERT_EQUAL(Vec[15], 42);
	test->ASSERT_EQUAL(Vec[16], 42);
	test->ASSERT_EQUAL(Vec[17], 42);
	test->ASSERT_EQUAL(Vec[18], 42);
	test->ASSERT_EQUAL(Vec[19], 42);
	test->ASSERT_EQUAL(Vec[20], 42);
	test->ASSERT_EQUAL(Vec[21], 42);
	test->ASSERT_EQUAL(Vec[22], 7);
	test->ASSERT_EQUAL(Vec[23], 8);
	test->ASSERT_EQUAL(Vec[24], 9);
	test->ASSERT_EQUAL(Vec[25], 1000);
	test->ASSERT_EQUAL(Vec[26], 1000);
	test->ASSERT_EQUAL(Vec[27], 1000);
	test->ASSERT_EQUAL(Vec[28], 1000);
	test->ASSERT_EQUAL(Vec[29], 1000);
	test->ASSERT_EQUAL(Vec[30], 1000);
	test->ASSERT_EQUAL(Vec[31], 1000);
	test->ASSERT_EQUAL(Vec[32], 1000);
	test->ASSERT_EQUAL(Vec[33], 1000);
	test->ASSERT_EQUAL(Vec[34], 1000);

	// vec2.push_back(-1);
	vec2.insert(vec2.begin(), Vec.begin(), Vec.end());
	// test->ASSERT_EQUAL(vec2, Vec); // == not implemented yet
	test->ASSERT_EQUAL(vec2.size(), Vec.size());
	test->ASSERT_EQUAL(*(vec2.begin()), *(Vec.begin()));
	test->ASSERT_EQUAL(*(vec2.end() - 1), *(Vec.end() - 1));
}

void	test_vector_clear(UnitTest *test)
{
	ft::vector<int> vec(5, 42);

	test->ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(5));
	unsigned long original_cap = vec.capacity();
	vec.clear();
	test->ASSERT_EQUAL(vec.capacity(), original_cap);
	test->ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(0));
}

void	test_vector_assign(UnitTest *test)
{
	ft::vector<int> vec(5, 42);

	test->ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(5));
	unsigned long original_cap = vec.capacity();
	vec.clear();
	test->ASSERT_EQUAL(vec.capacity(), original_cap);
	test->ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(0));
	vec.assign(3, 15);
	test->ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(3));
	test->ASSERT_EQUAL(vec[2], 15);
	vec.assign(vec.begin(), vec.end() - 1);
	test->ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(2));
	test->ASSERT_EQUAL(vec[2], 15);

}

void	test_vector_erase_one(UnitTest *test)
{
	ft::vector<int> vec(5, 42);

	test->ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(5));
	unsigned long original_cap = vec.capacity();
	vec.erase(vec.begin()+2);
	test->ASSERT_EQUAL(vec.capacity(), original_cap);
	test->ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(4));
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

	test->ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(10));
	unsigned long original_cap = vec.capacity();
	ft::vector<int>::iterator ret = vec.erase(vec.begin()+2, vec.begin()+6);
	test->ASSERT_EQUAL(*ret, vec[2]);
	test->ASSERT_EQUAL(vec.capacity(), original_cap);
	test->ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(6));
	test->ASSERT_EQUAL(vec.at(1), 2);
	test->ASSERT_EQUAL(vec.at(2), 7);
	test->ASSERT_EQUAL(vec.at(3), 8);
	test->ASSERT_EQUAL(vec.at(4), 9);
	test->ASSERT_EQUAL(vec.at(5), 10);
	ret = vec.erase(vec.begin()+2, vec.end());
	test->ASSERT_EQUAL(*ret, *vec.end());
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

	test->ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(10));
	unsigned long original_cap = vec.capacity();
	ft::vector<int>::iterator end = vec.end();
	int count = 0;
	for (ft::vector<int>::iterator it = vec.begin(); it != end; ++it)
	{
		test->ASSERT_EQUAL(*it, count + 1);
		++count;
	}
	test->ASSERT_EQUAL(count, 10);
	vec.pop_back();
	vec.pop_back();
	end = vec.end();
	count = 0;
	for (ft::vector<int>::iterator it = vec.begin(); it != end; ++it)
	{
		test->ASSERT_EQUAL(*it, count + 1);
		++count;
	}
	test->ASSERT_EQUAL(count, 8);
	test->ASSERT_EQUAL(vec.capacity(), original_cap);
	test->ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(8));
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

	test->ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(10));
	unsigned long original_cap = vec.capacity();
	ft::vector<int>::iterator end = vec.end();
	int count = 0;
	for (ft::vector<int>::iterator it = vec.begin(); it != end; ++it)
	{
		test->ASSERT_EQUAL(*it, count);
		++count;
	}
	test->ASSERT_EQUAL(count, 10);
	vec.resize(8);
	end = vec.end();
	count = 0;
	for (ft::vector<int>::iterator it = vec.begin(); it != end; ++it)
	{
		test->ASSERT_EQUAL(*it, count);
		++count;
	}
	test->ASSERT_EQUAL(count, 8);
	test->ASSERT_EQUAL(vec.capacity(), original_cap);
	test->ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(8));
	vec.resize(15, 42);
	end = vec.end();
	count = 0;
	for (ft::vector<int>::iterator it = vec.begin(); it != end; ++it)
	{
		if (count < 8)
			test->ASSERT_EQUAL(*it, count);
		else
			test->ASSERT_EQUAL(*it, 42);
		++count;
	}
	test->ASSERT_EQUAL(count, 15);
	test->ASSERT_EQUAL(vec.capacity(), original_cap);
	test->ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(15));
	
}

void	test_vector_swap(UnitTest *test)
{
	ft::vector<int> v1(3, 100);
	ft::vector<int> v2(5, 200);

	ft::vector<int>::iterator it = v1.begin() + 2;
	v1.swap(v2);
	test->ASSERT_EQUAL(v1.size(), static_cast<unsigned int>(5));
	test->ASSERT_EQUAL(v2.size(), static_cast<unsigned int>(3));
	test->ASSERT_EQUAL(v1.at(3), 200);
	test->ASSERT_EQUAL(v2.at(2), 100);
	test->ASSERT_EQUAL(*it, 100);

}

int	main(int argc, char **argv)
{
	if (!argc || !argv)
		return (0);

	INIT;
	ADD_TEST(test_vector_empty);
	ADD_TEST(test_vector_void_constructor);
	ADD_TEST(test_vector_push_back);
	ADD_TEST(test_vector_push_back_twice);
	ADD_TEST(test_vector_push_back_thrice);
	ADD_TEST(test_vector_push_back_x4);
	ADD_TEST(test_vector_push_back_x5);
	ADD_TEST(test_vector_push_back_x15);

	ADD_TEST(test_vector_iterator_forward);
	// ADD_TEST(test_vector_at); // Causes differences in allocations due to stringstream use in vector::at()
	ADD_TEST(test_vector_operater_bracket);
	ADD_TEST(test_vector_capacity);
	ADD_TEST(test_vector_capacity_cppref);

	ADD_TEST(test_vector_max_size);
	ADD_TEST(test_vector_reserve);
	ADD_TEST(test_vector_count_value_constructor);
	ADD_TEST(test_vector_copy_constructor);
	// ADD_TEST(test_vector_iter_constructor);
	ADD_TEST(test_vector_insert);

	// ADD_TEST(test_vector_insert_count);
	// ADD_TEST(test_vector_insert_iter);

	ADD_TEST(test_vector_clear);
	ADD_TEST(test_vector_erase_one);
	ADD_TEST(test_vector_erase_range);
	ADD_TEST(test_vector_pop_back);
	ADD_TEST(test_vector_resize);
	ADD_TEST(test_vector_assign);
	ADD_TEST(test_vector_swap);

	ADD_TEST_SUITE(add_test_iterator_suite);

	

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
				RUN_TEST(i - 1);
				runAll = false;
			}
			else
			{
				std::cout << "VERBOSE MODE" << std::endl;
				SET_VERBOSITY(true);
			}
			++argNumber;
		}
	}
	if (!runAll)
		return(0);

	RUN_ALL_TESTS();
	REPORT();
	return (0);
}
