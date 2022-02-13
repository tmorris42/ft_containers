#include "tests.hpp"
#include <list>

template <class T>
static void print_vector(FT::vector<T> const & v)
{
	if (!VERBOSE)
		return;

	std::cout << "size: " << v.size() << std::endl;
	std::cout << "capacity: " << v.capacity() << std::endl;  // Differences in memory allocated still exist
	std::cout << "max_size: " << v.max_size() << std::endl;

	typename FT::vector<T>::const_iterator ite = v.end();
	for (typename FT::vector<T>::const_iterator it = v.begin(); it != ite; ++it)
	{
		std::cout << "-- " << *it << std::endl;
	}
}

int test_vector_int_void_constructor()
{
	FT::vector<int> Vec;

	ASSERT_EQUAL(Vec.size(), (unsigned long)0);
	ASSERT_EQUAL(Vec.empty(), true);
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)0);
	print_vector(Vec);
	return (0);
}

int test_vector_int_count_value_constructor()
{
	FT::vector<int> Vec(5, 42);

	ASSERT_EQUAL(Vec.size(), (unsigned long)5);
	ASSERT_EQUAL(Vec.empty(), false);
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)5);
	ASSERT_EQUAL(Vec[0], 42);
	ASSERT_EQUAL(Vec[1], 42);
	ASSERT_EQUAL(Vec[2], 42);
	ASSERT_EQUAL(Vec[3], 42);
	ASSERT_EQUAL(Vec[4], 42);
	print_vector(Vec);
	return (0);
}

int test_vector_int_copy_constructor()
{
	FT::vector<int> original(5, 42);
	FT::vector<int> Vec(original);

	ASSERT_EQUAL(Vec.size(), original.size());
	ASSERT_EQUAL(Vec.empty(), false);
	ASSERT_EQUAL(Vec.capacity(), original.capacity());
	ASSERT_EQUAL(Vec[0], 42);
	ASSERT_EQUAL(Vec[1], 42);
	ASSERT_EQUAL(Vec[2], 42);
	ASSERT_EQUAL(Vec[3], 42);
	ASSERT_EQUAL(Vec[4], 42);
	print_vector(original);
	print_vector(Vec);
	return (0);
}

int test_vector_int_iter_constructor()
{
	FT::vector<int> original(5, 42);
	FT::vector<int> Vec(original.begin(), original.end());

	ASSERT_EQUAL(Vec.size(), original.size());
	ASSERT_EQUAL(Vec.empty(), false);
	ASSERT_EQUAL(Vec.capacity(), original.capacity());
	ASSERT_EQUAL(Vec[0], 42);
	ASSERT_EQUAL(Vec[1], 42);
	ASSERT_EQUAL(Vec[2], 42);
	ASSERT_EQUAL(Vec[3], 42);
	ASSERT_EQUAL(Vec[4], 42);
	print_vector(Vec);
	return (0);
}

int test_vector_int_push_back()
{
	FT::vector<int> Vec;
	Vec.push_back(5);
	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(1));
	ASSERT_EQUAL(Vec.front(), 5);
	print_vector(Vec);
	return (0);
}

int test_vector_int_push_back_twice()
{
	FT::vector<int> Vec;
	Vec.push_back(5);
	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(1));
	Vec.push_back(6);
	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(2));
	ASSERT_EQUAL(Vec.front(), 5);
	ASSERT_EQUAL(Vec.back(), 6);
	print_vector(Vec);
	return (0);
}

int test_vector_int_push_back_thrice()
{
	FT::vector<int> Vec;
	Vec.push_back(5);
	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(1));
	Vec.push_back(6);
	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(2));
	Vec.push_back(7);
	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(3));
	ASSERT_EQUAL(Vec.front(), 5);
	ASSERT_EQUAL(Vec.back(), 7);
	print_vector(Vec);
	return (0);
}

int test_vector_int_push_back_x4()
{
	FT::vector<int> Vec;
	Vec.push_back(5);
	Vec.push_back(6);
	Vec.push_back(7);
	Vec.push_back(8);
	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(4));
	ASSERT_EQUAL(Vec.front(), 5);
	ASSERT_EQUAL(Vec.back(), 8);
	print_vector(Vec);
	return (0);
}

int test_vector_int_push_back_x5()
{
	FT::vector<int> Vec;
	Vec.push_back(5);
	Vec.push_back(6);
	Vec.push_back(7);
	Vec.push_back(8);
	Vec.push_back(9);
	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(5));
	ASSERT_EQUAL(Vec.front(), 5);
	ASSERT_EQUAL(Vec.back(), 9);
	print_vector(Vec);
	return (0);
}

int test_vector_int_push_back_x15()
{
	FT::vector<int> Vec;
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
	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(15));
	ASSERT_EQUAL(Vec.front(), 5);
	ASSERT_EQUAL(Vec.back(), 42);
	print_vector(Vec);
	return (0);
}

int test_vector_int_empty()
{
	FT::vector<int> Vec;
	ASSERT_EQUAL(Vec.empty(), true);
	Vec.push_back(1);
	ASSERT_EQUAL(Vec.empty(), false);
	print_vector(Vec);
	Vec.pop_back();
	ASSERT_EQUAL(Vec.empty(), true);
	print_vector(Vec);
	return (0);
}

int test_vector_int_iterator_forward()
{
	FT::vector<int> Vec;
	Vec.push_back(0);
	Vec.push_back(1);
	Vec.push_back(2);
	Vec.push_back(3);
	Vec.push_back(4);
	FT::vector<int>::iterator it = Vec.begin();
	FT::vector<int>::iterator ite = Vec.end();
	while (it != ite)
	{
		ASSERT_EQUAL((*it), it - Vec.begin());
		++it;
	}
	print_vector(Vec);
	return (0);
}

int test_vector_int_at()
{
	FT::vector<int> Vec;
	Vec.push_back(0);
	Vec.push_back(1);
	Vec.push_back(2);
	Vec.push_back(3);
	Vec.push_back(4);
	FT::vector<int>::reference ref = Vec.at(2);
	FT::vector<int>::const_reference cref = Vec.at(4);
	ASSERT_EQUAL(ref, 2);
	ASSERT_EQUAL(cref, 4);
	ASSERT_ERROR(Vec.at(9))
	ASSERT_ERROR(Vec.at(-1))
	print_vector(Vec);
	return (0);
}

int test_vector_int_operater_bracket()
{
	FT::vector<int> Vec;
	Vec.push_back(0);
	Vec.push_back(1);
	Vec.push_back(2);
	Vec.push_back(3);
	Vec.push_back(4);
	FT::vector<int>::reference ref = Vec[2];
	FT::vector<int>::const_reference cref = Vec[4];
	ASSERT_EQUAL(ref, 2);
	ASSERT_EQUAL(cref, 4);
	ASSERT_NO_ERROR(Vec[9])
	ASSERT_NO_ERROR(Vec[-1])
	print_vector(Vec);
	return (0);
}

int test_vector_int_capacity()
{
	FT::vector<int> Vec;
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)(0));
	Vec.push_back(5);
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)1);
	Vec.push_back(6);
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)2);
	Vec.push_back(7);
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)4);
	Vec.push_back(8);
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)4);
	Vec.push_back(9);
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)8);
	Vec.push_back(5);
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)8);
	Vec.push_back(6);
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)8);
	Vec.push_back(7);
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)8);
	Vec.push_back(8);
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)16);
	Vec.push_back(9);
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)16);
	Vec.push_back(5);
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)16);
	Vec.push_back(6);
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)16);
	Vec.push_back(7);
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)16);
	Vec.push_back(8);
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)16);
	Vec.push_back(42);
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)16);
	print_vector(Vec);
	return (0);
}

int test_vector_int_capacity_cppref()
{
	int sz = 200;
	FT::vector<int> v1;
	unsigned long expected_cap = 0;

	unsigned long starting_cap = v1.capacity();
	ASSERT_EQUAL(starting_cap, expected_cap);
	expected_cap += 1;

	for (int n = 0; n < sz; ++n)
	{
		if (v1.size() == expected_cap)
			expected_cap *= 2;
		v1.push_back(n);
		ASSERT_EQUAL(expected_cap, v1.capacity());
	}

	ASSERT_EQUAL(v1.size(), (unsigned long)200);
	ASSERT_EQUAL(v1.capacity(), (unsigned long)256);
	print_vector(v1);
	return (0);
}

int test_vector_int_max_size()
{
	FT::vector<int> Vec;

	ASSERT_EQUAL(Vec.max_size(), (unsigned long)2305843009213693951);
	// ASSERT_EQUAL(Vec.max_size(), (unsigned long)9223372036854775807);
	print_vector(Vec);
	return (0);
}

int test_vector_int_reserve()
{
	FT::vector<int> Vec;

	// ASSERT_EQUAL(Vec.max_size(), (unsigned long)2305843009213693951);
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)0);
	Vec.reserve(200);
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)200);
	Vec.reserve(100);
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)200);
	Vec.reserve(2220);
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)2220);
	print_vector(Vec);
	return (0);
}

int test_vector_int_reserve_overmax()
{
	FT::vector<int> Vec;

	// ASSERT_EQUAL(Vec.max_size(), (unsigned long)2305843009213693951);
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)0);
	ASSERT_ERROR(Vec.reserve(Vec.max_size() + 1));
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)0);
	print_vector(Vec);
	return (0);
}

int test_vector_int_insert()
{
	FT::vector<int> Vec;
	Vec.push_back(5);
	Vec.push_back(6);
	Vec.push_back(7);
	Vec.push_back(8);
	Vec.push_back(9);
	FT::vector<int>::iterator it = Vec.insert(Vec.begin() + 2, 42);
	ASSERT_EQUAL(*it, 42);
	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(6));
	ASSERT_EQUAL(Vec.front(), 5);
	ASSERT_EQUAL(Vec.back(), 9);
	ASSERT_EQUAL(Vec[0], 5);
	ASSERT_EQUAL(Vec[1], 6);
	ASSERT_EQUAL(Vec[2], 42);
	ASSERT_EQUAL(Vec[3], 7);
	ASSERT_EQUAL(Vec[4], 8);
	ASSERT_EQUAL(Vec[5], 9);
	it = Vec.insert(Vec.end(), 21);
	ASSERT_EQUAL(*it, 21);
	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(7));
	ASSERT_EQUAL(Vec[6], 21);
	ASSERT_EQUAL(Vec.capacity(), static_cast<unsigned int>(8));
	it = Vec.insert(Vec.end(), 21);
	it = Vec.insert(Vec.end(), 21);
	ASSERT_EQUAL(Vec.capacity(), static_cast<unsigned int>(16));
	ASSERT_EQUAL(Vec[0], 5);
	ASSERT_EQUAL(Vec[1], 6);
	ASSERT_EQUAL(Vec[2], 42);
	ASSERT_EQUAL(Vec[3], 7);
	ASSERT_EQUAL(Vec[4], 8);
	ASSERT_EQUAL(Vec[5], 9);
	ASSERT_EQUAL(Vec[6], 21);
	ASSERT_EQUAL(Vec[7], 21);
	ASSERT_EQUAL(Vec[8], 21);
	print_vector(Vec);
	return (0);
}

int test_vector_int_insert_count_allocation_amount()
{
	FT::vector<int> Vec;
	Vec.push_back(5);
	Vec.push_back(6);
	Vec.push_back(7);
	Vec.push_back(8);
	Vec.push_back(9);
	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(5));
	ASSERT_EQUAL(Vec.capacity(), static_cast<unsigned int>(8));
	Vec.insert(Vec.begin(), (std::size_t)10, 42);
	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(15));
	ASSERT_EQUAL(Vec.capacity(), static_cast<unsigned int>(15));
	Vec.insert(Vec.begin(), (std::size_t)10, 42);
	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(25));
	ASSERT_EQUAL(Vec.capacity(), static_cast<unsigned int>(30));
	Vec.insert(Vec.begin(), (std::size_t)10, 42);
	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(35));
	ASSERT_EQUAL(Vec.capacity(), static_cast<unsigned int>(50));
	print_vector(Vec);
	return (0);
}

int test_vector_int_insert_count()
{
	FT::vector<int> Vec;
	Vec.push_back(5);
	Vec.push_back(6);
	Vec.push_back(7);
	Vec.push_back(8);
	Vec.push_back(9);
	Vec.insert(Vec.begin() + 2, (std::size_t)10, 42);
	print_vector(Vec);
	Vec.insert(Vec.begin(), (std::size_t)10, 500);
	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(25));
	ASSERT_EQUAL(Vec.capacity(), static_cast<unsigned int>(30));
	print_vector(Vec);
	Vec.insert(Vec.end(), (std::size_t)10, 1000);
	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(35));
	print_vector(Vec);
	return (0);
}

int test_vector_int_insert_iter()
{
	FT::vector<int> Vec;
	FT::vector<int> vec2;

	Vec.push_back(5);
	Vec.push_back(6);
	Vec.push_back(7);
	Vec.push_back(8);
	Vec.push_back(9);
	Vec.insert(Vec.begin() + 2, (std::size_t)10, 42);
	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(15));
	ASSERT_EQUAL(Vec.front(), 5);
	ASSERT_EQUAL(Vec.back(), 9);
	ASSERT_EQUAL(Vec[0], 5);
	ASSERT_EQUAL(Vec[1], 6);
	ASSERT_EQUAL(Vec[2], 42);
	ASSERT_EQUAL(Vec[3], 42);
	ASSERT_EQUAL(Vec[4], 42);
	ASSERT_EQUAL(Vec[5], 42);
	ASSERT_EQUAL(Vec[6], 42);
	ASSERT_EQUAL(Vec[7], 42);
	ASSERT_EQUAL(Vec[8], 42);
	ASSERT_EQUAL(Vec[9], 42);
	ASSERT_EQUAL(Vec[10], 42);
	ASSERT_EQUAL(Vec[11], 42);
	ASSERT_EQUAL(Vec[12], 7);
	ASSERT_EQUAL(Vec[13], 8);
	ASSERT_EQUAL(Vec[14], 9);
	Vec.insert(Vec.begin(), (std::size_t)10, 500);
	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(25));
	ASSERT_EQUAL(Vec[0], 500);
	ASSERT_EQUAL(Vec[1], 500);
	ASSERT_EQUAL(Vec[2], 500);
	ASSERT_EQUAL(Vec[3], 500);
	ASSERT_EQUAL(Vec[4], 500);
	ASSERT_EQUAL(Vec[5], 500);
	ASSERT_EQUAL(Vec[6], 500);
	ASSERT_EQUAL(Vec[7], 500);
	ASSERT_EQUAL(Vec[8], 500);
	ASSERT_EQUAL(Vec[9], 500);
	ASSERT_EQUAL(Vec[10], 5);
	ASSERT_EQUAL(Vec[11], 6);
	ASSERT_EQUAL(Vec[12], 42);
	ASSERT_EQUAL(Vec[13], 42);
	ASSERT_EQUAL(Vec[14], 42);
	ASSERT_EQUAL(Vec[15], 42);
	ASSERT_EQUAL(Vec[16], 42);
	ASSERT_EQUAL(Vec[17], 42);
	ASSERT_EQUAL(Vec[18], 42);
	ASSERT_EQUAL(Vec[19], 42);
	ASSERT_EQUAL(Vec[20], 42);
	ASSERT_EQUAL(Vec[21], 42);
	ASSERT_EQUAL(Vec[22], 7);
	ASSERT_EQUAL(Vec[23], 8);
	ASSERT_EQUAL(Vec[24], 9);
	Vec.insert(Vec.end(), (std::size_t)10, 1000);
	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(35));
	ASSERT_EQUAL(Vec[0], 500);
	ASSERT_EQUAL(Vec[1], 500);
	ASSERT_EQUAL(Vec[2], 500);
	ASSERT_EQUAL(Vec[3], 500);
	ASSERT_EQUAL(Vec[4], 500);
	ASSERT_EQUAL(Vec[5], 500);
	ASSERT_EQUAL(Vec[6], 500);
	ASSERT_EQUAL(Vec[7], 500);
	ASSERT_EQUAL(Vec[8], 500);
	ASSERT_EQUAL(Vec[9], 500);
	ASSERT_EQUAL(Vec[10], 5);
	ASSERT_EQUAL(Vec[11], 6);
	ASSERT_EQUAL(Vec[12], 42);
	ASSERT_EQUAL(Vec[13], 42);
	ASSERT_EQUAL(Vec[14], 42);
	ASSERT_EQUAL(Vec[15], 42);
	ASSERT_EQUAL(Vec[16], 42);
	ASSERT_EQUAL(Vec[17], 42);
	ASSERT_EQUAL(Vec[18], 42);
	ASSERT_EQUAL(Vec[19], 42);
	ASSERT_EQUAL(Vec[20], 42);
	ASSERT_EQUAL(Vec[21], 42);
	ASSERT_EQUAL(Vec[22], 7);
	ASSERT_EQUAL(Vec[23], 8);
	ASSERT_EQUAL(Vec[24], 9);
	ASSERT_EQUAL(Vec[25], 1000);
	ASSERT_EQUAL(Vec[26], 1000);
	ASSERT_EQUAL(Vec[27], 1000);
	ASSERT_EQUAL(Vec[28], 1000);
	ASSERT_EQUAL(Vec[29], 1000);
	ASSERT_EQUAL(Vec[30], 1000);
	ASSERT_EQUAL(Vec[31], 1000);
	ASSERT_EQUAL(Vec[32], 1000);
	ASSERT_EQUAL(Vec[33], 1000);
	ASSERT_EQUAL(Vec[34], 1000);

	// vec2.push_back(-1);
	vec2.insert(vec2.begin(), Vec.begin(), Vec.end());
	ASSERT_EQUAL(vec2.size(), Vec.size());

	ASSERT_EQUAL(vec2[0], 500);
	ASSERT_EQUAL(vec2[1], 500);
	ASSERT_EQUAL(vec2[2], 500);
	ASSERT_EQUAL(vec2[3], 500);
	ASSERT_EQUAL(vec2[4], 500);
	ASSERT_EQUAL(vec2[5], 500);
	ASSERT_EQUAL(vec2[6], 500);
	ASSERT_EQUAL(vec2[7], 500);
	ASSERT_EQUAL(vec2[8], 500);
	ASSERT_EQUAL(vec2[9], 500);
	ASSERT_EQUAL(vec2[10], 5);
	ASSERT_EQUAL(vec2[11], 6);
	ASSERT_EQUAL(vec2[12], 42);
	ASSERT_EQUAL(vec2[13], 42);
	ASSERT_EQUAL(vec2[14], 42);
	ASSERT_EQUAL(vec2[15], 42);
	ASSERT_EQUAL(vec2[16], 42);
	ASSERT_EQUAL(vec2[17], 42);
	ASSERT_EQUAL(vec2[18], 42);
	ASSERT_EQUAL(vec2[19], 42);
	ASSERT_EQUAL(vec2[20], 42);
	ASSERT_EQUAL(vec2[21], 42);
	ASSERT_EQUAL(vec2[22], 7);
	ASSERT_EQUAL(vec2[23], 8);
	ASSERT_EQUAL(vec2[24], 9);
	ASSERT_EQUAL(vec2[25], 1000);
	ASSERT_EQUAL(vec2[26], 1000);
	ASSERT_EQUAL(vec2[27], 1000);
	ASSERT_EQUAL(vec2[28], 1000);
	ASSERT_EQUAL(vec2[29], 1000);
	ASSERT_EQUAL(vec2[30], 1000);
	ASSERT_EQUAL(vec2[31], 1000);
	ASSERT_EQUAL(vec2[32], 1000);
	ASSERT_EQUAL(vec2[33], 1000);
	ASSERT_EQUAL(vec2[34], 1000);

	ASSERT_EQUAL(*(vec2.begin()), *(Vec.begin()));
	ASSERT_EQUAL(*(vec2.end() - 1), *(Vec.end() - 1));
	ASSERT_EQUALQ(vec2, Vec); // == not implemented yet
	print_vector(Vec);
	print_vector(vec2);
	return (0);
}

int test_vector_int_clear()
{
	FT::vector<int> vec(5, 42);

	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(5));
	unsigned long original_cap = vec.capacity();
	vec.clear();
	ASSERT_EQUAL(vec.capacity(), original_cap);
	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(0));
	print_vector(vec);
	return (0);
}

int test_vector_int_assign()
{
	FT::vector<int> vec(5, 42);

	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(5));
	unsigned long original_cap = vec.capacity();
	vec.clear();
	ASSERT_EQUAL(vec.capacity(), original_cap);
	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(0));
	vec.assign(3, 15);
	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(3));
	ASSERT_EQUAL(vec[2], 15);
	vec.assign(vec.begin(), vec.end() - 1);
	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(2));
	ASSERT_EQUAL(vec[2], 15);
	print_vector(vec);
	return (0);
}

int test_vector_int_erase_one()
{
	FT::vector<int> vec(5, 42);

	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(5));
	unsigned long original_cap = vec.capacity();
	vec.erase(vec.begin() + 2);
	ASSERT_EQUAL(vec.capacity(), original_cap);
	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(4));
	print_vector(vec);
	return (0);
}

int test_vector_int_erase_range()
{
	FT::vector<int> vec;

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

	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(10));
	unsigned long original_cap = vec.capacity();
	FT::vector<int>::iterator ret = vec.erase(vec.begin() + 2, vec.begin() + 6);
	ASSERT_EQUAL(*ret, vec[2]);
	ASSERT_EQUAL(vec.capacity(), original_cap);
	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(6));
	ASSERT_EQUAL(vec.at(1), 2);
	ASSERT_EQUAL(vec.at(2), 7);
	ASSERT_EQUAL(vec.at(3), 8);
	ASSERT_EQUAL(vec.at(4), 9);
	ASSERT_EQUAL(vec.at(5), 10);
	ret = vec.erase(vec.begin() + 2, vec.end());
	ASSERT_EQUAL(*ret, *vec.end());
	print_vector(vec);
	return (0);
}

int test_vector_int_pop_back()
{
	FT::vector<int> vec;

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

	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(10));
	unsigned long original_cap = vec.capacity();
	FT::vector<int>::iterator end = vec.end();
	int count = 0;
	for (FT::vector<int>::iterator it = vec.begin(); it != end; ++it)
	{
		ASSERT_EQUAL(*it, count + 1);
		++count;
	}
	ASSERT_EQUAL(count, 10);
	vec.pop_back();
	vec.pop_back();
	end = vec.end();
	count = 0;
	for (FT::vector<int>::iterator it = vec.begin(); it != end; ++it)
	{
		ASSERT_EQUAL(*it, count + 1);
		++count;
	}
	ASSERT_EQUAL(count, 8);
	ASSERT_EQUAL(vec.capacity(), original_cap);
	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(8));
	print_vector(vec);
	return (0);
}

int test_vector_int_resize()
{
	FT::vector<int> vec;

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

	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(10));
	unsigned long original_cap = vec.capacity();
	FT::vector<int>::iterator end = vec.end();
	int count = 0;
	for (FT::vector<int>::iterator it = vec.begin(); it != end; ++it)
	{
		ASSERT_EQUAL(*it, count);
		++count;
	}
	ASSERT_EQUAL(count, 10);
	vec.resize(8);
	end = vec.end();
	count = 0;
	for (FT::vector<int>::iterator it = vec.begin(); it != end; ++it)
	{
		ASSERT_EQUAL(*it, count);
		++count;
	}
	ASSERT_EQUAL(count, 8);
	ASSERT_EQUAL(vec.capacity(), original_cap);
	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(8));
	vec.resize(15, 42);
	end = vec.end();
	count = 0;
	for (FT::vector<int>::iterator it = vec.begin(); it != end; ++it)
	{
		if (count < 8)
			ASSERT_EQUAL(*it, count);
		else
			ASSERT_EQUAL(*it, 42);
		++count;
	}
	ASSERT_EQUAL(count, 15);
	ASSERT_EQUAL(vec.capacity(), original_cap);
	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(15));
	print_vector(vec);
	return (0);
}

int test_vector_int_swap()
{
	FT::vector<int> v1(3, 100);
	FT::vector<int> v2(5, 200);

	FT::vector<int>::iterator it = v1.begin() + 2;
	v1.swap(v2);
	ASSERT_EQUAL(v1.size(), static_cast<unsigned int>(5));
	ASSERT_EQUAL(v2.size(), static_cast<unsigned int>(3));
	ASSERT_EQUAL(v1.at(3), 200);
	ASSERT_EQUAL(v2.at(2), 100);
	ASSERT_EQUAL(*it, 100);
	print_vector(v1);
	print_vector(v2);
	return (0);
}

int test_vector_int_swap_overload()
{
	FT::vector<int> v1(3, 100);
	FT::vector<int> v2(5, 200);

	FT::vector<int>::iterator it = v1.begin() + 2;
	FT::swap(v1, v2);
	ASSERT_EQUAL(v1.size(), static_cast<unsigned int>(5));
	ASSERT_EQUAL(v2.size(), static_cast<unsigned int>(3));
	ASSERT_EQUAL(v1.at(3), 200);
	ASSERT_EQUAL(v2.at(2), 100);
	ASSERT_EQUAL(*it, 100);
	print_vector(v1);
	print_vector(v2);
	return (0);
}

int test_vector_int_comparisons()
{
	FT::vector<int> a(3, 100);
	FT::vector<int> b(5, 200);

	ASSERT_EQUAL(a == b, false);
	ASSERT_EQUAL(a != b, true);
	ASSERT_EQUAL(a < b, true);
	ASSERT_EQUAL(a <= b, true);
	ASSERT_EQUAL(b < a, false);
	ASSERT_EQUAL(b <= a, false);
	print_vector(a);
	print_vector(b);
	return (0);
}

int test_vector_int_mli_bidirectional_it()
{
	std::list<int> lst;
	std::list<int>::iterator lst_it;

	for (int i = 1; i < 5; ++i)
		lst.push_back(i * 3);

	FT::vector<int> vct(lst.begin(), lst.end());
	ASSERT_EQUAL(vct.size(), (unsigned long)4);

	for (int i = 0; i < 4; ++i)
	{
		ASSERT_EQUAL(vct[i], (i + 1) * 3);
	}

	lst_it = lst.begin();
	for (int i = 1; lst_it != lst.end(); ++i)
	{
		*lst_it++ = i * 5;
	}
	vct.assign(lst.begin(), lst.end());
	ASSERT_EQUAL(vct.size(), (unsigned long)4);
	for (int i = 0; i < 4; ++i)
	{
		ASSERT_EQUAL(vct[i], (i + 1) * 5);
	}

	vct.insert(vct.end(), lst.rbegin(), lst.rend());
	ASSERT_EQUAL(vct.size(), (unsigned long)8);
	for (int i = 0; i < 4; ++i)
	{
		ASSERT_EQUAL(vct[i], (i + 1) * 5);
	}
	for (int i = 4; i < 8; ++i)
	{
		ASSERT_EQUAL(vct[i], 20 - (5 * (i - 4)));
	}
	ASSERT_EQUAL(vct.capacity(), (unsigned long)8);
	print_vector(vct);
	return (0);
}

int test_vector_int_mli_rite2()
{
	const int size = 5;
	FT::vector<int> vct(size);
	FT::vector<int>::reverse_iterator it = vct.rbegin();
	FT::vector<int>::const_reverse_iterator ite = vct.rbegin();

	for (int i = 0; i < size; ++i)
		it[i] = (size - i) * 5;

	it = it + 5;
	it = 1 + it;
	it = it - 4;
	ASSERT_EQUAL(*(it += 2), 5);
	ASSERT_EQUAL(*(it -= 1), 10);

	*(it -= 2) = 42;
	*(it += 2) = 21;

	ASSERT_EQUAL(*(ite += 2), 15);
	ASSERT_EQUAL(*(ite -= 2), 25);
	ASSERT_EQUAL(ite == it, false);
	ASSERT_EQUAL(ite - it, -3);
	ASSERT_EQUALQ(ite + 3, it);

	ASSERT_EQUAL(vct.size(), (unsigned long)5);
	ASSERT_EQUAL(vct.capacity(), (unsigned long)5);
	ASSERT_EQUAL(vct.max_size(), (unsigned long)2305843009213693951);

	print_vector(vct);
	return (0);
}

template <class T>
static void	checkErase(FT::vector<T> const &vct,
					typename FT::vector<T>::const_iterator const &it)
{
	static int i = 0;
	if (VERBOSE)
		std::cout << "[" << i++ << "] " << "erase: " << it - vct.begin() << std::endl;
	print_vector<T>(vct);
}

int		test_vector_string_mli_erase(void)
{
	FT::vector<std::string> vct(10);

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = std::string((vct.size() - i), i + 65);
	print_vector(vct);

	checkErase(vct, vct.erase(vct.begin() + 2));

	checkErase(vct, vct.erase(vct.begin()));
	checkErase(vct, vct.erase(vct.end() - 1));

	checkErase(vct, vct.erase(vct.begin(), vct.begin() + 3));
	checkErase(vct, vct.erase(vct.end() - 3, vct.end() - 1));

	vct.push_back("Hello");
	vct.push_back("Hi there");
	print_vector(vct);
	checkErase(vct, vct.erase(vct.end() - 3, vct.end()));

	vct.push_back("ONE");
	vct.push_back("TWO");
	vct.push_back("THREE");
	vct.push_back("FOUR");
	print_vector(vct);
	checkErase(vct, vct.erase(vct.begin(), vct.end()));

	return (0);
}


template <typename Ite_1, typename Ite_2>
static void ft_eq_ope(const Ite_1 &first, const Ite_2 &second, const bool redo = 1)
{
	if (!VERBOSE)
		return;
	std::cout << (first < second) << std::endl;
	std::cout << (first <= second) << std::endl;
	std::cout << (first > second) << std::endl;
	std::cout << (first >= second) << std::endl;
	if (redo)
		ft_eq_ope(second, first, 0);
}

int		test_vector_int_mli_rite_eq_ope(void)
{
	const int size = 5;
	FT::vector<int> vct(size);
	FT::vector<int>::reverse_iterator it_0(vct.rbegin());
	FT::vector<int>::reverse_iterator it_1(vct.rend());
	FT::vector<int>::reverse_iterator it_mid;

	FT::vector<int>::const_reverse_iterator cit_0 = vct.rbegin();
	FT::vector<int>::const_reverse_iterator cit_1;
	FT::vector<int>::const_reverse_iterator cit_mid;

	for (int i = size; it_0 != it_1; --i)
		*it_0++ = i;
	print_vector(vct);
	it_0 = vct.rbegin();
	cit_1 = vct.rend();
	it_mid = it_0 + 3;
	cit_mid = it_0 + 3; cit_mid = cit_0 + 3; cit_mid = it_mid;

	if (VERBOSE)
	{
		std::cout << std::boolalpha;
		std::cout << ((it_0 + 3 == cit_0 + 3) && (cit_0 + 3 == it_mid)) << std::endl;

		std::cout << "\t\tft_eq_ope:" << std::endl;
	}
	// regular it
	ft_eq_ope(it_0 + 3, it_mid);
	ft_eq_ope(it_0, it_1);
	ft_eq_ope(it_1 - 3, it_mid);
	// const it
	ft_eq_ope(cit_0 + 3, cit_mid);
	ft_eq_ope(cit_0, cit_1);
	ft_eq_ope(cit_1 - 3, cit_mid);
	// both it
	ft_eq_ope(it_0 + 3, cit_mid);
	ft_eq_ope(it_mid, cit_0 + 3);
	ft_eq_ope(it_0, cit_1);
	ft_eq_ope(it_1, cit_0);
	ft_eq_ope(it_1 - 3, cit_mid);
	ft_eq_ope(it_mid, cit_1 - 3);

	return (0);
}

void add_test_vector_int_suite(FRAMEWORK_NAMESPACE::vector<Test2> *testlist)
{
	ADD_TEST(testlist, test_vector_int_empty);
	ADD_TEST(testlist, test_vector_int_void_constructor);
	ADD_TEST(testlist, test_vector_int_push_back);
	ADD_TEST(testlist, test_vector_int_push_back_twice);
	ADD_TEST(testlist, test_vector_int_push_back_thrice);
	ADD_TEST(testlist, test_vector_int_push_back_x4);
	ADD_TEST(testlist, test_vector_int_push_back_x5);
	ADD_TEST(testlist, test_vector_int_push_back_x15);

	ADD_TEST(testlist, test_vector_int_iterator_forward);
	ADD_TEST(testlist, test_vector_int_at); // Causes differences in allocations due to stringstream use in vector::at()
	ADD_TEST(testlist, test_vector_int_operater_bracket);
	ADD_TEST(testlist, test_vector_int_capacity);
	ADD_TEST(testlist, test_vector_int_capacity_cppref);

	ADD_TEST(testlist, test_vector_int_max_size);
	ADD_TEST(testlist, test_vector_int_reserve);
	ADD_TEST(testlist, test_vector_int_reserve_overmax);
	ADD_TEST(testlist, test_vector_int_count_value_constructor);
	ADD_TEST(testlist, test_vector_int_copy_constructor);
	ADD_TEST(testlist, test_vector_int_iter_constructor);
	ADD_TEST(testlist, test_vector_int_insert);

	ADD_TEST(testlist, test_vector_int_insert_count); // Allocates different amount of memory than REAL
	ADD_TEST(testlist, test_vector_int_insert_count_allocation_amount); // Allocates different amount of memory than REAL
	ADD_TEST(testlist, test_vector_int_insert_iter);

	ADD_TEST(testlist, test_vector_int_clear);
	ADD_TEST(testlist, test_vector_int_erase_one);
	ADD_TEST(testlist, test_vector_int_erase_range);
	ADD_TEST(testlist, test_vector_int_pop_back);
	ADD_TEST(testlist, test_vector_int_resize);
	ADD_TEST(testlist, test_vector_int_assign);
	ADD_TEST(testlist, test_vector_int_swap);
	ADD_TEST(testlist, test_vector_int_swap_overload);
	ADD_TEST(testlist, test_vector_int_comparisons);

	ADD_TEST(testlist, test_vector_int_mli_bidirectional_it);
	ADD_TEST(testlist, test_vector_int_mli_rite2);
	ADD_TEST(testlist, test_vector_string_mli_erase);
	ADD_TEST(testlist, test_vector_int_mli_rite_eq_ope);
}
