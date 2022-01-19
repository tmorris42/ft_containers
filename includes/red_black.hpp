#ifndef RED_BLACK_HPP
#define RED_BLACK_HPP

#define RB_BLACK 0
#define RB_RED 1

#include <memory> // std::allocator

namespace ft
{
	template <class ValueType>
	class RBIterator
	{
		typedef ft::biderectional_iterator_tag	iterator_category;
		typedef ValueType	value_type;
		typedef ptrdiff_t	difference_type;
		typedef *ValueType	pointer;
		typedef &ValueType	reference;

		RBIterator(pointer ptr = NULL) : data(ptr){}
		RBIterator(RBIterator const & src)  : data(src.data) {}
		RBIterator const & operator=(RBIterator const & src) {
			if (this != &src)
				this->data = src.data;
			return (*this);
		}
		~RBIterator() {}

		bool	operator==(RBIterator const & other) { return (this->data == other.data); }
		bool	operator!=(RBIterator const & other) { return (this->data != other.data); }

		pointer		operator*() { return (this->data); }
		reference	operator->() { return (&(this->operator*())); }

		RBIterator const &	operator++() {
			
		}
		RBIterator const &	operator++(int) {}
		RBIterator const &	operator--() {}
		RBIterator const &	operator--(int) {}

		private:
			pointer	data;

	};

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
			void	swap_nodes(node_type *node1, node_type *node2)
			{
				node_type *tmp;
				node_type **tmp_addr;

				tmp_addr = this->get_reference(node1);
				*tmp_addr = node2;
				tmp_addr = this->get_reference(node2);
				*tmp_addr = node1;
				tmp_addr = NULL;
				
				tmp = node1->parent;
				node1->parent = node2->parent;
				node2->parent = tmp;

				tmp = node1->left;
				node1->left = node2->parent;
				node2->left = tmp;

				tmp = node1->right;
				node1->right = node2->parent;
				node2->right = tmp;
			}
			void		replace_node(node_type *oldNode, node_type * newNode)
			{
				this->swap_nodes(oldNode, newNode);
				this->destroy_node(oldNode);
			}
			node_type *insert(value_type const & value)
			{
				node_type	*current_node = this->root;
				node_type	*new_node = node_new(NULL, value);
				if (!this->root)
				{
					this->root = new_node;
				}
				while (current_node)
				{
					if (current_node->value == value)
					{
						this->replace_node(current_node, new_node);
						break ;
					}
					if (value < current_node->value)
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
				return (new_node);
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
								this->rotate_right(new_node);
							this->rotate_left(parent);
						}
						else
						{
							if (grandparent && grandparent->left == parent)
								this->rotate_left(new_node);
							this->rotate_right(parent);
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
			void	rotate_left(node_type *child)
			{
				node_type *parent = this->getParent(child);
				node_type *grandparent = this->getGrandparent(child);
				node_type **parent_addr = this->get_reference(parent);
				if (!child || !parent)
					return ;
				
				*parent_addr = child;
				child->parent = grandparent;
				parent->left = child->right;
				if (child->right)
					child->right->parent = parent;
				child->right = parent;
				parent->parent = child;
			}
			void	rotate_right(node_type *child)
			{
				node_type *parent = this->getParent(child);
				node_type *grandparent = this->getGrandparent(child);
				node_type **parent_addr = this->get_reference(parent);
				if (!child || !parent)
					return ;
				
				*parent_addr = child;
				child->parent = grandparent;
				parent->right = child->left;
				if (child->left)
					child->left->parent = parent;
				child->left = parent;
				parent->parent = child;
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
				delete_tree(node->left);
				delete_tree(node->right);
				destroy_node(node);
			}

			void	destroy_node(node_type *node)
			{
				node_type **node_addr = this->get_reference(node);
				__alloc.deallocate(node, 1);
				*node_addr = NULL;
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
