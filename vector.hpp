/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez <fgomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:11:27 by fgomez            #+#    #+#             */
/*   Updated: 2021/11/08 11:35:13 by fgomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"
#include "utils.hpp"
#include <iterator>
#include <iostream>

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
		public :
			typedef	T														value_type;
			typedef Alloc													allocator_type;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::size_type          			size_type;
			typedef typename ft::random_access_iterator<pointer>			iterator;
			typedef typename ft::random_access_iterator<const_pointer>		const_iterator;
			typedef typename ft::reverse_iterator<iterator> 				reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator> 			const_reverse_iterator;

		protected :
			pointer			_start;								// First Element
			pointer			_end;								// Last Element
			size_type		_capacity;
			allocator_type	_alloc;


		public :
			//============CONSTRUCTOR=========//
			explicit vector (const allocator_type& alloc = allocator_type())
			{
				_alloc = alloc;
				_start = NULL;
				_end = NULL;
				_capacity = 0;
			}

			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
			{
				_alloc = alloc;
				_start = _alloc.allocate( n );
				_end = _start;
				_capacity = n;
				while (n--)
				{
					_alloc.construct(_end, val);
					_end++;
				}
			}

			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL) : _alloc(alloc)
			{
				size_type n = std::distance(first, last);
				_start = _alloc.allocate( n );
				_end = _start;
				_capacity = n;
				
				for ( ; first != last; first++, _end++) {
					_alloc.construct(_end, *first);
				}		
			}

			vector (const vector& x)
			{
				_start = NULL;
				_end = NULL;
				_capacity = 0;
				*this = x;
			}
			
			//============DESTRUCTEUR==========//

			~vector(void)
			{
				while (_start != _end)
				{
					_end--;
					_alloc.destroy(_end);
				}
				_alloc.deallocate(_start, _capacity);
			}
	
			//===============Operateur====================

			vector &operator=(const vector& x)
			{
				if (*this == x)
				{
					return (*this);
				}
				assign(x.begin(), x.end());
				return (*this);
			}

			reference operator[] (size_type n)
			{
				return (*(_start + n));
			}

			const_reference operator[] (size_type n) const
			{
				return (*(_start + n));
			}

			//=============Begin // End==============

			iterator		begin(void)
			{
				return (iterator(_start));
			}

			const_iterator	begin(void) const
			{
				return (const_iterator(_start));
			}

			reverse_iterator rbegin()
			{
				return (reverse_iterator(this->end()));
			}

			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(this->end()));
			}

			iterator		end(void)
			{
				return (iterator(_end));
			}

			const_iterator	end(void) const
			{
				return (const_iterator(_end));
			}

			reverse_iterator rend()
			{
				return (reverse_iterator(this->begin()));
			}

			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(this->begin()));
			}

			//=============Push_Back et Pop_Back ==========

			void push_back (const value_type& val)
			{
				if (_start == NULL)
					reserve(1);
				if (size() >= _capacity)
				{
					this->reserve(size() * 2);
				}
				if (size() < _capacity)
				{
					_alloc.construct(_end, val);
					_end++;
				}
			}

			void	pop_back(void)
			{
				_alloc.destroy(&this->back());
				_end--;
			}

			//=============Clear et Empty==============

			void	clear(void)
			{
				size_type size = this->size();
				for (size_type i = 0; i < size; i++)
				{
					_alloc.destroy(_end - 1);
					_end--;
				}
			}

			bool	empty(void) const
			{
				return (size() == 0 ? true : false);
			}

			//==============Front // Back=============
			
			reference front(void)
			{
				return (*_start);
			}

			const_reference front(void) const
			{
				return (*_start);
			}

			reference	back(void)
			{
				return (*(_end - 1));
			}

			const_reference back(void) const
			{
				return (*(_end - 1));
			}

			//==============At=================

			reference at (size_type n)
			{
				if (n > this->size())
					throw (std::out_of_range("Vector::Range"));
				return ((*this)[n]);
			}

			const_reference at (size_type n) const
			{
				if (n > this->size())
					throw (std::out_of_range("Vector::Range"));
				return ((*this)[n]);
			}

			//===============Size // Max_size // Resize======================

			size_type size(void) const
			{
				return (_end - _start);
			}

			size_type max_size(void) const
			{
				if (sizeof(value_type) == 1)
					return (_alloc.max_size() / 2);
				return (_alloc.max_size());
			}
			
			void resize (size_type n, value_type val = value_type())
			{
				if (n > this->max_size())
					throw (std::length_error("vector::reserve"));
				else if (n < this->size())
				{
					while (n < this->size())
					{
						_end--;
						_alloc.destroy(_end);
					}
				}
				else
				{
					pointer new_start = pointer();
					pointer new_end = pointer();
					size_type new_capacity = size_type();

					new_capacity = _capacity;
					if (_capacity < n)
						new_capacity = (n <= SIZE_MAX / 2) ? _capacity * 2 : SIZE_MAX;
					if (n > new_capacity)
						new_capacity = n;
					if (new_capacity == 0)
						new_capacity = 1;
					new_start = _alloc.allocate( new_capacity );
					new_end = new_start + n;
					_capacity = new_capacity;
					
					size_type i = 0;
					while (i < size())
					{
						_alloc.construct(new_start + i, *(_start + i));
						i++;
						n--;
					}

					while (n)
					{
						_alloc.construct(new_start + i, val);
						i++;
						n--;
					}
					_alloc.deallocate(_start, _capacity);

					_start = new_start;
					_end = new_end;
					_capacity = new_capacity;
				}
			}

			//===============Capacity==================

			size_type capacity(void) const
			{
				return (_capacity);
			}

			//===============Reserve===================

			void	reserve(size_type n)
			{
				if (n <= _capacity)
					return ;
				pointer prev_start = _start;
				size_type prev_size = this->size();
				size_type prev_capacity = this->capacity();

				_start = _alloc.allocate( n );
				_capacity = n;
				_end = _start;
				
				size_type i = 0;
				for ( ; i < prev_size ; i++ )
				{
						_alloc.construct(_start + i, prev_start[i]);
						_end++;
				}

				for (size_type j = 0; j != i ; j++)
				{
					_alloc.destroy(prev_start + j);
				}
				_alloc.deallocate(prev_start , prev_capacity);
			}

			//===============Assign==================

			template <class InputIterator>
			void assign (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
			{
				this->clear();
				size_type dist = std::distance(first, last);
				if (dist > this->capacity())
				{
					_alloc.deallocate(_start, _capacity);
					_start = _alloc.allocate( dist );
					_end = _start;
					_capacity = dist;
					while (&(*first) != &(*last))
					{
						_alloc.construct(_end, *first);
						_end++;
						first++;
					}
				} 
				else
				{
					while (&(*first) != &(*last))
					{
						_alloc.construct(_end, *first);
						first++;
						_end++;
					}
				}
			}

			void assign (size_type n, const value_type& val)
			{
				this->clear();
				if (n == 0)
					return ;
				if (n > this->capacity())
				{
					_alloc.deallocate(_start, _capacity);
					_start = _alloc.allocate( n );
					_end = _start;
					_capacity = n;
					while (n)
					{
						_alloc.construct(_end, val);
						_end++;
						n--;
					}
				}
				else
				{
					while (n)
					{
						_alloc.construct(_end, val);
						_end++;
						n--;
					}
				}
			}

			//===============Swap====================

			void swap (vector& x)
			{
				pointer	save_start = _start;
				pointer save_end = _end;
				size_type save_capacity = _capacity;
				allocator_type	save_alloc = _alloc;


				_start = x._start;
				_end = x._end;
				_capacity = x._capacity;
				_alloc = x._alloc;

				x._start = save_start;
				x._end = save_end;
				x._capacity = save_capacity;
				x._alloc = save_alloc;
			}

			//===============Insert==================

			iterator insert (iterator position, const value_type& val)
			{
				size_type pos_len = position.base() - _start;
				if (_start == NULL)
					this->reserve(1);
				if (_capacity < this->size() + 1)
					this->reserve(_capacity * 2);
				if (position.base() != NULL && position.base() > _end)
					position = _end;
				if (position.base() != NULL && position.base() < _start)
					position = _start;
				else if (position.base() == NULL)
				{
					this->reserve(1);
					push_back(val);
					return (_end - 1);
				}

				pointer _savestart = _start;

				ft::vector<value_type>		vect_tmp;

				vect_tmp._start		= _alloc.allocate(_capacity);
				vect_tmp._end		= vect_tmp._start;
				vect_tmp._capacity	= _capacity;

				pointer	new_pos	= vect_tmp._start + pos_len;
				
				for ( ; vect_tmp._end != new_pos ; ) {
					vect_tmp._alloc.construct(vect_tmp._end, *_start);
					_start++;
					vect_tmp._end++;
				}
				vect_tmp._alloc.construct(vect_tmp._end, val);
				vect_tmp._end++;
				for ( ; _start != _end ;) {
					vect_tmp._alloc.construct(vect_tmp._end, *_start);
					_start++;
					vect_tmp._end++;
				}
				
				_start = _savestart; 
				
				swap(vect_tmp);
				
				return (_start + pos_len);
			}

			void insert (iterator position, size_type n, const value_type& val)
			{
				size_type pos_len = position.base() - _start;
				if (_start == NULL)
					this->reserve(1);
				if (_capacity < this->size() + n)
					this->reserve(_capacity * 2);
				if (position.base() != NULL && position.base() > _end)
					position = _end;
				if (position.base() != NULL && position.base() < _start)
					position = _start;
				else if (position.base() == NULL)
				{
					this->reserve(n);
					for ( ; 0 < n; n--) {
						push_back(val);
					}
					return ;
				}
				if (_capacity < this->size() + n)
					_capacity = this->size() + n;

				pointer _savestart = _start;

				ft::vector<value_type>		vect_tmp;


				vect_tmp._start		= _alloc.allocate(_capacity);
				vect_tmp._end		= vect_tmp._start;
				vect_tmp._capacity	= _capacity;

				pointer	new_pos	= vect_tmp._start + pos_len;

				for ( ; vect_tmp._end != new_pos ; ) {
					vect_tmp._alloc.construct(vect_tmp._end, *_start);
					_start++;
					vect_tmp._end++;
				}
				for ( ; 0 < n; ) {
					_alloc.construct(vect_tmp._end, val);
					vect_tmp._end++;
					n--;
				}
				for ( ; _start != _end ;) {
					vect_tmp._alloc.construct(vect_tmp._end, *_start);
					_start++;
					vect_tmp._end++;
				}
				_start = _savestart;
				swap(vect_tmp);
			}

			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
			{
				size_type pos_len = position.base() - _start;
				size_type dist = std::distance(first, last);
				if (_start == NULL)
					this->reserve(1);
				if (_capacity < this->size() + dist)
					this->reserve(_capacity * 2);
				if (position.base() != NULL && position.base() > _end)
					position = _end;
				if (position.base() != NULL && position.base() < _start)
					position = _start;
				else if (position.base() == NULL)
				{
					this->reserve(dist);
					for ( ; first != last; first++) {
						push_back(*first);
					}
					return ;
				}
				if (_capacity < this->size() + dist)
					_capacity = this->size() + dist;

				pointer _savestart = _start;

				ft::vector<value_type>		vect_tmp;


				vect_tmp._start		= _alloc.allocate(_capacity);
				vect_tmp._end		= vect_tmp._start;
				vect_tmp._capacity	= _capacity;

				pointer	new_pos	= vect_tmp._start + pos_len;

				for ( ; vect_tmp._end != new_pos ; ) {
					vect_tmp._alloc.construct(vect_tmp._end, *_start);
					_start++;
					vect_tmp._end++;
				}
				for ( ; first != last; ) {
					_alloc.construct(vect_tmp._end, *first);
					vect_tmp._end++;
					first++;
				}
				for ( ; _start != _end ;) {
					vect_tmp._alloc.construct(vect_tmp._end, *_start);
					_start++;
					vect_tmp._end++;
				}
				_start = _savestart;
				swap(vect_tmp);
			}

			//===============Erase==================

			iterator erase (iterator position)
			{
				_alloc.destroy(position.base());
				if (position.base() == _end - 1)
					;
				else
				{
					for (int i = 0; position.base() + i != _end; i++)
					{
						_alloc.construct(position.base() + i, *(position.base() + i + 1));
						_alloc.destroy(position.base() + i + 1);
					}
				}
				_end--;
				return (iterator(position));
			}

			iterator erase (iterator first, iterator last)
			{
				for (int i = 0; first.base() + i != last.base(); i++)
					_alloc.destroy(first.base() + i);
				for (int i = 0; i < _end - last.base(); i++)
				{
					_alloc.construct(first.base() + i, *(last.base() + i));
					_alloc.destroy(last.base() + i);
				}
				_end -= (last.base() - first.base());
				return (iterator(first));
			}
	};
	
	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>&y)
	{
		x.swap(y);
	}

	template <class T, class Alloc>
	bool operator== (const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		typename ft::vector<T>::const_iterator first1 = lhs.begin();
		typename ft::vector<T>::const_iterator first2 = rhs.begin();
		while (first1 != lhs.end())
		{
			if (first2 == rhs.end() || *first1 != *first2)
				return (false);
			++first1;
			++first2;
		}
		return (true);
	}

	template <class T, class Alloc>
	bool operator!= (const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool operator<  (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator<= (const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Alloc>
	bool operator>= (const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}

	template <class T, class Alloc>
	bool operator> (const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
	{
		return (rhs < lhs);
	}
}

#endif