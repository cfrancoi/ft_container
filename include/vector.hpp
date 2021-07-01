#include <memory>
#include <iterator.hpp>

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
				typedef _Tp&			reference;
				typedef _Self			iterator_type;
				typedef std::random_access_iterator_tag iterator_category;
				typedef std::ptrdiff_t difference_type;
			
			Random_acc_iter() : _add(NULL) {}

			Random_acc_iter(pointer src) : _add(src) {}

			Random_acc_iter(const _Self& src) { *this = src; }

			//Random_acc_iter(const _List_Iterator<_Tp>& src) { *this = src; }

			~Random_acc_iter() {}
			
			reference	operator*() { return *_add; }
			pointer		operator->() { return _add; }

			//reference operator[]();
			//const_reference operator[](size_type n) const;

			_Self& operator=(const _Self & ref)
			{
				_add = ref._add;
				return *this;
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

		~vector() {}

		/*
			*** Iterators Function ***
		*/

		iterator begin() {	return _start; }
		const_iterator begin() const;

		iterator end();
		const_iterator end() const;

		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;

		reverse_iterator rend();
		const_reverse_iterator rend() const;

		/*
			*** Capacity Function ***
		*/

		// return actual size
		size_type size(void) const;

		// return max size
		size_type max_size(void) const;

		// return allocated size
		size_type capacity(void) const;

		bool empty() const;

		void reserve(size_type n);


		/*
			*** Access Function ***
		*/

		reference operator[](size_type n);

		const_reference operator[](size_type n) const;

		reference at(size_type n);
		
		const_reference at(size_type n) const;

		reference front(void);
		
		const_reference front(void) const;		

		reference back(void);
		
		const_reference back(void) const;

		/*
			*** Modifier Function ***
		*/

		

		void assign (size_type n, const value_type& val)
		{

		}

		//template <class Ite>
		//void assign (Ite f, Ite l);


		void resize (size_type n, const value_type & val = value_type());




	};
	
} // namespace ft
