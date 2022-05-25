/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez <fgomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:11:17 by fgomez            #+#    #+#             */
/*   Updated: 2021/11/08 15:25:12 by fgomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

#include <iostream>
#include <deque>
#include "utils.hpp"

namespace ft
{
	template<class T, class container = std::deque<T> >
	class stack
	{
		public:
			typedef	T			value_type;
			typedef container	container_type;
			typedef	size_t		size_type;

		protected:
			container_type		c;

		public:
			//============CONSTRUCTOR=========//
			explicit stack (const container_type& ctnr = container_type()) : c(ctnr)
			{
				ft::static_assert_ft<ft::is_same<T, typename container_type::value_type >::value>::func();;
			}

			//============DESTRUCTEUR=========//
			~stack(void) { }

			//============EMPTY===============//
			bool empty(void) const
			{
				return (c.empty());
			}

			//============PUSH================//
			void push (const value_type& val)
			{
				return (c.push_back(val));
			}

			//============POP=================//
			void pop(void)
			{
				return (c.pop_back());
			}

			//============SIZE================//
			size_type size(void) const
			{
				return (c.size());
			}

			//============TOP=================//
			value_type& top(void)
			{
				return (c.back());
			}

			const value_type& top(void) const
			{
				return (c.back());
			}
			
			//============BOOL================//

			template <class Tn, class ContainerN>
			friend bool operator== (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs);

			template <class Tn, class ContainerN>
			friend bool operator!= (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs);
			
			template <class Tn, class ContainerN>
			friend bool operator< (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs);

			template <class Tn, class ContainerN>
			friend bool operator<= (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs);

			template <class Tn, class ContainerN>
			friend bool operator> (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs);

			template <class Tn, class ContainerN>
			friend bool operator>= (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs);
	};

	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c == rhs.c);
	}
	
	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c != rhs.c);
	}
	
	template <class T, class Container>
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c < rhs.c);
	}
	
	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c <= rhs.c);
	}

	template <class T, class Container>
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c > rhs.c);
	}

	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c >= rhs.c);
	}
}

#endif