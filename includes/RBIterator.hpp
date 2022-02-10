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
		typedef NodeType		node_type;
		typedef typename node_type::value_type	value_type;
		typedef typename node_type::const_value_type	const_value_type;
		typedef std::ptrdiff_t	difference_type;
		typedef std::size_t	size_type;
		typedef NodeType *	node_pointer;
		typedef typename NodeType::value_type *	pointer;
		typedef typename NodeType::value_type &	reference;

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
		~RBIterator() {}

		bool operator==(RBIterator const &other)
		{
			return (this->data == other.data);
		}
		bool operator!=(RBIterator const &other)
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
		RBIterator operator++(int) {
			RBIterator temp;
			temp = *this;
			this->operator++();
			return (temp);
		}
		RBIterator &	operator--() {
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

		bool	values_equal(value_type const & value1, value_type const & value2) const
		{
			return (!Compare()(value1, value2) && !Compare()(value2, value1));
		}
		bool	values_less_than(value_type const & value1, value_type const & value2) const
		{
			return (Compare()(value1, value2));
		}

		protected:
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
