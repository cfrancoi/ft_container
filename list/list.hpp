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
		
			void	setNext(Node *pt) { _next = pt; }
			void	setPrev(Node *pt) {	_prev = pt; }

			/*bool operator==(const _Self& __x, const _Self& __y)	{ return _data == _data; }
			bool operator==(const _Self& __x, const _Self& __y)	{ return _data != _data; }*/
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

			typedef	_Tp		value_type;
			typedef	_Tp*	pointer;
			typedef	_Tp&	reference;
			

			_List_Iterator() : _node(NULL) {}

			_List_Iterator(const Tnode * src) : _node(src) {}
			
			reference	operator*() { return _node->_data; }
			pointer		operator->() {return &(_node->_data); }

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
		typedef	const _List_Iterator<value_type>			const_iterator;

		typedef	size_t										size_type;

		typedef Node<_Tp>	Tnode;


		list<_Tp>() : _size(0)
		{
			_last._node = new Tnode();
			_last._node->_next = _last._node;
			_last._node->_prev = _last._node;
		};

		list<_Tp>(size_t n, const _Tp& src) : _size(0)
		{
			_last._node = new Tnode();
			_last._node->_next = _last._node;
			_last._node->_prev = _last._node;
			insert(_last, n, src);
		};
		
		// todo
		~list<_Tp>()
		{
			while (_size != 0)
			{
				pop_back();
			}
			delete _last._node;
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

		// todo const_iterator begin(void) const {}

		iterator end(void) { return _last; }

		// todo const_iterator end(void) const { return _last; }


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

				delete pop._node;
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

				delete pop._node;
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

	private:
		iterator		data;
		size_t			_size;
		iterator		_begin;
		iterator		_last;
		iterator		_end;
		

	private:
		Tnode * new_node(const value_type& src)
		{
			Tnode * tmp = new Tnode(src);
			return tmp;
		}


	};
}
#endif // __LIST_H__
