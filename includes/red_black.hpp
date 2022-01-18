#ifndef RED_BLACK_HPP
#define RED_BLACK_HPP

#define RB_BLACK 0
#define RB_RED 1

#include <memory> // std::allocator

namespace ft
{
	template <class ValueType>
	struct Node
	{
		ValueType	value;
		Node		*left;
		Node		*right;
		Node		*parent;
		bool		color;

		Node(ValueType const & val)
		: value(val), left(NULL), right(NULL), parent(NULL), color(RB_BLACK)
		{}
	};

	template <class ValueType>
	Node<ValueType> const operator++(Node<ValueType> & a)
	{
		Node<ValueType> *next;

		next = a.min(a.right);
		if (!next)
			next = a.parent;
	}

	template <class ValueType, class Allocator = std::allocator < Node < ValueType > > >
	class RB_Tree
	{
		public:
			typedef Node<ValueType> node_type;
			typedef ValueType		value_type;
			typedef Allocator		allocator_type;
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
				if (current_node->value == value)
					return (current_node);
				if (value < current_node->value)
					return (recursive_search(current_node->left, value));
				return (recursive_search(current_node->right, value));
			}
			node_type *search(value_type const & value)
			{
				return (recursive_search(this->root, value));
			}
			node_type *insert(value_type const & value)
			{
				node_type	*current_node = this->root;
				if (!this->root)
					this->root = node_new(NULL, value);
				while (current_node)
				{
					if (current_node->value == value)
						return (NULL);
					if (value < current_node->value)
					{
						if (!current_node->left)
						{
							current_node->left = node_new(current_node, value);
							current_node->left->color = RB_RED;
							return (current_node->left);
						}
						else
							current_node = current_node->left;
					}
					else
					{
						if (!current_node->right)
						{
							current_node->right = node_new(current_node, value);
							current_node->right->color = RB_RED;
							return (current_node->right);
						}
						else
							current_node = current_node->right;
					}
				}
				return (NULL);
			}
			

			node_type	*max(node_type *node)
			{
				if (node == NULL)
					return (NULL);
				if (node->right)
					return (this->max(node->right));
				return (node);
			}
			node_type	*max()
			{
				return (this->max(this->root));
			}

			node_type	*min(node_type *node)
			{
				if (node == NULL)
					return (NULL);
				if (node->left)
					return (this->min(node->left));
				return (node);
			}
			node_type	*min()
			{
				return (this->min(this->root));
			}

			node_type **get_reference(node_type *node)
			{
				node_type **node_addr;
				if (!node || !node->parent)
					return (&this->root);
				if (node->parent->value < node->value)
					node_addr = &(node->parent->right);
				else
					node_addr = &(node->parent->left);
				return (node_addr);
			}
			void	delete_node(node_type *node, value_type const & value)
			{
				if (node == NULL)
					return ;
				if (value < node->value)
					this->delete_node(node->left, value);
				else if (value > node->value)
					this->delete_node(node->right, value);
				else //value == node->value
				{
					node_type **node_addr = this->get_reference(node);
					if (!node->left && !node->right)
					{
						*node_addr = NULL;
						this->destroy_node(node);
					}
					else if (!node->left)
					{
						*node_addr = node->right;
						node->right->parent = node->parent;
						this->destroy_node(node);
					}
					else if (!node->right)
					{
						*node_addr = node->left;
						node->left->parent = node->parent;
						this->destroy_node(node);
					}
					else
					{
						node_type *replacement = this->max(node->left);
						node->value = replacement->value;
						this->delete_node(node->left, replacement->value);
					}				
				}
				return ;
			}

			void	delete_tree(node_type *node)
			{
				if (!node)
					return ;
				node_type **node_addr = this->get_reference(node);
				delete_tree(node->left);
				delete_tree(node->right);
				destroy_node(node);
				*node_addr = NULL;
			}

			void	destroy_node(node_type *node)
			{
				// node_type **node_addr = this->get_reference(node);
				__alloc.deallocate(node, 1);
				// *node_addr = NULL;
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
	};
}


#endif
