#ifndef STACK_HPP
# define STACK_HPP

#include "vector.hpp"

namespace ft
{
	template < class T, class Container = vector<T> >
	class stack
	{
		public:
			// Member Types
			typedef T			value_type;
			typedef Container	container_type;
			typedef size_t				size_type;

			// Constructor
			explicit stack (const container_type & cntr = container_type()) : c(cntr) {

			}

			// Member Functions
			bool empty() const {
				return (this->c.empty());
			}
			size_type	size() const {
				return (this->c.size());
			}
			value_type &	top() {
				return (this->c.back());
			}
			const value_type &	top() const {
				return (this->c.back());
			}
			void	push(const value_type & val) {
				this->c.push_back(val);
			}
			void	pop() {
				this->c.pop_back();
			}

		protected:
			container_type	c;

		public:
			// Non-member Relational Operators
			friend bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
				return (lhs.c == rhs.c);
			}

			friend bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
				return (lhs.c != rhs.c);
			}

			friend bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
				return (lhs.c < rhs.c);
			}

			friend bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
				return (lhs.c <= rhs.c);
			}

			friend bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
				return (lhs.c > rhs.c);
			}

			friend bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
				return (lhs.c >= rhs.c);
			}
	};
}

#endif
