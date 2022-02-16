#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

namespace ft
{
	template <bool B, class T = void>
	struct enable_if
	{

	};

	template <class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	template <class T, T v>
	struct s_is_integral {
		static const T value = v;
		typedef T value_type;
		typedef s_is_integral<T, v> type;
		operator T() { return v; }
	};
	template <typename T>
	struct integral_constant_sub : public s_is_integral<bool, false> {};
	template <>	struct integral_constant_sub<bool> : public s_is_integral<bool, true> {};
	template <>	struct integral_constant_sub<char> : public s_is_integral<char, true> {};
	// template <>	struct integral_constant_sub<char16_t> : public s_is_integral<char16_t, true> {};
	// template <>	struct integral_constant_sub<char32_t> : public s_is_integral<char32_t, true> {};
	template <>	struct integral_constant_sub<wchar_t> : public s_is_integral<wchar_t, true> {};
	template <>	struct integral_constant_sub<signed char> : public s_is_integral<signed char, true> {};

	template <>	struct integral_constant_sub<short int> : public s_is_integral<short int, true> {};
	template <>	struct integral_constant_sub<int> : public s_is_integral<int, true> {};
	template <>	struct integral_constant_sub<long int> : public s_is_integral<long int, true> {};
	// template <>	struct integral_constant_sub<long long int> : public s_is_integral<long long int, true> {};
	
	template <>	struct integral_constant_sub<unsigned char> : public s_is_integral<unsigned char, true> {};
	template <>	struct integral_constant_sub<unsigned short int> : public s_is_integral<unsigned short int, true> {};
	template <>	struct integral_constant_sub<unsigned int> : public s_is_integral<unsigned int, true> {};
	template <>	struct integral_constant_sub<unsigned long int> : public s_is_integral<unsigned long int, true> {};
	// template <>	struct integral_constant_sub<unsigned long long int> : public s_is_integral<unsigned long long int, true> {};

	template <typename T>
	struct is_integral : public integral_constant_sub<T> {} ;

	template<bool flag, class IsTrue, class IsFalse> struct is_const;
	template<class IsTrue, class IsFalse>
	struct is_const<true, IsTrue, IsFalse>
	{
		typedef IsTrue type;
	};
	template<class IsTrue, class IsFalse>
	struct is_const<false, IsTrue, IsFalse>
	{
		typedef IsFalse type;
	};

}
#endif
