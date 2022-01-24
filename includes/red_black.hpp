#ifndef RED_BLACK_HPP
#define RED_BLACK_HPP

#define RB_BLACK 0
#define RB_RED 1

#include <functional> // std::less
#include <memory> // std::allocator

namespace ft
{
	template <class NodeType, class Compare>
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
		: data(ptr), past_the_end(false), before_the_start(false)
		{}
		RBIterator(RBIterator const & src)
		: data(src.data), past_the_end(src.past_the_end), before_the_start(src.before_the_start)
		{}
		RBIterator const & operator=(RBIterator const & src) {
			if (this != &src)
			{
				this->data = src.data;
				this->past_the_end = src.past_the_end;
				this->before_the_start = src.before_the_start;
			}
			return (*this);
		}
		~RBIterator() {}

		bool operator==(RBIterator const &other)
		{
			if (this->past_the_end != other.past_the_end)
				return (false);
			if (this->before_the_start != other.before_the_start)
				return (false);
			return (this->data == other.data);
		}
		bool operator!=(RBIterator const &other)
		{
			return (!(*this == other));
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
		RBIterator operator++(int) {
			RBIterator temp;
			temp = *this;
			this->operator++();
			return (temp);
		}
		RBIterator &	operator--() {
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
		RBIterator operator--(int) {
			RBIterator temp;
			temp = *this;
			this->operator--();
			return (temp);
		}

		bool operator!() const
		{
			return (this->before_the_start || this->past_the_end || (!this->data));
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

	template <class ValueType>
	struct Node
	{
		typedef Node	node_type;
		typedef ValueType	value_type;
		typedef const ValueType	const_value_type;

		ValueType	value;
		Node		*left;
		Node		*right;
		Node		*parent;
		bool		color;

		Node(ValueType const & val)
		: value(val), left(NULL), right(NULL), parent(NULL), color(RB_BLACK)
		{}

		node_type	*max(node_type *node)
		{
			if (!node)
				return (NULL);
			if (node->right)
				return (this->max(node->right));
			return (node);
		}
		node_type	*max()
		{
			return (this->max(this));
		}
		node_type	*min(node_type *node)
		{
			if (!node)
				return (NULL);
			if (node->left)
				return (this->min(node->left));
			return (node);
		}
		node_type	*min()
		{
			return (this->min(this));
		}
		const node_type	*min(node_type *node) const
		{
			if (node == NULL)
				return (NULL);
			if (node->left)
				return (this->min(node->left));
			return (node);
		}
		const node_type	*min() const
		{
			return (this->min(this));
		}


	};

	template <class ValueType>
	Node<ValueType> const operator++(Node<ValueType> & a)
	{
		Node<ValueType> *next;

		next = a.min(a.right);
		if (!next)
			next = a.parent;
	}

	template <class ValueType, class Compare = std::less < ValueType >, class Allocator = std::allocator < Node < ValueType > > >
	class RB_Tree
	{
		public:
			typedef Node<ValueType> node_type;
			typedef Node<ValueType> const_node_type;
			typedef ValueType		value_type;
			typedef const ValueType		const_value_type;
			typedef Allocator		allocator_type;

			typedef RBIterator<node_type, Compare>			iterator;		// should be custom LRAI
			typedef RBIterator<const_node_type, Compare >	const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			node_type	*root;

			RB_Tree() : root(NULL), __alloc(allocator_type())
			{
				return;
			}
			~RB_Tree()
			{
				this->delete_tree(this->root);
			}

			node_type *recursive_search(node_type *current_node, value_type const & value)
			{
				if (!current_node)
					return (NULL);
				if (this->values_equal(current_node->value, value))
					return (current_node);
				if (this->values_less_than(value, current_node->value))
					return (recursive_search(current_node->left, value));
				return (recursive_search(current_node->right, value));
			}
			const_node_type *recursive_search(node_type *current_node, value_type const & value) const
			{
				if (!current_node)
					return (NULL);
				if (this->values_equal(current_node->value, value))
					return (current_node);
				if (this->values_less_than(value, current_node->value))
					return (recursive_search(current_node->left, value));
				return (recursive_search(current_node->right, value));
			}
			iterator search(value_type const & value)
			{
				node_type *node;
				iterator it;
				node = recursive_search(this->root, value);
				if (!node)
					it = this->end();
				else
					it = iterator(node);
				return (it);
			}
			const_iterator search(value_type const & value) const
			{
				const_node_type *node = recursive_search(this->root, value);
				if (!node)
					return (this->end());
				return (const_iterator(node));
			}
			void	swap_nodes(node_type *node1, node_type *node2)
			{
				node_type *tmp_parent = node1->parent;
				node_type *tmp_left = node1->left;
				node_type *tmp_right = node1->right;
				
				if (node2->parent == node1)
					node1->parent = node2;
				else
					node1->parent = node2->parent;

				if (node2->left == node1)
					node1->left = node2;
				else
					node1->left = node2->left;
				if (node1->left)
					node1->left->parent = node1;

				if (node2->right == node1)
					node1->right = node2;
				else
					node1->right = node2->right;
				if (node1->right)
					node1->right->parent = node1;

				if (tmp_parent == node2)
					node2->parent = node1;
				else
					node2->parent = tmp_parent;
				if (tmp_left == node2)
					node2->left = node1;
				else
					node2->left = tmp_left;
				if (node2->left)
					node2->left->parent = node2;
				if (tmp_right == node2)
					node2->right = node1;
				else
					node2->right = tmp_right;
				if (node2->right)
					node2->right->parent = node2;

				if (this->root == node1)
					this->root = node2;
				else if (this->root == node2)
					this->root = node1;
				
				if (node1->parent)
				{
					if (node1->parent->right == node2)
						node1->parent->right = node1;
					else if (node1->parent->left == node2)
						node1->parent->left = node1;
				}
				if (node2->parent)
				{
					if (node2->parent->right == node1)
						node2->parent->right = node2;
					else if (node2->parent->left == node1)
						node2->parent->left = node2;
				}
			}
			void		replace_node(node_type *oldNode, node_type * newNode)
			{
				this->swap_nodes(oldNode, newNode);
				this->destroy_node(oldNode);
				// this->deallocate_node(oldNode);
			}
			bool	values_equal(value_type const & value1, value_type const & value2) const
			{
				return (!Compare()(value1, value2) && !Compare()(value2, value1));
			}
			bool	values_less_than(value_type const & value1, value_type const & value2) const
			{
				return (Compare()(value1, value2));
			}

			iterator insert(value_type const & value)
			{
				node_type	*current_node = this->root;
				node_type	*new_node = node_new(NULL, value);
				iterator	it;
				if (!this->root)
				{
					this->root = new_node;
				}
				while (current_node)
				{
					if (values_equal(current_node->value, value))
					{
						this->replace_node(current_node, new_node);
						break ;
					}
					if (values_less_than(value, current_node->value))
					{
						if (!current_node->left)
						{
							new_node->parent = current_node;
							current_node->left = new_node;
							current_node->left->color = RB_RED;
							break ;
						}
						else
							current_node = current_node->left;
					}
					else
					{
						if (!current_node->right)
						{
							new_node->parent = current_node;
							current_node->right = new_node;
							current_node->right->color = RB_RED;
							break ;
						}
						else
							current_node = current_node->right;
					}
				}
				this->recolor(new_node);
				it = iterator(new_node);
				return (it);
			}
			void		recolor(node_type *new_node)
			{
				if (!new_node)
					return ;
				if (new_node == this->root)
					new_node->color = RB_BLACK;
				else if (new_node->parent && new_node->parent->color == RB_RED)
				{
					node_type *parent = getParent(new_node);
					node_type *grandparent = getGrandparent(new_node);
					node_type *uncle = getUncle(new_node);
					if (uncle && uncle->color == RB_RED)
					{
						uncle->color = RB_BLACK;
						parent->color = RB_BLACK;
						grandparent->color = RB_RED;
						this->recolor(grandparent);
						return ;
					}
					else
					{
						// Have to rotate
						if (parent->left == new_node)
						{
							if (grandparent && grandparent->right == parent)
								this->rotateLeft(new_node);
							this->rotateRight(parent);
						}
						else
						{
							if (grandparent && grandparent->left == parent)
								this->rotateRight(new_node);
							this->rotateLeft(parent);
						}
						this->swap_color(parent, grandparent);
						this->root->color = RB_BLACK;
					}
				}
			}
			void	swap_color(node_type *node1, node_type *node2)
			{
				bool tmp;

				if (!node1 || !node2)
					return ;
				tmp = node1->color;
				node1->color = node2->color;
				node2->color = tmp;
			}
			void	swap(RB_Tree<ValueType, Compare, Allocator> & other)
			{
				node_type *tmp;
				
				tmp = this->root;
				this->root = other.root;
				other.root = tmp;
			}
			node_type *rotateLeft(node_type *node)
			{
				node_type *parent = this->getParent(node);
				node_type *grandparent = this->getGrandparent(node);

				if (!node || !parent || parent->right != node)
					return (NULL);

				// Attach left child of node to parent
				if (node->left)
					node->left->parent = parent;
				parent->right = node->left;

				// Attach node to root or grandparent
				if (!grandparent)
				{
					this->root = node;
					node->parent = NULL;
				}
				else if (grandparent->left == parent)
				{
					grandparent->left = node;
					node->parent = grandparent;
				}
				else
				{
					grandparent->right = node;
					node->parent = grandparent;
				}

				// Reattach parent as child of node
				parent->parent = node;
				node->left = parent;

				return (node);
			}
			node_type *rotateRight(node_type *node)
			{
				node_type *parent = this->getParent(node);
				node_type *grandparent = this->getGrandparent(node);

				if (!node || !parent || parent->left != node)
					return (NULL);

				// Attach left child of node to parent
				if (node->right)
					node->right->parent = parent;
				parent->left = node->right;

				// Attach node to root or grandparent
				if (!grandparent)
				{
					this->root = node;
					node->parent = NULL;
				}
				else
				{
					if (grandparent->right == parent)
						grandparent->right = node;
					else
						grandparent->left = node;
					node->parent = grandparent;
				}

				// Reattach parent as child of node
				parent->parent = node;
				node->right = parent;

				return (node);
			}
			node_type	*getSibling(node_type *node)
			{
				if (!node || !node->parent)
					return (NULL);
				if (node->parent->right == node)
					return (node->parent->left);
				return (node->parent->right);
			}
			node_type	*getGrandparent(node_type *node)
			{
				if (!node || !node->parent)
					return (NULL);
				return (node->parent->parent);
			}
			node_type	*getParent(node_type *node)
			{
				if (!node)
					return (NULL);
				return (node->parent);
			}
			node_type	*getUncle(node_type *node)
			{
				if (!node)
					return (NULL);
				return (this->getSibling(node->parent));
			}

			node_type	*max(node_type *node)
			{
				return (node->max());
			}
			node_type	*max()
			{
				return (this->max(this->root));
			}
			const_node_type	*max(node_type *node) const
			{
				return (node->max());
			}
			const_node_type	*max() const
			{
				return (this->max(this->root));
			}
			node_type	*min(node_type *node)
			{
				return (node->min());
			}
			const_node_type	*min(node_type *node) const
			{
				return (node->min());
			}
			node_type	*min()
			{
				return (this->min(this->root));
			}
			const_node_type	*min() const
			{
				return (this->min(this->root));
			}

			iterator	begin()
			{
				iterator it(this->min());
				return (it);
			}
			iterator	end()
			{
				iterator it(this->max());
				++it;
				return (it);
			}
			const_iterator	begin() const
			{
				iterator it(this->min());
				return (it);
			}
			const_iterator	end() const
			{
				const_iterator it(this->max());
				++it;
				return (it);
			}
			reverse_iterator	rbegin()
			{
				iterator it(this->max());
				return (it);
			}
			reverse_iterator	rend()
			{
				iterator it(this->min());
				--it;
				return (it);
			}

			node_type **get_reference(node_type *node)
			{
				if (!node)
					return (NULL);
				if (!node->parent && this->root == node)
					return (&this->root);
				if (node->parent->right == node)
					return(&(node->parent->right));
				else if (node->parent->left == node)
					return(&(node->parent->left));
				return (NULL);
			}

			node_type **get_reference_safe(node_type *node)
			{
				if (!node->parent && this->root == node)
					return (&this->root);
				if (!node->parent)
					return (NULL);
				if (node->parent->right == node)
					return (&node->parent->right);
				if (node->parent->left == node)
					return (&node->parent->left);
				return (NULL);
			}
			void	delete_node(node_type *node, value_type const & value)
			{
				if (!node)
					return ;
				if (this->values_less_than(value, node->value))
					this->delete_node(node->left, value);
				else if (values_less_than(node->value, value))
					this->delete_node(node->right, value);
				else //value == node->value
				{
					node_type **node_addr = this->get_reference_safe(node);
					if (!node->left && !node->right)
					{
						if (node_addr)
							*node_addr = NULL;
						this->destroy_node(node);
					}
					else if (!node->left)
					{
						if (node_addr)
							*node_addr = node->right;
						node->right->parent = node->parent;
						this->destroy_node(node);
					}
					else if (!node->right)
					{
						if (node_addr)
							*node_addr = node->left;
						node->left->parent = node->parent;
						this->destroy_node(node);
					}
					else
					{
						this->swap_nodes(node, this->max(node->left));
						// node_type *replacement = this->max(node->left);
						// node->value = replacement->value;
						this->delete_node(node, value);
					}				
				}
				return ;
			}

			void	delete_tree(node_type *node)
			{
				if (!node)
					return ;
				delete_tree(node->left);
				delete_tree(node->right);
				destroy_node(node);
			}

			void	destroy_node(node_type *node)
			{
				if (!node)
					return ;
				if (this->root == node)
					this->root = NULL;
				else if (node->parent && node->parent->right == node)
					node->parent->right = NULL;
				else if (node->parent && node->parent->left == node)
					node->parent->left = NULL;
				this->deallocate_node(node);
			}

			void	deallocate_node(node_type *node)
			{
				this->__alloc.deallocate(node, 1);
			}

			size_t	size_subtree(node_type *node) const
			{
				if (!node)
					return (0);
				return (this->size_subtree(node->left) + 1 + this->size_subtree(node->right));
			}

			size_t	size() const
			{
				return (size_subtree(this->root));
			}

			size_t max_size() const
			{
				return (this->__alloc.max_size());
			}

		private:
			node_type	*initialize_node(node_type *node, node_type *parent, value_type const & value)
			{
				// this->__alloc.construct(node, value);
				node->value = value;
				node->left = NULL;
				node->right = NULL;
				node->parent = parent;
				node->color = RB_BLACK;
				return (node);
			}
			node_type	*node_new(node_type *parent, value_type const & value)
			{
				node_type	*node = __alloc.allocate(1);
				__alloc.construct(node, value);
				node->parent = parent;
				return (node);
				// return (initialize_node(node, parent, value));
			}
			allocator_type	__alloc;
			// typedef Compare	less_func;
	};
}


#endif
