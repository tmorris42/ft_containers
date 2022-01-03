#ifndef ITERATOR_HPP
# define ITERATOR_HPP

namespace ft
{
	struct random_access_iterator_tag {};

	template <class Iterator>
	class iterator_traits
	{
		public:
			static typename Iterator::difference_type	difference_type;
			static typename Iterator::value_type		value_type;
			static typename Iterator::pointer			pointer;
			static typename Iterator::reference			reference;
			static typename Iterator::iterator_category	iterator_category;
	};

	template <class T>
	class iterator_traits<T*>
	{
		public:
			static std::ptrdiff_t					difference_type;
			static T								value_type;
			static T								*pointer;
			static T								&reference;
			static ft::random_access_iterator_tag	iterator_category;
	};

	template <class T>
	class iterator_traits<const T*>
	{
		public:
			static std::ptrdiff_t						difference_type;
			static T								value_type;
			static const T *						pointer;
			static const T &						reference;
			static ft::random_access_iterator_tag	iterator_category;
	};
}

#endif
