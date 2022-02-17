#ifndef SET_HPP
# define SET_HPP

# include <memory> // for std::allocator
//# include <iostream> // For input output
# include <stdexcept> // For standard exceptions
# include <sstream> // For exception what() string generation
# include <limits> // For numeric_limits in max_size()

# include "iterator.hpp"
# include "type_traits.hpp"
# include "algorithm.hpp"
# include "utility.hpp"
# include "RBTree.hpp"

namespace ft
{
	template < class T, class Compare = std::less < T >,
				class Allocator = std::allocator< T > >
	class set
	{
		public:
			// Member types
			typedef T									key_type;
			typedef T									value_type;
			typedef Compare								key_compare;
			typedef Compare								value_compare;

			typedef Allocator			allocator_type;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef	typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;

			typedef typename RB_Tree< value_type, value_compare >::iterator			iterator;
			typedef typename RB_Tree< value_type, value_compare >::const_iterator	const_iterator;
			typedef typename RB_Tree< value_type, value_compare >::reverse_iterator			reverse_iterator;
			typedef typename RB_Tree< value_type, value_compare >::const_reverse_iterator	const_reverse_iterator;

			typedef typename iterator_traits<iterator>::difference_type		difference_type;
			typedef typename iterator::size_type							size_type;

			explicit set(const key_compare &comp = key_compare(),
						 const allocator_type &alloc = allocator_type())
				:  __alloc(alloc), __comp(comp), c()
			{
			}
			template <class InputIterator>
  			set (InputIterator first, InputIterator last,
					const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type())
				:  __alloc(alloc), __comp(comp), c()
			{
				this->insert(first, last);
			}
			set (const set & src) : __alloc(src.__alloc), __comp(src.__comp), c()
			{
				this->insert(src.begin(), src.end());
			}
			set & operator=(const set & other)
			{
				this->clear();
				this->insert(other.begin(), other.end());
				return (*this);
			}
			~set()
			{
				this->clear();
			}
			bool	empty() const
			{
				return (this->size() == 0);
			}

			size_type	size() const
			{
				return (this->c.size());
			}

			size_type	max_size() const
			{
				return (this->c.max_size());
			}

			ft::pair<iterator, bool>	insert (const value_type & val)
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
			iterator insert(iterator position, const value_type & val)
			{
				++position; // Just to use parameter position
				return (this->insert(val).first); // Not optimized for position
			}
			
			template <class InputIterator>
			void	insert(InputIterator first, InputIterator last)
			{
				while (first != last)
				{
					this->insert(*first);
					++first;
				}
			}

			iterator begin()
			{
				return (this->c.begin());
			}
			iterator end()
			{
				return (this->c.end());
			}
			const_iterator begin() const
			{
				return (this->c.begin());
			}
			const_iterator end() const
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
				iterator it = this->c.search(k);
				return (it);
			}

			const_iterator find(const key_type & k) const
			{
				return (this->c.search(k));
			}

			size_type count(const key_type & k) const
			{
				const_iterator it(this->c.search(k));
				if (!it || *it != k)
					return (0);
				return (1);
			}

			void erase(iterator position)
			{
				this->c.delete_node(this->c.stump.left, *position); // Not optimized, should start from iterator position, not root
			}
			size_type erase(const key_type & k)
			{
				iterator it = this->c.search(k);
				if (!it)
					return (0);
				this->erase(it);
				return (1);
			}
			void erase(iterator first, iterator last)
			{
				iterator next;
				iterator ite = this->end();

				while (first != ite && first != last)
				{
					next = first + 1;
					this->erase(first);
					first = next;
				}
			}
			void swap(set<T, Compare, Allocator> & other)
			{
				this->c.swap(other.c);
			}
			void	clear()
			{
				this->c.delete_tree(this->c.stump.left);
			}

			iterator lower_bound(const key_type & k)
			{
				iterator	it = this->begin();
				iterator	ite = this->end();
				while (it != ite && this->key_comp()(*it, k))
					++it;
				return (it);
			}
			const_iterator lower_bound(const key_type & k) const
			{
				const_iterator	it = this->begin();
				const_iterator	ite = this->end();
				while (it != ite && this->key_comp()(*it, k))
					++it;
				return (it);
			}
			iterator upper_bound(const key_type & k)
			{
				iterator	it = this->begin();
				iterator	ite = this->end();
				while (it != ite && !this->key_comp()(k, *it))
					++it;
				return (it);
			}
			const_iterator upper_bound(const key_type & k) const
			{
				const_iterator	it = this->begin();
				const_iterator	ite = this->end();
				while (it != ite && !this->key_comp()(k, *it))
					++it;
				return (it);
			}
			ft::pair<iterator, iterator>	equal_range(const key_type & k)
			{
				ft::pair<iterator, iterator>	p;
				p.first = this->lower_bound(k);
				p.second = this->upper_bound(k);
				return (p);
			}
			ft::pair<const_iterator, const_iterator>	equal_range(const key_type & k) const
			{
				ft::pair<const_iterator, const_iterator>	p;
				p.first = this->lower_bound(k);
				p.second = this->upper_bound(k);
				return (p);
			}

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

	// Relational Operator overloads for set
	template <class T, class Compare, class Alloc>
	bool operator==( const set<T, Compare, Alloc> & lhs, const set<T, Compare, Alloc> & rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		typename set<T, Compare, Alloc>::const_iterator it1 = lhs.begin();
		typename set<T, Compare, Alloc>::const_iterator it2 = rhs.begin();
		typename set<T, Compare, Alloc>::const_iterator ite1 = lhs.end();
		return (ft::equal(it1, ite1, it2));
	}
	template <class T, class Compare, class Alloc>
	bool operator!=( const set<T, Compare, Alloc> & lhs, const set<T, Compare, Alloc> & rhs)
	{
		return (!(lhs == rhs));
	}
	template <class T, class Compare, class Alloc>
	bool operator<( const set<T, Compare, Alloc> & lhs, const set<T, Compare, Alloc> & rhs)
	{
		typename set<T, Compare, Alloc>::const_iterator it1 = lhs.begin();
		typename set<T, Compare, Alloc>::const_iterator it2 = rhs.begin();
		typename set<T, Compare, Alloc>::const_iterator ite1 = lhs.end();
		typename set<T, Compare, Alloc>::const_iterator ite2 = rhs.end();

		return (ft::lexicographical_compare(it1, ite1, it2, ite2));	
	}
	template <class T, class Compare, class Alloc>
	bool operator<=( const set<T, Compare, Alloc> & lhs, const set<T, Compare, Alloc> & rhs)
	{
		return (!(rhs < lhs));
	}
	template <class T, class Compare, class Alloc>
	bool operator>( const set<T, Compare, Alloc> & lhs, const set<T, Compare, Alloc> & rhs)
	{
		return (rhs < lhs);
	}
	template <class T, class Compare, class Alloc>
	bool operator>=( const set<T, Compare, Alloc> & lhs, const set<T, Compare, Alloc> & rhs)
	{
		return (!(lhs < rhs));
	}
} 
#endif
