#ifndef CONST_TREE_ITERATOR_HPP
#define CONST_TREE_ITERATOR_HPP

#include "iterator.hpp"
#include "RBIterator.hpp"
namespace ft
{
	template <class ValueType, class NodeType, class Compare>
	class ConstRBIterator : public RBIterator<ValueType, NodeType, Compare>
	{
		public:
		typedef ft::biderectional_iterator_tag	iterator_category;
		typedef NodeType		node_type;
		typedef typename node_type::value_type	value_type;
		typedef typename node_type::const_value_type	const_value_type;
		typedef std::ptrdiff_t	difference_type;
		typedef std::size_t	size_type;
		typedef NodeType const *	node_pointer;
		typedef typename NodeType::value_type *	pointer;
		typedef typename NodeType::value_type &	reference;
		typedef RBIterator<ValueType, NodeType, Compare> iterator;
		typedef ConstRBIterator<ValueType, NodeType, Compare>	const_iterator;

		ConstRBIterator(node_pointer const ptr = 0)
		: data(ptr)
		{
		}
		ConstRBIterator(const_iterator const & src)
		: data(src.data)
		{}
		ConstRBIterator(iterator const & src)
		: RBIterator<value_type, NodeType, Compare>(src)
		{
			this->data = this->RBIterator<value_type, NodeType, Compare>::data;
		}
		ConstRBIterator const & operator=(ConstRBIterator const & src) {
			if (this != &src)
			{
				this->data = src.data;
			}
			return (*this);
		}
		ConstRBIterator const & operator=(iterator const & src) {
			if (this != &src)
			{
				this->RBIterator<value_type, NodeType, Compare> = src;
				this->data = this->RBIterator<value_type, NodeType, Compare>::data;
			}
			return (*this);
		}
		~ConstRBIterator() {}

		bool operator==(ConstRBIterator const &other)
		{
			return (this->data == other.data);
		}
		bool operator!=(ConstRBIterator const &other)
		{
			return (!((*this) == other));
		}

		const_value_type	&operator*() const
		{
			return (this->data->value);
		}
		const_value_type	*operator->() const
		{
			return (&(this->operator*()));
		}

		ConstRBIterator & operator++()
		{
			if (this->data && !this->data->parent)
			{
				this->data = this->data->min(this->data);
			}
			else if (this->data && this->data->right)
			{
				this->data = this->data->min(this->data->right);
			}
			else
			{
				this->data = this->getNextGreaterParent();
			}
			return (*this);		
		}
		ConstRBIterator operator++(int) {
			ConstRBIterator temp;
			temp = *this;
			this->operator++();
			return (temp);
		}
		ConstRBIterator &	operator--() {
			if (!this->data->parent)
			{
				this->data = this->data->max(this->data->left);
			}
			else if (this->data && this->data->left)
				this->data = this->data->max(this->data->left);
			else
				this->data = this->getNextLesserParent();
			return (*this);
		}
		ConstRBIterator operator--(int) {
			ConstRBIterator temp;
			temp = *this;
			this->operator--();
			return (temp);
		}

		bool operator!() const
		{
			return (!this->data || !this->data->parent);
		}

		ConstRBIterator & operator+=(difference_type const & n )
		{
			difference_type i = 0;
			while (i < n)
			{
				this->operator++();
				++i;
			}
			return (*this);
		}
		ConstRBIterator & operator-=(difference_type const & n )
		{
			difference_type i = 0;
			while (i < n)
			{
				this->operator--();
				++i;
			}
			return (*this);
		}
		ConstRBIterator operator+(difference_type const & n ) const
		{
			ConstRBIterator ret = *this;
			ret += n;
			return (ret);
		}
		ConstRBIterator operator-(difference_type const & n ) const
		{
			ConstRBIterator ret = *this;
			ret -= n;
			return (ret);
		}

		private:
			node_pointer	data;

			node_pointer getNextGreaterParent()
			{
				if (!this->data)
					return (NULL);
				node_pointer current = this->data;
				value_type	target = current->value;
				while (current && !this->values_less_than(target, current->value))
				{
					if (!current->parent)
						return (current);
					current = current->parent;
				}
				return (current);
			}
			node_pointer getNextLesserParent()
			{
				if (!this->data)
					return (NULL);
				node_pointer current = this->data;
				value_type	target = current->value;
				while (current && !this->values_less_than(current->value, target))
				{
					if (!current->parent)
						return (current);
					current = current->parent;
				}
				return (current);
			}

	};
}
#endif
