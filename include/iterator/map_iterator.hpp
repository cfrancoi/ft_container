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
			typedef std::bidirectional_iterator_tag iterator_category;
			typedef std::ptrdiff_t 					difference_type;
			typedef size_t							size_type;
			
			typedef M_Node<_Tp>						Node;

			map_iterator() : _it(NULL) {}
			map_iterator(Node * n) : _it(n) {}
			map_iterator(const map_iterator &ref) { *this = ref; }

			map_iterator& operator=(const map_iterator & ref) { _it = ref._it; return *this;}
			reference	operator*() { return *(_it->key); }
			pointer		operator->() { return _it->key; }

			map_iterator& operator++()
			{
				if (_it == NULL)
					return *this;
				if (_it->right != NULL)
				{
					_it = _it->right;
					while (_it->left != NULL)
						_it = _it->left;		
				}
				else if (_it->right == NULL)
				{
					Node *top;

					top = _it->top;
					while (top != NULL && top->right == _it)
					{
						_it = top;
						top = top->top;
					}
					_it = top;
				}
				return *this;
			}

			map_iterator operator++(int)
			{
				map_iterator tmp = *this;
				++(*this);
				return tmp;
			}

			map_iterator& operator--()
			{
				if (_it == NULL)
					return *this;
				
				if (_it->left != NULL)
				{
					_it = _it->left;
					while (_it->right != NULL)
						_it = _it->right;
				}
				else
				{
					Node *top;

					top = _it->top;
					while (top != NULL && top->left == _it)
					{
						_it = top;
						top = top->top;
					}
					_it = top;
				}
				return *this;
			}

			map_iterator operator--(int)
			{
				map_iterator tmp = *this;
				--(*this);
				return tmp;
			}

			friend bool operator==(const map_iterator<_Tp> &lhs, const map_iterator<_Tp> &rhs)
			{
				return (lhs._it == rhs._it);
			}
			friend bool operator!=(const map_iterator &lhs, const map_iterator & rhs)
			{
				return !(lhs == rhs);
			}
		
			Node*	_it;
	};
};

#endif // __MAP_ITERATOR_H__