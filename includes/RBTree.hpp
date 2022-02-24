#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#define RB_BLACK 0
#define RB_RED 1

#include <functional> // std::less
#include <memory>	  // std::allocator
#include "RBIterator.hpp"
#include "ConstRBIterator.hpp"

namespace ft
{
	template <class ValueType, class Compare>
	struct Node
	{
		typedef Node node_type;
		typedef Node *node_pointer;
		typedef Node const *const_node_pointer;
		typedef ValueType value_type;
		typedef const ValueType const_value_type;

		ValueType value;
		Node *left;
		Node *right;
		Node *parent;
		bool color;

		Node(ValueType const &val)
			: value(val), left(NULL), right(NULL), parent(NULL), color(RB_BLACK)
		{
		}

		Node()
			: value(), left(NULL), right(NULL), parent(NULL), color(RB_BLACK)
		{
		}

		value_type &operator*()
		{
			return (this->value);
		}
		const_value_type &operator*() const
		{
			return (this->value);
		}
		value_type *operator->()
		{
			return (&(this->operator*()));
		}
		const_value_type *operator->() const
		{
			return (&(this->operator*()));
		}

		node_type *max(node_type *node)
		{
			if (!node)
				return (NULL);
			if (node->right)
				return (this->max(node->right));
			return (node);
		}
		node_type *max()
		{
			return (this->max(this));
		}
		node_type const *max(node_type const *node) const
		{
			if (!node)
				return (NULL);
			if (node->right)
				return (this->max(node->right));
			return (node);
		}
		node_type *max() const
		{
			return (this->max(this));
		}
		node_type *min(node_type *node)
		{
			if (!node)
				return (NULL);
			if (node->left)
				return (this->min(node->left));
			return (node);
		}
		node_type *min()
		{
			return (this->min(this));
		}
		const node_type *min(node_type const *node) const
		{
			if (node == NULL)
				return (NULL);
			if (node->left)
				return (this->min(node->left));
			return (node);
		}
		const node_type *min() const
		{
			return (this->min(this));
		}

		node_type *get_root()
		{
			node_type *root = this;
			while (root->parent)
			{
				root = root->parent;
			}
			return (root);
		}

		const node_type *prev() const
		{
			if (!this->parent || this->left)
				return (this->max(this->left));
			return (this->getNextLesserParent());
		}
		node_type *prev()
		{
			return (const_cast<node_type *>(static_cast<const Node &>(*this).prev()));
		}

		const node_type *next() const
		{
			if (!this->parent)
				return (this->min());
			if (this->right)
				return (this->min(this->right));
			return (this->getNextGreaterParent());
		}
		node_type *next()
		{
			return (const_cast<node_type *>(static_cast<const Node &>(*this).next()));
		}

	private:
		bool values_equal(value_type const &value1, value_type const &value2) const
		{
			return (!Compare()(value1, value2) && !Compare()(value2, value1));
		}
		bool values_less_than(value_type const &value1, value_type const &value2) const
		{
			return (Compare()(value1, value2));
		}

		const_node_pointer getNextGreaterParent() const
		{
			if (!this->parent)
				return (NULL);
			const_node_pointer current = this;
			while (current && current->parent && current->parent->right == current)
				current = current->parent;
			return (current->parent);
		}
		const_node_pointer getNextLesserParent() const
		{
			if (!this->parent)
				return (NULL);
			const_node_pointer current = this;
			while (current && current->parent && current->parent->left == current)
				current = current->parent;
			if (current->parent)
				return (current->parent);
			return (current);
		}
	};

	template <class ValueType, class Compare>
	Node<ValueType, Compare> const operator++(Node<ValueType, Compare> &a)
	{
		Node<ValueType, Compare> *next;

		next = a.min(a.right);
		if (!next)
			next = a.parent;
	}

	template <class ValueType, class Compare = std::less<ValueType>, class Allocator = std::allocator<Node<ValueType, Compare> > >
	class RB_Tree
	{
	public:
		typedef Node<ValueType, Compare> node_type;
		typedef Node<const ValueType, Compare> const_node_type;
		typedef ValueType value_type;
		typedef const ValueType const_value_type;
		typedef Allocator allocator_type;
		typedef typename allocator_type::size_type size_type;

		typedef RBIterator<value_type, node_type> iterator;
		typedef ConstRBIterator<value_type, node_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		node_type root;

		RB_Tree(Compare const & c) : root(), __alloc(allocator_type()), __comp(c)
		{
			return;
		}
		~RB_Tree()
		{
			this->delete_tree(this->root.left);
		}

		node_type *iterative_search(value_type const &value) const
		{
			node_type *node = this->root.left;
			while (node)
			{
				if (this->values_less_than(node->value, value))
					node = node->right;
				else if (this->values_less_than(value, node->value))
					node = node->left;
				else
					break;
			}
			return (node);
		}
		iterator search(value_type const &value)
		{
			node_type *node = iterative_search(value);
			if (!node)
				return (this->end());
			return (iterator(node));
		}
		const_iterator search(value_type const &value) const
		{
			node_type *node = iterative_search(value);
			if (!node)
				return (this->end());
			return (const_iterator(node));
		}
		void swap_nodes(node_type *node1, node_type *node2)
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

			if (this->root.left == node1)
				this->root.left = node2;
			else if (this->root.left == node2)
				this->root.left = node1;

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
		void replace_node(node_type *oldNode, node_type *newNode)
		{
			this->swap_nodes(oldNode, newNode);
			this->destroy_node(oldNode);
		}
		bool values_equal(value_type const &value1, value_type const &value2) const
		{
			return (!this->__comp(value1, value2) && !this->__comp(value2, value1));
		}
		bool values_less_than(value_type const &value1, value_type const &value2) const
		{
			return (this->__comp(value1, value2));
		}

		iterator insert(node_type *hint, value_type const &value)
		{
			node_type *current_node = hint;
			node_type *new_node = node_new(NULL, value);
			iterator it;
			if (!this->root.left)
			{
				this->root.left = new_node;
				new_node->parent = &this->root;
			}
			while (current_node)
			{
				if (values_equal(current_node->value, value))
				{
					this->replace_node(current_node, new_node);
					break;
				}
				if (values_less_than(value, current_node->value))
				{
					if (!current_node->left)
					{
						new_node->parent = current_node;
						current_node->left = new_node;
						current_node->left->color = RB_RED;
						break;
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
						break;
					}
					else
						current_node = current_node->right;
				}
			}
			this->recolor_insert_iter(new_node);
			it = iterator(new_node);
			return (it);
		}
		iterator insert(value_type const &value)
		{
			return (this->insert(this->root.left, value));
		}
		iterator insert(const_iterator hint, value_type const &value)
		{
			iterator it = reinterpret_cast<iterator &>(hint);
			return (this->insert(it, value));
		}
		iterator insert(iterator hint, value_type const &value)
		{
			node_type *node = reinterpret_cast<node_type *>(&(*hint));
			return (this->insert(node, value));
		}
		void recolor_insert_iter(node_type *node)
		{
			while (node && node->parent && node->parent->color == RB_RED)
			{
				if (node->parent == this->root.left)
				{
					node->color = RB_BLACK;
					return;
				}
				node_type *parent = getParent(node);
				node_type *grandparent = getGrandparent(node);
				node_type *uncle = getUncle(node);
				if (node->parent == grandparent->left)
				{
					// Fix double red in left subtree
					if (uncle && uncle->color == RB_RED)
					{
						// grandparent has two red children
						node->parent->color = RB_BLACK;
						uncle->color = RB_BLACK;
						// if (grandparent)
						grandparent->color = RB_RED;
						node = grandparent;
					}
					else
					{
						// grandparent has one black and one red child
						if (node == parent->right)
						{
							node = parent;
							this->rotateLeft(node);
						}
						node->parent->color = RB_BLACK;
						node->parent->parent->color = RB_RED;
						this->rotateRight(node->parent->parent);
					}
				}
				else
				{
					// Fix double red in right subtree
					if (uncle && uncle->color == RB_RED)
					{
						// grandparent has two red children
						node->parent->color = RB_BLACK;
						uncle->color = RB_BLACK;
						// if (grandparent)
						grandparent->color = RB_RED;
						node = grandparent;
					}
					else
					{
						// grandparent has one black and one red child
						if (node == parent->left)
						{
							node = parent;
							this->rotateRight(node);
						}
						node->parent->color = RB_BLACK;
						node->parent->parent->color = RB_RED;
						this->rotateLeft(node->parent->parent);
					}
				}
			}
			this->root.color = RB_BLACK;
			if (this->root.left)
				this->root.left->color = RB_BLACK;
		}

		void swap(RB_Tree<ValueType, Compare, Allocator> &other)
		{
			node_type *tmp;

			tmp = this->root.left;
			this->root.left = other.root.left;
			if (this->root.left)
				this->root.left->parent = &this->root;
			other.root.left = tmp;
			if (other.root.left)
				other.root.left->parent = &other.root;
		}
		node_type *rotateLeft(node_type *node)
		{
			node_type *parent = node;
			node_type *grandparent = this->getParent(parent);
			node_type *child = parent->right;

			if (!child || !parent || parent == &this->root || parent->right != child)
				return (NULL);

			// Attach left child of child to parent
			if (child->left)
				child->left->parent = parent;
			parent->right = child->left;

			// Attach child to root or grandparent
			if (!grandparent)
			{
				this->root.left = child;
				child->parent = &this->root;
			}
			else if (grandparent->left == parent)
			{
				grandparent->left = child;
				child->parent = grandparent;
			}
			else
			{
				grandparent->right = child;
				child->parent = grandparent;
			}

			// Reattach parent as child of child
			parent->parent = child;
			child->left = parent;

			return (child);
		}
		node_type *rotateRight(node_type *node)
		{
			node_type *parent = node;
			node_type *child = parent->left;
			node_type *grandparent = this->getParent(parent);

			if (!child || !parent || parent == &this->root || parent->left != child)
				return (NULL);

			// Attach left child of child to parent
			if (child->right)
				child->right->parent = parent;
			parent->left = child->right;

			// Attach child to root or grandparent
			if (!grandparent)
			{
				this->root.left = child;
				child->parent = &this->root;
			}
			else
			{
				if (grandparent->right == parent)
					grandparent->right = child;
				else
					grandparent->left = child;
				child->parent = grandparent;
			}

			// Reattach parent as child of child
			parent->parent = child;
			child->right = parent;

			return (child);
		}
		node_type *getSibling(node_type *node)
		{
			if (!node || !node->parent)
				return (NULL);
			if (node->parent->right == node)
				return (node->parent->left);
			return (node->parent->right);
		}
		node_type *getGrandparent(node_type *node)
		{
			if (!node || !node->parent)
				return (NULL);
			return (node->parent->parent);
		}
		node_type *getParent(node_type *node)
		{
			if (!node)
				return (NULL);
			return (node->parent);
		}
		node_type *getUncle(node_type *node)
		{
			if (!node)
				return (NULL);
			return (this->getSibling(node->parent));
		}

		node_type *max(node_type *node)
		{
			if (!node)
				return (&(this->root));
			return (node->max());
		}
		node_type *max()
		{
			return (this->max(this->root.left));
		}
		const node_type *max(node_type *node) const
		{
			if (!node)
				return (&(this->root));
			return (node->max());
		}
		const node_type *max() const
		{
			return (this->max(this->root.left));
		}
		node_type *min(node_type *node)
		{
			if (!node)
				return (&(this->root));
			return (node->min());
		}
		const node_type *min(node_type *node) const
		{
			if (!node)
				return ((&(this->root)));
			return (node->min());
		}
		node_type *min()
		{
			return (this->min(this->root.left));
		}
		const node_type *min() const
		{
			return (this->min(this->root.left));
		}

		iterator begin()
		{
			iterator it(this->min());
			return (it);
		}
		iterator end()
		{
			iterator it(this->max());
			++it;
			return (it);
		}
		const_iterator begin() const
		{
			const_iterator it(this->min());
			return (it);
		}
		const_iterator end() const
		{
			const_iterator it(this->max());
			++it;
			return (it);
		}
		reverse_iterator rbegin()
		{
			iterator it(this->max());
			return (it);
		}
		reverse_iterator rend()
		{
			iterator it(this->min());
			--it;
			return (it);
		}

		size_type get_black_height(node_type *node) const
		{
			if (node == NULL)
				return (1);
			size_type left_height = this->get_black_height(node->left);
			if (left_height == 0)
				return (0);
			size_type right_height = this->get_black_height(node->right);
			if (right_height == 0)
				return (0);
			if (left_height != right_height)
				return (0);
			return (left_height);
		}
		size_type get_black_height() const
		{
			if (this->root.left && this->root.left->color == RB_RED)
				return (0);
			return (this->get_black_height(this->root.left));
		}

		bool is_red_black() const
		{
			if (this->root.left && this->root.left->color == RB_RED)
				return (false);
			if (!this->get_black_height())
				return (false);
			node_type *node = this->root.left;
			while (node && const_iterator(node) != this->end())
			{
				if (node->color == RB_RED)
				{
					if (node->left && node->left->color == RB_RED)
						return (false);
					if (node->right && node->right->color == RB_RED)
						return (false);
				}
				node = node->next();
			}
			return (true);
		}

		node_type **get_reference(node_type *node)
		{
			if (!node)
				return (NULL);
			if (!node->parent && this->root.left == node)
				return (&this->root.left);
			if (node->parent->right == node)
				return (&(node->parent->right));
			else if (node->parent->left == node)
				return (&(node->parent->left));
			return (NULL);
		}

		node_type **get_reference_safe(node_type *node)
		{
			if (!node->parent && this->root.left == node)
				return (&this->root.left);
			if (!node->parent)
				return (NULL);
			if (node->parent->right == node)
				return (&node->parent->right);
			if (node->parent->left == node)
				return (&node->parent->left);
			return (NULL);
		}
		void delete_node(const_iterator &hint, value_type const &value)
		{
			iterator &it = reinterpret_cast<iterator &>(hint);
			this->delete_node(it, value);
		}
		void delete_node(iterator hint, value_type const &value)
		{
			node_type *node = reinterpret_cast<node_type *>(&(*hint));
			this->delete_node(node, value);
		}
		void delete_node(node_type *node, value_type const &value)
		{
			if (!node)
				return;
			if (this->values_less_than(value, node->value))
				this->delete_node(node->left, value);
			else if (values_less_than(node->value, value))
				this->delete_node(node->right, value);
			else // value == node->value
			{
				node_type **node_addr = this->get_reference_safe(node);
				if (!node->left && !node->right)
				{
					node_type *sibling = this->getSibling(node);
					if (node_addr)
						*node_addr = NULL;
					if (node->color == RB_BLACK)
						this->fix_double_black(node->parent, sibling);
					this->destroy_node(node);
				}
				else if (!node->left)
				{
					if (node_addr)
						*node_addr = node->right;
					node->right->parent = node->parent;
					if (node->color == RB_RED || node->right->color == RB_RED)
						node->right->color = RB_BLACK;
					else
						this->fix_double_black(node->right);
					this->destroy_node(node);
				}
				else if (!node->right)
				{
					if (node_addr)
						*node_addr = node->left;
					node->left->parent = node->parent;
					if (node->color == RB_RED || node->left->color == RB_RED)
						node->left->color = RB_BLACK;
					else
						this->fix_double_black(node->left);
					this->destroy_node(node);
				}
				else
				{
					this->swap_nodes(node, this->max(node->left));
					this->delete_node(node, value);
				}
			}
			return;
		}

		void fix_double_black(node_type *parent, node_type *sibling)
		{
			if (!sibling)
			{
				this->fix_double_black(parent);
				return;
			}
			if (sibling->color == RB_RED)
			{
				parent->color = RB_RED;
				sibling->color = RB_BLACK;
				if (parent->left == sibling)
				{
					this->rotateRight(parent);
					this->fix_double_black(parent, sibling->right);
				}
				else
				{
					this->rotateLeft(parent);
					this->fix_double_black(parent, sibling->left);
				}
			}
			else
			{
				if (sibling->left && sibling->left->color == RB_RED)
				{
					if (parent->left == sibling)
					{
						sibling->left->color = sibling->color;
						sibling->color = parent->color;
						this->rotateRight(parent);
					}
					else
					{
						sibling->left->color = parent->color;
						this->rotateRight(sibling);
						this->rotateLeft(parent);
					}
					parent->color = RB_BLACK;
				}
				else if (sibling->right && sibling->right->color == RB_RED)
				{
					if (parent->right == sibling)
					{
						sibling->right->color = sibling->color;
						sibling->color = parent->color;
						this->rotateLeft(parent);
					}
					else
					{
						sibling->right->color = parent->color;
						this->rotateLeft(sibling);
						this->rotateRight(parent);
					}
					parent->color = RB_BLACK;
				}
				else // 2 Black Children
				{
					sibling->color = RB_RED;
					if (parent->color == RB_BLACK)
						this->fix_double_black(parent);
					else
						parent->color = RB_BLACK;
				}
			}
		}

		void fix_double_black(node_type *node)
		{
			if (!node || node == &this->root)
				return;
			node_type *sibling = this->getSibling(node);
			node_type *parent = node->parent;
			this->fix_double_black(parent, sibling);
		}

		void delete_tree(node_type *node)
		{
			if (!node)
				return;
			delete_tree(node->left);
			delete_tree(node->right);
			if (this->root.left == node)
				this->root.left = NULL;
			if (node->parent)
			{
				if (node->parent->right == node)
					node->parent->right = NULL;
				else if (node->parent->left == node)
					node->parent->left = NULL;
			}
			destroy_node(node);
		}

		void destroy_node(node_type *node)
		{
			if (!node)
				return;
			if (this->root.left == node)
				this->root.left = NULL;
			else if (node->parent && node->parent->right == node)
				node->parent->right = NULL;
			else if (node->parent && node->parent->left == node)
				node->parent->left = NULL;
			this->deallocate_node(node);
		}

		void deallocate_node(node_type *node)
		{
			if (node)
			{
				this->__alloc.destroy(node);
				this->__alloc.deallocate(node, 1);
			}
		}

		size_t size_subtree(node_type *node) const
		{
			if (!node)
				return (0);
			return (this->size_subtree(node->left) + 1 + this->size_subtree(node->right));
		}

		size_t size() const
		{
			return (size_subtree(this->root.left));
		}

		size_t max_size() const
		{
			return (this->__alloc.max_size());
		}

		node_type *lower_bound(const value_type &v)
		{
			node_type *current = this->root.left;
			node_type *best_guess = &this->root;

			while (current)
			{
				if (this->values_less_than(current->value, v))
				{
					if (!current->right)
						return (best_guess);
					current = current->right;
				}
				else if (this->values_less_than(v, current->value))
				{
					if (best_guess == &this->root || this->values_less_than(current->value, best_guess->value))
						best_guess = current;
					if (!current->left)
						return (best_guess);
					current = current->left;
				}
				else
					return (current);
			}
			return (best_guess);
		}

		const node_type *lower_bound(const value_type &v) const
		{
			const node_type *current = this->root.left;
			const node_type *best_guess = &this->root;

			while (current)
			{
				if (this->values_less_than(current->value, v))
				{
					if (!current->right)
						return (best_guess);
					current = current->right;
				}
				else if (this->values_less_than(v, current->value))
				{
					if (best_guess == &this->root || this->values_less_than(current->value, best_guess->value))
						best_guess = current;
					if (!current->left)
						return (best_guess);
					current = current->left;
				}
				else
					return (current);
			}
			return (best_guess);
		}

	private:
		node_type *initialize_node(node_type *node, node_type *parent, value_type const &value)
		{
			node->value = value;
			node->left = NULL;
			node->right = NULL;
			node->parent = parent;
			node->color = RB_BLACK;
			return (node);
		}
		node_type *node_new(node_type *parent, value_type const &value)
		{
			node_type *node = __alloc.allocate(1);
			__alloc.construct(node, value);
			node->parent = parent;
			return (node);
		}
		allocator_type __alloc;
		Compare __comp;
	};
}

#endif
