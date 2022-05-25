#ifndef MAP_HPP
# define MAP_HPP

#include <iostream>
# include "utils.hpp"
# include "pair.hpp"
# include "BST.hpp"
# include "btree_iterator.hpp"


namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public :
			typedef Key												key_type;
			typedef T												mapped_type;
			typedef ft::pair<const key_type, mapped_type>			value_type;

			typedef Compare											key_compare;

			typedef Alloc											allocator_type;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;

		protected:
			typedef RBtree<value_type, Compare, Alloc>				tree_type;

		public:
			typedef typename tree_type::iterator					iterator;
			typedef typename tree_type::const_iterator				const_iterator;
			typedef typename tree_type::reverse_iterator			reverse_iterator;
			typedef typename tree_type::const_reverse_iterator		const_reverse_iterator;

			typedef size_t												size_type;

			class value_compare : ft::binary_function<value_type, value_type, bool>
			{
				friend class map<key_type, mapped_type, key_compare, Alloc>;

				protected:
					Compare comp;

					// ========================CONSTRUCTEUR=======================
  					value_compare (Compare c) : comp(c) { }

				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;

					bool operator() (const value_type &x, const value_type & y)
					{ return (comp(x.first, y.first)); }
			};

		
		public:
			allocator_type				_alloc;
			Compare						_comp;
			tree_type					_rbt;

		public:
			// ========================CONSTRUCTEUR=======================
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _comp(comp), _rbt() { }

			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _comp(comp)
			{
				this->insert(first, last);
			}

			map (const map& x) : _alloc(x._alloc), _comp(x._comp)
			{
				*this = x;
			}

			// ========================DESTRCUTEUR=========================

			~map(void)
			{ 
				_rbt._node_alloc.destroy(_rbt._nil);
				_rbt._node_alloc.deallocate(_rbt._nil, 1);
			}
			
			// ========================OPERATOR/=/=========================

			map& operator= (const map& x)
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
				return (_rbt.insert(&(_rbt._root), val));
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
				return const_iterator(_rbt.begin());
			}

			reverse_iterator rbegin(void)
			{
				return reverse_iterator(_rbt.end());
			}

			const_reverse_iterator rbegin(void) const
			{
				return const_reverse_iterator(_rbt.end());
			}

			// ===========================END============================

			iterator end(void)
			{
				return (_rbt.end());
			}

			const_iterator end(void) const
			{
				return (_rbt.end());
			}

			reverse_iterator rend(void)
			{
				return reverse_iterator(_rbt.begin());
			}

			const_reverse_iterator rend(void) const
			{
				return const_reverse_iterator(_rbt.begin());
			}

			// ===========================LowerBound============================

			iterator lower_bound (const key_type& k)
			{
				iterator it = this->begin();
				iterator ite = this->end();

				for ( ; it != ite; it++)
					if (_comp(it->first, k) == false)
						break ;
				return (it);
			}
			const_iterator lower_bound (const key_type& k) const
			{
				const_iterator it = this->begin();
				const_iterator ite = this->end();

				for ( ; it != ite; it++)
					if (_comp(it->first, k) == false)
						break ;
				return (it);
			}

			// ===========================UpperBound============================

			iterator upper_bound (const key_type& k)
			{
				iterator _start = this->begin();
				iterator _end = this->end();

				while (_start != _end)
				{
					if (_comp(k, _start->first))
						break;
					_start++;
				}
				return (iterator(_start));
			}

			const_iterator upper_bound (const key_type& k) const
			{
				const_iterator _start = this->begin();
				const_iterator _end = this->end();

				while (_start != _end)
				{
					if (_comp(k, _start->first))
						break;
					_start++;
				}
				return (const_iterator(_start));
			}

			// ===========================Equal_range============================

			pair<const_iterator,const_iterator> equal_range (const key_type& k) const
			{
				return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
			}

			pair<iterator,iterator>             equal_range (const key_type& k)
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

			// =========================OPERATOR[]===============================

			mapped_type& operator[] (const key_type& k)
			{
				return (((this->insert(ft::make_pair(k,mapped_type()))).first))->second;
			}

			// =========================FIND===============================

			iterator find (const key_type& k)
			{
				return (iterator(_rbt.find_key(ft::make_pair(k, mapped_type())), _rbt._nil));
			}

			const_iterator find (const key_type& k) const
			{
				return (const_iterator(reinterpret_cast<typename tree_type::const_node_ptr>(_rbt.find_key(ft::make_pair(k, mapped_type()))), reinterpret_cast<typename tree_type::const_node_ptr>(_rbt._nil)));
			}

			// =========================COUNT===============================
			
			size_type count (const key_type& k) const
			{
				const_iterator	_start = this->begin();
				const_iterator	_end = this->end();

				while (_start != _end)
				{
					if (_start->first == k)
						return (1);
					_start++;
				}
				return (0);
			}

			// =========================Key_comp && Value_comp===============================

			key_compare key_comp() const
			{
				return (key_compare());
			}

			value_compare value_comp() const
			{
				return (value_compare(key_compare()));
			}

			// =========================ERASE================================================

			void erase (iterator position)
			{
				erase((*position).first);
			}

			size_type erase(const key_type& k)
			{
				if (_rbt.find_key(ft::make_pair(k, mapped_type())) == _rbt._nil)
					return (0);
				_rbt.delete_node_tree(k);
				return (1);
			}

			void erase (iterator first, iterator last)
			{
				while (first != last)
					this->erase((*(first++)).first);
			}

			// =========================CLEAR && EMPTY========================================

			void clear()
			{
				_rbt.btree_clear(_rbt._root);
			}
			
			bool empty() const
			{
				if (_rbt._size == 0)
					return (true);
				return (false);
			}

			// =========================SWAP===========================

			void swap (map& x)
			{
				_rbt.btree_swap(x._rbt);
			}

			allocator_type get_allocator(void) const
			{
				return (_alloc);
			}
	};

	template <class Key, class T, class Compare, class Alloc>
	void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y)
	{
		x.swap(y);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator== ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		if (lhs._rbt._size != rhs._rbt._size)
			return (false);
		if (ft::equal(lhs.begin(), lhs.end(), rhs.begin()) == false)
			return (false);
		return (true);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return !(lhs == rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(rhs < lhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return (rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs < rhs));
	}
}

#endif