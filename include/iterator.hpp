#ifndef __ITERATOR_H__
#define __ITERATOR_H__
#include <type_traits.hpp>

namespace ft
{



	/*typename enable_if<ft::is_same<std::random_access_iterator_tag,
				typename ft::iterator_traits<Input>::iterator_category>, bool>::type>
	is_input_iterator : std::true_type {};*/
	

	template <class, class Enable = void> struct is_iterator : std::false_type {};
	
	template <typename T> 
	struct is_iterator
	<T, 
	 typename std::enable_if<
	    std::is_base_of<
			std::random_access_iterator_tag,
			typename std::iterator_traits<T>::iterator_category
			>::value,
		bool
	 >::type> 
	 : std::true_type {};

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

	template <class, class Enable = void> struct is_input_iterator : std::false_type {};
	
	// random acces
	template<class Input>
	struct is_input_iterator<Input,
		typename ft::enable_if<ft::is_same<std::input_iterator_tag,
		typename ft::iterator_traits<Input>::iterator_category>
		>::type> : std::true_type {};

	template<class Input>
	struct is_input_iterator<Input,
		typename ft::enable_if<ft::is_same<std::forward_iterator_tag,
		typename ft::iterator_traits<Input>::iterator_category>
		>::type> : std::true_type {};

	template<class Input>
	struct is_input_iterator<Input,
		typename ft::enable_if<ft::is_same<std::bidirectional_iterator_tag,
		typename ft::iterator_traits<Input>::iterator_category>
		>::type> : std::true_type {};
	
	template<class Input>
	struct is_input_iterator<Input,
		typename ft::enable_if<ft::is_same<std::random_access_iterator_tag,
		typename ft::iterator_traits<Input>::iterator_category>
		>::type> : std::true_type {};
	
	
	
	/*
        ** Reverse itarator
    */
    template <class Iter>
    class reverse_iterator
    {       
        public:
            
        	typedef	typename Iter::value_type			    value_type;
			typedef typename Iter::pointer			        pointer;
			typedef typename Iter::reference		        reference;
			typedef typename Iter::iterator_type		    iterator_type;
			typedef typename Iter::iterator_category        iterator_category;
			typedef typename Iter::difference_type          difference_type;
            typedef reverse_iterator<Iter>                  _Self;

            reverse_iterator<Iter>() : _it() {}

            reverse_iterator<Iter>(const Iter & src) : _it(src) {}

            reverse_iterator<Iter>(const _Self & src) { *this = src; }

            ~reverse_iterator<Iter>() {}


            reference	operator*() { return *_it; }
			pointer		operator->() { return _it.operator->(); }
            
            _Self& operator=(const _Self & ref)
			{
				_it = ref._it;
				return *this;
			}

            _Self& operator++()
			{
				--_it;
				return *this;
			}

			_Self operator++(int)
			{
                _it--;
                return *this;
			}

			_Self& operator--()
			{
                ++_it;
				return *this;
			}

			_Self operator--(int)
			{
                _it++;
				return *this;
			}

			friend
			bool operator!=(const _Self& __x, const _Self& __y) { return (__x._it != __y._it); }
			friend
			bool operator==(const _Self& __x, const _Self& __y) { return (__x._it == __y._it); }

            private:
                Iter _it;
    };


};
#endif // __ITERATOR_H__