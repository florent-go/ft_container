#ifndef BST_HPP
# define BST_HPP

#include <iostream>
#include "pair.hpp"
#include "utils.hpp"
#include "btree_iterator.hpp"

# define BLACK 0
# define RED 1

# include "reverse_iterator.hpp"

namespace ft
{
	template<class T, class Compare, class Alloc >
	class RBtree
	{
		public:
			typedef	RBtree														tree;
			typedef T															value_type;
			typedef typename value_type::first_type								key_type;
			typedef typename value_type::second_type							mapped_type;
			typedef Compare														value_compare;
			typedef typename Alloc::template rebind<ft::node<T> >::other		allocator_type;
			typedef typename ft::RBtree_iterator<value_type>					iterator;
			typedef typename ft::RBtree_iterator_const<value_type>				const_iterator;
			typedef typename ft::reverse_iterator<iterator> 					reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>				const_reverse_iterator;

			typedef size_t														size_type;
			
			typedef ft::node<T>						node_type;
			typedef ft::node<const T>*				const_node_ptr;
			typedef node_type*						node_ptr;


		public:
			node_ptr				_root;
			allocator_type			_node_alloc;
			value_compare			_comp;
			node_ptr				_nil;
			size_type				_size;

		public:
			RBtree(void)
			{
				_nil =_node_alloc.allocate(1);
				_node_alloc.construct(_nil, value_type());
				_nil->_right = NULL;
				_nil->_left = NULL;
				_nil->_color = BLACK;
				_nil->_nil = NULL;

				_root = _nil;
				_size = 0;
			}

			RBtree(const value_type &val)
			{
				_nil =_node_alloc.allocate(1);
				_node_alloc.construct(_nil, val);
				_nil->_right = NULL;
				_nil->_left = NULL;
				_nil->_color = BLACK;
				_nil->_nil = NULL;

				_root = _nil;
				_size = 0;
			}

			// ===========================DESTRCUTEUR============================

			~RBtree(void)
			{
				btree_clear(_root);
			}

			// ===========================BEGIN============================

			node_ptr get_last(void) const
			{
				node_ptr tmp = _root;
				if (tmp != tmp->_nil)
				{
					while (tmp->_right != tmp->_nil)
						tmp = tmp->_right;
				}
				return (tmp);
			}

			iterator begin (void)
			{
				node_ptr tmp = _root;
				if (tmp != _nil)
				{
					while (tmp->_left != tmp->_nil)
						tmp = tmp->_left;
				}
				return (iterator(tmp, get_last()));
			}

			const_iterator begin(void) const
			{
				const_node_ptr tmp = reinterpret_cast<const_node_ptr>(_root);
				if (tmp == reinterpret_cast<const_node_ptr>(_nil))
					return (const_iterator(tmp, reinterpret_cast<const_node_ptr>(get_last())));

				if (tmp != reinterpret_cast<const_node_ptr>(_nil))
				{
					while (tmp->_left != tmp->_nil)
						tmp = tmp->_left;
				}
				return (const_iterator(tmp, reinterpret_cast<const_node_ptr>(get_last())));
			}
			// ===========================END============================

			iterator end(void)
			{
				return (iterator(_nil, get_last()));
			}

			const_iterator end(void) const
			{
				return (const_iterator( reinterpret_cast<const_node_ptr>(_nil), reinterpret_cast<const_node_ptr>(get_last())));
			}
			// ==========================SIZE============================

			size_type max_size( void ) const {
				return (std::numeric_limits<size_type>::max() / (sizeof(node_type) - sizeof(node_ptr)));
			}

			size_type size() const
			{
				return (_size);
			}

			// ===========================FIND=============================

			node_ptr find_key(const value_type & k) const
			{
				node_ptr node = _root;

				while (node != _nil)
				{
					if (_comp(node->_value.first, k.first) == false && _comp(k.first, node->_value.first) == false)
						return (node);
					if (_comp(node->_value.first, k.first))
						node = node->_right;
					else if (_comp(k.first, node->_value.first))
						node = node->_left;
				}

				return (_nil);
			}

			// ===========================CLEAR=================================

			void	btree_clear(node_ptr root)
			{
				if (root == _nil)
					return ;
				btree_clear(root->_left);
				btree_clear(root->_right);
				_node_alloc.destroy(root);
				_node_alloc.deallocate(root, 1);
				_root = _nil;
				_size = 0;
			}

			// ===========================SWAP==================================

			void	btree_swap(RBtree &x)
			{
				node_ptr		tmp_root = _root;
				allocator_type	tmp_node_alloc = _node_alloc;
				size_type		tmp_size = _size;
				value_compare	tmp_comp = _comp;
				node_ptr		tmp_nil = _nil;

				_root = x._root;
				_node_alloc = x._node_alloc;
				_size = x._size;
				_comp = x._comp;
				_nil = x._nil;

				x._root = tmp_root;
				x._node_alloc = tmp_node_alloc;
				x._size = tmp_size;
				x._comp = tmp_comp;
				x._nil = tmp_nil;
			}

			// ===========================Erase Fix=============================

			void delete_fixup(node_ptr x)
			{
				node_ptr	w;
				while(x != _root && x->_color == BLACK)
				{
					if(x == x->_parent->_left)
					{
						w = x->_parent->_right;
						if(w->_color == RED)
						{
							w->_color = BLACK;
							x->_parent->_color = RED;
							left_rotate(x->_parent);
							w = x->_parent->_right;
						}
						if(w->_left->_color == BLACK && w->_right->_color == BLACK)
						{
							w->_color = RED;
							x = x->_parent;
						}
						else
						{
							if(w->_right->_color == BLACK)
							{
								w->_left->_color = BLACK;
								w->_color = RED;
								right_rotate(w);
								w = x->_parent->_right;
							}
							w->_color = x->_parent->_color;
							x->_parent->_color = BLACK;
							w->_right->_color = BLACK;
							left_rotate(x->_parent);
							x = _root;
						}
					}
					else
					{
						w = x->_parent->_left;
						if(w->_color == RED)
						{
							w->_color = BLACK;
							x->_parent->_color = RED;
							right_rotate(x->_parent);
							w = x->_parent->_left;
						}
						if(w->_right->_color == BLACK && w->_left->_color == BLACK)
						{
							w->_color = RED;
							x = x->_parent;
						}
						else
						{
							if(w->_left->_color == BLACK)
							{
								w->_right->_color = BLACK;
								w->_color = RED;
								left_rotate(w);
								w = x->_parent->_left;
							}
							w->_color = x->_parent->_color;
							x->_parent->_color = BLACK;
							w->_left->_color = BLACK;
							right_rotate(x->_parent);
							x = _root;
						}
					}
				}
				x->_color = BLACK;
			}

			// ===========================Erase=============================

			node_ptr delete_node_tree(const key_type& k)
			{
				node_ptr temp = find_key(ft::make_pair(k, mapped_type()));
				if (temp != _nil)
				{
					_size--;
					erase(temp);
				}
				return (_root);
			}
			
			node_ptr minimum_right(node_ptr child_right)
			{
				while(child_right->_left != _nil)
					child_right = child_right->_left;
				return (child_right);
			}

			void	transplant(node_ptr u, node_ptr v)
			{
				if (u->_parent == _nil)
					_root = v;
				else if (u == u->_parent->_left)
					u->_parent->_left = v;
				else
					u->_parent->_right = v;
				v->_parent = u->_parent;
			}

			void	erase(node_ptr z)
			{
				node_ptr y = z;
				node_ptr x;
				bool y_orignal_color = y->_color;
				if(z->_left == _nil)
				{
					x = z->_right;
					transplant(z, z->_right);
				}
				else if(z->_right == _nil)
				{
					x = z->_left;
					transplant(z, z->_left);
				}
				else
				{
					y = minimum_right(z->_right);
					y_orignal_color = y->_color;
					x = y->_right;
					if(y->_parent == z) {
						x->_parent = y;
					}
					else
					{
						transplant(y, y->_right);
						y->_right = z->_right;
						y->_right->_parent = y;
					}
					transplant(z, y);
					y->_left = z->_left;
					y->_left->_parent = y;
					y->_color = z->_color;
				}
				_node_alloc.destroy(z);
				_node_alloc.deallocate(z, 1);
				if (y_orignal_color == BLACK)
					delete_fixup(x);
			}

			// ===========================Create_node=======================

			void	create_node(node_ptr* root, const value_type &val)
			{
				*root = _node_alloc.allocate(1);
				_node_alloc.construct(*root, val);
				(*root)->_nil = _nil;
				(*root)->_left = _nil;
				(*root)->_right = _nil;
				_size++;
			}

			// ===========================INSERT FIX============================

			void	left_rotate(node_ptr    x)
			{
				node_ptr	y;

				y = x->_right;
				x->_right = y->_left;
				if (y->_left != _nil)
					y->_left->_parent = x;
				y->_parent = x->_parent;
				if (x->_parent == _nil)
					_root = y;
				else if (x == x->_parent->_left)
					x->_parent->_left = y;
				else
					x->_parent->_right = y;
				y->_left = x;
				x->_parent = y;
			}

			void	right_rotate(node_ptr    x)
			{
				node_ptr	y;

				y = x->_left;
				x->_left = y->_right;
				if (y->_right != _nil)
					y->_right->_parent = x;
				y->_parent = x->_parent;
				if (x->_parent == _nil)
					_root = y;
				else if (x == x->_parent->_right)
					x->_parent->_right = y;
				else
					x->_parent->_left = y;
				y->_right = x;
				x->_parent = y;
			}

			node_ptr insert_fix(node_ptr z)
			{
				node_ptr	temp = z;    // Stock z pour pouvoir le return dans mon iterator
				node_ptr	y;

				while(z->_parent->_color == RED)
				{
					if(z->_parent == z->_parent->_parent->_left) // z.parent is the left child
					{
						
						y = z->_parent->_parent->_right; //uncle of z

						if(y->_color == RED) //case 1
						{
							z->_parent->_color = BLACK;
							y->_color = BLACK;
							z->_parent->_parent->_color = RED;
							z = z->_parent->_parent;
						}
						else // case 2 or case 3
						{
							if(z == z->_parent->_right) //case 2
							{
								z = z->_parent; //marked z.parent as new z
								left_rotate(z);
							}
							// case 3
							z->_parent->_color = BLACK; //made parent BLACK
							z->_parent->_parent->_color = RED; //made parent red
							right_rotate(z->_parent->_parent);
						}
					}
					else //z.parent is the right child
					{
						y = z->_parent->_parent->_left; //uncle of z

						if(y->_color == RED)
						{
							z->_parent->_color = BLACK;
							y->_color = BLACK;
							z->_parent->_parent->_color = RED;
							z = z->_parent->_parent;
						}
						else
						{
							if(z == z->_parent->_left)
							{
								z = z->_parent; //marked z.parent as new z
								right_rotate(z);
							}
							z->_parent->_color = BLACK; //made parent BLACK
							z->_parent->_parent->_color = RED; //made parent red
							left_rotate(z->_parent->_parent);
						}
					}
				}
				_root->_color = BLACK;
				return temp;
			}

			// ===========================INSERT============================

			iterator insert(node_ptr* root, const value_type &val)
			{
				if ((*root) == _nil)
				{
					create_node(&(*root), val);
					(*root)->_color = BLACK;
					(*root)->_parent = _nil;
					return (iterator(insert_fix((*root)), _nil));
				}
				while ((*root) != _nil)
				{
					if (_comp((*root)->_value.first, val.first) == false && _comp(val.first, (*root)->_value.first) == false)
						return (iterator(insert_fix((*root)), _nil));
					if ((*root)->_left == _nil && !_comp((*root)->_value.first, val.first))
					{
						create_node(&((*root)->_left), val);
						(*root)->_left->_parent = (*root);
						return (iterator(insert_fix((*root)->_left), _nil));
					}
					if ((*root)->_right == _nil && _comp((*root)->_value.first, val.first))
					{
						create_node(&((*root)->_right), val);
						(*root)->_right->_parent = (*root);
						return (iterator(insert_fix((*root)->_right), _nil));
					}
					if (_comp((*root)->_value.first, val.first))
						root = &((*root)->_right);
					else if (_comp(val.first, (*root)->_value.first))
						root = &((*root)->_left);
				}
				return (iterator(_nil, _nil));
			}

			void	btree_display(node_ptr root, int space) const
			{
				int	i = 5;

				if (root->_nil == NULL)
					return ;
				space += 5;
				btree_display(root->_right, space);
				while (i++ < space)
					std::cout << " ";
				std::cout << root->_value.first << "(";
				if (  root->_color == 1 ) 
					std::cout << "R)" << std::endl;
				else if (  root->_color == 0 ) 
					std::cout << "B)" << std::endl;
				btree_display(root->_left, space);
			}

	};
}

#endif