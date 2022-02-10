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
		typedef NodeType *	node_pointer;
		typedef NodeType const *	const_node_pointer;
		typedef typename NodeType::value_type *	pointer;
		typedef typename NodeType::value_type &	reference;
		typedef RBIterator<ValueType, NodeType, Compare> iterator;
		typedef ConstRBIterator<ValueType, NodeType, Compare>	const_iterator;

		ConstRBIterator(node_pointer const ptr = 0)
		: RBIterator<value_type, NodeType, Compare>(ptr)
		{
		}
		ConstRBIterator(const_iterator const & src)
		: RBIterator<value_type, NodeType, Compare>(src.data)
		{}
		ConstRBIterator(iterator const & src)
		: RBIterator<value_type, NodeType, Compare>(src)
		{}
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
				this->data = src.data;
			}
			return (*this);
		}
		~ConstRBIterator() {}

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
	};
}
#endif
