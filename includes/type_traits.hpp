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
	struct integral_constant {
		static const T value = v;
		typedef T value_type;
		typedef integral_constant<T, v> type;
		operator T() { return v; }
	};
	template <typename T>
	struct is_integral : public integral_constant<bool, false> {};
	template <>	struct is_integral<bool> : public integral_constant<bool, true> {};
	template <>	struct is_integral<char> : public integral_constant<char, true> {};
	// template <>	struct is_integral<char16_t> : public integral_constant<char16_t, true> {};
	// template <>	struct is_integral<char32_t> : public integral_constant<char32_t, true> {};
	template <>	struct is_integral<wchar_t> : public integral_constant<wchar_t, true> {};
	template <>	struct is_integral<signed char> : public integral_constant<signed char, true> {};

	template <>	struct is_integral<short int> : public integral_constant<short int, true> {};
	template <>	struct is_integral<int> : public integral_constant<int, true> {};
	template <>	struct is_integral<long int> : public integral_constant<long int, true> {};
	// template <>	struct is_integral<long long int> : public integral_constant<long long int, true> {};
	
	template <>	struct is_integral<unsigned char> : public integral_constant<unsigned char, true> {};
	template <>	struct is_integral<unsigned short int> : public integral_constant<unsigned short int, true> {};
	template <>	struct is_integral<unsigned int> : public integral_constant<unsigned int, true> {};
	template <>	struct is_integral<unsigned long int> : public integral_constant<unsigned long int, true> {};
	// template <>	struct is_integral<unsigned long long int> : public integral_constant<unsigned long long int, true> {};

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

	template<class T, class U>
	struct is_same{
		static const bool value = false;
		operator T() { return value; }
		operator U() { return value; }
	};
	
	template<class T>
	struct is_same<T, T> {
		static const bool value = true;
		operator T() { return value; }
	};
}
#endif
