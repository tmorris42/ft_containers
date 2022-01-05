#ifndef MAIN_HPP
# define MAIN_HPP

# include <iostream>
# include <sstream>

# include "UnitTest.hpp"
# include "test_iterator.hpp"
# include "test_vector.hpp"

# ifdef FT_REAL_VERSION // Create version using real STL containers
#  include <map>
#  include <stack>
#  include <vector>
#  include <iterator>
#  include <type_traits>
#  include <algorithm>
#  include <utility>
   namespace ft = std;
# else // Create using my version by default
// #  "map.hpp"
	// #include "stack.hpp"
#  include "vector.hpp"
#  include "iterator.hpp"
#  include "type_traits.hpp"
#  include "algorithm.hpp"
#  include "utility.hpp"
# endif

#endif
