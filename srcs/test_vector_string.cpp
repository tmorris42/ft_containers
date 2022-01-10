#include "test_vector_string.hpp"

int	test_vector_string_void_constructor()
{
	FT::vector<std::string> Vec;

	ASSERT_EQUAL(Vec.size(), (unsigned long)0);
	ASSERT_EQUAL(Vec.empty(), true);
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)0);
	return (0);
}

int	test_vector_string_count_value_constructor()
{
	FT::vector<std::string> Vec(5, "test");

	ASSERT_EQUAL(Vec.size(), (unsigned long)5);
	ASSERT_EQUAL(Vec.empty(), false);
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)5);
	for (int n = 0; n < 5; ++n)
		ASSERT_EQUAL(Vec[n], "test");
	return (0);
}

int	test_vector_string_copy_constructor()
{
	FT::vector<std::string> original(5, "test");
	FT::vector<std::string> Vec(original);

	ASSERT_EQUAL(Vec.size(), original.size());
	ASSERT_EQUAL(Vec.empty(), false);
	ASSERT_EQUAL(Vec.capacity(), original.capacity());
	for (int n = 0; n < 5; ++n)
		ASSERT_EQUAL(Vec[n], "test");
	return (0);
}

int	test_vector_string_iter_constructor()
{
	FT::vector<std::string> original(5, "test");
	FT::vector<std::string> Vec(original.begin(), original.end());

	ASSERT_EQUAL(Vec.size(), original.size());
	ASSERT_EQUAL(Vec.empty(), false);
	ASSERT_EQUAL(Vec.capacity(), original.capacity());
	for (int n = 0; n < 5; ++n)
		ASSERT_EQUAL(Vec[n], "test");
	return (0);
}

int	test_vector_string_push_back()
{
	FT::vector<std::string> Vec;
	Vec.push_back("hi");
	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(1));
	ASSERT_EQUAL(Vec.front(), "hi");
	return (0);
}

int	test_vector_string_push_back_twice()
{
	FT::vector<std::string> Vec;
	Vec.push_back("hi");
	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(1));
	Vec.push_back("there");
	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(2));
	ASSERT_EQUAL(Vec.front(), "hi");
	ASSERT_EQUAL(Vec.back(), "there");
	return (0);
}

int	test_vector_string_push_back_thrice()
{
	FT::vector<std::string> Vec;
	Vec.push_back("hi");
	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(1));
	Vec.push_back("there");
	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(2));
	Vec.push_back("okay");
	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(3));
	ASSERT_EQUAL(Vec.front(), "hi");
	ASSERT_EQUAL(Vec.back(), "okay");
	return (0);
}

int	test_vector_string_push_back_x15()
{
	FT::vector<std::string> Vec;
	Vec.push_back("5");
	Vec.push_back("6");
	Vec.push_back("7");
	Vec.push_back("8");
	Vec.push_back("9");
	Vec.push_back("5");
	Vec.push_back("6");
	Vec.push_back("7");
	Vec.push_back("8");
	Vec.push_back("9");
	Vec.push_back("5");
	Vec.push_back("6");
	Vec.push_back("7");
	Vec.push_back("8");
	Vec.push_back("42");
	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(15));
	ASSERT_EQUAL(Vec.front(), "5");
	ASSERT_EQUAL(Vec.back(), "42");
	return (0);
}

int	test_vector_string_empty()
{
	FT::vector<std::string> Vec;
	ASSERT_EQUAL(Vec.empty(), true);
	Vec.push_back("a");
	ASSERT_EQUAL(Vec.empty(), false);
	return (0);
}

int	test_vector_string_iterator_forward()
{
	FT::vector<std::string> Vec;
	Vec.push_back("0");
	Vec.push_back("1");
	Vec.push_back("2");
	Vec.push_back("3");
	Vec.push_back("4");
	FT::vector<std::string>::iterator it = Vec.begin();
	FT::vector<std::string>::iterator ite = Vec.end();
	while (it != ite)
	{
		ASSERT_EQUAL((*it).c_str()[0], '0' + (it - Vec.begin()));
		++it;
	}
	return (0);
}

int	test_vector_string_at()
{
	FT::vector<std::string> Vec;
	Vec.push_back("0");
	Vec.push_back("1");
	Vec.push_back("2");
	Vec.push_back("3");
	Vec.push_back("4");
	FT::vector<std::string>::reference ref = Vec.at(2);
	FT::vector<std::string>::const_reference cref = Vec.at(4);
	ASSERT_EQUAL(ref, "2");
	ASSERT_EQUAL(cref, "4");
	ASSERT_ERROR(Vec.at(9))
	ASSERT_ERROR(Vec.at(-1))
	return (0);
}

int	test_vector_string_operater_bracket()
{
	FT::vector<std::string> Vec;
	Vec.push_back("0");
	Vec.push_back("1");
	Vec.push_back("2");
	Vec.push_back("3");
	Vec.push_back("4");
	FT::vector<std::string>::reference ref = Vec[2];
	FT::vector<std::string>::const_reference cref = Vec[4];
	ASSERT_EQUAL(ref, "2");
	ASSERT_EQUAL(cref, "4");
	ASSERT_NO_ERROR(Vec[9])
	ASSERT_NO_ERROR(Vec[-1])
	return (0);
}

int	test_vector_string_capacity()
{
	FT::vector<std::string> Vec;
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)(0));
	Vec.push_back("5");
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)1);
	Vec.push_back("6");
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)2);
	Vec.push_back("7");
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)4);
	Vec.push_back("8");
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)4);
	Vec.push_back("9");
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)8);
	Vec.push_back("5");
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)8);
	Vec.push_back("6");
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)8);
	Vec.push_back("7");
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)8);
	Vec.push_back("8");
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)16);
	Vec.push_back("9");
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)16);
	Vec.push_back("5");
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)16);
	Vec.push_back("6");
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)16);
	Vec.push_back("7");
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)16);
	Vec.push_back("8");
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)16);
	Vec.push_back("42");
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)16);
return (0);
}

int	test_vector_string_capacity_cppref()
{
	int sz = 200;
    FT::vector<std::string> v1;
	unsigned long	expected_cap = 0;
 
 	unsigned long starting_cap = v1.capacity();
	ASSERT_EQUAL(starting_cap, expected_cap);
	expected_cap += 1;
 
    for (int n = 0; n < sz; ++n) {
		if (v1.size() == expected_cap)
			expected_cap *= 2;
        v1.push_back("test");
		ASSERT_EQUAL(expected_cap, v1.capacity());
    }
	ASSERT_EQUAL(v1.size(), (unsigned long)200);
	ASSERT_EQUAL(v1.capacity(), (unsigned long)256);
	return (0);
}

int	test_vector_string_max_size()
{
	FT::vector<std::string> Vec;
	
	ASSERT_EQUAL(Vec.max_size(), (unsigned long)288230376151711743);
	return (0);
}

int	test_vector_string_reserve()
{
	FT::vector<std::string> Vec;
	
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)0);
	Vec.reserve(200);
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)200);
	Vec.reserve(100);
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)200);
	Vec.reserve(2220);
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)2220);
	return (0);
}

int	test_vector_string_reserve_overmax()
{
	FT::vector<std::string> Vec;
	
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)0);
	ASSERT_ERROR(Vec.reserve(Vec.max_size() + 1));
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)0);
	return (0);
}

int	test_vector_string_insert()
{
	FT::vector<std::string> Vec;
	Vec.push_back("5");
	Vec.push_back("6");
	Vec.push_back("7");
	Vec.push_back("8");
	Vec.push_back("9");
	FT::vector<std::string>::iterator it = Vec.insert(Vec.begin() + 2, "42");
	ASSERT_EQUAL(*it, "42");
	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(6));
	ASSERT_EQUAL(Vec.front(), "5");
	ASSERT_EQUAL(Vec.back(), "9");
	ASSERT_EQUAL(Vec[0], "5");
	ASSERT_EQUAL(Vec[1], "6");
	ASSERT_EQUAL(Vec[2], "42");
	ASSERT_EQUAL(Vec[3], "7");
	ASSERT_EQUAL(Vec[4], "8");
	ASSERT_EQUAL(Vec[5], "9");
	it = Vec.insert(Vec.end(), "21");
	ASSERT_EQUAL(*it, "21");
	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(7));
	ASSERT_EQUAL(Vec[6], "21");
	ASSERT_EQUAL(Vec.capacity(), static_cast<unsigned int>(8));
	it = Vec.insert(Vec.end(), "21");
	it = Vec.insert(Vec.end(), "21");
	ASSERT_EQUAL(Vec.capacity(), static_cast<unsigned int>(16));
	ASSERT_EQUAL(Vec[0], "5");
	ASSERT_EQUAL(Vec[1], "6");
	ASSERT_EQUAL(Vec[2], "42");
	ASSERT_EQUAL(Vec[3], "7");
	ASSERT_EQUAL(Vec[4], "8");
	ASSERT_EQUAL(Vec[5], "9");
	ASSERT_EQUAL(Vec[6], "21");
	ASSERT_EQUAL(Vec[7], "21");
	ASSERT_EQUAL(Vec[8], "21");
	return (0);
}

int	test_vector_string_insert_count_allocation_amount()
{
	FT::vector<std::string> Vec;
	Vec.push_back("5");
	Vec.push_back("6");
	Vec.push_back("7");
	Vec.push_back("8");
	Vec.push_back("9");
	Vec.insert(Vec.begin(), (std::size_t)10, "42");
	Vec.insert(Vec.begin(), (std::size_t)10, "42");
	Vec.insert(Vec.begin(), (std::size_t)10, "42");
	ASSERT_EQUAL(Vec.capacity(), static_cast<unsigned int>(50));
	return (0);
}

int	test_vector_string_insert_count()
{
	FT::vector<std::string> Vec;
	Vec.push_back("5");
	Vec.push_back("6");
	Vec.push_back("7");
	Vec.push_back("8");
	Vec.push_back("9");
	Vec.insert(Vec.begin() + 2, (std::size_t)10, "42");
	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(15));
	ASSERT_EQUAL(Vec.capacity(), static_cast<unsigned int>(15));
	ASSERT_EQUAL(Vec.front(), "5");
	ASSERT_EQUAL(Vec.back(), "9");
	ASSERT_EQUAL(Vec[0], "5");
	ASSERT_EQUAL(Vec[1], "6");
	ASSERT_EQUAL(Vec[2], "42");
	ASSERT_EQUAL(Vec[3], "42");
	ASSERT_EQUAL(Vec[4], "42");
	ASSERT_EQUAL(Vec[5], "42");
	ASSERT_EQUAL(Vec[6], "42");
	ASSERT_EQUAL(Vec[7], "42");
	ASSERT_EQUAL(Vec[8], "42");
	ASSERT_EQUAL(Vec[9], "42");
	ASSERT_EQUAL(Vec[10], "42");
	ASSERT_EQUAL(Vec[11], "42");
	ASSERT_EQUAL(Vec[12], "7");
	ASSERT_EQUAL(Vec[13], "8");
	ASSERT_EQUAL(Vec[14], "9");
	Vec.insert(Vec.begin(), (std::size_t)10, "500");
	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(25));
	ASSERT_EQUAL(Vec.capacity(), static_cast<unsigned int>(30));
	ASSERT_EQUAL(Vec[0], "500");
	ASSERT_EQUAL(Vec[1], "500");
	ASSERT_EQUAL(Vec[2], "500");
	ASSERT_EQUAL(Vec[3], "500");
	ASSERT_EQUAL(Vec[4], "500");
	ASSERT_EQUAL(Vec[5], "500");
	ASSERT_EQUAL(Vec[6], "500");
	ASSERT_EQUAL(Vec[7], "500");
	ASSERT_EQUAL(Vec[8], "500");
	ASSERT_EQUAL(Vec[9], "500");
	ASSERT_EQUAL(Vec[10], "5");
	ASSERT_EQUAL(Vec[11], "6");
	ASSERT_EQUAL(Vec[12], "42");
	ASSERT_EQUAL(Vec[13], "42");
	ASSERT_EQUAL(Vec[14], "42");
	ASSERT_EQUAL(Vec[15], "42");
	ASSERT_EQUAL(Vec[16], "42");
	ASSERT_EQUAL(Vec[17], "42");
	ASSERT_EQUAL(Vec[18], "42");
	ASSERT_EQUAL(Vec[19], "42");
	ASSERT_EQUAL(Vec[20], "42");
	ASSERT_EQUAL(Vec[21], "42");
	ASSERT_EQUAL(Vec[22], "7");
	ASSERT_EQUAL(Vec[23], "8");
	ASSERT_EQUAL(Vec[24], "9");
	Vec.insert(Vec.end(), (std::size_t)10, "1000");
	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(35));
	ASSERT_EQUAL(Vec[0], "500");
	ASSERT_EQUAL(Vec[1], "500");
	ASSERT_EQUAL(Vec[2], "500");
	ASSERT_EQUAL(Vec[3], "500");
	ASSERT_EQUAL(Vec[4], "500");
	ASSERT_EQUAL(Vec[5], "500");
	ASSERT_EQUAL(Vec[6], "500");
	ASSERT_EQUAL(Vec[7], "500");
	ASSERT_EQUAL(Vec[8], "500");
	ASSERT_EQUAL(Vec[9], "500");
	ASSERT_EQUAL(Vec[10], "5");
	ASSERT_EQUAL(Vec[11], "6");
	ASSERT_EQUAL(Vec[12], "42");
	ASSERT_EQUAL(Vec[13], "42");
	ASSERT_EQUAL(Vec[14], "42");
	ASSERT_EQUAL(Vec[15], "42");
	ASSERT_EQUAL(Vec[16], "42");
	ASSERT_EQUAL(Vec[17], "42");
	ASSERT_EQUAL(Vec[18], "42");
	ASSERT_EQUAL(Vec[19], "42");
	ASSERT_EQUAL(Vec[20], "42");
	ASSERT_EQUAL(Vec[21], "42");
	ASSERT_EQUAL(Vec[22], "7");
	ASSERT_EQUAL(Vec[23], "8");
	ASSERT_EQUAL(Vec[24], "9");
	ASSERT_EQUAL(Vec[25], "1000");
	ASSERT_EQUAL(Vec[26], "1000");
	ASSERT_EQUAL(Vec[27], "1000");
	ASSERT_EQUAL(Vec[28], "1000");
	ASSERT_EQUAL(Vec[29], "1000");
	ASSERT_EQUAL(Vec[30], "1000");
	ASSERT_EQUAL(Vec[31], "1000");
	ASSERT_EQUAL(Vec[32], "1000");
	ASSERT_EQUAL(Vec[33], "1000");
	ASSERT_EQUAL(Vec[34], "1000");
	return (0);
}

int	test_vector_string_insert_iter()
{
	FT::vector<std::string> Vec;
	FT::vector<std::string> vec2;

	Vec.push_back("5");
	Vec.push_back("6");
	Vec.push_back("7");
	Vec.push_back("8");
	Vec.push_back("9");
	Vec.insert(Vec.begin() + 2, (std::size_t)10, "42");
	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(15));
	ASSERT_EQUAL(Vec.front(), "5");
	ASSERT_EQUAL(Vec.back(), "9");
	ASSERT_EQUAL(Vec[0], "5");
	ASSERT_EQUAL(Vec[1], "6");
	ASSERT_EQUAL(Vec[2], "42");
	ASSERT_EQUAL(Vec[3], "42");
	ASSERT_EQUAL(Vec[4], "42");
	ASSERT_EQUAL(Vec[5], "42");
	ASSERT_EQUAL(Vec[6], "42");
	ASSERT_EQUAL(Vec[7], "42");
	ASSERT_EQUAL(Vec[8], "42");
	ASSERT_EQUAL(Vec[9], "42");
	ASSERT_EQUAL(Vec[10], "42");
	ASSERT_EQUAL(Vec[11], "42");
	ASSERT_EQUAL(Vec[12], "7");
	ASSERT_EQUAL(Vec[13], "8");
	ASSERT_EQUAL(Vec[14], "9");
	Vec.insert(Vec.begin(), (std::size_t)10, "500");
	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(25));
	ASSERT_EQUAL(Vec[0], "500");
	ASSERT_EQUAL(Vec[1], "500");
	ASSERT_EQUAL(Vec[2], "500");
	ASSERT_EQUAL(Vec[3], "500");
	ASSERT_EQUAL(Vec[4], "500");
	ASSERT_EQUAL(Vec[5], "500");
	ASSERT_EQUAL(Vec[6], "500");
	ASSERT_EQUAL(Vec[7], "500");
	ASSERT_EQUAL(Vec[8], "500");
	ASSERT_EQUAL(Vec[9], "500");
	ASSERT_EQUAL(Vec[10], "5");
	ASSERT_EQUAL(Vec[11], "6");
	ASSERT_EQUAL(Vec[12], "42");
	ASSERT_EQUAL(Vec[13], "42");
	ASSERT_EQUAL(Vec[14], "42");
	ASSERT_EQUAL(Vec[15], "42");
	ASSERT_EQUAL(Vec[16], "42");
	ASSERT_EQUAL(Vec[17], "42");
	ASSERT_EQUAL(Vec[18], "42");
	ASSERT_EQUAL(Vec[19], "42");
	ASSERT_EQUAL(Vec[20], "42");
	ASSERT_EQUAL(Vec[21], "42");
	ASSERT_EQUAL(Vec[22], "7");
	ASSERT_EQUAL(Vec[23], "8");
	ASSERT_EQUAL(Vec[24], "9");
	Vec.insert(Vec.end(), (std::size_t)10, "1000");
	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(35));
	ASSERT_EQUAL(Vec[0], "500");
	ASSERT_EQUAL(Vec[1], "500");
	ASSERT_EQUAL(Vec[2], "500");
	ASSERT_EQUAL(Vec[3], "500");
	ASSERT_EQUAL(Vec[4], "500");
	ASSERT_EQUAL(Vec[5], "500");
	ASSERT_EQUAL(Vec[6], "500");
	ASSERT_EQUAL(Vec[7], "500");
	ASSERT_EQUAL(Vec[8], "500");
	ASSERT_EQUAL(Vec[9], "500");
	ASSERT_EQUAL(Vec[10], "5");
	ASSERT_EQUAL(Vec[11], "6");
	ASSERT_EQUAL(Vec[12], "42");
	ASSERT_EQUAL(Vec[13], "42");
	ASSERT_EQUAL(Vec[14], "42");
	ASSERT_EQUAL(Vec[15], "42");
	ASSERT_EQUAL(Vec[16], "42");
	ASSERT_EQUAL(Vec[17], "42");
	ASSERT_EQUAL(Vec[18], "42");
	ASSERT_EQUAL(Vec[19], "42");
	ASSERT_EQUAL(Vec[20], "42");
	ASSERT_EQUAL(Vec[21], "42");
	ASSERT_EQUAL(Vec[22], "7");
	ASSERT_EQUAL(Vec[23], "8");
	ASSERT_EQUAL(Vec[24], "9");
	ASSERT_EQUAL(Vec[25], "1000");
	ASSERT_EQUAL(Vec[26], "1000");
	ASSERT_EQUAL(Vec[27], "1000");
	ASSERT_EQUAL(Vec[28], "1000");
	ASSERT_EQUAL(Vec[29], "1000");
	ASSERT_EQUAL(Vec[30], "1000");
	ASSERT_EQUAL(Vec[31], "1000");
	ASSERT_EQUAL(Vec[32], "1000");
	ASSERT_EQUAL(Vec[33], "1000");
	ASSERT_EQUAL(Vec[34], "1000");
	vec2.insert(vec2.begin(), Vec.begin(), Vec.end());
	ASSERT_EQUAL(vec2.size(), Vec.size());
	ASSERT_EQUAL(vec2[0], "500");
	ASSERT_EQUAL(vec2[1], "500");
	ASSERT_EQUAL(vec2[2], "500");
	ASSERT_EQUAL(vec2[3], "500");
	ASSERT_EQUAL(vec2[4], "500");
	ASSERT_EQUAL(vec2[5], "500");
	ASSERT_EQUAL(vec2[6], "500");
	ASSERT_EQUAL(vec2[7], "500");
	ASSERT_EQUAL(vec2[8], "500");
	ASSERT_EQUAL(vec2[9], "500");
	ASSERT_EQUAL(vec2[10], "5");
	ASSERT_EQUAL(vec2[11], "6");
	ASSERT_EQUAL(vec2[12], "42");
	ASSERT_EQUAL(vec2[13], "42");
	ASSERT_EQUAL(vec2[14], "42");
	ASSERT_EQUAL(vec2[15], "42");
	ASSERT_EQUAL(vec2[16], "42");
	ASSERT_EQUAL(vec2[17], "42");
	ASSERT_EQUAL(vec2[18], "42");
	ASSERT_EQUAL(vec2[19], "42");
	ASSERT_EQUAL(vec2[20], "42");
	ASSERT_EQUAL(vec2[21], "42");
	ASSERT_EQUAL(vec2[22], "7");
	ASSERT_EQUAL(vec2[23], "8");
	ASSERT_EQUAL(vec2[24], "9");
	ASSERT_EQUAL(vec2[25], "1000");
	ASSERT_EQUAL(vec2[26], "1000");
	ASSERT_EQUAL(vec2[27], "1000");
	ASSERT_EQUAL(vec2[28], "1000");
	ASSERT_EQUAL(vec2[29], "1000");
	ASSERT_EQUAL(vec2[30], "1000");
	ASSERT_EQUAL(vec2[31], "1000");
	ASSERT_EQUAL(vec2[32], "1000");
	ASSERT_EQUAL(vec2[33], "1000");
	ASSERT_EQUAL(vec2[34], "1000");
	ASSERT_EQUAL(*(vec2.begin()), *(Vec.begin()));
	ASSERT_EQUAL(*(vec2.end() - 1), *(Vec.end() - 1));
	// ASSERT_EQUALQ(vec2, Vec); // == not implemented yet
	return (0);
}

int	test_vector_string_clear()
{
	FT::vector<std::string> vec(5, "42");

	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(5));
	unsigned long original_cap = vec.capacity();
	vec.clear();
	ASSERT_EQUAL(vec.capacity(), original_cap);
	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(0));
	return (0);
}

int	test_vector_string_assign()
{
	FT::vector<std::string> vec(5, "42");

	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(5));
	unsigned long original_cap = vec.capacity();
	vec.clear();
	ASSERT_EQUAL(vec.capacity(), original_cap);
	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(0));
	vec.assign(3, "15");
	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(3));
	ASSERT_EQUAL(vec[2], "15");
	vec.assign(vec.begin(), vec.end() - 1);
	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(2));
	ASSERT_EQUAL(vec[2], "15");
	return (0);
}

int	test_vector_string_erase_one()
{
	FT::vector<std::string> vec(5, "42");

	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(5));
	unsigned long original_cap = vec.capacity();
	vec.erase(vec.begin()+2);
	ASSERT_EQUAL(vec.capacity(), original_cap);
	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(4));
	return (0);
}

int	test_vector_string_erase_range()
{
	FT::vector<std::string> vec;

	vec.push_back("1");
	vec.push_back("2");
	vec.push_back("3");
	vec.push_back("4");
	vec.push_back("5");
	vec.push_back("6");
	vec.push_back("7");
	vec.push_back("8");
	vec.push_back("9");
	vec.push_back("10");

	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(10));
	unsigned long original_cap = vec.capacity();
	FT::vector<std::string>::iterator ret = vec.erase(vec.begin()+2, vec.begin()+6);
	ASSERT_EQUAL(*ret, vec[2]);
	ASSERT_EQUAL(vec.capacity(), original_cap);
	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(6));
	ASSERT_EQUAL(vec.at(1), "2");
	ASSERT_EQUAL(vec.at(2), "7");
	ASSERT_EQUAL(vec.at(3), "8");
	ASSERT_EQUAL(vec.at(4), "9");
	ASSERT_EQUAL(vec.at(5), "10");
	ret = vec.erase(vec.begin()+2, vec.end());
	ASSERT_EQUAL(*ret, *vec.end());
	return (0);
}

int	test_vector_string_pop_back()
{
	FT::vector<std::string> vec;

	vec.push_back("1");
	vec.push_back("2");
	vec.push_back("3");
	vec.push_back("4");
	vec.push_back("5");
	vec.push_back("6");
	vec.push_back("7");
	vec.push_back("8");
	vec.push_back("9");
	vec.push_back("10");

	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(10));
	unsigned long original_cap = vec.capacity();
	ASSERT_EQUAL(*(vec.end() - 1), "10");
	vec.pop_back();
	vec.pop_back();
	ASSERT_EQUAL(*(vec.end() - 1), "8");
	ASSERT_EQUAL(vec.capacity(), original_cap);
	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(8));
	return (0);
}

int	test_vector_string_resize()
{
	FT::vector<std::string> vec(10, "test");

	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(10));
	unsigned long original_cap = vec.capacity();
	vec.resize(8);
	ASSERT_EQUAL(vec.capacity(), original_cap);
	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(8));
	vec.resize(15, "newtest");
	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(15));
	ASSERT_EQUAL(vec.capacity(), static_cast<unsigned long>(16));
	ASSERT_EQUAL((*vec.begin()), "test");
	ASSERT_EQUAL((*(vec.end() - 1)), "newtest");
	return (0);
}

int	test_vector_string_swap()
{
	FT::vector<std::string> v1(3, "100");
	FT::vector<std::string> v2(5, "200");

	FT::vector<std::string>::iterator it = v1.begin() + 2;
	v1.swap(v2);
	ASSERT_EQUAL(v1.size(), static_cast<unsigned int>(5));
	ASSERT_EQUAL(v2.size(), static_cast<unsigned int>(3));
	ASSERT_EQUAL(v1.at(3), "200");
	ASSERT_EQUAL(v2.at(2), "100");
	ASSERT_EQUAL(*it, "100");
	return (0);
}

int	test_vector_string_swap_overload()
{
	FT::vector<std::string> v1(3, "100");
	FT::vector<std::string> v2(5, "200");

	FT::vector<std::string>::iterator it = v1.begin() + 2;
	FT::swap(v1, v2);
	ASSERT_EQUAL(v1.size(), static_cast<unsigned int>(5));
	ASSERT_EQUAL(v2.size(), static_cast<unsigned int>(3));
	ASSERT_EQUAL(v1.at(3), "200");
	ASSERT_EQUAL(v2.at(2), "100");
	ASSERT_EQUAL(*it, "100");
	return (0);
}

int	test_vector_string_comparisons()
{
	FT::vector<std::string> a(3, "100");
	FT::vector<std::string> b(5, "200");

	ASSERT_EQUAL(a == b, false);
	ASSERT_EQUAL(a != b, true);
	ASSERT_EQUAL(a < b, true);
	ASSERT_EQUAL(a <= b, true);
	ASSERT_EQUAL(b < a, false);
	ASSERT_EQUAL(b <= a, false);
	return (0);
}

void	add_test_vector_string_suite(FRAMEWORK_NAMESPACE::vector<Test2> *testlist)
{
	ADD_TEST(testlist, test_vector_string_empty);
	ADD_TEST(testlist, test_vector_string_void_constructor);
	ADD_TEST(testlist, test_vector_string_push_back);
	ADD_TEST(testlist, test_vector_string_push_back_twice);
	ADD_TEST(testlist, test_vector_string_push_back_thrice);
	ADD_TEST(testlist, test_vector_string_push_back_x15);

	ADD_TEST(testlist, test_vector_string_iterator_forward);
	// ADD_TEST(testlist, test_vector_string_at); // Causes differences in allocations due to stringstream use in vector::at()
	ADD_TEST(testlist, test_vector_string_operater_bracket);
	ADD_TEST(testlist, test_vector_string_capacity);
	ADD_TEST(testlist, test_vector_string_capacity_cppref);

	ADD_TEST(testlist, test_vector_string_max_size);
	ADD_TEST(testlist, test_vector_string_reserve);
	ADD_TEST(testlist, test_vector_string_count_value_constructor);
	ADD_TEST(testlist, test_vector_string_copy_constructor);
	ADD_TEST(testlist, test_vector_string_iter_constructor);
	ADD_TEST(testlist, test_vector_string_insert);

	ADD_TEST(testlist, test_vector_string_insert_count); // Allocates different amount of memory than REAL
	ADD_TEST(testlist, test_vector_string_insert_count_allocation_amount); // Allocates different amount of memory than REAL
	ADD_TEST(testlist, test_vector_string_insert_iter);

	ADD_TEST(testlist, test_vector_string_clear);
	ADD_TEST(testlist, test_vector_string_erase_one);
	ADD_TEST(testlist, test_vector_string_erase_range);
	ADD_TEST(testlist, test_vector_string_pop_back);
	ADD_TEST(testlist, test_vector_string_resize);
	ADD_TEST(testlist, test_vector_string_assign);
	ADD_TEST(testlist, test_vector_string_swap);
	ADD_TEST(testlist, test_vector_string_swap_overload);
	ADD_TEST(testlist, test_vector_string_comparisons);
}
