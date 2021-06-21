#ifndef __LIST_H__
#define __LIST_H__

#include <memory>
#include <string>
#include <iostream>

#include <iterator.hpp>


namespace ft
{

	/*
	 * Node Contain data
	*/

	template <typename _Tp>
	class Node
	{
		public:
			
			typedef Node<_Tp>	_Self;
			typedef	_Tp		value_type;
			typedef	_Tp*	pointer;
			typedef	_Tp&	reference;

			Node<_Tp>() : _next(0), _prev(0), _data() {}

			Node<_Tp>(const value_type& ref)  : _next(0), _prev(0), _data(ref) {}

			Node *	_next;
			Node *	_prev;

			_Tp		_data;
	};

	/*
		struct for List::iterator
			fuction overload
	*/

	template <typename _Tp>
	class _List_Iterator
	{
		public:
			typedef	_List_Iterator<_Tp>		_Self;
			typedef Node<_Tp>				Tnode;

			typedef	_Tp				value_type;
			typedef _Tp*			pointer;
			typedef _Tp&			reference;
			typedef _Self			iterator_type;
			typedef std::bidirectional_iterator_tag iterator_category;
			//typedef typename std::iterator_traits<_Self>::value_type value_type;
			typedef std::ptrdiff_t difference_type;
			

			_List_Iterator<_Tp>() : _node(NULL) {}

			_List_Iterator<_Tp>(Tnode * src) : _node(src) {}

			_List_Iterator<_Tp>(const _List_Iterator & src) { *this = src; }

			~_List_Iterator<_Tp>() {};

			reference	operator*() { return _node->_data; }
			pointer		operator->() { return &(_node->_data); }


			_Self& operator=(const _Self & ref)
			{
				_node = ref._node;
				return *this;
			}

			//Tnode* operator->() {return _node;};

			_Self& operator++()
			{
				_node = _node->_next;
				return *this;
			}

			_Self operator++(int)
			{
				_Self _tmp = *this;
				++*this;
				return _tmp;
			}

			_Self& operator--()
			{
				_node = _node->_prev;
				return *this;

			}

			_Self operator--(int)
			{
				_Self _tmp = *this;
				_node = _node->_prev;
				return _tmp;
			}
			
			friend bool
			operator==(const _Self& __x, const _Self& __y)	{ return __x._node == __y._node; }
			friend bool
			operator!=(const _Self& __x, const _Self& __y)	{ return __x._node != __y._node; }

		public:
			Tnode * _node;
	};

	template <typename _Tp>
	class _Const_List_Iterator
	{
		public:
			typedef	_Const_List_Iterator<_Tp>		_Self;
			typedef Node<_Tp>				Tnode;

			typedef	_Tp				value_type;
			typedef const _Tp*			pointer;
			typedef const _Tp&			reference;
			typedef _Self			iterator_type;
			typedef std::bidirectional_iterator_tag iterator_category;
			typedef std::ptrdiff_t difference_type;
			

			_Const_List_Iterator() : _node(NULL) {}

			_Const_List_Iterator(Tnode * src) : _node(src) {}

			_Const_List_Iterator(const _Self& src) { *this = src; }

			_Const_List_Iterator(const _List_Iterator<_Tp>& src) { *this = src; }

			~_Const_List_Iterator() {}
			
			reference	operator*() { return _node->_data; }
			pointer		operator->() { return &(_node->_data); }

			_Self& operator=(const _Self & ref)
			{
				_node = ref._node;
				return *this;
			}

			_Self& operator=(const _List_Iterator<_Tp> & ref)
			{
				_node = ref._node;
				return *this;
			}

			_Self& operator++()
			{
				_node = _node->_next;
				return *this;
			}

			_Self operator++(int)
			{
				_Self _tmp = *this;
				++*this;
				return _tmp;
			}

			_Self& operator--()
			{
				_node = _node->_prev;
				return *this;

			}

			_Self operator--(int)
			{
				_Self _tmp = *this;
				_node = _node->_prev;
				return _tmp;
			}
			
			friend bool
			operator==(const _Self& __x, const _Self& __y)	{ return __x._node == __y._node; }
			friend bool
			operator!=(const _Self& __x, const _Self& __y)	{ return __x._node != __y._node; }

		public:
			Tnode * _node;
	};

	template < class _Tp, class Allocator = std::allocator<_Tp> >
	class list
	{
	public:
		typedef	_Tp								value_type;
		typedef Allocator						allocator_type;
		
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;

		typedef	_List_Iterator<value_type>					iterator;
		typedef	_Const_List_Iterator<value_type>			const_iterator;

		typedef	ft::reverse_iterator<iterator>					reverse_iterator;
		typedef	ft::reverse_iterator<const_iterator>			const_reverse_iterator;

		typedef	size_t										size_type;

		typedef std::ptrdiff_t  difference_type;

		typedef Node<_Tp>	Tnode;


		explicit list<_Tp>() : _size(0)
		{
			_last._node = new_node(value_type());
			_last._node->_next = _last._node;
			_last._node->_prev = _last._node;
		}
		
		template < class InputIterator >
		list<value_type>(InputIterator st, InputIterator end, const allocator_type& alloc = allocator_type()) : _size(0)
		{
			(void)alloc;
			_last._node = new_node(value_type());
			_last._node->_next = _last._node;
			_last._node->_prev = _last._node;
			while (st != end)
			{
				push_back(*st);
				st++;
			}
		}

		//TODO
		explicit list<_Tp>(size_t n, const value_type& src = value_type(), const allocator_type& alloc = allocator_type()) : _size(0)
		{
			(void)alloc;
			_last._node = new_node(src);
			_last._node->_next = _last._node;
			_last._node->_prev = _last._node;
			insert(_last, n, src);
		}
		
		explicit list<_Tp>(int n, const value_type& src = value_type(), const allocator_type& alloc = allocator_type()) : _size(0)
		{
			(void)alloc;
			_last._node = new_node(src);
			_last._node->_next = _last._node;
			_last._node->_prev = _last._node;
			insert(_last, n, src);
		}	

		list<_Tp>(const list& x) : _size(0)
		{
			_last._node = new_node(value_type());
			_last._node->_next = _last._node;
			_last._node->_prev = _last._node;
			for (const_iterator it = x.begin(); it != x.end(); it++)
				push_back(*it);
		}

		~list<_Tp>()
		{
			while (_size)
				pop_front();
			delete_node(_last._node);
		}

		/*
			** Iterators **
		*/


		iterator begin(void)
		{
			iterator begin(_last._node->_next);
			return begin;
		}

		//TODO
		const_iterator begin(void) const
		{
			const_iterator begin(_last._node->_next);
			return begin;
		}

		reverse_iterator rbegin()
		{
			reverse_iterator it(rend());
			return it++;
		}

		const_reverse_iterator rbegin() const
		{
			const_reverse_iterator it(rend());
			return it++;
		}

		iterator end(void) { return _last; }

		const_iterator end(void) const { return _last; }

		reverse_iterator rend()
		{
			reverse_iterator it(end());
			return it;
		}

		const_reverse_iterator rend() const
		{
			const_reverse_iterator it(end());
			return it;
		}


		/*
			** Capacity **
		*/
		size_type	size(void) const { return _size; }
		
		// to do
		size_type	max_size(void) const { return _size; }

		bool	 	empty(void) const { return (!_size); }


		/*
			** Elements access **
		*/

		reference front() { return *begin();}
		
		const_reference front() const { return *begin();}

		reference back() 
		{
			iterator it = end();
			it--;
			return *it;
		}
		const_reference back() const {return *end(); }
		

		/*
			** Modifier **
		*/
		
		template <class InputIterator>
  		void assign (InputIterator first, InputIterator last)
		{
			clear();
			while (first != last)
				push_back(*first++);
		}

		void assign (size_type n, const value_type& val)
		{
			clear();
			while (n != _size)
				push_back(val);
		}

		void assign (int n, const value_type& val)
		{
			clear();
			while ((size_t)n != _size)
				push_back(val);
		}

		void push_front(const value_type & val)
		{
			insert(begin(), val);
		}

		void pop_front(void)
		{
			if (_size > 0)
			{
				iterator pop = begin();
				iterator nbegin = ++begin();

				nbegin._node->_prev = _last._node;
				_last._node->_next = nbegin._node;

				delete_node(pop._node);
				_size--;
			}
		}

		void push_back(const value_type & val)
		{
			insert(end(), val);
		}

		void pop_back(void)
		{
			if (_size > 0)
			{
				iterator pop = --end();

				_last._node->_prev = pop._node->_prev;
				pop._node->_prev->_next = _last._node;

				delete_node(pop._node);
				_size--;
			}
		}

		iterator insert (iterator pos, const value_type& val)
		{
			iterator tmp;

			tmp._node = new_node(val);

			
			pos._node->_prev->_next = tmp._node;
			tmp._node->_prev = pos._node->_prev;
			tmp._node->_next = pos._node;
			pos._node->_prev = tmp._node;

			_size++;
			return pos;
		}

		iterator insert (iterator pos, size_type n, const value_type& val)
		{
			while (n--)
			{
				insert(pos, val);
			}
			return pos;
		}

		//TODO
		iterator insert (iterator pos, int n, const value_type& val)
		{
			while (n--)
			{
				insert(pos, val);
			}
			return pos;
		}

		template <class InputIterator>
    	void insert (iterator position, InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				insert(position, *first++);
			}
		}
		
		iterator erase(iterator pos)
		{
			iterator tmp = pos;

			pos++;

			pos._node->_prev = tmp._node->_prev;
			tmp._node->_prev->_next = pos._node;
			
			_size--;
			delete_node(tmp._node);
			return pos;
		}

		iterator erase(iterator first, iterator last)
		{
			while (first != last)
				erase(first++);
			return first;
		}

		void swap(list &x)
		{
			iterator it = begin();
			splice(it, x); // x -> at start of y // x {0 1 2} y {1 2 3} = x {} y {0 1 2 1 2 3}
			x.splice(x.end() , *this, it, end()); // it.y -> x
		}
		
		void resize(size_type n, value_type val = value_type())
		{
			if (n < size())
			{
				while (n != size())
					pop_front();
			}
			else
			{
				while (n != size())
					push_back(val);
			}
		}

		void clear()
		{
			while (size() != 0)
				pop_back();
		}

		/*
		 * operation
		*/

	private:


	public:
		/*
			No element are copied 
		*/
		void splice(iterator pos, list& x)
		{
			iterator it = x.begin();
			 while (x._size)
			 {
				// std::cout << "x.size" << x.size() << std::endl;
				 splice(pos, x, it++);
			 }
		}

		void splice(iterator pos, list& x, iterator it)
		{

			it._node->_prev->_next = it._node->_next;
			it._node->_next->_prev = it._node->_prev;
			x._size--;

			pos._node->_prev->_next = it._node;
			it._node->_prev = pos._node->_prev;

			pos._node->_prev = it._node;
			it._node->_next = pos._node;
			_size++;
		}

		void splice(iterator pos, list& x, iterator first, iterator last)
		{
			iterator it = first;

			while (it != last)
				splice(pos, x, it++);
		}

		void remove(const value_type& val)
		{
			for (iterator it = begin(); it != end();)
			{
				if (*it == val)
					it = erase(it);
				else
					it++;
			}
		}

		template <class Predicate>
		void remove_if(Predicate pre)
		{
			for (iterator it = begin(); it != end();)
			{
				if (pre(*it))
					it = erase(it);
				else
					it++;
			}
		}

		void unique()
		{
			iterator it;

			for(it = begin(); it != _last; it++)
			{
				iterator cmp = it;
				cmp++;
				while (cmp != _last)
				{
					if (*it == *cmp)
						cmp = erase(cmp);
					else
						break;
				}
			}
		}

		template <class BinaryPredicate>
  		void unique (BinaryPredicate binary_pred)
		{
			iterator it;

			for(it = begin(); it != end(); it++)
			{
				iterator cmp = it;
				cmp++;
				while (cmp != _last)
				{
					if (binary_pred(*it, *cmp))
						cmp = erase(cmp);
					else
						break;
				}
			}
		}


	private:
		void mergeSort(list<value_type> & lst)
		{
			list<value_type> f;
			list<value_type> s;
			iterator it;
			size_t len;



			if (lst.size() > 1)
			{
				len = lst.size() * 0.5;
				it = lst.begin();
				while (len--)
					it++;
				f.splice(f.end(), lst, lst.begin(), it);
				s.splice(s.end(), lst);

				f.mergeSort(f);
				s.mergeSort(s);
				
			}
			lst.merge(s, f);

		}

		void merge(list<value_type> & first, list<value_type> & second)
		{
			iterator fit = first.begin();
			iterator sit = second.begin();

			while (first._size != 0 || second._size != 0)
			{
				if (fit != first._last && (sit == second._last || *fit < *sit))
				{
					splice(_last, first, fit);
					fit = first.begin();
				}
				else
				{
					splice(_last, second, sit);
					sit = second.begin();
				}
			}
		}
	public:
		void	sort()
		{
			mergeSort(*this);	
		}
		
		/*
			* Operator
		*/

		
	template <class T, class Alloc>
	friend
	 bool operator==(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
			
		const_iterator its = rhs.begin();
		for (const_iterator it = lhs.begin(); it != lhs.end(); it++, its++)
		{
			if (*it != *its)
				return false;
		}
		return true;
	}

	template <class T, class Alloc>
	friend
	bool operator!=(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Alloc>
	friend
	bool operator>(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
	{
		if (lhs.size() > rhs.size())
			return true;
		const_iterator its = rhs.begin();
		for (const_iterator it = lhs.begin(); it != lhs.end() || its != rhs.end(); it++, its++)
		{
			if (!(*it < *its))
				return false;
		}
		return true;
	}

	template <class T, class Alloc>
	friend
	bool operator<=(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) { return !(lhs > rhs); }

	template <class T, class Alloc>
	friend
	bool operator<(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
	{
		if (lhs.size() < rhs.size())
			return true;
		const_iterator its = rhs.begin();
		for (const_iterator it = lhs.begin(); it != lhs.end(); it++, its++)
		{
			if (*it <= *its)
				return false;
		}
		return true;
	}

	template <class T, class Alloc>
	friend
	bool operator>=(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) { return !(lhs < rhs); }

	private:
		iterator		data;
		size_t			_size;
		iterator		_begin;
		iterator		_last;
		iterator		_end;
		
	private:
		std::allocator<Tnode> _alloc;
		Tnode * new_node(const value_type& src)
		{
			Tnode * tmp =  _alloc.allocate(1);
			_alloc.construct(tmp, src);
			return tmp;
		}
		void	delete_node(Tnode * node)
		{
			_alloc.deallocate(node, 1);
			//delete node;
		}
	};
};

namespace std // work but is good ??
{
	
	template <class T, class Alloc>
	void swap (ft::list<T,Alloc>& x, ft::list<T,Alloc>& y)
	{
		x.swap(y);
	}
};

#endif // __LIST_H__