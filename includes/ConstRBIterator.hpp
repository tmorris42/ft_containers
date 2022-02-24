#ifndef CONST_RB_ITERATOR_HPP
#define CONST_RB_ITERATOR_HPP

#include "iterator.hpp"

namespace ft
{
	template <class ValueType, class NodeType>
	class ConstRBIterator
	{
	public:
		typedef NodeType node_type;
		typedef NodeType *node_pointer;

		typedef ConstRBIterator<ValueType, NodeType> const_iterator;

		typedef std::ptrdiff_t difference_type;
		typedef ft::bidirectional_iterator_tag iterator_category;
		typedef ValueType value_type;
		typedef const value_type const_value_type;
		typedef const_value_type *pointer;
		typedef const_value_type &reference;
		typedef std::size_t size_type;

		typedef NodeType const *const_node_pointer;

		ConstRBIterator(const_node_pointer const ptr = 0)
			: data(ptr)
		{
		}

		ConstRBIterator(const_iterator const &src)
			: data(src.data)
		{
		}

		ConstRBIterator const &operator=(ConstRBIterator const &src)
		{
			if (this != &src)
			{
				this->data = src.data;
			}
			return (*this);
		}

		virtual ~ConstRBIterator() {}

		virtual bool operator==(ConstRBIterator const &other)
		{
			return (this->data == other.data);
		}
		virtual bool operator!=(ConstRBIterator const &other)
		{
			return (!((*this) == other));
		}

		const_value_type &operator*()
		{
			return (this->data->value);
		}
		const_value_type &operator*() const
		{
			return (this->data->value);
		}
		const_value_type *operator->()
		{
			return (&(this->operator*()));
		}
		const_value_type *operator->() const
		{
			return (&(this->operator*()));
		}

		ConstRBIterator &operator++()
		{
			if (this->data)
				this->data = this->data->next();
			return (*this);
		}
		ConstRBIterator operator++(int)
		{
			ConstRBIterator temp;
			temp = *this;
			this->operator++();
			return (temp);
		}
		ConstRBIterator &operator--()
		{
			if (this->data)
				this->data = this->data->prev();
			return (*this);
		}
		ConstRBIterator operator--(int)
		{
			ConstRBIterator temp;
			temp = *this;
			this->operator--();
			return (temp);
		}

		bool operator!() const
		{
			return (!this->data || !this->data->parent);
		}

	protected:
		const_node_pointer data;
	};
}
#endif
