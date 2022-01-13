#ifndef MAP_HPP
# define MAP_HPP

# include <memory> // for std::allocator
//# include <iostream> // For input output
# include <stdexcept> // For standard exceptions
# include <sstream> // For exception what() string generation
# include <limits> // For numeric_limits in max_size()

# include "iterator.hpp"
# include "type_traits.hpp"
# include "algorithm.hpp"
# include "utility.hpp"

namespace ft
{
	template < class Key, class T, class Compare = std::less < Key >,
				class Allocator = std::allocator< pair < const Key, T> > >
	class map
	{
		public:
			// Member types
			typedef Key									key_type;
			typedef T									mapped_type;
			typedef pair< const key_type, mapped_type >	value_type;
			typedef Compare								key_compare;
			// typedef ???									value_compare;

			typedef Allocator			allocator_type;
			typedef std::ptrdiff_t		difference_type;	// should be iterator_trais<iterator>::difference_type (usually equiv. ptrdiff_t)
			typedef std::size_t			size_type;			// An unsigned integral type that can represent any non-negative value of difference_type (Usually size_t)

			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef	typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;

			typedef pointer									iterator;		// should be a bidirectional iterator
			typedef const_pointer							const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
	};
} 
#endif
