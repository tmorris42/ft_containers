#ifndef MAIN_HPP
# define MAIN_HPP

# include <iostream>
# include <sstream>

# include "UnitTest.hpp"

# ifdef FT_REAL_VERSION // Create version using real STL containers
#  include <map>
#  include <stack>
#  include <vector>
   namespace ft = std;
# else // Create using my version by default
// #  "map.hpp"
	// #include "stack.hpp"
#  include "vector.hpp"
# endif

#endif
