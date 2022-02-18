#ifndef MAIN_HPP
# define MAIN_HPP

# include <iostream>
# include <sstream>
# include <cstring>	//strcmp

# include "UnitTest.hpp"
# include "tests.hpp"

# ifdef FT_REAL_VERSION // Create version using real STL containers
#  include <map>
#  include <stack>
#  include <vector>
#  include <set>
#  include <iterator>
#  include <type_traits>
#  include <algorithm>
#  include <utility>
#  define FT std
# else // Create using my version by default
#  include "map.hpp"
#  include "stack.hpp"
#  include "vector.hpp"
#  include "iterator.hpp"
#  include "type_traits.hpp"
#  include "algorithm.hpp"
#  include "utility.hpp"
#  include "RBTree.hpp"
#  include "set.hpp"
#  define FT ft
# endif

#endif
