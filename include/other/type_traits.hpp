#ifndef __TYPE_TRAITS_H__
#define __TYPE_TRAITS_H__

namespace ft
{

	template <class T, T val>
	struct integral_constant
	{
		typedef integral_constant<T, val>  type;
		typedef T                          value_type;
		static const T value = val;
		operator T()const;
	};

	typedef integral_constant<bool, true>  true_type;
	typedef integral_constant<bool, false> false_type;

	template <bool B, class T = void>
	struct enable_if_c {
	    typedef T type;
	};

	template <class T>
	struct enable_if_c<false, T> {};

	template <class Cond, class T = void>
	struct enable_if : public enable_if_c<Cond::value, T> {};

	template <class _Tp, class _Up>
	struct is_same           : public false_type {};
	template <class _Tp>
	struct is_same<_Tp, _Tp> : public true_type {};





	
}

#endif // __TYPE_TRAITS_H__