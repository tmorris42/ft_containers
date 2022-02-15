#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

#include "iterator.hpp"
namespace ft
{
	template <class ValueType, class NodeType >
	class RBIterator
	{
		public:
		typedef ft::biderectional_iterator_tag	iterator_category;
		typedef ValueType	value_type;
		typedef const value_type	const_value_type;
		typedef std::ptrdiff_t	difference_type;
		typedef std::size_t	size_type;
		typedef NodeType *	node_pointer;
		typedef value_type *	pointer;
		typedef value_type &	reference;

		typedef NodeType const *	const_node_pointer;

		typedef RBIterator<ValueType, NodeType>	iterator_type;
		typedef RBIterator<ValueType const, NodeType>	const_iterator_type;

		operator RBIterator<ValueType const, NodeType>() const
		{
			return (const_iterator_type(this->data));
		}

		RBIterator(node_pointer const ptr = 0)
		: data(ptr)
		{
		}
		RBIterator(iterator_type const & src)
		: data(src.data)
		{}

		RBIterator(const_node_pointer ptr)
		: data(const_cast<node_pointer>(ptr))
		{} // BEWARE CONST_CAST ********
		RBIterator const & operator=(iterator_type const & src) {
			if (this != &src)
			{
				this->data = src.data;
			}
			return (*this);
		}
		virtual ~RBIterator() {}

		virtual bool operator==(iterator_type const &other)
		{
			return (this->data == other.data);
		}
		virtual bool operator!=(iterator_type const &other)
		{
			return (!((*this) == other));
		}

		value_type	&operator*()
		{
			return (this->data->value);
		}
		const_value_type	&operator*() const
		{
			return (this->data->value);
		}
		value_type	*	operator->()
		{
			return (&(this->operator*()));
		}
		const_value_type	*operator->() const
		{
			return (&(this->operator*()));
		}

		iterator_type & operator++()
		{
			if (this->data)
				this->data = this->data->next();
			return (*this);
		}
		iterator_type operator++(int) {
			iterator_type temp;
			temp = *this;
			this->operator++();
			return (temp);
		}
		iterator_type &	operator--() {
			if (this->data)
				this->data = this->data->prev();
			return (*this);
		}
		iterator_type operator--(int) {
			iterator_type temp;
			temp = *this;
			this->operator--();
			return (temp);
		}

		bool operator!() const
		{
			return (!this->data || !this->data->parent);
		}

		iterator_type & operator+=(difference_type const & n )
		{
			difference_type i = 0;
			while (i < n)
			{
				this->operator++();
				++i;
			}
			return (*this);
		}
		iterator_type & operator-=(difference_type const & n )
		{
			difference_type i = 0;
			while (i < n)
			{
				this->operator--();
				++i;
			}
			return (*this);
		}
		iterator_type operator+(difference_type const & n ) const
		{
			iterator_type ret = *this;
			ret += n;
			return (ret);
		}
		iterator_type operator-(difference_type const & n ) const
		{
			iterator_type ret = *this;
			ret -= n;
			return (ret);
		}

		protected:
			node_pointer	data;
	};
}
#endif
