#ifndef ITERATOR_HPP
#define ITERATOR_HPP

namespace ft
{
	struct input_iterator_tag
	{
	};
	struct output_iterator_tag
	{
	};
	struct forward_iterator_tag : public input_iterator_tag
	{
	};
	struct bidirectional_iterator_tag : public forward_iterator_tag
	{
	};
	struct random_access_iterator_tag : public bidirectional_iterator_tag
	{
	};

	// iterator_traits
	template <class Iterator>
	class iterator_traits
	{
	public:
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};

	template <class T>
	class iterator_traits<T *>
	{
	public:
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
		typedef ft::random_access_iterator_tag iterator_category;
	};

	template <class T>
	class iterator_traits<const T *>
	{
	public:
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef const T *pointer;
		typedef const T &reference;
		typedef ft::random_access_iterator_tag iterator_category;
	};

	// reverse_iterator
	template <class Iter>
	class reverse_iterator
	{
	public:
		typedef Iter iterator_type;
		typedef typename ft::iterator_traits<Iter>::iterator_category iterator_category;
		typedef typename ft::iterator_traits<Iter>::value_type value_type;
		typedef typename ft::iterator_traits<Iter>::difference_type difference_type;
		typedef typename ft::iterator_traits<Iter>::pointer pointer;
		typedef typename ft::iterator_traits<Iter>::reference reference;

		reverse_iterator() : current() {}
		explicit reverse_iterator(iterator_type x) : current(x) {}
		template <class U>
		reverse_iterator(const reverse_iterator<U> &other) : current(other.base())
		{
		}
		template <class U>
		reverse_iterator &operator=(reverse_iterator<U> const &other)
		{
			if (*this == other)
				return (*this);
			this->current = other.base();
			return (*this);
		}

		reverse_iterator &operator+=(difference_type n)
		{
			this->current -= n;
			return (*this);
		}

		const reverse_iterator operator+(difference_type n) const
		{
			return reverse_iterator(this->current - n);
		}

		reverse_iterator &operator++()
		{
			--this->current;
			return (*this);
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator ret = *this;
			++(*this);
			return (ret);
		}

		reverse_iterator &operator-=(difference_type n)
		{
			this->current += n;
			return (*this);
		}

		const reverse_iterator operator-(difference_type n) const
		{
			reverse_iterator ret(*this);
			ret -= n;
			return (ret);
		}

		reverse_iterator &operator--()
		{
			++this->current;
			return (*this);
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator ret = *this;
			--(*this);
			return (ret);
		}

		reference operator*()
		{
			iterator_type temp(this->current);
			--temp;
			return (*temp);
		}

		pointer operator->()
		{
			return (&this->operator*());
		}
		reference operator*() const
		{
			iterator_type temp(this->current);
			--temp;
			return (*temp);
		}

		pointer operator->() const
		{
			return (&this->operator*());
		}

		reference operator[](difference_type n) const
		{
			return ((*this + (n + 1)).current[0]);
		}

		iterator_type base() const
		{
			return (this->current);
		}

	protected:
		iterator_type current;
	};
	template <class Iterator1, class Iterator2>
	bool operator==(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{
		return (lhs.base() == rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator!=(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{
		return !(lhs == rhs);
	}
	template <class Iterator1, class Iterator2>
	bool operator<(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{
		return (lhs.base() > rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator<=(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator>(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{
		return (lhs.base() < rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator>=(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}
	template <class Iter>
	reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter> &it)
	{
		return (it + n);
	}
	template <class Iterator1, class Iterator2>
	typename reverse_iterator<Iterator1>::difference_type operator-(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{
		return (rhs.base() - lhs.base());
	}
}

#endif
