#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include <iostream>
# include "iterator_trait.hpp"

namespace ft
{
	// ===========================Reverse_iterator==============================
	template <class Iterator>
	class reverse_iterator
	{
		public:
			typedef Iterator								iterator_type;
			typedef typename Iterator::iterator_category	iterator_category;
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::difference_type		difference_type;

			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;
		
		 private:
			iterator_type							_elem;

		public:
			// ============CONSTRUCTEUR=============

			reverse_iterator() : _elem() { }

			explicit reverse_iterator (iterator_type it) : _elem(it) { }

			template <class Iter>
			reverse_iterator (const reverse_iterator<Iter> & rev_it) : _elem(rev_it.base()) { }

			// ==============DESTRUCTEUR==============

			virtual ~reverse_iterator(void) { }

			// ==============BASE=====================

			iterator_type base(void) const
			{
				return (_elem);
			}

			// ==============OPERATOR*=================

			reference operator*(void) const
			{
				iterator_type	tmp = _elem;
				return *(--tmp);
			}

			// ==============OPERATOR++=================

			reverse_iterator operator+ (difference_type n) const
			{
				return (reverse_iterator(_elem.base() - n));
			}

			reverse_iterator& operator++(void)
			{
				--_elem;
				return (*this);
			}

			reverse_iterator operator++(int)
			{
				reverse_iterator tmp = *this;
				operator++();
				return (tmp);
			}

			reverse_iterator& operator+= (difference_type n)
			{
				_elem -= n;
				return (*this);
			}

			// ==============OPERATOR--=================

			reverse_iterator operator- (difference_type n) const
			{
				return (reverse_iterator(_elem.base() + n));
			}

			reverse_iterator& operator--(void)
			{
				++_elem;
				return (*this);
			}

			reverse_iterator operator--(int)
			{
				reverse_iterator tmp = *this;
				operator--();
				return (tmp);
			}

			reverse_iterator& operator-= (difference_type n)
			{
				_elem += n;
				return (*this);
			}

			// ==============OPERATOR->=================

			pointer operator->(void) const
			{
				return &(operator*());
			}

			// ==============OPERATOR[]==================

			reference operator[] (difference_type n) const
			{
				return (this->base()[-n - 1]);
			}
	};

	template <class Iterator>
	reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
	{
		return (rev_it + n);
	}

	template <class T_L, class T_R>
	typename reverse_iterator<T_R>::difference_type operator- (const reverse_iterator<T_L>& lhs, const reverse_iterator<T_R>& rhs)
	{
		return (rhs.base() - lhs.base());
	}

	template<typename T_L, typename  T_R>
	bool operator==(const ft::reverse_iterator<T_L> lhs, const ft::reverse_iterator<T_R> rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template<typename T_L, typename  T_R>
	bool operator!=(const ft::reverse_iterator<T_L> lhs, const ft::reverse_iterator<T_R> rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template<typename T_L, typename  T_R>
	bool operator<(const ft::reverse_iterator<T_L> lhs, const ft::reverse_iterator<T_R> rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template<typename T_L, typename  T_R>
	bool operator>(const ft::reverse_iterator<T_L> lhs, const ft::reverse_iterator<T_R> rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template<typename T_L, typename  T_R>
	bool operator>=(const ft::reverse_iterator<T_L> lhs, const ft::reverse_iterator<T_R> rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template<typename T_L, typename  T_R>
	bool operator<=(const ft::reverse_iterator<T_L> lhs, const ft::reverse_iterator<T_R> rhs)
	{
		return (lhs.base() >= rhs.base());
	}
};

#endif