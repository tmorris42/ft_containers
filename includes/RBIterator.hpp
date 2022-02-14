#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

#include "iterator.hpp"
namespace ft
{
	template <class ValueType, class NodeType, class Compare>
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

		RBIterator(node_pointer const ptr = 0)
		: data(ptr)
		{
		}
		RBIterator(RBIterator const & src)
		: data(src.data)
		{}
		RBIterator const & operator=(RBIterator const & src) {
			if (this != &src)
			{
				this->data = src.data;
			}
			return (*this);
		}
		virtual ~RBIterator() {}

		virtual bool operator==(RBIterator const &other)
		{
			return (this->data == other.data);
		}
		virtual bool operator!=(RBIterator const &other)
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

		RBIterator & operator++()
		{
			if (this->data)
				this->data = this->data->next();
			return (*this);
		}
		RBIterator operator++(int) {
			RBIterator temp;
			temp = *this;
			this->operator++();
			return (temp);
		}
		RBIterator &	operator--() {
			if (this->data)
				this->data = this->data->prev();
			return (*this);
		}
		RBIterator operator--(int) {
			RBIterator temp;
			temp = *this;
			this->operator--();
			return (temp);
		}

		bool operator!() const
		{
			return (!this->data || !this->data->parent);
		}

		RBIterator & operator+=(difference_type const & n )
		{
			difference_type i = 0;
			while (i < n)
			{
				this->operator++();
				++i;
			}
			return (*this);
		}
		RBIterator & operator-=(difference_type const & n )
		{
			difference_type i = 0;
			while (i < n)
			{
				this->operator--();
				++i;
			}
			return (*this);
		}
		RBIterator operator+(difference_type const & n ) const
		{
			RBIterator ret = *this;
			ret += n;
			return (ret);
		}
		RBIterator operator-(difference_type const & n ) const
		{
			RBIterator ret = *this;
			ret -= n;
			return (ret);
		}

		protected:
			node_pointer	data;
	};
}
#endif
