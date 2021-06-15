#ifndef __LIST_H__
#define __LIST_H__

#include <memory>
#include <string>
#include <iostream>


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

/*	template <class _Tp>
	class _List_iterator_base
	{
		public:
			typedef	_List_iterator_base<_Tp>			_Self;
			typedef Node<_Tp>							Tnode;
			typedef	_Tp									value_type;
			typedef	std::bidirectional_iterator_tag 	iterator_category;
			typedef	ptrdiff_t 							difference_type;

			_List_iterator_base<_Tp>() : _node(NULL) {}
			_List_iterator_base<_Tp>(Tnode * ptr) : _node(ptr) {}
			virtual ~_List_iterator_base<_Tp>() {}

			virtual
			_Self& operator=(const _Self & ref)
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
		friend bool operator!=(const _Self& __x, const _Self& __y)	{ return __x._node != __y._node; }
		public:
			Tnode * _node;
	};


	template <typename _Tp>
	class _List_Iterator : public _List_iterator_base<_Tp>
	{
		typedef	_List_Iterator<_Tp> _Iter;
		typedef _Tp*				pointer;
		typedef _Tp&				reference;
		typedef Node<_Tp>			Tnode;

		public:
			_List_Iterator<_Tp>() : _List_iterator_base<_Tp>() {}
			_List_Iterator<_Tp>(Tnode * src) : _List_iterator_base<_Tp>(src) {}
			virtual ~_List_Iterator<_Tp>() {}

			_List_Iterator<_Tp>& operator=(const _List_iterator_base<_Tp> & ref)
			{
				this->_node = ref._node;
				return *this;
			}

		_Iter& operator++(){ _List_iterator_base<_Tp>::operator++(); return *this; }
		_Iter operator++(int){ _List_iterator_base<_Tp>::operator++(int()); return *this; }

		_Iter& operator--(){ _List_iterator_base<_Tp>::operator--(); return *this; }
		_Iter operator--(int){ _List_iterator_base<_Tp>::operator--(int()); return *this; }

		friend bool
		operator==(const _Iter& __x, const _Iter& __y)	{ return _List_iterator_base<_Tp>::operator==(__x, __y);}
		//friend bool
		//operator!=(const _Iter& __x, const _Iter& __y)	{ return _List_iterator_base<_Tp>::operator!=(__x, __y);}

		reference		operator*() { return this->_node->_data; }
		pointer			operator->() { return &(this->_node->_data); }
	};*/

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
			typedef ptrdiff_t difference_type;
			

			_List_Iterator() : _node(NULL) {}

			_List_Iterator(Tnode * src) : _node(src) {}

			//_List_Iterator(_Self & src) { *this = src; }
			
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

	/*template <typename _Tp>
	class _Const_List_Iterator
	{
		public:
			typedef	_Const_List_Iterator<_Tp>		_Self;
			typedef Node<_Tp>						Tnode;

			typedef	_Tp		value_type;
			typedef	const _Tp*	pointer;
			typedef	const _Tp&	reference;
			typedef _Self	iterator_type;
			typedef std::bidirectional_iterator_tag iterator_category;
			//typedef typename std::iterator_traits<_Self>::value_type value_type;
			typedef ptrdiff_t difference_type;
			

			_Const_List_Iterator() : _node(NULL) {}

			_Const_List_Iterator(const Tnode * src) : _node(src) {}

			//_Const_List_Iterator(_Self & src) { *this = src; }
			
			reference	operator*() { return _node->_data; }
			pointer		operator->() { return &(_node->_data); }

			_Self& operator=(_Self & ref)
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
			const Tnode * _node;
	};*/

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
		typedef	_List_Iterator<value_type>					const_iterator;

		typedef	size_t										size_type;

		typedef ptrdiff_t  difference_type;

		typedef Node<_Tp>	Tnode;


		explicit list<_Tp>() : _size(0)
		{
			_last._node = new Tnode();
			_last._node->_next = _last._node;
			_last._node->_prev = _last._node;
		}
		
		template < class InputIterator >
		list<value_type>(InputIterator st, InputIterator end, const allocator_type& alloc = allocator_type()) : _size(0)
		{
			_last._node = new Tnode();
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
			_last._node = new_node(src);
			_last._node->_next = _last._node;
			_last._node->_prev = _last._node;
			insert(_last, n, src);
		}
		
		explicit list<_Tp>(int n, const value_type& src = value_type(), const allocator_type& alloc = allocator_type()) : _size(0)
		{
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
			for (iterator it = x.begin(); it != x.end(); it++)
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
			iterator begin;
			begin = _last;
			begin++;
			return begin;
		}

		//TODO
		const_iterator begin(void) const
		{
			const_iterator begin(_last._node);
			begin++;
			return begin;
		}

		iterator end(void) { return _last; }

		const_iterator end(void) const { return _last; }


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
			while (n != _size)
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

		void splice(iterator pos, list& x)
		{
			 insert(pos, x.begin(), x.end());
			 x.clear();
		}

		void splice(iterator pos, list& x, iterator it)
		{
			insert(pos, *it);
			x.erase(it);
		}

		void splice(iterator pos, list& x, iterator first, iterator last)
		{
			iterator it = first;

			while (it != last)
				insert(pos, *it++);
			x.erase(first, last);
		}

		void remove(const value_type& val)
		{
			for (iterator it = begin(); it != end(); it++)
			{
				if (*it == val)
					erase(it);
			}
		}

		template <class Predicate>
		void remove_if(Predicate pre)
		{
			for (iterator it = begin(); it != end(); it++)
			{
				if (pre(*it))
					erase(it);
			}
		}

		void unique()
		{
			iterator it;

			for(it = begin(); it != _last; it++)
			{
				iterator cmp = it;
				while (++cmp != _last)
				{
					if (*it == *cmp)
					{
						erase(cmp);
					}
					else
					{
						break;
					}
				}
			}
		}

		template <class BinaryPredicate>
  		void unique (BinaryPredicate binary_pred)
		{
			iterator it;

			for(it = begin(); it != _last; it++)
			{
				iterator cmp = it;
				while (++cmp != _last)
				{
					if (binary_pred(*it, *cmp))
					{
						erase(cmp);
					}
					else
					{
						break;
					}
				}
			}
		}

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
