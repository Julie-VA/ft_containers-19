/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 10:45:07 by rvan-aud          #+#    #+#             */
/*   Updated: 2022/03/21 17:57:53 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "utils.hpp"

# define L 0
# define R 1

namespace	ft
{
	template <class T>class map_iterator;

	template < class Key, class T >
	class	Node
	{
		public:

			//---- Member types ----//
			typedef size_t	size_type;

			Node					*parent;
			Node					*left;
			Node					*right;
			Node					*null;
			int						side;
			ft::pair<const Key, T>	data;

			//---- Constructors ----//

			/* Default constructor */
			Node() : parent(NULL), left(NULL), right(NULL), side(0) {};

			/* Constructs a normal node */
			Node(Node *parent, int side, const ft::pair<Key, T> val, Node *null)
			: parent(parent), left(null), right(null), null(null), side(side), data(val) {};

			/* Constructs null node */
			Node(int side, const ft::pair<Key, T> val)
			: parent(NULL), left(NULL), right(NULL), side(side), data(val) {};

			//---- Destructor ----//
			~Node() {};

			/* Recursively deletes every element in the tree, including the null node. Called by the map destructor */
			// void	delete_tree(std::allocator<Node<Key, T> > alloc)
			// {
			// 	if (this == this->null)
			// 	{
			// 		alloc.destroy(null);
			// 		alloc.deallocate(null, 1);
			// 		return ;
			// 	}
			// 	if (!(this->left == this->null && this->right == this->null))
			// 	{
			// 		if (this->left != this->null)
			// 			this->left->delete_tree(alloc);
			// 		if (this->right != this->null)
			// 			this->right->delete_tree(alloc);
			// 	}
			// 	if (this->parent == NULL)
			// 	{
			// 		alloc.destroy(null);
			// 		alloc.deallocate(null, 1);
			// 	}
			// 	alloc.destroy(this);
			// 	alloc.deallocate(this, 1);
			// }

			/* Recursively calculate tree's size */
			size_type	size() const
			{
				if (this == this->null || (this->left == NULL && this->right == NULL))
					return (0);
				return(this->left->size() + this->right->size() + 1);
			}
	};

	template < class Key, class T, class Compare,
		class Alloc = std::allocator<Node<Key, T> > >
	class	BST
	{
		public:

			//---- Member types ----//
			typedef Key															key_type;
			typedef T															mapped_type;
			typedef Compare														key_compare;
			typedef ft::pair<const key_type, mapped_type>						value_type;
			typedef Alloc														allocator_type;
			typedef Node<Key, T>												node_type;
			typedef size_t														size_type;
			typedef typename ft::map_iterator<pair<const Key, T> >				iterator;
			typedef typename ft::map_iterator<const ft::pair<const Key, T> >	const_iterator;

			node_type		*root;
			node_type		*null;
			allocator_type	alloc;
			Compare			comp;

			//---- Constructors ----//

			/* Default constructor : sets up the tree by creating a null node, the tree is empty but that null node is what every leaf is going
			to point to */
			BST(const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
			:
				alloc(alloc),
				comp(comp)
			{
				this->null = this->alloc.allocate(1);
				this->alloc.construct(this->null, node_type(-1, value_type()));
				this->null->null = this->null; //need pointer on null in the node as well for iterators
				this->root = this->null;
			};

			/* Same as default constructor but we're passing key_compare as an argument, we're using the dummy to easily
			differentiate between this one and default */
			BST(const key_compare& comp,
				const allocator_type& alloc, bool dummy)
			:
				alloc(alloc),
				comp(comp)
			{
				(void)dummy;
				this->null = this->alloc.allocate(1);
				this->alloc.construct(this->null, node_type(-1, value_type()));
				this->null->null = this->null; //need pointer on null in the node as well for iterators
				this->root = this->null;
			};

			//---- Destructor ----//
			~BST() {};

		private:

			/* Allocates and constructs new nodes, the first condition is for the very first element */
			void	new_node(const value_type& val, bool side, node_type *parent)
			{
				if (this->root->side == -1)
				{
					this->root = this->alloc.allocate(1);
					this->alloc.construct(this->root, node_type(NULL, 0, val, this->null));
					this->root = this->root;
					this->null->parent = this->root;
				}
				else
				{
					node_type	*tmp;

					tmp = this->alloc.allocate(1);
					if (side == L)
					{
						this->alloc.construct(tmp, node_type(parent, L, val, this->null));
						parent->left = tmp;
					}
					else if (side == R)
					{
						this->alloc.construct(tmp, node_type(parent, R, val, this->null));
						parent->right = tmp;
					}
				}
			};

		public:

			//---- Capacity ----//

			/* Return true if the container is empty, false if it isn't */
			bool	empty() const
			{
				if (this->root->left == NULL && this->root->right == NULL)
					return (true);
				return (false);
			};

			/* Returns size of the container (number of elements) */
			size_type	size() const
			{
				if (this->empty() == 1)
					return (0);
				return (this->root->size());
			};

			/* Returns the maximum size of elements the map can hold */
			size_type	max_size() const {return (this->alloc.max_size());};

			//---- Modifiers ----//

			/* Iteratively inserts new nodes in the tree */		
			ft::pair<iterator,bool>	insert(const value_type& val)
			{
				if (this->root->side == -1)
				{
					this->new_node(val, 0, NULL);
					return (ft::pair<iterator, bool>(iterator(this->root), true));
				}
				node_type	*tmp = this->root;
				while (1)
				{
					if (this->comp(val.first, tmp->data.first))
					{
						if (tmp->left != this->null)
						{
							tmp = tmp->left;
							continue ;
						}
						this->new_node(val, L, tmp);
						return (ft::pair<iterator, bool>(iterator(tmp->left), true));
					}
					else if (this->comp(tmp->data.first, val.first))
					{
						if (tmp->right != this->null)
						{
							tmp = tmp->right;
							continue ;
						}
						this->new_node(val, R, tmp);
						return (ft::pair<iterator, bool>(iterator(tmp->right), true));
					}
					return (ft::pair<iterator, bool>(iterator(tmp), false));
				}
			}

			/* Recursively inserts new nodes in the tree */	
			// ft::pair<iterator,bool>	insert(const value_type& val)
			// {
			// 	if (this->node->side == -1)
			// 	{
			// 		this->new_node(val, 0);
			// 		return (ft::pair<iterator, bool>(iterator(this->node), true));
			// 	}
			// 	else if (this->comp(val.first, this->node->data.first))
			// 	{
			// 		if (this->node->left != this->null)
			// 		{
			// 			this->node = this->node->left;
			// 			return (this->insert(val));
			// 		}
			// 		else
			// 		{
			// 			this->new_node(val, L);
			// 			return (ft::pair<iterator, bool>(iterator(this->node->left), true));
			// 		}
			// 	}
			// 	else if (this->comp(this->node->data.first, val.first))
			// 	{
			// 		if (this->node->right != this->null)
			// 		{
			// 			this->node = this->node->right;
			// 			return (this->insert(val));
			// 		}
			// 		else
			// 		{
			// 			this->new_node(val, R);
			// 			return (ft::pair<iterator, bool>(iterator(this->node->right), true));
			// 		}
			// 	}
			// 	return (ft::pair<iterator, bool>(iterator(this->node), false));
			// };

			//https://www.youtube.com/watch?v=DkOswl0k7s4
			//https://www.geeksforgeeks.org/binary-search-tree-set-2-delete/#:~:text=1)%20Node%20to%20be%20deleted,Simply%20remove%20from%20the%20tree.&text=3)%20Node%20to%20be%20deleted,predecessor%20can%20also%20be%20used.
			//If leaf : delete node and parent’s left or right child to null
			//If one child : parent of node points to child, child points to parent and delete node
			//If 2 children : get min in right subtree (last left), assign that min to node, parent of node points to min,
			//min points to old left and right child, min points to old parent, old min parent points to null and delete node
			/* Removes nodes from the tree at position */
			void	erase(iterator position)
			{
				node_type	*old = position.base();

				if (old->left == this->null && old->right == this->null) //if node is a leaf
				{
					if (old == this->root)
					{
						this->root = this->null;
						if (old->side == L)
							old->left = old->parent;
					}
					else
					{
						if (old->side == L)
							old->parent->left = this->null;
						else if (old->side == R)
							old->parent->right = this->null;
					}
					this->alloc.destroy(old);
					this->alloc.deallocate(old, 1);
				}
				else if (old->left != this->null && old->right == this->null) //if node has a left child
				{
					if (old == this->root)
						this->root = old->left;
					else
					{
						if (old->side == L)
							old->parent->left = old->left;
						else if (old->side == R)
							old->parent->right = old->left;
					}
					old->left->parent = old->parent;
					old->left->side = old->side;
					this->alloc.destroy(old);
					this->alloc.deallocate(old, 1);
				}
				else if (old->left == this->null && old->right != this->null) //if node has a right child
				{
					if (old == this->root)
						this->root = old->right;
					else
					{
						if (old->side == L)
							old->parent->left = old->right;
						else if (old->side == R)
							old->parent->right = old->right;
					}
					old->right->parent = old->parent;
					old->right->side = old->side;
					this->alloc.destroy(old);
					this->alloc.deallocate(old, 1);
				}
				else //if node has 2 children
				{
					node_type	*tmp = old->right;

					while (tmp->left != this->null) //get minimum in right subtree
						tmp = tmp->left;
					tmp->left = old->left;
					tmp->left->parent = tmp;
					if (tmp->right != this->null)
					{
						tmp->right->parent = tmp->parent;
						tmp->right->side = tmp->side;
						if (tmp->side == L)
							tmp->parent->left = tmp->right;
						else if (tmp->side == R)
							tmp->parent->right = tmp->right;
					}
					else if (tmp->side == L)
						tmp->parent->left = this->null;
					else if (tmp->side == R)
						tmp->parent->right = this->null;
					tmp->right = old->right;
					tmp->right->parent = tmp;
					tmp->parent = old->parent;
					tmp->side = old->side;
					if (old == this->root)
						this->root = tmp;
					else
					{
						if (old->side == L)
							old->parent->left = tmp;
						else if (old->side == R)
							old->parent->right = tmp;
					}
					this->alloc.destroy(old);
					this->alloc.deallocate(old, 1);
				}
				this->null->parent = this->root;
			}

			/* Exchanges the content of the container with the contents of x */
			void swap (BST& x)
			{
				if (&x == this)
					return ;
				node_type	*tmp_root = this->root;
				node_type	*tmp_null = this->null;
				this->root = x.root;
				this->null = x.null;
				x.root = tmp_root;
				x.null = tmp_null;
			}

			/* Returns iterator to element whose key is k */
			iterator find (const key_type& k)
			{
				node_type	*tmp = this->root;

				while (tmp != this->null && tmp->data.first != k)
				{
					if (this->comp(k, tmp->data.first))
						tmp = tmp->left;
					else
						tmp = tmp->right;
				}
				return (iterator(tmp));
			};
			const_iterator find (const key_type& k) const
			{
				node_type	*tmp = this->root;

				while (tmp != this->null && tmp->data.first != k)
				{
					if (this->comp(k, tmp->data.first))
						tmp = tmp->left;
					else
						tmp = tmp->right;
				}
				return (const_iterator(tmp));
			};

			/* Deletes the null node */
			void	delete_null()
			{
				this->alloc.destroy(this->null);
				this->alloc.deallocate(this->null, 1);
			}

			/* Recursively deletes every element in the tree, including the null node, called by the map destructor */
			// void	delete_tree() {this->root->delete_tree(this->alloc);};
	};
}
