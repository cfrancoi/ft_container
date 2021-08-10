#ifndef __MAP_ITERATOR_H__
#define __MAP_ITERATOR_H__


namespace ft
{
	template <class T>
	class M_Node
	{
		public:
			T * key;
			M_Node *parent;
			M_Node *left;
			M_Node *right;

			M_Node() : key(NULL) , parent(NULL), left(NULL), right(NULL) {};
			M_Node(const T & k) : key(k) , parent(NULL), left(NULL), right(NULL) {};

			M_Node & operator=(const M_Node & x) { key = x.key; parent = x.parent; left = x.left; right = x.right; return *this; };

			~M_Node() {};
	};

	template < class _Tp >
	class const_map_iterator;

	template < class _Tp >
	class map_iterator
	{
		public:
			typedef	_Tp								value_type;
			typedef _Tp *							pointer;
			typedef _Tp &							reference;
			//typedef _Self							iterator_type;
			typedef std::bidirectional_iterator_tag iterator_category;
			typedef std::ptrdiff_t 					difference_type;
			typedef size_t							size_type;
			
			typedef M_Node<_Tp>						Node;

			map_iterator() : _it(NULL) {};
			map_iterator(Node * n) : _it(n) {};


			reference	operator*() { return *(_it->key); }
			pointer		operator->() { return _it; }


		private:
			Node*	_it;
	};
};

#endif // __MAP_ITERATOR_H__