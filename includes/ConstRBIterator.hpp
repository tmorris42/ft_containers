#ifndef CONST_TREE_ITERATOR_HPP
#define CONST_TREE_ITERATOR_HPP

#include "iterator.hpp"
#include "RBIterator.hpp"
namespace ft
{
	template <class ValueType, class NodeType, class Compare>
	class ConstRBIterator
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
		: data(ptr), past_the_end(false), before_the_start(false)
		{
			if (!ptr)
				past_the_end = true;
		}
		ConstRBIterator(const_iterator const & src)
		: data(src.data), past_the_end(src.past_the_end), before_the_start(src.before_the_start)
		{}
		ConstRBIterator(iterator const & src)
		: data(src.data), past_the_end(src.past_the_end), before_the_start(src.before_the_start)
		{}
		ConstRBIterator const & operator=(ConstRBIterator const & src) {
			if (this != &src)
			{
				this->data = src.data;
				this->past_the_end = src.past_the_end;
				this->before_the_start = src.before_the_start;
			}
			return (*this);
		}
		ConstRBIterator const & operator=(iterator const & src) {
			if (this != &src)
			{
				this->data = src.data;
				this->past_the_end = src.past_the_end;
				this->before_the_start = src.before_the_start;
			}
			return (*this);
		}
		~ConstRBIterator() {}

		bool operator==(ConstRBIterator const &other)
		{
			if ((this->past_the_end && other.past_the_end) || (this->before_the_start && other.before_the_start))
				return (true);
			if (this->past_the_end != other.past_the_end)
				return (false);
			if (this->before_the_start != other.before_the_start)
				return (false);
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
			if (this->past_the_end)
				return (*this);
			if (this->before_the_start)
			{
				this->before_the_start = false;
				return (*this);
			}
			if (this->data && this->data->right)
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
			if (this->before_the_start)
				return (*this);
			if (this->past_the_end)
			{
				this->past_the_end = false;
				return (*this);
			}
			if (this->data && this->data->left)
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
			return (this->before_the_start || this->past_the_end || (!this->data));
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

		bool	values_equal(value_type const & value1, value_type const & value2) const
		{
			return (!Compare()(value1, value2) && !Compare()(value2, value1));
		}
		bool	values_less_than(value_type const & value1, value_type const & value2) const
		{
			return (Compare()(value1, value2));
		}

		private:
			node_pointer	data;
			bool 	past_the_end;
			bool	before_the_start;

			node_pointer getNextGreaterParent()
			{
				if (!this->data)
					return (NULL);
				node_pointer current = this->data;
				value_type	target = current->value;
				while (current && !this->values_less_than(target, current->value))
				{
					current = current->parent;
				}
				if (!current)
				{
					this->past_the_end = true;
					return (this->data);
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
					current = current->parent;
				}
				if (!current)
				{
					this->before_the_start = true;
					return (this->data);
				}
				return (current);
			}

	};
}
#endif
