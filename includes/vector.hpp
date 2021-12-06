#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>

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
			// value_type							&reference;
			// value_type const					&const_reference;

			// LegacyRandomAccessIterator<T>			iterator;
			// LegacyRandomAccessIterator<T> const		const_iterator;
			// std::reverse_iterator<iterator>			reverse_iterator;
			// std::reverse_iterator<const_iterator>	const_reverse_iterator;
			
			//Member functions
			vector() {};
			~vector() {};
			vector const &	operator=(vector const & rhs);
			
			void	assign();
			Allocator	get_allocator();

			// Element access
			void	at();
			void	operator[](unsigned int index);
			T &		front() { return (*(new T()));};
			T const &		front() const { };
			void	back();
			void	data();
			
			// Iterators
			void	begin();
			void	end();
			void	rbegin();
			void	rend();

			// Capacity
			void	empty();
			size_type	size() { return (-99);};
			void	max_size();
			void	reserve();
			void	capacity();

			// Modifiers
			void	clear();
			void	insert();
			void	erase();
			void	push_back(T element) {T temp; temp = element; if (temp == element) return;};
			void	pop_back();
			void	resize();
			void	swap();


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
