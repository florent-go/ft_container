#ifndef UTILS_HPP
# define UTILS_HPP

#include <iostream>

namespace ft
{

	// ======================Enable_if===============================

	template<bool Cond, class T = void> struct enable_if { };
	template<class T> struct enable_if<true, T> { typedef T type; };

	template <bool is_integral, typename T>
	struct is_integral_res
	{
		typedef T type;
		static const bool value = is_integral;
	};

	template <typename>
    struct is_integral_type : public is_integral_res<false, bool> {};

	template<>
	struct is_integral_type<bool> : public is_integral_res<true, bool> {};

	template<>
	struct is_integral_type<char> : public is_integral_res<true, char> {};
	
	template<>
	struct is_integral_type<char16_t> : public is_integral_res<true, char16_t> {};

	template<>
	struct is_integral_type<char32_t> : public is_integral_res<true, char32_t> {};

	template<>
	struct is_integral_type<wchar_t> : public is_integral_res<true, wchar_t> {};

	template<>
	struct is_integral_type<signed char> : public is_integral_res<true, signed char> {};

	template<>
	struct is_integral_type<short int> : public is_integral_res<true, short int> {};

	template<>
	struct is_integral_type<int> : public is_integral_res<true, int> {};

	template<>
	struct is_integral_type<long int> : public is_integral_res<true, long int> {};

	template<>
	struct is_integral_type<long long int> : public is_integral_res<true, long long int> {};

	template<>
	struct is_integral_type<unsigned char> : public is_integral_res<true, unsigned char> {};

	template<>
	struct is_integral_type<unsigned short int> : public is_integral_res<true, unsigned short int> {};

	template<>
	struct is_integral_type<unsigned int> : public is_integral_res<true, unsigned int> {};

	template<>
	struct is_integral_type<unsigned long int> : public is_integral_res<true, unsigned long int> {};

	template<>
	struct is_integral_type<unsigned long long int> : public is_integral_res<true, unsigned long long int> {};

	template <class T>
	struct is_integral : public is_integral_type<T> { };

	// ======================lexicographical===============================

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			first1++;
			first2++;
		}
		return (first2 != last2);
	}

	// ======================LESS or BINARY===============================
	template <class Arg1, class Arg2, class Result>
	struct binary_function
	{
		/* The first argument type */
		typedef Arg1 first_argument_type;

		/* The second arguement type */
		typedef Arg2 second_argument_type;

		/* The result type */
		typedef Result result_type;
	};

	// ==========================EQUAL============================

	template <class InputIterator1, class InputIterator2>
	bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
	{
		while (first1 != last1)
		{
			if (!(*first1 == *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}

	// ==========================static_assert============================

	template<typename T, typename U>
	struct is_same			// Rentre dedans si c'est un type different
	{
		static const bool value = false; 
	};
	
	template<typename T>
	struct is_same<T, T>		// Rentre dedans si c'est le même type
	{ 
		static const bool value = true; 
	};

	template<bool>
	struct static_assert_ft
	{
	};

	template<>
	struct static_assert_ft<true>	// Si c'est true la fonction existe et ca compile
	{
		static void func() { /* ne sert a rien */ }
	};
}

#endif