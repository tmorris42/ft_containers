#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <iostream>

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
			std::ptrdiff_t		difference_type;

			typedef typename allocator_type::pointer		pointer;
			typedef typename allocator_type::const_pointer	const_pointer;
			typedef	value_type							& reference;
			typedef value_type const					& const_reference;

			// LegacyRandomAccessIterator<T>			iterator;
			// LegacyRandomAccessIterator<T> const		const_iterator;
			// std::reverse_iterator<iterator>			reverse_iterator;
			// std::reverse_iterator<const_iterator>	const_reverse_iterator;
			
			//Member functions
			vector() : __start(), __capacity(0), __size(0) {
				// __start = get_allocator().allocate(1);
			};
			~vector() {
				// std::cout << "Deleting vector" << std::endl;
				// get_allocator().deallocate(__start, 1);
				for (; this->__size > 0; --this->__size)
				{
					this->get_allocator().destroy(this->__start + this->__size);
				}
				this->get_allocator().deallocate(this->__start, this->__size);
			};
			vector const &	operator=(vector const & rhs);
			
			void	assign();
			allocator_type	get_allocator() {return (allocator_type());};

			// Element access
			void	at();
			void	operator[](unsigned int index);
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

			void	data();
			
			// Iterators
			void	begin();
			void	end();
			void	rbegin();
			void	rend();

			// Capacity
			void	empty();
			size_type	size() {
				return (this->__size);
			};
			void	max_size();
			void	reserve();
			void	capacity();

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
					pointer new_space = this->get_allocator().allocate(new_capacity);
					this->__copy_space(new_space, this->__start, this->__size);
					this->__destroy_space(this->__start, this->__size);
					this->__start = new_space;
					this->get_allocator().construct(this->__start + this->__size, element);
					++this->__size;
					this->__capacity = new_capacity;
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
