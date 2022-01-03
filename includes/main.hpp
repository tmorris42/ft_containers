#ifndef MAIN_HPP
# define MAIN_HPP

# include <iostream>
# include <sstream>

# include "UnitTest.hpp"
# include "test_iterator.hpp"

# ifdef FT_REAL_VERSION // Create version using real STL containers
#  include <map>
#  include <stack>
#  include <vector>
#  include <iterator>
   namespace ft = std;
# else // Create using my version by default
// #  "map.hpp"
	// #include "stack.hpp"
#  include "vector.hpp"
#  include "iterator.hpp"
# endif

#endif
