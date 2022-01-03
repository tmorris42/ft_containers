#ifndef ITERATOR_HPP
# define ITERATOR_HPP

namespace ft
{
	struct random_access_iterator_tag {};

	// iterator_traits
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

	// reverse_iterator
	template <class Iter>
	class reverse_iterator
	{
		public:
			typedef Iter													iterator_type;
			typedef typename std::iterator_traits<Iter>::iterator_category	iterator_category;
			typedef typename std::iterator_traits<Iter>::value_type			value_type;
			typedef typename std::iterator_traits<Iter>::difference_type	difference_type;
			typedef typename std::iterator_traits<Iter>::pointer			pointer;
			typedef typename std::iterator_traits<Iter>::reference			reference;

			reverse_iterator() : current() {}
			explicit reverse_iterator(iterator_type x) : current(x) {}
			template <class U> reverse_iterator( const reverse_iterator<U> & other) : current(other.base()) {}
			template< class U > reverse_iterator& operator=( const reverse_iterator<U>& other ) {
				if (this == &other)
					return (*this);
				this->current = other->current;
				return (*this);
			}

			reverse_iterator & operator+=( difference_type n ) {
				this->current -= n;
				return (*this);
			}

			reverse_iterator operator+( difference_type n ) const {
				reverse_iterator	ret(*this);
				ret += n;
				return (ret);
			}

			reverse_iterator& operator++() {
				return (*this += 1);
			}

			reverse_iterator operator++( int ) {
				reverse_iterator ret = *this;
				++(*this);
				return (ret);
			}

			reverse_iterator & operator-=( difference_type n ) {
				this->current += n;
				return (*this);
			}

			reverse_iterator operator-( difference_type n ) const {
				reverse_iterator	ret(*this);
				ret -= n;
				return (ret);
			}

			reverse_iterator& operator--() {
				return (*this -= 1);
			}

			reverse_iterator operator--( int ) {
				reverse_iterator ret = *this;
				--(*this);
				return (ret);
			}

			reference operator*() const {
				return (*(this->current - 1));
			}

			pointer operator->() const {
				return (&this->operator*());
			}

			reference operator[](difference_type n) const {
				reverse_iterator<Iter> tmp(*this);
				tmp += n;
				return (tmp.operator*());
			}

			iterator_type base() const {
				return (this->current);
			}

		protected:
			iterator_type current;
	};
	template <class Iterator1, class Iterator2>
	bool operator==(const reverse_iterator<Iterator1> & lhs, const reverse_iterator<Iterator2> & rhs) {
		return (lhs.base() == rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator!=(const reverse_iterator<Iterator1> & lhs, const reverse_iterator<Iterator2> & rhs) {
		return !(lhs == rhs);
	}
	template <class Iterator1, class Iterator2>
	bool operator<(const reverse_iterator<Iterator1> & lhs, const reverse_iterator<Iterator2> & rhs) {
		return (lhs.base() > rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator<=(const reverse_iterator<Iterator1> & lhs, const reverse_iterator<Iterator2> & rhs) {
		return (lhs.base() >= rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator>(const reverse_iterator<Iterator1> & lhs, const reverse_iterator<Iterator2> & rhs) {
		return (lhs.base() < rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator>=(const reverse_iterator<Iterator1> & lhs, const reverse_iterator<Iterator2> & rhs) {
		return (lhs.base() <= rhs.base());
	}
	template < class Iter >
	reverse_iterator<Iter>	operator+( typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it ) {
		return (it + n);
	}
	template< class Iterator >
	typename reverse_iterator<Iterator>::difference_type	operator-( const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs ) {
		return (rhs.base() - lhs.base());
	}
}

#endif
