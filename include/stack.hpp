#ifndef __STACK_H__
#define __STACK_H__

#include <vector.hpp>

namespace ft
{
	template < class T, class Container = ft::vector<T> >
	class stack
	{
		public:
		/* default typedef */
			typedef	T value_type;
			typedef	Container container_type;
			typedef size_t size_type;
		/* other typedef */
			typedef typename container_type::iterator iterator;


		explicit stack(const container_type & ctnr = container_type());
	//	~stack();

		bool empty() const;
		size_type size() const;

		value_type& top(void);
		const value_type& top(void) const;

		void	push(const value_type& val);
		void	pop(void);

		template < class T1, class C1 >
		friend bool operator==(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs);

		template < class T1, class C1 >
		friend bool operator<(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs);

		protected:
			container_type	_cntr;
	};
	
	

	template < class T, class Container >
	bool stack<T, Container>::empty() const
	{
		return _cntr.empty();
	}

	template < class T, class Container >
	typename stack<T, Container>::size_type stack<T, Container>::size() const
	{
		return _cntr.size();
	}
	
	template < class T, class Container >
	typename stack<T, Container>::value_type& stack<T, Container>::top() 
	{
		return _cntr.top();
	}

	template < class T, class Container >
	const typename stack<T, Container>::value_type& stack<T, Container>::top() const
	{
		return _cntr.top();
	}
	
	template < class T, class Container >
	void stack<T, Container>::push(const value_type& val) 
	{
		_cntr.push_back(val);
		return;
	}
	
	template < class T, class Container >
	void stack<T, Container>::pop(void) 
	{
		_cntr.pop_back();
		return;
	}

	/*
		** Constructor & destructor
	*/

	template < class T, class Container >
	stack<T, Container>::stack(const container_type & ctnr) : _cntr(ctnr)
	{
		return;
	}

/*	template < class T, class Container >
	stack<T, Container>::~stack()
	{
		return;
	}*/

	template <class T, class Container>
 	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._cntr == rhs._cntr);
	}

	template <class T, class Container>
  	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return !(lhs._cntr == rhs._cntr);
	}

	template <class T, class Container>
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._cntr < rhs._cntr);
	}
	
	template <class T, class Container>
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return !(rhs > lhs);
	}

	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return !(lhs < rhs );
	}

};
#endif // __STACK_H__