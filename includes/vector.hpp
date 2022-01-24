#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory> // for std::allocator
//# include <iostream> // For input output
# include <stdexcept> // For standard exceptions
# include <sstream> // For exception what() string generation
# include <limits> // For numeric_limits in max_size()

# include "iterator.hpp"
# include "type_traits.hpp"
# include "algorithm.hpp"

namespace ft
{
	template < class T, class Allocator = std::allocator < T > >
	class vector
	{
		public:
			// Member types
			typedef T														value_type;
			typedef Allocator												allocator_type;
			typedef	typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			// LegacyRandomAccessIterator<T>								iterator;
			// LegacyRandomAccessIterator<T> const							const_iterator;
			typedef pointer													iterator;		// should be custom LRAI
			typedef const_pointer											const_iterator;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type difference_type;	// should be iterator_trais<iterator>::difference_type (usually equiv. ptrdiff_t)
			typedef typename allocator_type::size_type						size_type;			// An unsigned integral type that can represent any non-negative value of difference_type (Usually size_t)
			
			// Member functions
			// Constructors
			explicit vector(const Allocator & alloc = allocator_type()) : __start(0), __capacity(0), __size(0),  __alloc(alloc)
			{
			}

			explicit vector( size_type count, const value_type & value = value_type(),
								const allocator_type & alloc = allocator_type()) 
							: __start(0), __capacity(0), __size(0), __alloc(alloc)
			{
				this->reserve(count);
				for (size_type i = 0; i < count; ++i)
				{
					this->push_back(value);
				}
			}

			template< class InputIt >
			vector( InputIt first, InputIt last,
					const allocator_type & alloc = allocator_type(),
					typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL)  : __start(0), __capacity(0), __size(0), __alloc(alloc)
			{
				this->insert(this->begin(), first, last);
			}

			vector( const vector & other ) : __start(0), __capacity(0), __size(0),  __alloc(other.get_allocator())
			{
				this->reserve(other.capacity());
				this->__copy_space(this->__start, other.begin(), (other.size())); //use insert instead?
				this->__size = other.size();
			}

			~vector() {
				// std::cout << "Deleting vector" << std::endl;
				// get_allocator().deallocate(__start, this->capacity());
				__destruct_vector(); //Should destruct, or only deallocate???
			};
			vector &	operator=(vector const & other) {
				if (this != &other)
				{
					this->assign(other.begin(), other.end());
				}
				return (*this);
			}
			
			void	assign(size_type n, const value_type & value)
			{
				this->clear();
				this->reserve(n);
				this->insert(this->begin(), n, value);
			}

			template <class InputIt>
			void	assign(InputIt first, InputIt last,
						typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL)
			{
				this->clear();
				this->insert(this->begin(), first, last);
			}

			allocator_type	get_allocator() const {
				return (this->__alloc);
			};

			// Element access
			reference	at(size_type pos) {
				if (!(pos < this->size()))
				{
					std::stringstream ss;
					ss << "vector::_M_range_check: __n (which is " << pos << ") >= this->size() (which is " << this->size() << ")";
					throw std::out_of_range(ss.str());
				}
				return (*(this->__start + pos));
			}
			const_reference	at(size_type pos) const {
				if (!(pos < this->size()))
				{
					std::stringstream ss;
					ss << "vector::_M_range_check: __n (which is " << pos << ") >= this->size() (which is " << this->size() << ")";
					throw std::out_of_range(ss.str());
				}
				return (*(this->__start + pos));
			}

			reference		operator[](size_type pos) {
				return (*(this->__start + pos));
			}
			const_reference	operator[](size_type pos) const {
				return (*(this->__start + pos));
			}

			reference		front() {
				return (*__start);
			};
			const_reference		front() const {
				return (*__start);
			};
			reference	back() {
				return (*(this->__start + this->size() - 1));
			};
			const_reference	back() const {
				return (*(this->__start + this->size() - 1));
			};

			pointer	data() {
				return (this->__start);
			}

			const_pointer	data() const {
				return (this->__start);
			}
			
			// Iterators
			iterator	begin() {
				return (this->__start);
			}
			const_iterator	begin() const {
				return (this->__start);
			}
			iterator	end() {
				return (this->__start + this->size());
			}
			const_iterator	end() const {
				return (this->__start + this->size());
			}

			reverse_iterator	rbegin()  {
				return (reverse_iterator(this->end()));
			}
			const_reverse_iterator	rbegin() const {
				return (reverse_iterator(this->end()));
			}
			reverse_iterator	rend() {
				return (reverse_iterator(this->begin()));
			}
			const_reverse_iterator	rend() const {
				return (reverse_iterator(this->begin()));
			}

			// Capacity
			bool	empty() const {
				return (this->begin() == this->end());
			}
			
			size_type	size() const {
				return (this->__size);
			};

			size_type	max_size() const {
				return (this->get_allocator().max_size());
			}

			void	reserve( size_type new_cap ) {
				if (new_cap > this->max_size())
				{
					throw std::length_error("vector::reserve"); // Check this exception message against real
				}
				if (this->capacity() < new_cap)
				{
					pointer new_space = this->get_allocator().allocate(new_cap);
					this->__copy_space(new_space, this->__start, this->size());
					this->__destroy_space(this->__start, this->size());
					this->__start = new_space;
					this->__capacity = new_cap;
				}
			}
			size_type	capacity() const {
				return (this->__capacity);
			}

			// Modifiers
			void	clear()
			{
				for (size_type i = 0; i < this->size(); ++i)
				{
					this->get_allocator().destroy(this->__start + i);
				}
				this->__size = 0;
			}
			
			iterator insert( iterator pos, const T& value )
			{
				difference_type		diff = pos - this->begin();
				if (diff < 0)
					diff = 0;
				if (this->__capacity - this->size() < 1)
				{
					size_type	new_capacity = 2 * this->__capacity;
					if (this->__capacity == 0)
						new_capacity = 1;
					this->reserve(new_capacity);	
				}
				this->__copy_space(this->__start + diff + 1, this->__start + diff, this->size() - diff);
				this->get_allocator().construct(this->__start + diff, value);
				++this->__size;
				return (this->__start + diff);
			}

			void insert( iterator pos, size_type count, const value_type& value )
			{
				difference_type		diff = pos - this->begin();
				if (this->__capacity - this->size() < count)
				{
					size_type	new_capacity = this->__capacity;
					if (count > this->__capacity)
						new_capacity += count - (this->__capacity - this->size());
					else if ((this->__capacity * 2) - this->size() < count)
						new_capacity += count - (this->__capacity - this->size());
					else
						new_capacity *= 2;
					this->reserve(new_capacity);
				}
				this->__copy_space(this->__start + diff + count, this->__start + diff, this->size() - diff);
				while (count > 0)
				{
					this->get_allocator().construct(this->__start + diff, value);
					++diff;
					--count;
					++this->__size;
				}
			}

			template <class InputIt>
			void insert(iterator pos, InputIt first, InputIt last,
						typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type * = NULL)
			{
				difference_type diff = pos - this->begin();
				difference_type len = 0;

				for (InputIt it = first; it != last; ++it)
					++len;
				this->reserve(len);
				this->__copy_space(this->__start + diff + len, this->__start + diff, this->size() - diff);
				while (first != last)
				{
					this->get_allocator().construct(this->__start + diff, *first);
					++diff;
					++first;
					++this->__size;
				}
			}

			iterator	erase(iterator pos)
			{
				//check if pos is past end?
				iterator ret = pos;
				while (pos + 1 != this->end())
				{
					*pos = *(pos + 1);
					++pos;
				}
				this->get_allocator().destroy(pos);
				this->__size -= 1;
				return (ret);
			}

			iterator	erase(iterator first, iterator last)
			{
				//check if first and last are in range, or not?
				difference_type N = last - first;
				while (first + N != this->end())
				{
					(*first) = *(first + N);
					++first;
				}
				while (first != this->end())
				{
					this->get_allocator().destroy(first);
					++first;
				}
				this->__size -= N;
				return (last);
			}


			void	push_back(T element) {
				this->insert(this->end(), element);
			};
			
			void	pop_back()
			{
				this->erase(this->end() - 1);
			}

			void resize( size_type count, T value = T() )
			{
				while (count < this->size())
					this->pop_back();
				while (count > this->size())
					this->push_back(value);
			}

			void	swap(vector<T, Allocator> & x)
			{
				if (this == &x)
					return ;

				pointer start_tmp = x.__start;
				size_type size_tmp = x.size();
				size_type cap_tmp = x.__capacity;
				allocator_type alloc_tmp = x.__alloc;
				x.__start = this->__start;
				x.__size = this->size();
				x.__capacity = this->__capacity;
				x.__alloc = this->__alloc;	
				this->__start = start_tmp;
				this->__size = size_tmp;
				this->__capacity = cap_tmp;
				this->__alloc = alloc_tmp;
			}

		private:
			pointer __start;				//pointer to start
			pointer	__end;					// pointer to end of elements;
			size_type		__capacity;		// allocated size
			size_type		__size;		// number of elements
			allocator_type	__alloc; // Allocator

			void	__copy_space(pointer	dest, const_iterator	src, difference_type const N) {
				difference_type	i;

				if (dest > src)
				{
					i = N - 1;
					while (i >= 0)
					{
						this->get_allocator().construct(dest + i, *(src + i));
						--i;
					}
				}
				else
				{
					i = 0;
					while (i < N)
					{
						this->get_allocator().construct(dest + i, *(src + i));
						++i;
					}
				}
			}
			void	__destroy_space(pointer	start, size_type N) {
				for (int i = N - 1; i >= 0; --i)
				{
					this->get_allocator().destroy(start + i);
				}
				this->get_allocator().deallocate(start, N);
			}
			void	__destruct_vector() {
				for (int i = this->size() - 1; i >= 0; --i)
				{
					this->get_allocator().destroy(this->__start + i);
				}
				this->get_allocator().deallocate(this->__start, this->capacity());
			}
	};


	template < class T, class U >
	bool	operator==(vector<T, U> const & lhs, vector<T, U> const & rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		typename vector<T, U>::const_iterator it1 = lhs.begin();
		typename vector<T, U>::const_iterator it2 = rhs.begin();
		typename vector<T, U>::const_iterator ite1 = lhs.end();
		typename vector<T, U>::const_iterator ite2 = rhs.end();
		while (it1 != ite1 && it2 != ite2)
		{
			if (*it1 != *it2)
				return (false);
			++it1;
			++it2;
		}
		return (true);
	}
	template < class T, class U >
	bool	operator!=(vector<T, U> const & lhs, vector<T, U> const & rhs)
	{
		return (!(lhs == rhs));
	}
	template < class T, class U >
	bool	operator<(vector<T, U> const & lhs, vector<T, U> const & rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	template < class T, class U >
	bool	operator<=(vector<T, U> const & lhs, vector<T, U> const & rhs)
	{
		return (!(rhs < lhs));
	}
	template < class T, class U >
	bool	operator>(vector<T, U> const & lhs, vector<T, U> const & rhs)
	{
		return (rhs < lhs);
	}
	template < class T, class U >
	bool	operator>=(vector<T, U> const & lhs, vector<T, U> const & rhs)
	{
		return (!(lhs < rhs));
	}

	template < class T, class U >
	void	swap(vector<T, U> & v1, vector<T, U> & v2)
	{
		v1.swap(v2);
	}

}
#endif
