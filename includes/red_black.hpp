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
