#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include <iostream>
# include "iterator_trait.hpp"

namespace ft
{
	// ===========================Random_access_iterator==============================
	template <typename T>
	class random_access_iterator
	{
		protected :
			typedef ft::iterator_traits<T>	it;
		public :
			typedef typename it::iterator_category			iterator_category;
			typedef typename it::value_type					value_type;
			typedef typename it::difference_type			difference_type;

			typedef typename it::pointer					pointer;
			typedef typename it::reference					reference;

		public :
			pointer		_elem; // Element pointer par l'iterator
		
		public :
			// ============CONSTRUCTEUR=============
			random_access_iterator(void) : _elem(NULL) { }

			random_access_iterator(pointer elem) : _elem(elem) { }

			template<typename TB>
			random_access_iterator(const random_access_iterator<TB> & rhs) : _elem(rhs.base()) { }

			// ==============DESTRUCTEUR==============

			~random_access_iterator(void) { }

			// ==============BASE=====================

			pointer	base(void) const
			{
				return (_elem);
			}

			// ==============OPERATEUR/=/=============
			
			random_access_iterator &operator=(random_access_iterator const & rhs)
			{
				if (this == &rhs)
					return (*this);
				this->_elem = rhs._elem;
				return (*this);
			}
			
			// ==============OPERATEUR->==============

			pointer operator->(void)
			{
				return &(this->operator*());
			}

			// ==============OPERATEUR++==============

			random_access_iterator &operator++(void)
			{
				_elem++;
				return (*this);
			}

			random_access_iterator operator++(int)
			{
				random_access_iterator tmp(*this);
				operator++();
				return (tmp);
			}
			
			// ==============OPERATEUR--=============

			random_access_iterator &operator--(void)
			{
				_elem--;
				return (*this);
			}

			random_access_iterator operator--(int)
			{
				random_access_iterator tmp(*this);
				operator--();
				return (tmp);
			}

			// ==============OPERATEUR*==============

			reference operator*(void) const
			{
				return (*_elem);
			}

			// ==============OPERATEUR=+==============

			random_access_iterator &operator+=(difference_type n)
			{
				_elem += n;
				return (*this);
			}

			// ==============OPERATEUR=-==============

			random_access_iterator &operator-=(difference_type n)
			{
				_elem -= n;
				return (*this);
			}

			// ==============OPERATEUR[]==============

			reference	operator[](difference_type n) const
			{
				return (*(_elem + n));
			}

			// ==============OPERATEUR+==============

			random_access_iterator operator+(difference_type n) const 
			{
				return (n + _elem);
			}

			// ==============OPERATEUR-==============

			random_access_iterator operator-(difference_type n) const
			{
				return (_elem - n);
			}

			difference_type operator-(random_access_iterator n) const
			{
				return (_elem - n._elem);
			}
	};

	template<typename T>
	ft::random_access_iterator<T> operator+( typename ft::random_access_iterator<T>::difference_type n, typename ft::random_access_iterator<T>& it )
	{
		return (it.base() + n);
	}

 	template<typename T_L, typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type operator-(const ft::random_access_iterator<T_L> lhs, const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() - rhs.base());
    }

	template<typename T_L, typename  T_R>
	bool operator==(const ft::random_access_iterator<T_L> lhs, const ft::random_access_iterator<T_R> rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template<typename T_L, typename  T_R>
	bool operator!=(const ft::random_access_iterator<T_L> lhs, const ft::random_access_iterator<T_R> rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template<typename T_L, typename  T_R>
	bool operator<(const ft::random_access_iterator<T_L> lhs, const ft::random_access_iterator<T_R> rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template<typename T_L, typename  T_R>
	bool operator>(const ft::random_access_iterator<T_L> lhs, const ft::random_access_iterator<T_R> rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template<typename T_L, typename  T_R>
	bool operator>=(const ft::random_access_iterator<T_L> lhs, const ft::random_access_iterator<T_R> rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template<typename T_L, typename  T_R>
	bool operator<=(const ft::random_access_iterator<T_L> lhs, const ft::random_access_iterator<T_R> rhs)
	{
		return (lhs.base() <= rhs.base());
	}
}

#endif