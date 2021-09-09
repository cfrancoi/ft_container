#ifndef __ITERATOR_H__
#define __ITERATOR_H__
#include <other/type_traits.hpp>
#include <cstddef>
#include <iterator>
namespace ft
{

	/*
		** Iterator_traits
    */

   	template<class T>
	class has_iterator_category
	{
		private:
			struct two { char x[2]; };

			template<class X> static two test(...);
			template<class X> static char test(typename X::iterator_category* = 0);
		public:
			static bool const value = sizeof(test<T>(0)) == 1; 
	};

	template<class _Tp, bool>
	struct _iter_traits_impl{};

	template<class _Tp>
	struct _iter_traits_impl<_Tp, true>
	{
		typedef typename _Tp::difference_type		difference_type;
		typedef typename _Tp::iterator_category		iterator_category;
		typedef typename _Tp::pointer				pointer;
		typedef typename _Tp::reference				reference;
		typedef typename _Tp::value_type			value_type;
	};

   	template<class _Tp>
	struct iterator_traits : _iter_traits_impl<_Tp, has_iterator_category<_Tp>::value >
	{
	};

	template<class _Tp>
	struct iterator_traits<_Tp *>
	{
		typedef typename std::ptrdiff_t difference_type;
		typedef typename std::random_access_iterator_tag iterator_category;
		typedef _Tp * pointer;
		typedef _Tp & reference;
		typedef _Tp value_type;
	};

	template<class _Tp>
	struct iterator_traits<const _Tp *>
	{
		typedef typename std::ptrdiff_t difference_type;
		typedef typename std::random_access_iterator_tag iterator_category;
		typedef const _Tp * pointer;
		typedef const _Tp & reference;
		typedef const _Tp value_type;
	};


	/*
		** is_input_iterator
	*/

	template <class, class Enable = void> struct is_input_iterator : ft::false_type {};
	
	// random acces
	template<class Input>
	struct is_input_iterator<Input,
		typename ft::enable_if<ft::is_same<std::input_iterator_tag,
		typename ft::iterator_traits<Input>::iterator_category>
		>::type> : ft::true_type {};

	template<class Input>
	struct is_input_iterator<Input,
		typename ft::enable_if<ft::is_same<std::forward_iterator_tag,
		typename ft::iterator_traits<Input>::iterator_category>
		>::type> : ft::true_type {};

	template<class Input>
	struct is_input_iterator<Input,
		typename ft::enable_if<ft::is_same<std::bidirectional_iterator_tag,
		typename ft::iterator_traits<Input>::iterator_category>
		>::type> : ft::true_type {};
	
	template<class Input>
	struct is_input_iterator<Input,
		typename ft::enable_if<ft::is_same<std::random_access_iterator_tag,
		typename ft::iterator_traits<Input>::iterator_category>
		>::type> : ft::true_type {};
	
	
	
	/*
        ** Reverse itarator
    */
    template <class Iter>
    class reverse_iterator
    {       
        public:
            typedef Iter		   							iterator_type;
        	typedef	typename ft::iterator_traits<Iter>::value_type			    value_type;
			typedef typename ft::iterator_traits<Iter>::pointer			        pointer;
			typedef typename ft::iterator_traits<Iter>::reference		        reference;
			typedef typename ft::iterator_traits<Iter>::iterator_category        iterator_category;
			typedef typename ft::iterator_traits<Iter>::difference_type          difference_type;
            typedef reverse_iterator<Iter>                  _Self;

		private:
           	Iter _base;
		public:	
            reverse_iterator<Iter>() : _base() {}

            reverse_iterator<Iter>(iterator_type it) : _base(it) {}

            //reverse_iterator<Iter>(const _Self & src) { *this = src; }

			template < class U >
			reverse_iterator<Iter>(const reverse_iterator< U > & src) { *this = src; }

            ~reverse_iterator<Iter>() {}


            reference	operator*() { return *_base; }
			pointer		operator->() { return _base.operator->(); }

			reference operator[](difference_type n) const { return reference(*(_base + n)); }

			iterator_type base() const { return iterator_type(_base);}

            _Self& operator++()
			{
				--_base;
				return *this;
			}

			_Self operator++(int)
			{
                _base--;
                return *this;
			}

			_Self& operator--()
			{
                ++_base;
				return *this;
			}

			_Self operator--(int)
			{
                _base++;
				return *this;
			}
			
			template < class U >
 			reverse_iterator <Iter>& operator=(const reverse_iterator< U >& u)
			{
				_base = u.base();
				return *this;
			}

			template < class U >
 			bool	operator!=(const reverse_iterator< U >& x)
			{
				return _base != x.base();
			}

			template < class U >
 			bool	operator==(const reverse_iterator< U >& x)
			{
				return _base != x.base();
			}

			/*
				** operator+
			*/

 			reverse_iterator	operator+(const difference_type& x) const
			{
				return reverse_iterator(base() - x);
			}

			/*
				** operator-
			*/

			/*template < class U >
 			reverse_iterator<Iter>& operator-(const reverse_iterator< U >& u) const
			{
				return reverse_iterator<Iter>(base() + u.base());
			}*/
			
 			reverse_iterator	operator-(const difference_type& x) const
			{
				return reverse_iterator(Iter(_base + x));
			}

			/*
				** operator += & -=
			*/

			reverse_iterator	&operator-=(const difference_type& x)
			{
				_base += x;
				return *this;
			}

			reverse_iterator	&operator+=(const difference_type& x)
			{
				_base -= x;
				return *this;
			}

			friend bool operator==(const reverse_iterator &x, const reverse_iterator & y) { return (x._base == y._base);}
			friend bool operator!=(const reverse_iterator &x, const reverse_iterator & y) { return (x._base != y._base);}
    };
	
	template <class Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
	{
		reverse_iterator<Iterator> ret(rev_it);

		ret += n;
		return ret;
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator-(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
	{
		reverse_iterator<Iterator> ret(rev_it);

		ret -= n;
		return ret;
	}


};
#endif // __ITERATOR_H__