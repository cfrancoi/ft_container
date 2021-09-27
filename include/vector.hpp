#ifndef __VECTOR_H__
#define __VECTOR_H__


#include <iterator/iterator.hpp>
#include <other/type_traits.hpp>
#include <other/algorithm.hpp>
#include <iterator/vector_iterator.hpp>

# include <memory> // std::allocator
# include <limits> // std::numeric_limits
# include <stdexcept> // std::exception for at() & operator[]

namespace ft
{
	template < class T, class Alloc = ::std::allocator<T> >
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

		typedef vector_iterator<T, T&, T*> 					iterator;
		typedef vector_iterator<T, const T&, const T*> 		const_iterator;

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
			size_type first_s = (first - begin());
			size_type stay = size() - n - first_s;
			iterator stop = end();
			if (n == 0)
				return begin() + first_s;
			
			for (iterator it = begin(); it != end() && stay ; it++)
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
			return begin() + first_s;
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
				const value_type& val = value_type(),
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
			clear();
			if (capacity() > x.size())
			{
				insert(begin(), x.begin(), x.end());
			}
			else
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

		reverse_iterator rbegin() { iterator it = end(); return reverse_iterator(it); }
		const_reverse_iterator rbegin() const { const_iterator it = end(); return const_reverse_iterator(it); }

		reverse_iterator rend() { iterator it = begin(); return reverse_iterator(it); }
		const_reverse_iterator rend() const { const_iterator it = begin(); return const_reverse_iterator(it); }

		/*
			*** Capacity Function ***
		*/

		// return actual size
		size_type size(void) const { return static_cast<size_type>(_end - _start); }

		// return max size
		size_type max_size(void) const 
		{
			//linux
			//return std::numeric_limits<difference_type>::max() / sizeof(T);
			//mac
			return std::numeric_limits<size_type>::max() / sizeof(T);
		
		}

		// return allocated size
		size_type capacity(void) const { return static_cast<size_type>(_end_of_storage - _start); }
		
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

		reference at(size_type n) {
			pointer pos = (_start + n);
			if (!(n < size()))
				throw(std::out_of_range("vector"));
			return *pos;
		}
		
		const_reference at(size_type n) const
		{
			if (!(n < size()))
				throw(std::out_of_range("vector"));
			return *(_start + n);
		}

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
					add_mem(capacity() * 2 < n ? n : capacity() * 2);
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
			return (exclude(last - first, first));
		}

		iterator insert(iterator pos, const value_type& val)
		{
			size_type p = static_cast<size_type>(pos - begin());
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
			size_type p = static_cast<size_type>(pos - begin());
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

		template <typename Input>
        typename ft::enable_if
		<
			ft::is_input_iterator<Input>
		>::type
		insert (iterator pos, Input first, Input last)
		{
			size_type p = static_cast<size_type>(pos - begin());
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

		allocator_type get_allocator(void) const
		{
			return _alloc;
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
	bool operator== (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool operator!= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool operator<  (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template<class T>
	static bool lower_or_eql(T const & a, T const & b)
	{
		return ( a > b);
	}
	
	template <class T, class Alloc>
	bool operator>  (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{
		return rhs < lhs;/*ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), lower_or_eql<T>);*/
	}
	
	template <class T, class Alloc>
	bool operator<= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Alloc>
	bool operator>= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{
		return !(lhs < rhs);
	}

} // namespace ft

#endif // __VECTOR_H__