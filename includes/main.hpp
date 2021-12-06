#ifndef MAIN_HPP
# define MAIN_HPP

# include <iostream>
# include <sstream>

# include "UnitTest.hpp"

#ifndef FT_REAL_VERSION//CREATE A REAL STL EXAMPLE
	// #include "map.hpp"
	// #include "stack.hpp"
	#include "vector.hpp"
#else
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#endif

#endif
