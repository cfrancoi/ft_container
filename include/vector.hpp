#include <memory>
#include <iterator.hpp>
#include <type_traits>
#include <iostream>

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
	private:
		template < class _Tp >
		class Random_acc_iter
		{
			
			public:
				typedef	Random_acc_iter<_Tp>		_Self;
				typedef	_Tp				value_type;
				typedef _Tp*			pointer;
				//typedef typename vector<_Tp>::pointer pointer;
				typedef _Tp&			reference;
				typedef _Self			iterator_type;
				typedef std::random_access_iterator_tag iterator_category;
				typedef std::ptrdiff_t difference_type;
				typedef size_t			size_type;
			
			Random_acc_iter() : _add(NULL) {}

			Random_acc_iter(pointer src) : _add(src) {}

			Random_acc_iter(const _Self& src) { *this = src; }

			//Random_acc_iter(const _List_Iterator<_Tp>& src) { *this = src; }

			~Random_acc_iter() {}
			
			reference	operator*() { return *_add; }
			pointer		operator->() { return _add; }

			reference operator[](size_type n) { return *(_add + n); }
			//const_reference operator[](size_type n) const;

			_Self& operator=(const _Self & ref)
			{
				_add = ref._add;
				return *this;
			}

			/*friend
			_Self operator+(const _Self & a, const _Self & i)
			{
				_Self n;

				n._add = a._add + i._add;

				return n;
			}*/

			friend
			_Self operator+(const _Self & a, const size_type & i)
			{
				_Self n;

				n._add = a._add + i;

				return n;
			}

			friend
			_Self operator-(const _Self & a, const size_type & i)
			{
				_Self n;

				n._add = a._add - i;

				return n;
			}

			friend
			_Self operator-( _Self & a, const _Self & b)
			{
				a._add -= b._add;

				_Self c(a._add);
				return c;
			}
            
		/*	_Self& operator=(const _List_Iterator<_Tp> & ref)
			{
				return *this;
			}*/

			_Self& operator++()
			{
				++_add;
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
				--_add;
				return *this;
			}

			_Self operator--(int)
			{
				_Self _tmp = *this;
				--*this;
				return _tmp;
			}


			friend bool
			operator==(const _Self& __x, const _Self& __y)	{ return __x._add == __y._add; }
			friend bool
			operator!=(const _Self& __x, const _Self& __y)	{ return __x._add != __y._add; }
			friend bool
			operator<(const _Self& __x, const _Self& __y)	{ return __x._add < __y._add; }
			friend bool
			operator>(const _Self& __x, const _Self& __y)	{ return __x._add > __y._add; }
			friend bool
			operator<=(const _Self& __x, const _Self& __y)	{ return __x._add <= __y._add; }
			friend bool
			operator>=(const _Self& __x, const _Self& __y)	{ return __x._add >=__y._add; }

			private:
				pointer		_add;
		};
		/* data */
	public:
		/*
			** Member Type **
		*/

		typedef T				value_type;
		typedef	Alloc			allocator_type;

		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;

		typedef Random_acc_iter<T> 							iterator;
		typedef Random_acc_iter<T> 							const_iterator;

		typedef	ft::reverse_iterator<iterator>				reverse_iterator;
		typedef	ft::reverse_iterator<const_iterator>		const_reverse_iterator;

		typedef	size_t										size_type;
		typedef std::ptrdiff_t								difference_type;

		/* pointer end / start / finish */
	private:
		allocator_type _alloc; //to do allocation
		pointer	_start;
		pointer	_end;
		pointer	_end_of_storage;

		/* allocation and deallocation */
	private:
		pointer		new_block(size_type n)
		{
			pointer ret = _alloc.allocate(n);
			return ret;
		}

		void		del_block(pointer to_del, size_type size)
		{
			for (int i=0; i<size; i++)
				_alloc.destroy(&to_del[i]);
			_alloc.deallocate(to_del, size);
		}

		void		add_mem(size_type n)
		{
			pointer new_v;

			new_v = new_block(n); // check fail alloc
			iterator it = begin();
			size_type n_size = n;
			size_type p_size = size();
			size_type i = 0;

			_end = new_v;
			while (i != p_size)
			{
				*_end++ = it[i];
				++i;
			}
			_end_of_storage = _end;
			while (i < n_size)
			{
				++_end_of_storage;
				++i;
			}

			pointer cpy = _start;
			_start = new_v;
			
			del_block(cpy, p_size);
		}
		void	add_size(size_type n, const value_type & val)
		{
			size_type i;

			i = 0;
			if (_end == NULL)
			{
				_alloc.construct(_end++, val);
				++i;
			}
			while (i < n && (_end) <= _end_of_storage)
			{
				_alloc.construct(_end++, val);
				++i;
			}
		}
		void	rm_size(size_type n)
		{
			size_type i;

			i = 0;
			while (i < n && _end >= _start)
			{
				_alloc.destroy(_end--);
				++i;
			}
		}

		/*
			** Constructor && Destructor **
		*/

	public:
		// Default Constructor
		explicit
		vector(const allocator_type& alloc = allocator_type()) : _start(NULL), _end(NULL), _end_of_storage(NULL), _alloc(alloc) {}

		// Fill Constructor
		explicit
		vector(size_type n,
				const value_type& val,
				const allocator_type& alloc = allocator_type()) : _start(NULL), _end(NULL), _end_of_storage(NULL), _alloc(alloc)
		{
			assign(n, val);
		}

		// Range Constructor
		template < class InputIterator >
		vector(const allocator_type& alloc = allocator_type()) : _start(NULL), _end(NULL), _end_of_storage(NULL), _alloc(alloc)
		{

		}

		// Copy Constructor
		vector(const vector& x)
		{
			*this = x;
		}

		~vector()
		{
			if (_start)
			{
				del_block(_start, size());
			}
		}

		/*
			*** Iterators Function ***
		*/

		iterator begin() {	return _start; }
		const_iterator begin() const;

		iterator end() { return _end; }
		const_iterator end() const;

		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;

		reverse_iterator rend();
		const_reverse_iterator rend() const;

		/*
			*** Capacity Function ***
		*/

		// return actual size
		size_type size(void) const { return static_cast<size_type>(_end - _start); }

		// return max size
		size_type max_size(void) const;

		// return allocated size
		size_type capacity(void) const { return static_cast<size_type>(_end_of_storage - _start); };

		bool empty() const;

		void reserve(size_type n);


		/*
			*** Access Function ***
		*/

		reference operator[](size_type n) { return this->at(n); }

		const_reference operator[](size_type n) const;

		reference at(size_type n) { return *(_start + n); }
		
		const_reference at(size_type n) const;

		reference front(void) { return *_start; }
		
		const_reference front(void) const { return *_start; } 		

		reference back(void) { return *(_end - 1); }
		
		const_reference back(void) const { return *(_end - 1); }

		/*
			*** Modifier Function ***
		*/
		void init_block(size_type n)
		{
			if (_start)
				del_block(_start, size());
			_start = new_block(n);
			_end = _start;
			_end_of_storage = _end;
			while (n != 0)
			{
				++_end_of_storage;
				--n;
			}	
		}

		void assign (size_type n, const value_type& val)
		{
			if (n == 0)
				return ;
			if (n > capacity())
				init_block(n);
			else
				rm_size(size()); // size == 0
			add_size(n, val);
		}

		void assign (int n, const value_type& val)
		{
			if (n == 0)
				return ;
			if (n > capacity())
				init_block(n);
			else
				rm_size(size()); // size == 0
			add_size(n, val);
		}

		template < class Ite >
		void assign (Ite f, Ite l)
		{
			size_type s;

			s = &*l - &*f;
			if (s > capacity())
				init_block(s);
			else
				rm_size(size()); // size == 0
			while (f != l)
				add_size(1, *f++);
		}

		void resize (size_type n, const value_type & val = value_type())
		{
			if (n == size())
				return ;
			else if (n < size())
			{
				rm_size(size() - n);
			}
			else if (n > size())
			{
				if (n > capacity())
				{
					init_block(n);
					add_size(n - size(), val);
				}
				else
					add_size(n - size(), val);
			}
		}

		void push_back(const value_type & val)
		{
			if (1 + size() > capacity())
				add_mem(capacity() ? capacity() * 2 : 1);
			add_size(1, val);
		}

		void pop_back(void)
		{
			if (size())
				rm_size(1);
		}
		
		/*
			n = new size
		*/
		iterator exclude(size_type n, iterator first, iterator last)
		{
			pointer		_new = new_block(n);
			iterator	end = begin();
			size_type	j = 0;

			for (size_type i = 0; i < size(); i++)
			{
				if (!(end >= first && end <= last))
					_alloc.construct(&(_new[j++]), *end);
				end++;
			}
			del_block(_start, size());
			_start = _new;
			_end = &(_new[j]);
			_end_of_storage = _end;

			return (_end);
		}


		iterator erase(iterator pos)
		{
			return(exclude(size() -1 , pos, pos+1));
		}

		iterator erase(iterator first, iterator last)
		{
			size_type s;

			iterator tmp; tmp = last - first;

			return(exclude(s, first, last));
		}
	};
	
} // namespace ft
