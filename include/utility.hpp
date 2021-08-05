#ifndef __UTILITY_HPP__
#define __UTILITY_HPP__

namespace ft
{
	template <class T1, class T2>
	struct pair
	{
		typedef T1	first_type;
		typedef T2	second_type;

		first_type	first;
		second_type	second;

		pair();

		template <class U, class V>
		pair(const pair<U, V>& pr);

		pair(const first_type& a, const second_type&b);

		pair& operator= (const pair& pr);


		template <class T1, class T2>
		bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs);

		template <class T1, class T2>
		bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs);

		template <class T1, class T2>
		bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs);

		template <class T1, class T2>
		bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs);

		template <class T1, class T2>
		bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs);

		template <class T1, class T2>
		bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs);
		
	};
};

#endif // __UTILITY_H__