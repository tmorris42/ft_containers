#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory> // for std::allocator
//# include <iostream> // For input output
# include <stdexcept> // For standard exceptions
# include <sstream> // For exception what() string generation
# include <limits> // For numeric_limits in max_size()

namespace ft
{
	template < class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
			// Member types
			typedef T			value_type;
			typedef Allocator	allocator_type;
			typedef std::size_t			size_type;
			typedef std::ptrdiff_t		difference_type;

			typedef typename allocator_type::pointer		pointer;
			typedef typename allocator_type::const_pointer	const_pointer;
			typedef	value_type							& reference;
			typedef value_type const					& const_reference;

			// LegacyRandomAccessIterator<T>			iterator;
			// LegacyRandomAccessIterator<T> const		const_iterator;
			typedef pointer								iterator;		// should be custom LRAI
			typedef const_pointer						const_iterator;
			// std::reverse_iterator<iterator>			reverse_iterator;
			// std::reverse_iterator<const_iterator>	const_reverse_iterator;
			
			//Member functions
			vector() : __start(0), __capacity(0), __size(0) {
			};
			~vector() {
				// std::cout << "Deleting vector" << std::endl;
				// get_allocator().deallocate(__start, 1);
				__destroy_space(this->__start, this->__size);
			};
			vector &	operator=(vector const & other) {
				this->reserve(other->size());
				__copy_space(this->__start, other->begin());
			}
			
			void	assign();
			allocator_type	get_allocator() {return (allocator_type());};

			// Element access
			reference	at(size_type pos) {
				if (!(pos < this->size()))
				{
					std::string err;// = "vector::_M_range_check: __n (which is "pos) >= this->size() (which is this->size())";
					std::stringstream ss;
					ss << "vector::_M_range_check: __n (which is " << pos << ") >= this->size() (which is " << this->size() << ")";
					err = ss.str();
					throw std::out_of_range(err);
				}
				return (*(this->__start + pos));
			}
			const_reference	at(size_type pos) const {
				if (!(pos < this->size()))
				{
					std::string err;// = "vector::_M_range_check: __n (which is "pos) >= this->size() (which is this->size())";
					std::stringstream ss;
					ss << "vector::_M_range_check: __n (which is " << pos << ") >= this->size() (which is " << this->size() << ")";
					err = ss.str();
					throw std::out_of_range(err);
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
				return (*(this->__start + this->__size - 1));
			};
			const_reference	back() const {
				return (*(this->__start + this->__size - 1));
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
				return (this->__start + this->__size);
			}
			const_iterator	end() const {
				return (this->__start + this->__size);
			}

			void	rbegin();
			void	rend();

			// Capacity
			bool	empty() {
				return (this->begin() == this->end());
			}
			size_type	size() {
				return (this->__size);
			};
			size_type	max_size() const {
				return (std::numeric_limits<difference_type>::max());
			}
			void	reserve( size_type new_cap ) {
				if (new_cap > this->max_size())
					throw std::length_error("Error, too new capcity is greater than max_size()");
				if (this->capacity() < new_cap)
				{
					pointer new_space = this->get_allocator().allocate(new_cap);
					this->__copy_space(new_space, this->__start, this->__size);
					this->__destroy_space(this->__start, this->__size);
					this->__start = new_space;
					this->__capacity = new_cap;
				}
			}
			size_type	capacity() const {
				return (this->__capacity);
			}

			// Modifiers
			void	clear();
			void	insert();
			void	erase();
			void	push_back(T element) {
				if (this->__capacity - this->__size < 1)
				{
					size_type	new_capacity = 1;
					if (this->__capacity > 0)
						new_capacity = 2 * this->__capacity;
					this->reserve(new_capacity);
					this->get_allocator().construct(this->__start + this->__size, element);
					++this->__size;
				}
				else
				{
					this->get_allocator().construct(this->__start + this->__size, element);
					++this->__size;
				}
			};
			void	pop_back();
			void	resize();
			void	swap();

		private:
			pointer		__start;	//pointer to start	
			size_type	__capacity;		// allocated size
			size_type	__size;		// number of elements

			void	__copy_space(pointer	dest, pointer	src, size_type N) {
				while (N > 0)
				{
					*dest = *src;
					++dest;
					++src;
					--N;
				}
			}
			void	__destroy_space(pointer	start, size_type N) {
				for (; N > 0; --N)
				{
					this->get_allocator().destroy(start + N);
				}
				this->get_allocator().deallocate(start, N);
			}
	};


	template < class T, class U >
	bool	operator==(vector<T, U> const & lhs, vector<T, U> const & rhs);
	template < class T, class U >
	bool	operator!=(vector<T, U> const & lhs, vector<T, U> const & rhs);
	template < class T, class U >
	bool	operator<(vector<T, U> const & lhs, vector<T, U> const & rhs);
	template < class T, class U >
	bool	operator<=(vector<T, U> const & lhs, vector<T, U> const & rhs);
	template < class T, class U >
	bool	operator>(vector<T, U> const & lhs, vector<T, U> const & rhs);
	template < class T, class U >
	bool	operator>=(vector<T, U> const & lhs, vector<T, U> const & rhs);

}
#endif
