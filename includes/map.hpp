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
			// typedef map::value_compare					value_compare;
			struct value_compare
			{
				bool operator() (const value_type & x, const value_type & y) const
				{
					return (key_compare()(x.first, y.first));
				}
			};

			typedef Allocator			allocator_type;
			typedef std::ptrdiff_t		difference_type;	// should be iterator_trais<iterator>::difference_type (usually equiv. ptrdiff_t)
			typedef std::size_t			size_type;			// An unsigned integral type that can represent any non-negative value of difference_type (Usually size_t)

			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef	typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;

			typedef typename RB_Tree< value_type, value_compare >::iterator			iterator;		// should be a bidirectional iterator
			typedef typename RB_Tree< value_type, value_compare >::const_iterator	const_iterator;
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
			~map()
			{
				this->c.~RB_Tree();
			}
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
			iterator insert(iterator position, const value_type & val);
			
			template <class InputIterator>
			void	insert(InputIterator first, InputIterator last);

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

			iterator find(const key_type & k)
			{
				value_type	p(k, mapped_type());
				iterator it = this->c.search(p);
				return (it);
			}

			const_iterator find(const key_type & k) const
			{
				value_type	p(k, mapped_type());
				// const_iterator it(this->c.search(p));
				return (this->c.search(p));
			}

			size_type count(const key_type & k) const
			{
				value_type	p(k, mapped_type());
				const_iterator it(this->c.search(p));
				// const_iterator it(this->c.search(p));
				if (it->first == k)
					return (1);
				return (0);
			}

			void erase(iterator position)
			{
				this->c.delete_node(this->c.root, *position); // Not optimized, should start from iterator position, not root
			}
			size_type erase(const key_type & k)
			{
				value_type	p(k, mapped_type());
				iterator it = this->c.search(p);
				if (!it)
					return (0);
				this->erase(it);
				return (1);
			}
			// void erase(iterator first, iterator last)
			// {
				
			// }
			void swap(map<Key, T, Compare, Allocator> & other)
			{
				this->c.swap(other.c);
			}
			void	clear()
			{
				this->c.delete_tree(this->c.root);
			}

			iterator lower_bound(const key_type & k)
			{
				return (this->find(k));
			}
			const_iterator lower_bound(const key_type & k) const
			{
				return (this->find(k));
			}
			// upper_bound;
			// equal_range;

			key_compare key_comp() const
			{
				return (key_compare());
			}
			value_compare value_comp() const
			{
				return (value_compare());
			}


		private:
			allocator_type						__alloc;
			key_compare							__comp;
			typedef ft::RB_Tree< value_type, value_compare >	_RB_tree_type;
			_RB_tree_type	c;
	};
} 
#endif
