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
# include "red_black.hpp"

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

			typedef typename RB_Tree< value_type >::iterator			iterator;		// should be a bidirectional iterator
			typedef typename RB_Tree< const value_type >::iterator	const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

			explicit map(const key_compare &comp = key_compare(),
						 const allocator_type &alloc = allocator_type())
				:  __alloc(alloc), __comp(comp), c()
			{
			}
			// template <class InputIterator>
  			// map (InputIterator first, InputIterator last,
			// 		const key_compare& comp = key_compare(),
			// 		const allocator_type& alloc = allocator_type());
			// map (const map& x);
			bool	empty()
			{
				return (this->size() == 0);
			}

			size_type	size() const
			{
				return (this->c.size());
			}

			size_type	max_size() const
			{
				return (this->__alloc.max_size());
			}

			ft::pair<iterator, bool>	insert (value_type & val)
			{
				iterator	node;
				ft::pair<iterator, bool>	ret;

				ret.second = false;
				node = this->c.search(val);
				if (!node)
				{
					node = this->c.insert(val);
					ret.second = true;
				}
				ret.first = node;
				return (ret);
			}

			mapped_type & operator[](const key_type & k)
			{
				mapped_type m;
				value_type v(k, m);
				pair<iterator, bool> ret;
				ret = this->insert(v);
				return (ret.first->second);
			}

			iterator begin()
			{
				return (this->c.begin());
			}
			iterator end()
			{
				return (this->c.end());
			}

			reverse_iterator rbegin()
			{
				return (reverse_iterator(this->end()));
			}
			reverse_iterator rend()
			{
				return (reverse_iterator(this->begin()));
			}


		private:
			allocator_type						__alloc;
			key_compare							__comp;

			template <class PairType>
			struct pair_compare
			{
				bool operator() (const PairType & x, const PairType & y) const
				{
					return (Compare()(x.first, y.first));
				}
			};
			ft::RB_Tree< value_type, pair_compare< value_type >	>	c;
	};
} 
#endif
