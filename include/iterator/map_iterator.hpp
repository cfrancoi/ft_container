#ifndef __MAP_ITERATOR_H__
#define __MAP_ITERATOR_H__

#include <iostream>

namespace ft
{
	template <class T>
	class M_Node
	{
		public:
			T * key;
			M_Node *top;
			M_Node *left;
			M_Node *right;

			M_Node() : key(NULL) , top(NULL), left(NULL), right(NULL) {};
			M_Node(const T & k) : key(k) , top(NULL), left(NULL), right(NULL) {};

			M_Node & operator=(const M_Node & x) { key = x.key; top = x.top; left = x.left; right = x.right; return *this; };

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

			map_iterator& operator++()
			{
				Node* prev = NULL;
				Node* ret = _it;
				Node* next = NULL;

		//		while (ret != NULL)
		//		{
					if (next == ret->top)
					{
						prev = ret;
						next = ret->left;
					}
					if (next == NULL ||  prev == ret->left)
					{
						prev = ret;
						next = ret->right;
					}
					if (next == NULL || prev == ret->right)
					{
						prev = ret;
						next = ret->top;
					}
					ret = next;
				//}
				_it = ret;
				return *this;
			}

			void print()
			{
				Node* prev = NULL;
				Node* ret = _it;
				Node* next = NULL;

				
				while (ret != NULL)
				{
					//std::cout << "key :" << (*ret->key).first << std::endl;
					if (prev == ret->top)
					{
						prev = ret;
						next = ret->left;
					}
					if (next == NULL ||  prev == ret->left)
					{
						prev = ret;
						next = ret->right;
					}
					if (next == NULL || prev == ret->right)
					{
						prev = ret;
						next = ret->top;
					}
					ret = next;
					//std::cout << "key :" << (*ret->key).first << std::endl;
				}

			}


		private:
			Node*	_it;
	};
};

#endif // __MAP_ITERATOR_H__