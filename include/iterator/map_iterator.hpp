#ifndef __MAP_ITERATOR_H__
#define __MAP_ITERATOR_H__


namespace ft
{
	template <class T>
	class M_Node
	{
		public:
			T key;
			M_Node *parent;
			M_Node *left;
			M_Node *right;

			M_Node() : key(T()) , parent(NULL), left(NULL), right(NULL) {};
			M_Node(const T & k) : key(k) , parent(NULL), left(NULL), right(NULL) {};

			M_Node & operator=(const M_Node & x) { key = x.key; parent = x.parent; left = x.left; right = x.right; return *this; };

			~M_Node() {};
	};

	template < class _Tp >
	class const_map_iterator;

	template < class _Tp >
	class map_iterator;
}

#endif // __MAP_ITERATOR_H__