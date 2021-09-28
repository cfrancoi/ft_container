#ifndef __ITERATOR_H__
#define __ITERATOR_H__
#include <other/type_traits.hpp>
#include <cstddef>
#include <iterator>

#include <iostream>
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
            typedef Iter		   												iterator_type;
        	typedef	typename ft::iterator_traits<Iter>::value_type			    value_type;
			typedef typename ft::iterator_traits<Iter>::pointer			        pointer;
			typedef typename ft::iterator_traits<Iter>::reference		        reference;
			typedef typename ft::iterator_traits<Iter>::iterator_category       iterator_category;
			typedef typename ft::iterator_traits<Iter>::difference_type         difference_type;
            typedef reverse_iterator<Iter>                  					_Self;

		private:
           	Iter _base;
		public:	
            reverse_iterator<Iter>() : _base() {}

            explicit reverse_iterator<Iter>(iterator_type it) : _base(it) {}

			template < class U >
			reverse_iterator<Iter>(const reverse_iterator< U > & src) { *this = src; }

            ~reverse_iterator<Iter>() {}

            reference	operator*() const { Iter tmp = base(); return *--tmp; }
			pointer		operator->() const { return &operator*(); }

			reference operator[](difference_type n) const { return (*(--base() - n)); }

			iterator_type base() const { return iterator_type(_base);}

            _Self& operator++()
			{
				--_base;
				return *this;
			}

			_Self operator++(int)
			{
				_Self tmp(_base);
                _base--;
                return tmp;
			}

			_Self& operator--()
			{
                ++_base;
				return *this;
			}

			_Self operator--(int)
			{
				_Self tmp(_base);
                _base++;
				return tmp;
			}
			
			template < class U >
 			reverse_iterator <Iter>& operator=(const reverse_iterator< U >& u)
			{
				_base = u.base();
				return *this;
			}

			/*
				** operator+
			*/
 			reverse_iterator	operator+(const difference_type& x) const { return reverse_iterator(_base - x);}
			/*
				** operator-
			*/
 			reverse_iterator	operator-(const difference_type& x) const { return reverse_iterator(_base + x); }
			/*
				** operator += & -=
			*/
			reverse_iterator	&operator-=(const difference_type& x) { _base += x; return *this;}
			reverse_iterator	&operator+=(const difference_type& x) { _base -= x; return *this; }



    };

	template <class A, class B> bool operator==(const reverse_iterator<A> &lhs, const reverse_iterator<B> &rhs){ return lhs.base() == rhs.base(); };
	template <class A, class B> bool operator!=(const reverse_iterator<A> &lhs, const reverse_iterator<B> &rhs) { return lhs.base()!= (rhs.base()); };
	template <class A, class B> bool operator<(const reverse_iterator<A> &lhs, const reverse_iterator<B> &rhs) { return lhs.base() > (rhs.base()); };
	template <class A, class B> bool operator<=(const reverse_iterator<A> &lhs, const reverse_iterator<B> &rhs) { return lhs.base() >= (rhs.base()); };
	template <class A, class B> bool operator>(const reverse_iterator<A> &lhs, const reverse_iterator<B> &rhs) { return lhs.base() < (rhs.base()); };
	template <class A, class B> bool operator>=(const reverse_iterator<A> &lhs, const reverse_iterator<B> &rhs) { return lhs.base() <= (rhs.base()); };
	
	template <class Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& it)
	{
		return reverse_iterator<Iterator>(it.base() - n);
	}
	
	template <class Iterator, class two>	
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<two>& rhs)
	{
		return (rhs.base() - lhs.base());
	}


};
#endif // __ITERATOR_H__