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
			int		h;

			M_Node() : key(NULL) , top(NULL), left(NULL), right(NULL), h(1)   {};
			M_Node(const T & k) : key(k) , top(NULL), left(NULL), right(NULL), h(1)  {};

			M_Node & operator=(const M_Node & x) { key = x.key; top = x.top; left = x.left; right = x.right; return *this; };

			//height
			int	height(M_Node * p)
			{
				if (p == NULL)
					return 0;
				return p->h;
			}

			int getBalance(M_Node * root)
			{
				if (root == NULL)
					return 0;
				return height(root->left) - height(root->right);
			}

			// diff factor
			size_t diff(M_Node *top)
			{
				size_t l_h = top->left->height();
				size_t r_h = top->right->height();

				return l_h - r_h;
			}

		
			M_Node * rr_rot(M_Node * parent)
			{

				M_Node * b;
				M_Node * top;

				b = parent->left;
				top = parent->top;
				if (top != NULL)
				{
					if (parent == top->left)
						top->left = b;
					else
						top->right = b;
				}
				b->top = top;
				parent->top = b;
				parent->left = b->right;
				if (parent->left)
					parent->left->top = parent;
				b->right = parent;

				
				parent->h = std::max(height(parent->left), height(parent->right));
				b->h = std::max(height(b->left), height(b->right));

				return b;
			}

			M_Node * ll_rot(M_Node * parent)
			{
				
				M_Node *b;
				M_Node *top;

				b = parent->right;
				top = parent->top;
				if (top != NULL)
				{
					if (parent == top->right)
					{
						top->right = b;
					}
					else
					{
						top->left = b;
					}
				}
				b->top = top;
				parent->top = b;
				parent->right = b->left;
				
				if (parent->right)
					parent->right->top = parent;
				b->left = parent;
				
				
				parent->h = std::max(height(parent->left), height(parent->right));
				b->h = std::max(height(b->left), height(b->right));

				
				return b;
			}
			M_Node * lr_rot(M_Node * pt);
			M_Node * rl_rot(M_Node * pt);


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
			reference	operator*() const { return *_it->key; }
			pointer		operator->() const { return _it->key; }

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

			bool operator==(const map_iterator& x) const { return _it == x._it;}
			bool operator!=(const map_iterator& x) const { return _it != x._it;}
		
		template <class, class, class, class> friend class map; // map can acces to private member
		template <class> friend class const_map_iterator; // map can acces to private member
		private:
			Node*	_it;
	};

	template < class _Tp >
	class const_map_iterator
	{
		public:
			typedef	_Tp								value_type;
			typedef const _Tp *							pointer;
			typedef const _Tp &							reference;
			typedef std::bidirectional_iterator_tag iterator_category;
			typedef std::ptrdiff_t 					difference_type;
			typedef size_t							size_type;
			
			typedef M_Node<_Tp>						Node;

			const_map_iterator() : _it(NULL) {}
			const_map_iterator(Node * n) : _it(n) {}
			const_map_iterator(const const_map_iterator &ref) { *this = ref; }
			const_map_iterator(const map_iterator<_Tp> &ref) : _it(ref._it) { }

			const_map_iterator& operator=(const const_map_iterator & ref) { _it = ref._it; return *this;}
			reference	operator*() const { return *(_it->key); }
			pointer		operator->() const { return _it->key; }

			const_map_iterator& operator++()
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

			const_map_iterator operator++(int)
			{
				const_map_iterator tmp = *this;
				++(*this);
				return tmp;
			}

			const_map_iterator& operator--()
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

			const_map_iterator operator--(int)
			{
				const_map_iterator tmp = *this;
				--(*this);
				return tmp;
			}

			bool operator==(const const_map_iterator& x) const { return _it == x._it;}
			bool operator!=(const const_map_iterator& x) const { return _it != x._it;}
			
			template <class, class, class, class> friend class map; // map can acces to private member
		
		private:
			Node*	_it;
	};
};

#endif // __MAP_ITERATOR_H__