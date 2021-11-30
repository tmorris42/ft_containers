#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>

template < class T, class Allocator = std::allocator<T> >
class vector
{
	public:
		// Member types
		T				value_type;
		Allocator		allocator_type;
		std::size_t		size_type;
		std::ptrdiff_t	difference_type;

		Allocator::pointer			*pointer;
		Allocator::pointer const	*const_pointer;
		T				&reference;
		T const			&const_reference;

		LegacyRandomAccessIterator<T>			iterator;
		LegacyRandomAccessIterator<T> const		const_iterator;
		std::reverse_iterator<iterator>			reverse_iterator;
		std::reverse_iterator<const_iterator>	const_reverse_iterator;
		
		//Member functions
		vector();
		~vector();
		vector const &	operator=(vector const & rhs);
		
		void	assign();
		Allocator	get_allocator();

		// Element access
		void	at();
		void	operator[]();
		void	front();
		void	back();
		void	data();
		
		// Iterators
		void	begin();
		void	end();
		void	rbegin();
		void	rend();

		// Capacity
		void	empty();
		void	size();
		void	max_size();
		void	reserve();
		void	capacity();

		// Modifiers
		void	clear();
		void	insert();
		void	erase();
		void	push_back();
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


#endif
