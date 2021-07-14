#ifndef __TYPE_TRAITS_H__
#define __TYPE_TRAITS_H__

namespace ft
{
	template <bool B, class T = void>
	struct enable_if_c {
	    typedef T type;
	};

	template <class T>
	struct enable_if_c<false, T> {};

	template <class Cond, class T = void>
	struct enable_if : public enable_if_c<Cond::value, T> {};

	template <class _Tp, class _Up>
	struct is_same           : public std::false_type {};
	template <class _Tp>
	struct is_same<_Tp, _Tp> : public std::true_type {};
}

#endif // __TYPE_TRAITS_H__