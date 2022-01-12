#ifndef MAIN_HPP
# define MAIN_HPP

# include <iostream>
# include <sstream>

# include "UnitTest.hpp"
# include "test_iterator.hpp"
# include "test_vector_int.hpp"
# include "test_vector_string.hpp"
# include "test_vector_struct.hpp"
# include "test_vector_class.hpp"

# ifdef FT_REAL_VERSION // Create version using real STL containers
#  include <map>
#  include <stack>
#  include <vector>
#  include <iterator>
#  include <type_traits>
#  include <algorithm>
#  include <utility>
#  define FT std
# else // Create using my version by default
// #  "map.hpp"
	// #include "stack.hpp"
#  include "vector.hpp"
#  include "iterator.hpp"
#  include "type_traits.hpp"
#  include "algorithm.hpp"
#  include "utility.hpp"
#  define FT ft
# endif

#endif
