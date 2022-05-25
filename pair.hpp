#ifndef PAIR_HPP
# define PAIR_HPP

#include <iostream>

# define BLACK 0
# define RED 1

namespace ft
{
	template <class Tkey, class Tvalue>
	class	pair
	{
		public:
			typedef Tkey		first_type;
			typedef	Tvalue		second_type;
		
		public:
			first_type		first;
			second_type		second;

		public:
			// ============CONSTRUCTEUR=============
			pair(void) : first(first_type()), second(second_type()) { }

			template<class U, class V>
			pair (const pair<U,V>& pr) : first(pr.first), second(pr.second) { }

			pair (const first_type& a, const second_type& b) : first(a), second(b) { }

			// =============DESTRUCTEUR==============

			~pair(void) { }

			// =============OPERATOR/=/==============
			
			pair& operator= (const pair& pr)
			{
				this->first = pr.first;
				this->second = pr.second;
				return (*this);
			}
	};

	template <class T1, class T2>
	bool operator== (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template <class T1, class T2>
	bool operator!= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T1, class T2>
	bool operator< (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{
		return (lhs.first < rhs.first || (!(lhs.first < rhs.first) && lhs.second < rhs.second));
	}

	template <class T1, class T2>
	bool operator<= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{
		return !(rhs < lhs);
	}
	
	template <class T1, class T2>
	bool operator> (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T1, class T2>
	bool operator>= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{
		return !(lhs < rhs);
	}

	template <class T1,class T2>
	pair<T1,T2> make_pair (T1 x, T2 y)
	{
		return ( pair<T1,T2>(x,y) );
	}

	// ======================NODE======================================

	template<class T>
	class node
	{
		public:
			typedef node *					node_ptr;
			typedef const node *			const_node_ptr;
			typedef T						value_type;
			typedef value_type				pair;

		public:
			pair			_value;

			node_ptr		_parent;
			node_ptr		_left;
			node_ptr		_right;
			node_ptr		_nil;

			bool			_color;

		public:
			node(void) : _parent(), _left(), _right(), _color(BLACK) { }

			node(const pair& val) : _value(val) , _parent(), _left(), _right(), _color(RED) { }

			node (const node & nd) : _value(nd._value), _parent(nd._parent), _left(nd._left), _right(nd._right), _color(nd._color), _nil(nd._nil) { }

			template<class TB>
			node (const node<TB> & nd) : _value(nd._value), _parent(nd._parent), _left(nd._left), _right(nd._right), _color(nd._color), _nil(nd._nil) { }

			node &operator=(const node& nd)
			{	
				_value = nd._value;
				_parent = nd._parent;
				_left = nd._left;
				_right = nd._right;
				_color = nd._color;
				_nil = nd._nil;
				return (*this);
			}

			bool operator==(const node_ptr& nd)
            {
                if (_value == nd->value)
                    return (true);
                return (false);
            }
	};
}

#endif