#ifndef RED_BLACK_HPP
#define RED_BLACK_HPP

#define RB_BLACK 0
#define RB_RED 1

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
	};

	template <class ValueType>
	class RB_Tree
	{
		public:
			typedef Node<ValueType> node_type;
			typedef ValueType		value_type;
			node_type	*root;
			RB_Tree() : root(NULL)
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
					this->root = node_new(this->root, value);
				while (current_node)
				{
					if (current_node->value == value)
						return (NULL);
					if (value < current_node->value)
					{
						if (!current_node->left)
						{
							current_node->left = node_new(current_node, value);
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

			node_type	*min(node_type *node)
			{
				if (node == NULL)
					return (NULL);
				if (node->left)
					return (this->min(node->left));
				return (node);
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
						this->destroy_node(node);
					else if (!node->left)
					{
						*node_addr = node->right;
						this->destroy_node(node);
					}
					else if (!node->right)
					{
						*node_addr = node->left;
						this->destroy_node(node);
					}
					else
					{
						node_type *replacement = this->max(node->left);
						node->value = replacement->value;
						this->destroy_node(replacement);
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
				node_type **node_addr = this->get_reference(node);
				*node_addr = NULL;
				delete node;
			}

		private:
			node_type	*node_new(node_type *parent, value_type const & value)
			{
				node_type	*node = new node_type();
				node->value = value;
				node->left = NULL;
				node->right = NULL;
				node->parent = parent;
				node->color = RB_BLACK;
				return (node);
			}
	};
}


#endif
