#ifndef SET_HPP
# define SET_HPP

#include <iostream>
# include "utils.hpp"
# include "pair.hpp"
# include "set_BST.hpp"
# include "btree_iterator.hpp"

namespace ft 
{
	template < class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
	class set
	{
		public :
			typedef T														key_type;
			typedef T														value_type;
			typedef Compare													key_compare;
			typedef Alloc													allocator_type;
			typedef	typename allocator_type::reference						reference;				// value_type&
			typedef typename allocator_type::const_reference				const_reference;		// const value_type&
			typedef	typename allocator_type::pointer						pointer;				// value_type*
			typedef	typename allocator_type::const_pointer					const_pointer;			// const value_type*
			typedef	typename allocator_type::difference_type				difference_type;
			typedef	size_t													size_type;

		protected:
			typedef	setRBtree<value_type, key_compare, allocator_type>		btree_type;

		public :
			typedef	typename btree_type::iterator						iterator;
			typedef	typename btree_type::iterator						const_iterator;
			typedef	ft::reverse_iterator<iterator>						reverse_iterator;
			typedef	ft::reverse_iterator<iterator>						const_reverse_iterator;

			class value_compare : ft::binary_function<value_type, value_type, bool>
			{
				friend class set;

				protected:
					Compare comp;

					// ========================CONSTRUCTEUR=======================
  					value_compare (Compare c) : comp(c) { }

				public:
					typedef bool	result_type;
					typedef			value_type first_argument_type;
					typedef			value_type second_argument_type;

					bool operator() (const value_type &x, const value_type & y)
					{ return comp(x, y); }
			};
		
		protected:
			allocator_type	_alloc;
			key_compare		_comp;
			btree_type		_rbt;

		public :
			// ========================CONSTRUCTEUR=======================	
			explicit set (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			{
				_alloc	= alloc;
				_comp	= comp;
			}

			template <class InputIterator>
			set (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			{
				_comp			= comp;
				_alloc			= alloc;
				this->insert(first, last);
			}

			set (const set& x)
			{
				_alloc	= x._alloc;
				_comp	= x._comp;
				*this	= x;
			}

			// =========================DESTRUCTEUR=========================

			~set()
			{
				_rbt._node_alloc.destroy(_rbt._nil);
				_rbt._node_alloc.deallocate(_rbt._nil, 1);
			}

			// ========================OPERATOR/=/=========================

			set& operator= (const set& x)
			{
				if (this != &x)
				{
					this->clear();
					this->insert(x.begin(), x.end());
				}
				return (*this);
			}

			// ========================insert=========================

			pair<iterator, bool> insert (const value_type& val)
			{
				bool insertable = _rbt.find_key(val) == _rbt._nil ? true : false;
				iterator it = _rbt.insert(&(_rbt._root), val);
				return ft::make_pair(it, insertable);
			}
			
			iterator insert (iterator position, const value_type& val)
			{
				(void)position;

				pair<iterator, bool> ret = this->insert(val);					
				return (ret.first);
			}

			template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
			{
				for ( ; first != last; first++)
					_rbt.insert(&(_rbt._root), *first);
			}

			// ===========================BEGIN============================

			iterator begin(void)
			{
				return iterator(_rbt.begin());
			}

			const_iterator begin(void) const
			{
				return iterator(_rbt.begin());
			}

			reverse_iterator rbegin(void)
			{
				return const_reverse_iterator(_rbt.end());
			}

			const_reverse_iterator rbegin(void) const
			{
				return const_reverse_iterator(_rbt.end());
			}

			// ===========================END============================

			iterator end(void)
			{
				return iterator(_rbt.end());
			}

			const_iterator end(void) const
			{
				return iterator(_rbt.end());
			}

			reverse_iterator rend(void)
			{
				return const_reverse_iterator(_rbt.begin());
			}

			const_reverse_iterator rend(void) const
			{
				return const_reverse_iterator(_rbt.begin());
			}

			// ===========================LowerBound============================

			iterator lower_bound (const key_type& k) const
			{
				iterator it = this->begin();
				iterator ite = this->end();

				for ( ; it != ite; it++)
					if (_comp(*it, k) == false)
						break ;
				return (it);
			}

			// ===========================UpperBound============================

			iterator upper_bound (const key_type& k) const
			{
				iterator it = this->begin();
				iterator _end = this->end();

				while (it != _end)
				{
					if (_comp(k, *it))
						break;
					it++;
				}
				return (iterator(it));
			}

			// =========================FIND===============================

			iterator find (const key_type& k) const
			{
				return (iterator(reinterpret_cast<typename btree_type::const_node_ptr>(_rbt.find_key(k)), reinterpret_cast<typename btree_type::const_node_ptr>(_rbt._nil)));
			}

			// =========================COUNT===============================
			
			size_type count (const key_type& k) const
			{
				const_iterator	_start = this->begin();
				const_iterator	_end = this->end();

				while (_start != _end)
				{
					if (*_start == k)
						return (1);
					_start++;
				}
				return (0);
			}

			// =========================Key_comp && Value_comp===============================

			key_compare key_comp(void) const
			{
				return (key_compare());
			}

			value_compare value_comp(void) const
			{
				return (value_compare(key_compare()));
			}

			// =========================ERASE================================================

			void erase (iterator position)
			{
				erase((*position));
			}

			size_type erase(const key_type& k)
			{
				if (_rbt.find_key(k) == _rbt._nil)
					return (0);
				_rbt.delete_node_tree(k);
				return (1);
			}

			void erase (iterator first, iterator last)
			{
				while (first != last)
					this->erase((*(first++)));
			}

			// =========================CLEAR && EMPTY========================================

			void clear(void)
			{
				_rbt.btree_clear(_rbt._root);
			}
			
			bool empty() const
			{
				return (!_rbt._size);
			}

			// =========================SWAP===========================

			void swap (set& x)
			{
				_rbt.btree_swap(x._rbt);
			}

			// ===========================Equal_range============================

			pair<iterator,iterator>             equal_range (const key_type& k) const
			{
				return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
			}

			// ==============================SIZE===============================

			size_type max_size() const
			{
				return (_rbt.max_size());
			}

			size_type size() const
			{
				return (_rbt.size());
			}

			// ==============================ALLOCATOR===============================

			allocator_type get_allocator() const
			{
				return (_alloc);
			}
	};
	
	template <class T, class Compare, class Alloc>
	void swap (set<T,Compare,Alloc>& x, set<T,Compare,Alloc>& y)
	{
		x.swap(y);
	}

	template <class T, class Compare, class Alloc>
	bool operator== ( const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs )
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Compare, class Alloc>
	bool operator!= ( const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs )
	{
		return !(lhs == rhs);
	}

	template <class T, class Compare, class Alloc>
	bool operator<  ( const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs )
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	
	template <class T, class Compare, class Alloc>
	bool operator<= ( const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs )
	{
		return !(rhs < lhs);
	}
	
	template <class T, class Compare, class Alloc>
	bool operator>  ( const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs )
	{
		return (rhs < lhs);
	}
	
	template <class T, class Compare, class Alloc>
	bool operator>= ( const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs )
	{
		return !(lhs < rhs);
	}
}

#endif