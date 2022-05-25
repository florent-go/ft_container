#ifndef BTREE_ITERATOR
# define BTREE_ITERATOR

// #include "iterator_trait.hpp"

namespace ft
{
	template<typename T>
	class RBtree_iterator
	{
		public:
			typedef T								value_type;
			typedef value_type*						pointer;
			typedef value_type&						reference;

			typedef std::bidirectional_iterator_tag	iterator_category;
			typedef size_t							difference_type;

			typedef ft::node<T>						node_type;
			typedef node_type*						node_ptr;

		public:
			node_ptr		_node;
			node_ptr		_last;

		public:
			// ============CONSTRUCTEUR=============
			RBtree_iterator(void) : _node(NULL), _last(NULL) { }

			RBtree_iterator(node_ptr nd, node_ptr last = NULL) : _node(nd), _last(last) { }

			template< class Iter >
			RBtree_iterator(RBtree_iterator<Iter> &rhs) : _node(rhs._node), _last(rhs._last) { }

			// ==============DESTRUCTEUR==============

			~RBtree_iterator(void) { }

			// ==============BASE==============

			pointer base(void) const
			{
				return (&(_node->_value));
			}

			// ==============OPERATEUR/=/=============

			RBtree_iterator operator=(const RBtree_iterator & rhs)
			{
				_node = rhs._node;
				_last = rhs._last;
				return (*this);
			}

			// ==============OPERATEUR*==============

			reference operator*(void) const
			{
				return (_node->_value);
			}

			// ==============OPERATEUR->==============

			pointer operator->(void) const
			{
				return (&(operator*()));
			}

			// ==============OPERATEUR+===============

			RBtree_iterator & operator++(void)
			{
				if (!_node->_nil)
					return *this;
				if (_node == _last)
					_node = _node->_nil;
				else if (_node != _node->_nil && _node->_right != _node->_nil)
				{
					_node = _node->_right;
					while (_node->_left != _node->_nil && _node != NULL)
						_node = _node->_left;
				}
				else
				{
					while (_node->_parent != _node->_nil && _node == _node->_parent->_right)
						_node = _node->_parent;
					_node = _node->_parent;
				}
				return (*this);
			}

			RBtree_iterator operator++(int)
			{
				RBtree_iterator tmp(*this);
				operator++();
				return (tmp);
			}

			// ==============OPERATEUR-===============

			RBtree_iterator & operator--(void)
			{
				if (_node->_nil == NULL)
				{
					_node = _last;
					return *this;
				}
				if (_node != _node->_nil && _node->_left != _node->_nil)
				{
					_node = _node->_left;
					while (_node->_right != _node->_nil && _node != NULL)
						_node = _node->_right;
				}
				else
				{
					while (_node->_parent != _node->_nil && _node == _node->_parent->_left)
						_node = _node->_parent;
					_node = _node->_parent;
				}
				return (*this);
			}

			RBtree_iterator operator--(int)
			{
				RBtree_iterator tmp(*this);
				operator--();
				return (tmp);
			}

	};

	template<typename T>
	class RBtree_iterator_const
	{
		public:
			typedef const T							value_type;
			typedef	value_type *					pointer;
			typedef value_type &					reference;

			typedef std::bidirectional_iterator_tag	iterator_category;
			typedef size_t							difference_type;

			typedef typename ft::node<value_type>	node_type;
			typedef node_type*						node_ptr;

		public:
			node_ptr		_node;
			node_ptr		_last;

		public:
			// ============CONSTRUCTEUR=============
			RBtree_iterator_const(void) : _node(NULL), _last(NULL) { }

			RBtree_iterator_const(node_ptr nd, node_ptr last = NULL) : _node(nd), _last(last) { }

			template<class Iter>
			RBtree_iterator_const(const RBtree_iterator_const<Iter> &rhs) : _node(rhs._node), _last(rhs._last) { }

			template<class Iter>
			RBtree_iterator_const(const RBtree_iterator<Iter> &rhs) :
				_node(reinterpret_cast<node_ptr>(rhs._node)),
				_last(reinterpret_cast<node_ptr>(rhs._last))
				{ }

			// ==============DESTRUCTEUR==============

			~RBtree_iterator_const(void) { }

			// ==============OPERATEUR/=/=============

			RBtree_iterator_const operator=(const RBtree_iterator_const & rhs)
			{
				_node = rhs._node;
				_last = rhs._last;
				return (*this);
			}

			// ==============BASE==============

			pointer base(void) const
			{
				return (&(_node->_value));
			}

			// ==============OPERATEUR*==============

			reference operator*(void) const
			{
				return (_node->_value);
			}

			// ==============OPERATEUR->==============

			pointer operator->(void) const
			{
				return &(operator*());
			}

			// ==============OPERATEUR+===============

			RBtree_iterator_const & operator++(void)
			{
				if (!_node->_nil)
					return *this;
				if (_node == _last)
					_node = _node->_nil;
				else if (_node != _node->_nil && _node->_right != _node->_nil)
				{
					_node = _node->_right;
					while (_node->_left != _node->_nil && _node != NULL)
						_node = _node->_left;
				}
				else
				{
					while (_node->_parent != _node->_nil && _node == _node->_parent->_right)
						_node = _node->_parent;
					_node = _node->_parent;
				}
				return (*this);
			}

			RBtree_iterator_const operator++(int)
			{
				RBtree_iterator_const tmp(*this);
				operator++();
				return (tmp);
			}

			// ==============OPERATEUR-===============

			RBtree_iterator_const & operator--(void)
			{
				if (_node->_nil == NULL)
				{
					_node = _last;
					return *this;
				}
				else if (_node != _node->_nil && _node->_left != _node->_nil)
				{
					_node = _node->_left;
					while (_node->_right != _node->_nil && _node != NULL)
						_node = _node->_right;
				}
				else
				{
					while (_node->_parent != _node->_nil && _node == _node->_parent->_left)
						_node = _node->_parent;
					_node = _node->_parent;
				}
				return (*this);
			}

			RBtree_iterator_const operator--(int)
			{
				RBtree_iterator_const tmp(*this);
				operator--();
				return (tmp);
			}
	};

	// ==============OPERATEUR/==/===============

	template <class Iterator1, class Iterator2>
	bool operator== (const ft::RBtree_iterator_const<Iterator1>& lhs, const ft::RBtree_iterator_const<Iterator2>& rhs)
	{
		return (lhs.base() == rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator== (const ft::RBtree_iterator<Iterator1>& lhs, const ft::RBtree_iterator<Iterator2>& rhs)
	{
		return (lhs.base() == rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator== (const ft::RBtree_iterator_const<Iterator1>& lhs, const ft::RBtree_iterator<Iterator2>& rhs)
	{
		return (lhs.base() == rhs.base());
	}

	// ==============OPERATEUR/!=/=================

	template <class Iterator1, class Iterator2>
	bool operator!= (const ft::RBtree_iterator_const<Iterator1>& lhs, const ft::RBtree_iterator_const<Iterator2>& rhs)
	{
		return (lhs.base() != rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator!= (const ft::RBtree_iterator<Iterator1>& lhs, const ft::RBtree_iterator<Iterator2>& rhs)
	{
		return (lhs.base() != rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator!= (const ft::RBtree_iterator_const<Iterator1>& lhs, const ft::RBtree_iterator<Iterator2>& rhs)
	{
		return (lhs.base() != rhs.base());
	}


}

#endif