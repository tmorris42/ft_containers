#include "tests.hpp"

struct Person
{
	std::string name;
	int			age;
};

bool	operator==(const Person & lhs, const Person & rhs)
{
	return (lhs.name == rhs.name && lhs.age == rhs.age);
}
bool	operator!=(const Person & lhs, const Person & rhs)
{
	return (!(lhs == rhs));
}
std::ostream & operator<<(std::ostream & lhs, const Person & rhs)
{
	lhs << rhs.name;
	return (lhs);
}

int	test_vector_struct_void_constructor()
{
	FT::vector<Person> Vec;

	ASSERT_EQUAL(Vec.size(), (unsigned long)0);
	ASSERT_EQUAL(Vec.empty(), true);
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)0);
	return (0);
}

int	test_vector_struct_count_value_constructor()
{
	FT::vector<Person> Vec(5, Person());

	ASSERT_EQUAL(Vec.size(), (unsigned long)5);
	ASSERT_EQUAL(Vec.empty(), false);
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)5);
	for (int n = 0; n < 5; ++n)
		ASSERT_EQUAL(Vec[n], Person());
	return (0);
}

int	test_vector_struct_copy_constructor()
{
	FT::vector<Person> original(5, Person());
	FT::vector<Person> Vec(original);

	ASSERT_EQUAL(Vec.size(), original.size());
	ASSERT_EQUAL(Vec.empty(), false);
	ASSERT_EQUAL(Vec.capacity(), original.capacity());
	for (int n = 0; n < 5; ++n)
		ASSERT_EQUAL(Vec[n], Person());
	return (0);
}

int	test_vector_struct_iter_constructor()
{
	FT::vector<Person> original(5, Person());
	FT::vector<Person> Vec(original.begin(), original.end());

	ASSERT_EQUAL(Vec.size(), original.size());
	ASSERT_EQUAL(Vec.empty(), false);
	ASSERT_EQUAL(Vec.capacity(), original.capacity());
	for (int n = 0; n < 5; ++n)
		ASSERT_EQUAL(Vec[n], Person());
	return (0);
}

int	test_vector_struct_push_back()
{
	FT::vector<Person> Vec;
	Person jeff;
	jeff.name = "Jeff";
	jeff.age = 5;
	Vec.push_back(jeff);
	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(1));
	ASSERT_EQUAL((Vec.front()).name, "Jeff");
	return (0);
}

int	test_vector_struct_push_back_thrice()
{
	FT::vector<Person> Vec;
	Person bob;
	bob.name = "Bob";
	bob.age = 5;
	Person jeff;
	jeff.name = "Jeff";
	jeff.age = 5;
	Vec.push_back(jeff);
	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(1));
	Vec.push_back(bob);
	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(2));
	Vec.push_back(bob);
	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(3));
	ASSERT_EQUAL(Vec.front().name, "Jeff");
	ASSERT_EQUAL(Vec.back().name, "Bob");
	return (0);
}

int	test_vector_struct_empty()
{
	FT::vector<Person> Vec;
	ASSERT_EQUAL(Vec.empty(), true);
	Vec.push_back(Person());
	ASSERT_EQUAL(Vec.empty(), false);
	return (0);
}

int	test_vector_struct_iterator_forward()
{
	FT::vector<Person> Vec(5, Person());
	FT::vector<Person>::iterator it = Vec.begin();
	FT::vector<Person>::iterator ite = Vec.end();
	while (it != ite)
	{
		ASSERT_EQUAL((*it).name, "");
		++it;
	}
	return (0);
}

int	test_vector_struct_at()
{
	FT::vector<Person> Vec(5, Person());
	FT::vector<Person>::reference ref = Vec.at(2);
	FT::vector<Person>::const_reference cref = Vec.at(4);
	ASSERT_EQUAL(ref.age, 0);
	ASSERT_EQUAL(cref.age, 0);
	ASSERT_ERROR(Vec.at(9))
	ASSERT_ERROR(Vec.at(-1))
	return (0);
}

int	test_vector_struct_operater_bracket()
{
	FT::vector<Person> Vec(5, Person());
	FT::vector<Person>::reference ref = Vec[2];
	FT::vector<Person>::const_reference cref = Vec[4];
	ASSERT_EQUAL(ref.age, 0);
	ASSERT_EQUAL(cref.age, 0);
	ASSERT_NO_ERROR(Vec[9])
	ASSERT_NO_ERROR(Vec[-1])
	return (0);
}

int	test_vector_struct_capacity()
{
	FT::vector<Person> Vec;
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)(0));
	Vec.push_back(Person());
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)1);
	Vec.push_back(Person());
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)2);
	Vec.push_back(Person());
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)4);
	Vec.push_back(Person());
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)4);
	Vec.push_back(Person());
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)8);
	Vec.push_back(Person());
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)8);
	Vec.push_back(Person());
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)8);
	Vec.push_back(Person());
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)8);
	Vec.push_back(Person());
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)16);
	Vec.push_back(Person());
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)16);
	Vec.push_back(Person());
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)16);
	Vec.push_back(Person());
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)16);
	Vec.push_back(Person());
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)16);
	Vec.push_back(Person());
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)16);
	Vec.push_back(Person());
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)16);
return (0);
}

int	test_vector_struct_capacity_cppref()
{
	int sz = 200;
    FT::vector<Person> v1;
	unsigned long	expected_cap = 0;
 
 	unsigned long starting_cap = v1.capacity();
	ASSERT_EQUAL(starting_cap, expected_cap);
	expected_cap += 1;
 
    for (int n = 0; n < sz; ++n) {
		if (v1.size() == expected_cap)
			expected_cap *= 2;
        v1.push_back(Person());
		ASSERT_EQUAL(expected_cap, v1.capacity());
    }
	ASSERT_EQUAL(v1.size(), (unsigned long)200);
	ASSERT_EQUAL(v1.capacity(), (unsigned long)256);
	return (0);
}

int	test_vector_struct_max_size()
{
	FT::vector<Person> Vec;
	
	ASSERT_EQUAL(Vec.max_size(), (unsigned long)230584300921369395);
	return (0);
}

int	test_vector_struct_reserve()
{
	FT::vector<Person> Vec;
	
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)0);
	Vec.reserve(200);
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)200);
	Vec.reserve(100);
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)200);
	Vec.reserve(2220);
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)2220);
	return (0);
}

int	test_vector_struct_reserve_overmax()
{
	FT::vector<Person> Vec;
	
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)0);
	ASSERT_ERROR(Vec.reserve(Vec.max_size() + 1));
	ASSERT_EQUAL(Vec.capacity(), (unsigned long)0);
	return (0);
}

int	test_vector_struct_insert()
{
	FT::vector<Person> Vec;
	Vec.insert(Vec.begin(), 15, Person());
	FT::vector<Person>::iterator it = Vec.insert(Vec.begin(), Person());
	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(16));
	Person bill;
	bill.name = "Bill";
	bill.age = 42;
	it = Vec.insert(Vec.begin() + 2, bill);
	ASSERT_EQUAL((*it).age, 42);
	ASSERT_EQUAL((*it).name, "Bill");
	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(17));
	ASSERT_EQUAL(Vec[2].age, 42);
	ASSERT_EQUAL(Vec[2].name, "Bill");
	ASSERT_EQUAL(Vec.capacity(), static_cast<unsigned int>(30));
	return (0);
}

// int	test_vector_struct_insert_count_allocation_amount()
// {
// 	FT::vector<Person> Vec;
// 	Vec.push_back("5");
// 	Vec.push_back("6");
// 	Vec.push_back("7");
// 	Vec.push_back("8");
// 	Vec.push_back("9");
// 	Vec.insert(Vec.begin(), (std::size_t)10, "42");
// 	Vec.insert(Vec.begin(), (std::size_t)10, "42");
// 	Vec.insert(Vec.begin(), (std::size_t)10, "42");
// 	ASSERT_EQUAL(Vec.capacity(), static_cast<unsigned int>(50));
// 	return (0);
// }

// int	test_vector_struct_insert_count()
// {
// 	FT::vector<Person> Vec;
// 	Vec.push_back("5");
// 	Vec.push_back("6");
// 	Vec.push_back("7");
// 	Vec.push_back("8");
// 	Vec.push_back("9");
// 	Vec.insert(Vec.begin() + 2, (std::size_t)10, "42");
// 	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(15));
// 	ASSERT_EQUAL(Vec.capacity(), static_cast<unsigned int>(15));
// 	ASSERT_EQUAL(Vec.front(), "5");
// 	ASSERT_EQUAL(Vec.back(), "9");
// 	ASSERT_EQUAL(Vec[0], "5");
// 	ASSERT_EQUAL(Vec[1], "6");
// 	ASSERT_EQUAL(Vec[2], "42");
// 	ASSERT_EQUAL(Vec[3], "42");
// 	ASSERT_EQUAL(Vec[4], "42");
// 	ASSERT_EQUAL(Vec[5], "42");
// 	ASSERT_EQUAL(Vec[6], "42");
// 	ASSERT_EQUAL(Vec[7], "42");
// 	ASSERT_EQUAL(Vec[8], "42");
// 	ASSERT_EQUAL(Vec[9], "42");
// 	ASSERT_EQUAL(Vec[10], "42");
// 	ASSERT_EQUAL(Vec[11], "42");
// 	ASSERT_EQUAL(Vec[12], "7");
// 	ASSERT_EQUAL(Vec[13], "8");
// 	ASSERT_EQUAL(Vec[14], "9");
// 	Vec.insert(Vec.begin(), (std::size_t)10, "500");
// 	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(25));
// 	ASSERT_EQUAL(Vec.capacity(), static_cast<unsigned int>(30));
// 	ASSERT_EQUAL(Vec[0], "500");
// 	ASSERT_EQUAL(Vec[1], "500");
// 	ASSERT_EQUAL(Vec[2], "500");
// 	ASSERT_EQUAL(Vec[3], "500");
// 	ASSERT_EQUAL(Vec[4], "500");
// 	ASSERT_EQUAL(Vec[5], "500");
// 	ASSERT_EQUAL(Vec[6], "500");
// 	ASSERT_EQUAL(Vec[7], "500");
// 	ASSERT_EQUAL(Vec[8], "500");
// 	ASSERT_EQUAL(Vec[9], "500");
// 	ASSERT_EQUAL(Vec[10], "5");
// 	ASSERT_EQUAL(Vec[11], "6");
// 	ASSERT_EQUAL(Vec[12], "42");
// 	ASSERT_EQUAL(Vec[13], "42");
// 	ASSERT_EQUAL(Vec[14], "42");
// 	ASSERT_EQUAL(Vec[15], "42");
// 	ASSERT_EQUAL(Vec[16], "42");
// 	ASSERT_EQUAL(Vec[17], "42");
// 	ASSERT_EQUAL(Vec[18], "42");
// 	ASSERT_EQUAL(Vec[19], "42");
// 	ASSERT_EQUAL(Vec[20], "42");
// 	ASSERT_EQUAL(Vec[21], "42");
// 	ASSERT_EQUAL(Vec[22], "7");
// 	ASSERT_EQUAL(Vec[23], "8");
// 	ASSERT_EQUAL(Vec[24], "9");
// 	Vec.insert(Vec.end(), (std::size_t)10, "1000");
// 	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(35));
// 	ASSERT_EQUAL(Vec[0], "500");
// 	ASSERT_EQUAL(Vec[1], "500");
// 	ASSERT_EQUAL(Vec[2], "500");
// 	ASSERT_EQUAL(Vec[3], "500");
// 	ASSERT_EQUAL(Vec[4], "500");
// 	ASSERT_EQUAL(Vec[5], "500");
// 	ASSERT_EQUAL(Vec[6], "500");
// 	ASSERT_EQUAL(Vec[7], "500");
// 	ASSERT_EQUAL(Vec[8], "500");
// 	ASSERT_EQUAL(Vec[9], "500");
// 	ASSERT_EQUAL(Vec[10], "5");
// 	ASSERT_EQUAL(Vec[11], "6");
// 	ASSERT_EQUAL(Vec[12], "42");
// 	ASSERT_EQUAL(Vec[13], "42");
// 	ASSERT_EQUAL(Vec[14], "42");
// 	ASSERT_EQUAL(Vec[15], "42");
// 	ASSERT_EQUAL(Vec[16], "42");
// 	ASSERT_EQUAL(Vec[17], "42");
// 	ASSERT_EQUAL(Vec[18], "42");
// 	ASSERT_EQUAL(Vec[19], "42");
// 	ASSERT_EQUAL(Vec[20], "42");
// 	ASSERT_EQUAL(Vec[21], "42");
// 	ASSERT_EQUAL(Vec[22], "7");
// 	ASSERT_EQUAL(Vec[23], "8");
// 	ASSERT_EQUAL(Vec[24], "9");
// 	ASSERT_EQUAL(Vec[25], "1000");
// 	ASSERT_EQUAL(Vec[26], "1000");
// 	ASSERT_EQUAL(Vec[27], "1000");
// 	ASSERT_EQUAL(Vec[28], "1000");
// 	ASSERT_EQUAL(Vec[29], "1000");
// 	ASSERT_EQUAL(Vec[30], "1000");
// 	ASSERT_EQUAL(Vec[31], "1000");
// 	ASSERT_EQUAL(Vec[32], "1000");
// 	ASSERT_EQUAL(Vec[33], "1000");
// 	ASSERT_EQUAL(Vec[34], "1000");
// 	return (0);
// }

// int	test_vector_struct_insert_iter()
// {
// 	FT::vector<Person> Vec;
// 	FT::vector<Person> vec2;

// 	Vec.push_back("5");
// 	Vec.push_back("6");
// 	Vec.push_back("7");
// 	Vec.push_back("8");
// 	Vec.push_back("9");
// 	Vec.insert(Vec.begin() + 2, (std::size_t)10, "42");
// 	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(15));
// 	ASSERT_EQUAL(Vec.front(), "5");
// 	ASSERT_EQUAL(Vec.back(), "9");
// 	ASSERT_EQUAL(Vec[0], "5");
// 	ASSERT_EQUAL(Vec[1], "6");
// 	ASSERT_EQUAL(Vec[2], "42");
// 	ASSERT_EQUAL(Vec[3], "42");
// 	ASSERT_EQUAL(Vec[4], "42");
// 	ASSERT_EQUAL(Vec[5], "42");
// 	ASSERT_EQUAL(Vec[6], "42");
// 	ASSERT_EQUAL(Vec[7], "42");
// 	ASSERT_EQUAL(Vec[8], "42");
// 	ASSERT_EQUAL(Vec[9], "42");
// 	ASSERT_EQUAL(Vec[10], "42");
// 	ASSERT_EQUAL(Vec[11], "42");
// 	ASSERT_EQUAL(Vec[12], "7");
// 	ASSERT_EQUAL(Vec[13], "8");
// 	ASSERT_EQUAL(Vec[14], "9");
// 	Vec.insert(Vec.begin(), (std::size_t)10, "500");
// 	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(25));
// 	ASSERT_EQUAL(Vec[0], "500");
// 	ASSERT_EQUAL(Vec[1], "500");
// 	ASSERT_EQUAL(Vec[2], "500");
// 	ASSERT_EQUAL(Vec[3], "500");
// 	ASSERT_EQUAL(Vec[4], "500");
// 	ASSERT_EQUAL(Vec[5], "500");
// 	ASSERT_EQUAL(Vec[6], "500");
// 	ASSERT_EQUAL(Vec[7], "500");
// 	ASSERT_EQUAL(Vec[8], "500");
// 	ASSERT_EQUAL(Vec[9], "500");
// 	ASSERT_EQUAL(Vec[10], "5");
// 	ASSERT_EQUAL(Vec[11], "6");
// 	ASSERT_EQUAL(Vec[12], "42");
// 	ASSERT_EQUAL(Vec[13], "42");
// 	ASSERT_EQUAL(Vec[14], "42");
// 	ASSERT_EQUAL(Vec[15], "42");
// 	ASSERT_EQUAL(Vec[16], "42");
// 	ASSERT_EQUAL(Vec[17], "42");
// 	ASSERT_EQUAL(Vec[18], "42");
// 	ASSERT_EQUAL(Vec[19], "42");
// 	ASSERT_EQUAL(Vec[20], "42");
// 	ASSERT_EQUAL(Vec[21], "42");
// 	ASSERT_EQUAL(Vec[22], "7");
// 	ASSERT_EQUAL(Vec[23], "8");
// 	ASSERT_EQUAL(Vec[24], "9");
// 	Vec.insert(Vec.end(), (std::size_t)10, "1000");
// 	ASSERT_EQUAL(Vec.size(), static_cast<unsigned int>(35));
// 	ASSERT_EQUAL(Vec[0], "500");
// 	ASSERT_EQUAL(Vec[1], "500");
// 	ASSERT_EQUAL(Vec[2], "500");
// 	ASSERT_EQUAL(Vec[3], "500");
// 	ASSERT_EQUAL(Vec[4], "500");
// 	ASSERT_EQUAL(Vec[5], "500");
// 	ASSERT_EQUAL(Vec[6], "500");
// 	ASSERT_EQUAL(Vec[7], "500");
// 	ASSERT_EQUAL(Vec[8], "500");
// 	ASSERT_EQUAL(Vec[9], "500");
// 	ASSERT_EQUAL(Vec[10], "5");
// 	ASSERT_EQUAL(Vec[11], "6");
// 	ASSERT_EQUAL(Vec[12], "42");
// 	ASSERT_EQUAL(Vec[13], "42");
// 	ASSERT_EQUAL(Vec[14], "42");
// 	ASSERT_EQUAL(Vec[15], "42");
// 	ASSERT_EQUAL(Vec[16], "42");
// 	ASSERT_EQUAL(Vec[17], "42");
// 	ASSERT_EQUAL(Vec[18], "42");
// 	ASSERT_EQUAL(Vec[19], "42");
// 	ASSERT_EQUAL(Vec[20], "42");
// 	ASSERT_EQUAL(Vec[21], "42");
// 	ASSERT_EQUAL(Vec[22], "7");
// 	ASSERT_EQUAL(Vec[23], "8");
// 	ASSERT_EQUAL(Vec[24], "9");
// 	ASSERT_EQUAL(Vec[25], "1000");
// 	ASSERT_EQUAL(Vec[26], "1000");
// 	ASSERT_EQUAL(Vec[27], "1000");
// 	ASSERT_EQUAL(Vec[28], "1000");
// 	ASSERT_EQUAL(Vec[29], "1000");
// 	ASSERT_EQUAL(Vec[30], "1000");
// 	ASSERT_EQUAL(Vec[31], "1000");
// 	ASSERT_EQUAL(Vec[32], "1000");
// 	ASSERT_EQUAL(Vec[33], "1000");
// 	ASSERT_EQUAL(Vec[34], "1000");
// 	vec2.insert(vec2.begin(), Vec.begin(), Vec.end());
// 	ASSERT_EQUAL(vec2.size(), Vec.size());
// 	ASSERT_EQUAL(vec2[0], "500");
// 	ASSERT_EQUAL(vec2[1], "500");
// 	ASSERT_EQUAL(vec2[2], "500");
// 	ASSERT_EQUAL(vec2[3], "500");
// 	ASSERT_EQUAL(vec2[4], "500");
// 	ASSERT_EQUAL(vec2[5], "500");
// 	ASSERT_EQUAL(vec2[6], "500");
// 	ASSERT_EQUAL(vec2[7], "500");
// 	ASSERT_EQUAL(vec2[8], "500");
// 	ASSERT_EQUAL(vec2[9], "500");
// 	ASSERT_EQUAL(vec2[10], "5");
// 	ASSERT_EQUAL(vec2[11], "6");
// 	ASSERT_EQUAL(vec2[12], "42");
// 	ASSERT_EQUAL(vec2[13], "42");
// 	ASSERT_EQUAL(vec2[14], "42");
// 	ASSERT_EQUAL(vec2[15], "42");
// 	ASSERT_EQUAL(vec2[16], "42");
// 	ASSERT_EQUAL(vec2[17], "42");
// 	ASSERT_EQUAL(vec2[18], "42");
// 	ASSERT_EQUAL(vec2[19], "42");
// 	ASSERT_EQUAL(vec2[20], "42");
// 	ASSERT_EQUAL(vec2[21], "42");
// 	ASSERT_EQUAL(vec2[22], "7");
// 	ASSERT_EQUAL(vec2[23], "8");
// 	ASSERT_EQUAL(vec2[24], "9");
// 	ASSERT_EQUAL(vec2[25], "1000");
// 	ASSERT_EQUAL(vec2[26], "1000");
// 	ASSERT_EQUAL(vec2[27], "1000");
// 	ASSERT_EQUAL(vec2[28], "1000");
// 	ASSERT_EQUAL(vec2[29], "1000");
// 	ASSERT_EQUAL(vec2[30], "1000");
// 	ASSERT_EQUAL(vec2[31], "1000");
// 	ASSERT_EQUAL(vec2[32], "1000");
// 	ASSERT_EQUAL(vec2[33], "1000");
// 	ASSERT_EQUAL(vec2[34], "1000");
// 	ASSERT_EQUAL(*(vec2.begin()), *(Vec.begin()));
// 	ASSERT_EQUAL(*(vec2.end() - 1), *(Vec.end() - 1));
// 	// ASSERT_EQUALQ(vec2, Vec); // == not implemented yet
// 	return (0);
// }

int	test_vector_struct_clear()
{
	FT::vector<Person> vec(5, Person());

	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(5));
	unsigned long original_cap = vec.capacity();
	vec.clear();
	ASSERT_EQUAL(vec.capacity(), original_cap);
	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(0));
	return (0);
}

// int	test_vector_struct_assign()
// {
// 	FT::vector<Person> vec(5, "42");

// 	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(5));
// 	unsigned long original_cap = vec.capacity();
// 	vec.clear();
// 	ASSERT_EQUAL(vec.capacity(), original_cap);
// 	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(0));
// 	vec.assign(3, "15");
// 	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(3));
// 	ASSERT_EQUAL(vec[2], "15");
// 	vec.assign(vec.begin(), vec.end() - 1);
// 	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(2));
// 	ASSERT_EQUAL(vec[2], "15");
// 	return (0);
// }

// int	test_vector_struct_erase_one()
// {
// 	FT::vector<Person> vec(5, "42");

// 	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(5));
// 	unsigned long original_cap = vec.capacity();
// 	vec.erase(vec.begin()+2);
// 	ASSERT_EQUAL(vec.capacity(), original_cap);
// 	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(4));
// 	return (0);
// }

// int	test_vector_struct_erase_range()
// {
// 	FT::vector<Person> vec;

// 	vec.push_back("1");
// 	vec.push_back("2");
// 	vec.push_back("3");
// 	vec.push_back("4");
// 	vec.push_back("5");
// 	vec.push_back("6");
// 	vec.push_back("7");
// 	vec.push_back("8");
// 	vec.push_back("9");
// 	vec.push_back("10");

// 	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(10));
// 	unsigned long original_cap = vec.capacity();
// 	FT::vector<Person>::iterator ret = vec.erase(vec.begin()+2, vec.begin()+6);
// 	ASSERT_EQUAL(*ret, vec[2]);
// 	ASSERT_EQUAL(vec.capacity(), original_cap);
// 	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(6));
// 	ASSERT_EQUAL(vec.at(1), "2");
// 	ASSERT_EQUAL(vec.at(2), "7");
// 	ASSERT_EQUAL(vec.at(3), "8");
// 	ASSERT_EQUAL(vec.at(4), "9");
// 	ASSERT_EQUAL(vec.at(5), "10");
// 	ret = vec.erase(vec.begin()+2, vec.end());
// 	ASSERT_EQUAL(*ret, *vec.end());
// 	return (0);
// }

// int	test_vector_struct_pop_back()
// {
// 	FT::vector<Person> vec;

// 	vec.push_back("1");
// 	vec.push_back("2");
// 	vec.push_back("3");
// 	vec.push_back("4");
// 	vec.push_back("5");
// 	vec.push_back("6");
// 	vec.push_back("7");
// 	vec.push_back("8");
// 	vec.push_back("9");
// 	vec.push_back("10");

// 	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(10));
// 	unsigned long original_cap = vec.capacity();
// 	ASSERT_EQUAL(*(vec.end() - 1), "10");
// 	vec.pop_back();
// 	vec.pop_back();
// 	ASSERT_EQUAL(*(vec.end() - 1), "8");
// 	ASSERT_EQUAL(vec.capacity(), original_cap);
// 	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(8));
// 	return (0);
// }

// int	test_vector_struct_resize()
// {
// 	FT::vector<Person> vec(10, "test");

// 	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(10));
// 	unsigned long original_cap = vec.capacity();
// 	vec.resize(8);
// 	ASSERT_EQUAL(vec.capacity(), original_cap);
// 	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(8));
// 	vec.resize(15, "newtest");
// 	ASSERT_EQUAL(vec.size(), static_cast<unsigned int>(15));
// 	ASSERT_EQUAL(vec.capacity(), static_cast<unsigned long>(16));
// 	ASSERT_EQUAL((*vec.begin()), "test");
// 	ASSERT_EQUAL((*(vec.end() - 1)), "newtest");
// 	return (0);
// }

// int	test_vector_struct_swap()
// {
// 	FT::vector<Person> v1(3, "100");
// 	FT::vector<Person> v2(5, "200");

// 	FT::vector<Person>::iterator it = v1.begin() + 2;
// 	v1.swap(v2);
// 	ASSERT_EQUAL(v1.size(), static_cast<unsigned int>(5));
// 	ASSERT_EQUAL(v2.size(), static_cast<unsigned int>(3));
// 	ASSERT_EQUAL(v1.at(3), "200");
// 	ASSERT_EQUAL(v2.at(2), "100");
// 	ASSERT_EQUAL(*it, "100");
// 	return (0);
// }

// int	test_vector_struct_swap_overload()
// {
// 	FT::vector<Person> v1(3, "100");
// 	FT::vector<Person> v2(5, "200");

// 	FT::vector<Person>::iterator it = v1.begin() + 2;
// 	FT::swap(v1, v2);
// 	ASSERT_EQUAL(v1.size(), static_cast<unsigned int>(5));
// 	ASSERT_EQUAL(v2.size(), static_cast<unsigned int>(3));
// 	ASSERT_EQUAL(v1.at(3), "200");
// 	ASSERT_EQUAL(v2.at(2), "100");
// 	ASSERT_EQUAL(*it, "100");
// 	return (0);
// }

// int	test_vector_struct_comparisons()
// {
// 	FT::vector<Person> a(3, "100");
// 	FT::vector<Person> b(5, "200");

// 	ASSERT_EQUAL(a == b, false);
// 	ASSERT_EQUAL(a != b, true);
// 	ASSERT_EQUAL(a < b, true);
// 	ASSERT_EQUAL(a <= b, true);
// 	ASSERT_EQUAL(b < a, false);
// 	ASSERT_EQUAL(b <= a, false);
// 	return (0);
// }

void	add_test_vector_struct_suite(FRAMEWORK_NAMESPACE::vector<Test2> *testlist)
{
	ADD_TEST(testlist, test_vector_struct_empty);
	ADD_TEST(testlist, test_vector_struct_void_constructor);
	ADD_TEST(testlist, test_vector_struct_push_back);
	ADD_TEST(testlist, test_vector_struct_push_back_thrice);

	ADD_TEST(testlist, test_vector_struct_iterator_forward);
	ADD_TEST(testlist, test_vector_struct_at); // Causes differences in allocations due to stringstream use in vector::at()
	ADD_TEST(testlist, test_vector_struct_operater_bracket);
	ADD_TEST(testlist, test_vector_struct_capacity);
	ADD_TEST(testlist, test_vector_struct_capacity_cppref);

	ADD_TEST(testlist, test_vector_struct_max_size);
	ADD_TEST(testlist, test_vector_struct_reserve);
	ADD_TEST(testlist, test_vector_struct_count_value_constructor);
	ADD_TEST(testlist, test_vector_struct_copy_constructor);
	ADD_TEST(testlist, test_vector_struct_iter_constructor);
	ADD_TEST(testlist, test_vector_struct_insert);

	// ADD_TEST(testlist, test_vector_struct_insert_count); // Allocates different amount of memory than REAL
	// ADD_TEST(testlist, test_vector_struct_insert_count_allocation_amount); // Allocates different amount of memory than REAL
	// ADD_TEST(testlist, test_vector_struct_insert_iter);

	ADD_TEST(testlist, test_vector_struct_clear);
	// ADD_TEST(testlist, test_vector_struct_erase_one);
	// ADD_TEST(testlist, test_vector_struct_erase_range);
	// ADD_TEST(testlist, test_vector_struct_pop_back);
	// ADD_TEST(testlist, test_vector_struct_resize);
	// ADD_TEST(testlist, test_vector_struct_assign);
	// ADD_TEST(testlist, test_vector_struct_swap);
	// ADD_TEST(testlist, test_vector_struct_swap_overload);
	// ADD_TEST(testlist, test_vector_struct_comparisons);
}
