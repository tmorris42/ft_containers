#ifndef RB_ITERATOR_HPP
#define RB_ITERATOR_HPP

#include "iterator.hpp"
#include "ConstRBIterator.hpp"
namespace ft
{
	template <class ValueType, class NodeType>
	class RBIterator : public ConstRBIterator<ValueType, NodeType>
	{
	public:
		typedef ft::bidirectional_iterator_tag iterator_category;
		typedef ValueType value_type;
		typedef const value_type const_value_type;
		typedef std::ptrdiff_t difference_type;
		typedef std::size_t size_type;
		typedef NodeType *node_pointer;
		typedef value_type *pointer;
		typedef value_type &reference;

		typedef NodeType const *const_node_pointer;

		typedef RBIterator<ValueType, NodeType> iterator_type;
		typedef ConstRBIterator<ValueType, NodeType> const_iterator_type;

		RBIterator(node_pointer const ptr = 0)
			: const_iterator_type(ptr)
		{
		}
		RBIterator(iterator_type const &src)
			: const_iterator_type(src.data)
		{
		}
		RBIterator const &operator=(RBIterator const &src)
		{
			if (this != &src)
			{
				this->data = src.data;
			}
			return (*this);
		}
		virtual ~RBIterator() {}

		node_pointer getMutableData()
		{
			return (const_cast<node_pointer>(this->data));
		}

		node_pointer getMutableData() const
		{
			return (const_cast<node_pointer>(this->data));
		}

		value_type &operator*()
		{
			return (this->getMutableData()->operator*());
		}
		value_type &operator*() const
		{
			return (this->getMutableData()->operator*());
		}
		value_type *operator->()
		{
			return (&(this->operator*()));
		}
		value_type *operator->() const
		{
			return (&(this->operator*()));
		}

		iterator_type &operator++()
		{
			if (this->data)
				this->data = this->data->next();
			return (*this);
		}
		iterator_type operator++(int)
		{
			iterator_type temp;
			temp = *this;
			this->operator++();
			return (temp);
		}
		iterator_type &operator--()
		{
			if (this->data)
				this->data = this->data->prev();
			return (*this);
		}
		iterator_type operator--(int)
		{
			iterator_type temp;
			temp = *this;
			this->operator--();
			return (temp);
		}
	};
}
#endif
