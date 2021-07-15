#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <memory>
#include <iterator.hpp>
#include <type_traits.hpp>
#include <type_traits>
#include <iostream>


namespace ft
{
	template < class _Tp >
	class const_viterator;
	
		template < class _Tp >
		class viterator
		{
			
			public:
			typedef	viterator<_Tp>		_Self;

			typedef	_Tp								value_type;
			typedef _Tp *							pointer;
			typedef _Tp &							reference;
			typedef _Self							iterator_type;
			typedef std::random_access_iterator_tag iterator_category;
			typedef std::ptrdiff_t 					difference_type;
			typedef size_t							size_type;
			
			viterator() : _add(NULL) {}

			viterator(pointer src) : _add(src) {}

			viterator(const _Self& src) { *this = src; }

			//Random_acc_iter(const _Self& src) { *this = src; }

			~viterator() {}
			
			reference	operator*() { return *_add; }
			pointer		operator->() { return _add; }

			reference operator[](size_type n) { return *(_add + n); }
			//const_reference operator[](size_type n) const;

			_Self& operator=(const _Self & ref)
			{
				_add = ref._add;
				return *this;
			}
	

			/* operator + */

			viterator operator+(const difference_type & n) const
			{
				return viterator(_add + n);
			}

			difference_type operator+(const viterator & n) const
			{
				return (_add + n._add);
			}

			/* operator - */
			
			viterator operator-(const difference_type & n) const
			{
				return viterator(_add - n);
			}
			
			difference_type operator-(const viterator & n) const
			{
				return (_add - n._add);
			}

			difference_type operator-(const const_viterator<_Tp> & n) const
			{
				return (_add - n._add);
			}
			

			viterator& operator+=(const difference_type & n)
			{
				_add += n;
				return *this;
			}

			viterator& operator-=(const difference_type & n)
			{
				_add -= n;
				return *this;
			}
			
			/* operator ++ / -- */

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

			public:
				pointer		_add;
		};

		template < class _Tp >
		class const_viterator
		{
			
			public:
			typedef	const_viterator<_Tp>		_Self;

			typedef	_Tp									value_type;
			typedef const _Tp *							pointer;
			typedef const _Tp &							reference;
			typedef _Self								iterator_type;
			typedef std::random_access_iterator_tag		iterator_category;
			typedef std::ptrdiff_t 						difference_type;
			typedef size_t								size_type;
			
			const_viterator() : _add(NULL) {}

			const_viterator(pointer src) : _add(src) {}

			const_viterator(const const_viterator& src) { *this = src; }

			const_viterator(const viterator<_Tp>& src) { *this = src; }

			//Random_acc_iter(const _Self& src) { *this = src; }

			~const_viterator() {}
			
			reference	operator*() { return *_add; }
			pointer		operator->() { return _add; }

			reference operator[](size_type n) { return *(_add + n); }
			//const_reference operator[](size_type n) const;

			_Self& operator=(const const_viterator & ref)
			{
				_add = ref._add;
				return *this;
			}

			_Self& operator=(const viterator<_Tp> & ref)
			{
				_add = ref._add;
				return *this;
			}
	

			/* operator + */

			const_viterator operator+(const difference_type & n) const
			{
				return const_viterator(_add + n);
			}

			difference_type operator+(const const_viterator & n) const
			{
				return (_add + n._add);
			}

			difference_type operator-(const viterator<_Tp> & n) const
			{
				return (_add - n._add);
			}
			/* operator - */
			
			const_viterator operator-(const difference_type & n) const
			{
				return const_viterator(_add - n);
			}
			
			difference_type operator-(const const_viterator & n) const
			{
				return (_add - n._add);
			}



			const_viterator& operator+=(const difference_type & n)
			{
				_add += n;
				return *this;
			}

			const_viterator& operator-=(const difference_type & n)
			{
				_add -= n;
				return *this;
			}
			
			/* operator ++ / -- */

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

			public:
				pointer		_add;
		};
	
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{

	
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

		typedef viterator<T> 								iterator;
		typedef const_viterator<T> 							const_iterator;

		typedef	ft::reverse_iterator<iterator>				reverse_iterator;
		typedef	ft::reverse_iterator<const_iterator>		const_reverse_iterator;

		typedef	size_t										size_type;
		typedef std::ptrdiff_t								difference_type;

		/* pointer end / start / finish */
	private:
		pointer	_start;
		pointer	_end;
		pointer	_end_of_storage;
		allocator_type _alloc; //to do allocation

		/* allocation and deallocation */
	private:

		/*
			** alloc new block
		*/
		pointer		new_block(size_type n)
		{
			pointer ret = _alloc.allocate(n);
			return ret;
		}
		/*
			** destroy all el and free block
		*/
		void		del_block(pointer to_del, size_type size)
		{
			for (size_type i=0; i<size; i++)
				_alloc.destroy(&to_del[i]);
			_alloc.deallocate(to_del, size);
		}

		/*
			** alloc with size n
			** copy previous vector
		*/
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

		/*
			add n value_type and inc _end
		*/
		void	add_size(size_type n, const value_type & val)
		{
			size_type i;

			i = 0;

			if (_end == _start)
			{
				_alloc.construct(_end++, val);
				++i;
			}
			while (i < n && (_end) < _end_of_storage)
			{
				_alloc.construct(_end++, val);
				++i;
			}
		}

		/*
			add_size with range iterator
		*/
		template <class Input>
		void 	add_range(Input f, Input l)
		{
			while (f != l)
				_alloc.construct(_end++, *f++);
		}
		
		/*
			** rm n el and dec _end
		*/
		void	rm_size(size_type n)
		{
			size_type i;

			i = 0;
			while (i < n && _end >= _start)
			{
				if (_end == _start)
					_alloc.destroy(_start);
				else
					_alloc.destroy(_end--);	
				++i;
			}
			//if (_end == _start)

		}

		/*
			** init a new_block of n capacity destroy last block if exist
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

		/*
			** rm n el from first 
			** move needed el
		*/
		iterator exclude(size_type n, iterator first)
		{
			size_type stay = size() - n;
			iterator stop = end();

			for (iterator it = begin(); it != stop; it++)
			{
				if (it >= first)
				{
					if (stay)
					{
						it[0] = it[n];
						--stay;
					}
				}
			}
			rm_size(n);
			return _end;
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
		vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) : _start(NULL), _end(NULL), _end_of_storage(NULL), _alloc(alloc)
		{
			assign(first, last);
		}

		// Copy Constructor
		vector(const vector& x) : _start(NULL), _end(NULL), _end_of_storage(NULL), _alloc(x._alloc)
		{
			*this = x;
		}

		// destructor
		~vector()
		{
			if (_start)
			{
				del_block(_start, size());
			}
		}

		vector& operator=(const vector& x)
		{
			if (_start)
				del_block(_start, size());
			_start = NULL;
			_end = NULL;
			_end_of_storage = NULL;
			
			assign(x.begin(), x.end());
			return *this;
		}

		/*
			*** Iterators Function ***
		*/

		iterator begin() {	return iterator(_start); }
		const_iterator begin() const{ return const_iterator(_start); }

		iterator end() { return iterator(_end); }
		const_iterator end() const { return const_iterator(_end); }

		reverse_iterator rbegin() { iterator it = --end(); return reverse_iterator(it); }
		const_reverse_iterator rbegin() const { const_iterator it = --end(); return const_reverse_iterator(it); }

		reverse_iterator rend() { iterator it = --begin(); return reverse_iterator(it); };
		const_reverse_iterator rend() const { const_iterator it = --begin(); return const_reverse_iterator(it); }

		/*
			*** Capacity Function ***
		*/

		// return actual size
		size_type size(void) const { return static_cast<size_type>(_end - _start); }

		// return max size
		size_type max_size(void) const { return std::numeric_limits<size_type>::max() / sizeof(T); };

		// return allocated size
		size_type capacity(void) const { return static_cast<size_type>(_end_of_storage - _start); };
		
		bool empty() const { return (size() == 0); }

		// fixe capicty
		void reserve(size_type n)
		{
			if ( n >  capacity() )
				add_mem(n);
		}

		/*
			*** Access Function ***
		*/

		reference operator[](size_type n) { return this->at(n); }

		const_reference operator[](size_type n) const { return this->at(n); }

		reference at(size_type n) { return *(_start + n); }
		
		const_reference at(size_type n) const { return *(_start + n); }

		reference front(void) { return *_start; }
		
		const_reference front(void) const { return *_start; }

		reference back(void) { return *(_end - 1); }
		
		const_reference back(void) const { return *(_end - 1); }

		/*
			*** Modifier Function ***
		*/

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

		template < class Ite >
		typename ft::enable_if<ft::is_input_iterator<Ite> >::type
		assign (Ite f, Ite l)
		{
			size_type s = 0;

			for (Ite it = f; it != l; it++)
				++s;
			if (s > capacity())
				init_block(s);
			else
				rm_size(size()); // size == 0
			add_range(f, l);
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
			if (!empty())
				rm_size(1);
		}
		
		/*
			n = new size
		*/

		iterator erase(iterator pos)
		{	
			return(exclude(1 , pos));
		}

		iterator erase(iterator first, iterator last)
		{
			size_type si;

			si = 0;
			for (iterator it = first; it != last; it++, si++)
				;
			return (exclude(si, first));
		}

		iterator insert(iterator pos, const value_type& val)
		{
			size_type p = static_cast<size_type>(pos._add - begin()._add);
			if (size() + 1 > capacity())
			{
				add_mem(capacity() ? capacity() * 2 : 1);
				pos = begin() + p;
			}
			add_size(1, val);
			for (iterator last = --end(); last != pos; last--)
			{
				*last = *(last - 1);
			}
			*pos = val;
			return pos;
		}

		void insert(iterator pos, size_type n, const value_type& val)
		{
			size_type p = static_cast<size_type>(pos._add - begin()._add);
			size_type to_rplc = size() - p;

			if (size() + n > capacity())
			{
				add_mem((size() + n) < capacity() * 2 ? capacity() * 2 : size() + n);
				pos = begin() + p; // pos after realocation
			}
			add_size(n, val);
			
			// place old value
			for (iterator last = --end(); to_rplc != 0; last--, to_rplc--)
				*last = pos[to_rplc - 1];
			*pos = val;

			//add new value
			for (size_type i = 0; i != n; i++)
				pos[i] = val; 
			return ;
		}

		pointer			create(size_type n)
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
				_alloc.construct(_end++, it[i++]);
			}
			_end_of_storage = _end;
			while (i < n_size)
			{
				++_end_of_storage;
				++i;
			}
			pointer cpy = _start;
			_start = new_v;
			
			return cpy;
		}

		template <typename Input>
        typename ft::enable_if
		<
			ft::is_input_iterator<Input>
		>::type
		insert (iterator pos, Input first, Input last)
		{
			size_type p = static_cast<size_type>(pos._add - begin()._add);
			size_type to_rplc = size() - p;
			size_type diff = 0;
			pointer		save = 0;
			size_type	size_save = size();

			for (Input it = first; it != last; it++)
				++diff;
			if (size() + diff > capacity())
			{
				save = create((capacity() * 2) < (size() + diff) ? size() + diff : (capacity() * 2));
				pos = begin() + p; // pos after realocation
			}
			add_size(diff , back());
			for (iterator last = --end(); to_rplc != 0; last--, to_rplc--)
				*last = pos[to_rplc - 1];
			for (size_type i = 0; i!= diff; i++)
				pos[i] = *first++;

			del_block(save, size_save);
		}

		void clear(void) { rm_size(size()); }

		void swap(vector & x)
		{
			pointer tmp;

			tmp = _start;
			_start = x._start;
			x._start = tmp;

			tmp = _end;
			_end = x._end;
			x._end = tmp;

			tmp = _end_of_storage;
			_end_of_storage = x._end_of_storage;
			x._end_of_storage = tmp;
			
		}
	};

	/*
		** function overload
	*/

	template <class T, class Alloc>
  	void swap (ft::vector<T,Alloc>& x, ft::vector<T,Alloc>& y)
	{
		x.swap(y);
	}

	/*
		** operator overload
	*/

	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

} // namespace ft

#endif // __VECTOR_H__