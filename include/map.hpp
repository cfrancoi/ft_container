#ifndef __MAP_H__
# define __MAP_H__
# include <functional>
# include <utility>
# include <memory> // std::allocator
# include <algorithm>
# include <limits>
# include <iterator/map_iterator.hpp>
# include <iterator/iterator.hpp>
# include <other/utility.hpp>
# include <other/type_traits.hpp>
# include <other/algorithm.hpp>

#include <iostream>
namespace ft
{	
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator< ft::pair<const Key, T> > >
	class map
	{
		public:

			// Member types
			typedef Key		key_type;
			typedef T		mapped_type;
			typedef ft::pair<const Key, T> value_type;
			typedef Compare			key_compare;
			class value_compare;

			typedef	Alloc	allocator_type;
			typedef typename allocator_type::reference 		reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer 		pointer;
			typedef typename allocator_type::const_pointer 	const_pointer;

			typedef map_iterator<value_type>					iterator;
			typedef const_map_iterator<value_type>				const_iterator;
			typedef ft::reverse_iterator<iterator> 			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> 	const_reverse_iterator;

			typedef std::ptrdiff_t 						difference_type;
			typedef size_t								size_type;

			typedef M_Node<value_type> Node;

			/*
				** Constructer & destructor
			*/

			explicit map(const key_compare & cmp = key_compare(), const allocator_type & alloc = allocator_type());

			template <class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare & cmp = key_compare(), const allocator_type & alloc = allocator_type());

			map(const map & x);

			~map();

			/*
				** operator=
			*/

			map& operator=(const map& x);

			/*
				** Iterator
			*/

			iterator begin();
			const_iterator begin() const;

			iterator end();
			const_iterator end() const;

			reverse_iterator rbegin();
			const_reverse_iterator rbegin() const;

			reverse_iterator rend();
			const_reverse_iterator rend() const;

			/*
				** Capacity
			*/

			bool empty() const;
			size_type size() const;
			size_type max_size() const;

			/*
				** Element access
			*/
			mapped_type & operator[](const key_type & k);

			/*
				** Modifiers
			*/
			
			//insert
			ft::pair<iterator, bool> insert(const value_type & val);
			iterator insert(iterator pos, const value_type& val);
			
			template<class InputIt>
			typename ft::enable_if<ft::is_input_iterator<InputIt>, void >::type
			insert(InputIt first, InputIt last);
			
			//erase
			void erase(iterator position);
			size_type erase(const key_type & k);
			void erase(iterator first, iterator last);

			//swap
			void swap(map& x);

			//clear
			void clear(void);

			/*
				** Observers
			*/

			key_compare key_comp(void) const;
			value_compare value_comp(void) const;

			/*
				** Operations
			*/

			//find
			iterator find(const key_type& k);
			const_iterator find(const key_type& k) const;

			// count
			size_type count (const key_type& k) const;

			//lower_bound
			iterator lower_bound(const key_type& k);
			const_iterator lower_bound(const key_type& k) const;

			//upper_bound
			iterator upper_bound(const key_type& k);
			const_iterator upper_bound(const key_type& k) const;

			//equal_range
			ft::pair<iterator, iterator> equal_range(const key_type& k);
			ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const;

			/*
				** Allocator
			*/

			allocator_type get_allocator(void) const;

			//attributs
			protected:
				key_compare		_cmp;
				allocator_type	_alloc;	
				Node			*_bt;
				size_type		_size;
				Node			*_end;
			
			/*
				** Allocation
			*/
			private:
				value_type		_key_end;
				Node	*newNode(void);
				void	delNode(Node * pos);

				pointer		newVal(const value_type& val);
				Node* 	placeRight(Node * pos, const value_type& val);
				Node* 	placeLeft(Node * pos, const value_type& val);
				Node* 	placeFirst(const value_type& val);

				void	delCaseZero(Node * pos);
				void 	delCaseOne(Node * pos);
				void	delCaseTwo(Node * pos);

				Node*	cloneBinaryTree(Node * root);

				Node	*balanceInsert(Node * root, const value_type & val);


	};

	template <class Key, class T, class Compare, class Alloc>
	class map<Key,T,Compare,Alloc>::value_compare
	{
		  friend class map;
		protected:
			Compare comp;
			value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator() (const value_type& x, const value_type& y) const
			{
				return comp(x.first, y.first);
			}
	};

	/*
		** Constructer & destructor
	*/

	//Default Constructor
	template < class Key, class T, class Compare , class Alloc >
	map<Key, T, Compare, Alloc >::map(const key_compare & cmp, const allocator_type & alloc) : _cmp(cmp), _alloc(alloc), _bt(newNode()), _size(0), _end(_bt)
	{
		_end->key = &_key_end;
	}

	//Copy constructor
	template < class K, class T, class Comp , class Alloc >
	map<K, T, Comp, Alloc >::map(const map<K, T, Comp, Alloc > & x) : _bt(newNode()), _size(0), _end(_bt)
	{
		_end->key = &_key_end;
		*this = x;
	}
	
	//Range constructor
	template < class K, class T, class Comp , class Alloc >
	template<class InputIterator>
	map<K, T, Comp, Alloc >::map(InputIterator first, InputIterator last, const key_compare & cmp, const allocator_type & alloc) : _cmp(cmp), _alloc(alloc), _bt(newNode()), _size(0), _end(_bt)
	{
		_end->key = &_key_end;
		insert(first, last);
	}
	
	//Destructor
	template < class K, class T, class Comp, class Alloc >
	map<K, T, Comp, Alloc >::~map() 
	{
		erase(begin(), end());
		delete end()._it;
	}
	
	//operator=
	template < class K, class T, class Comp, class Alloc >
	map<K, T, Comp, Alloc>& map<K, T, Comp, Alloc>::operator=(const map<K, T, Comp, Alloc >& x) 
	{
		this->erase(begin(), end());
		delete _end;
		_cmp = x._cmp;
		_alloc = x._alloc;
		_bt = cloneBinaryTree(x._bt);
		_end = _bt;
		while (_end->right != NULL)
			_end = _end->right;
		_size = x._size;
		return *this;
	}

	/*
		***** Iterator *****
	*/

	//begin iterator
	template < class K, class T, class Comp , class Alloc >
	typename map<K, T, Comp, Alloc >::iterator map<K, T, Comp, Alloc >::begin() 
	{
		Node *pt = _bt;

		while (pt->left != NULL)
			pt = pt->left;

		return iterator(pt);
	}

	//begin const_iterator
	template < class K, class T, class Comp , class Alloc >
	typename map<K, T, Comp, Alloc >::const_iterator map<K, T, Comp, Alloc >::begin() const
	{
		Node *pt = _bt;

		while (pt->left != NULL)
			pt = pt->left;

		return const_iterator(pt);
	}
	
	// end iterator
	template < class K, class T, class Comp , class Alloc >
	typename map<K, T, Comp, Alloc >::iterator map<K, T, Comp, Alloc >::end() 
	{
		return iterator(_end);
	}
	
	// end const_iterator
	template < class K, class T, class Comp , class Alloc >
	typename map<K, T, Comp, Alloc >::const_iterator map<K, T, Comp, Alloc >::end() const
	{
		return const_iterator(_end);
	}
	
	//rbegin
	template < class K, class T, class Comp , class Alloc >
	typename map<K, T, Comp, Alloc >::reverse_iterator map<K, T, Comp, Alloc >::rbegin() 
	{
		return (reverse_iterator(iterator(_end)));
	}

	//crbegin
	template < class K, class T, class Comp , class Alloc >
	typename map<K, T, Comp, Alloc >::const_reverse_iterator map<K, T, Comp, Alloc >::rbegin() const 
	{
		return (const_reverse_iterator(const_iterator(_end)));
	}
	
	//rend
	template < class K, class T, class Comp , class Alloc >
	typename map<K, T, Comp, Alloc >::reverse_iterator map<K, T, Comp, Alloc >::rend() 
	{
		return (reverse_iterator(iterator(begin())));
	}

	//crend
	template < class K, class T, class Comp , class Alloc >
	typename map<K, T, Comp, Alloc >::const_reverse_iterator map<K, T, Comp, Alloc >::rend() const
	{
		return (const_reverse_iterator(const_iterator(begin())));
	}
	
	/*
		************************* Capacity *************************
	*/

	//empty
	template < class K, class T, class Comp , class Alloc >
	bool map<K, T, Comp, Alloc >::empty() const
	{
		return (_size == 0);
	}
	
	//size
	template < class K, class T, class Comp , class Alloc >
	typename map<K, T, Comp, Alloc >::size_type map<K, T, Comp, Alloc >::size() const
	{
		return _size;
	}
	
	//max_size
	template < class K, class T, class Comp , class Alloc >
	typename map<K, T, Comp, Alloc >::size_type map<K, T, Comp, Alloc >::max_size() const
	{
		//std::cerr << sizeof(value_type) << " " << sizeof(std::pair< K, T >) << std::endl;
		return std::min<size_type>(std::numeric_limits<size_type>::max() / sizeof(Node) ,std::numeric_limits<difference_type>::max() / (sizeof(value_type)));
		//return std::numeric_limits<difference_type>::max() / sizeof(value_type);
		//return _alloc.max_size();
	}


	/*
		** Element access ***********************************************************
	*/

	//operator[]
	template < class K, class T, class Comp , class Alloc >
	typename map<K, T, Comp, Alloc >::mapped_type& map<K, T, Comp, Alloc>::operator[](const key_type & k) 
	{
		iterator it = find(k);
		if (it != end())
		{
			return (it._it->key->second);
		}
		value_type t = ft::make_pair(k, mapped_type());
		ft::pair<iterator, bool> ret = insert(t);
		return ret.first->second;
	}

	/*
		***** Modifiers *****
	*/

	//insert
	template < class Key, class T, class Compare , class Alloc >
	ft::pair<typename map<Key, T, Compare, Alloc >::iterator, bool> map<Key, T, Compare, Alloc >::insert(const value_type & val) 
	{
		if (_size == 0)
			return ft::make_pair<iterator, bool>(iterator(placeFirst(val)), true);
		Node *pt = _bt;
		while(1)
		{
			bool ret = _cmp((*pt->key).first, val.first);
			if (ret)
			{
				if (pt->right == NULL || pt->right == _end)
				{
					return ft::pair<iterator, bool>(iterator(placeRight(pt, val)), true);
				}
				else
					pt = pt->right;
			}
			else if ((*pt->key).first == val.first)
			{
				return ft::pair<iterator, bool>(iterator(pt), false);
			}
			else
			{
				if (pt->left == NULL)
				{
					return ft::pair<iterator, bool>(iterator(placeLeft(pt, val)), true);
				}
				else
					pt = pt->left;
			}
		}
	}
	
	//insert with pos
	template < class Key, class T, class Compare , class Alloc >
	typename map<Key, T, Compare, Alloc >::iterator map<Key, T, Compare, Alloc >::insert(iterator pos, const value_type& val) 
	{
		(void)pos;
		(void)val;
		return insert(val).first;
		if (_size == 0)
			return placeFirst(val);

		Node *pt = upper_bound(val.first)._it;
		while(1)
		{
			bool ret = _cmp((*pt->key).first, val.first);
			if (ret)
			{
				if (pt->right == NULL || pt->right == _end)
				{
					return placeRight(pt, val);
				}
				else
					pt = pt->right;
			}
			else if ((*pt->key).first == val.first)
			{
				return end();
			}
			else
			{
				if (pt->left)
				{
					pt = pt->left;
				}
				else
					return placeLeft(pt, val);
					
			}
		}
	}
	
	//insert Input iterator
	template < class Key, class T, class Compare , class Alloc >
	template <class InputIt>
	typename ft::enable_if<ft::is_input_iterator<InputIt>, void >::type
	map<Key, T, Compare, Alloc >::insert(InputIt first, InputIt last) 
	{
		while (first != last)
			insert(*first++);
	}

	//erase
	template < class Key, class T, class Compare , class Alloc >
 	void map<Key, T, Compare, Alloc >::erase(iterator position)
	{
		Node * p = position._it;
		
		if (_size == 0)
			return;
		
		// no child
		if ((!p->right) && !p->left)
		{
			//std::cerr << "case0\n";
			delCaseZero(p);
			return ;
		}
		else if ((p->right && !p->left) || ((!p->right) && p->left))
		{
			//std::cerr << "case1\n";
			delCaseOne(p);
			return;
		}
		else if ((p->right) && p->left)
		{
			//std::cerr << "case2\n";
			delCaseTwo(p);
			return;
		}
	}

	//erase
	template < class Key, class T, class Compare , class Alloc >
	void map<Key, T, Compare, Alloc >::erase(iterator first, iterator last) 
	{
		while (first != last && first._it != NULL)
		{
			erase(first++);
		}
	}

	//erase
	template < class Key, class T, class Compare , class Alloc >
	typename map<Key, T, Compare, Alloc >::size_type map<Key, T, Compare, Alloc >::erase(const key_type& k) 
	{
		
		if(_size == 0)
			return 0;
		
		iterator pos = find(k);
		if (pos != end())
		{
			erase(pos);
			return 1;
		}
		return 0;
	}
	
	//swap
	template < class Key, class T, class Compare , class Alloc >
	void map<Key, T, Compare, Alloc >::swap(map& x)
	{
		std::swap(this->_cmp, x._cmp);

		Node * swp = _bt;
		_bt = x._bt;
		x._bt = swp;

		swp = _end;
		_end = x._end;
		x._end = swp;

		size_type len = _size;
		_size = x._size;
		x._size = len;
	}
	
	//clear
	template < class Key, class T, class Compare , class Alloc >
	void map<Key, T, Compare, Alloc >::clear(void) 
	{
		erase(begin(), end());
	}

	/*
		***** Observer *****
	*/

	//key_comp
	template < class Key, class T, class Compare , class Alloc >
	typename map<Key, T, Compare, Alloc >::key_compare map<Key, T, Compare, Alloc >::key_comp(void) const
	{
		return _cmp;
	}
	
	template < class Key, class T, class Compare , class Alloc >
	typename map<Key, T, Compare, Alloc >::value_compare map<Key, T, Compare, Alloc >::value_comp(void) const
	{
		return typename map<Key, T, Compare, Alloc >::value_compare(_cmp);
	}
	
	/*
		***** Operations *****
	*/

	//find
	template < class Key, class T, class Compare , class Alloc >
	typename map<Key, T, Compare, Alloc >::iterator map<Key, T, Compare, Alloc >::find(const key_type& k) 
	{
		Node * cur = _bt;

		while (cur != _end && cur->key->first != k)
		{
			if (_cmp(cur->key->first, k))
				cur = cur->right;
			else
				cur = cur->left;
			
			if (cur == NULL || cur == _end)
				return end();
		}
		return (iterator(cur));

	}

	//find
	template < class Key, class T, class Compare , class Alloc >
	typename map<Key, T, Compare, Alloc >::const_iterator map<Key, T, Compare, Alloc >::find(const key_type& k) const
	{
		Node * cur = _bt;

		while (cur != _end && cur->key->first != k)
		{
			if (_cmp(cur->key->first, k))
				cur = cur->right;
			else
				cur = cur->left;
			
			if (cur == NULL || cur == _end)
				return end();
		}
		return (const_iterator(cur));

	}
	
	//count
	template < class Key, class T, class Compare , class Alloc >
	typename map<Key, T, Compare, Alloc >::size_type map<Key, T, Compare, Alloc >::map::count(const key_type& k) const
	{
		if (find(k) != end())
			return 1;
		return 0;
	}
	
	//lower_bound
	template < class Key, class T, class Compare , class Alloc >
	typename map<Key, T, Compare, Alloc >::iterator map<Key, T, Compare, Alloc >::lower_bound(const key_type& k) 
	{
		iterator it;

		it = begin();
		while (it != end() && _cmp(it->first, k))
		{
			it++;
		}
		return it;
	}

	//const_lower_bound
	template < class Key, class T, class Compare , class Alloc >
	typename map<Key, T, Compare, Alloc >::const_iterator map<Key, T, Compare, Alloc >::lower_bound(const key_type& k) const
	{
		const_iterator it;

		it = begin();
		while (it != end() && _cmp(it->first, k))
		{
			it++;
		}
		return it;
	}
	
	//upper_bound
	template < class Key, class T, class Compare , class Alloc >
	typename map<Key, T, Compare, Alloc >::iterator map<Key, T, Compare, Alloc >::upper_bound(const key_type& k) 
	{
		iterator it;

		it = begin();
		while (it != end() && (_cmp(it->first, k) || it->first == k))
		{
			it++;
		}
		return it;
	}

	//const_upper_bound
	template < class Key, class T, class Compare , class Alloc >
	typename map<Key, T, Compare, Alloc >::const_iterator map<Key, T, Compare, Alloc >::upper_bound(const key_type& k) const
	{
		const_iterator it;

		it = begin();
		while (it != end() && (_cmp(it->first, k) || it->first == k))
		{
			it++;
		}
		return it;
	}
	
	//equal_range
	template < class Key, class T, class Compare , class Alloc >
	ft::pair<typename map<Key, T, Compare, Alloc >::iterator, typename map<Key, T, Compare, Alloc >::iterator> map<Key, T, Compare, Alloc >::equal_range(const key_type& k) 
	{
		ft::pair<typename map<Key, T, Compare, Alloc >::iterator, typename map<Key, T, Compare, Alloc >::iterator> ret(lower_bound(k), upper_bound(k));
		return ret;
	}

	//const_equal_range
	template < class Key, class T, class Compare , class Alloc >
	ft::pair<typename map<Key, T, Compare, Alloc >::const_iterator, typename map<Key, T, Compare, Alloc >::const_iterator> map<Key, T, Compare, Alloc >::equal_range(const key_type& k) const 
	{
		ft::pair<typename map<Key, T, Compare, Alloc >::const_iterator, typename map<Key, T, Compare, Alloc >::const_iterator> ret(lower_bound(k), upper_bound(k));
		return ret;
	}
	
	//get_allocator
	template < class Key, class T, class Compare , class Alloc >
	typename map<Key, T, Compare, Alloc >::allocator_type map<Key, T, Compare, Alloc >::get_allocator(void) const
	{
		return _alloc;
	}

	/*
			****** Allocation ******
	*/

	template < class K, class T, class Comp , class Alloc >
	typename map<K, T, Comp, Alloc >::Node* map<K, T, Comp, Alloc >::newNode(void)
	{
		return new Node();
	}
	
	template < class K, class T, class Comp , class Alloc >
	typename map<K, T, Comp, Alloc >::pointer map<K, T, Comp, Alloc >::newVal(const value_type& val) 
	{
		pointer n = _alloc.allocate(1);

		_alloc.construct(n, val);
		return (n);
	}


	// PlaceRight 
	template < class K, class T, class Comp , class Alloc >
	typename map<K, T, Comp, Alloc >::Node* map<K, T, Comp, Alloc >::placeRight(Node * pos, const value_type& val) 
	{
		Node * end = pos->right;

		pos->right = newNode();
		pos->right->top = pos;
		pos->right->key = newVal(val);
		pos->right->right = end;
		if (pos->right->right)
			pos->right->right->top = pos->right;
		_size += 1;
		
		balanceInsert(pos, val);
		return (find(val.first)._it);
	}
	
	// PlaceLeft
	template < class K, class T, class Comp , class Alloc >
	typename map<K, T, Comp, Alloc >::Node*  map<K, T, Comp, Alloc >::placeLeft(Node * pos, const value_type& val) 
	{
		pos->left = newNode();
		pos->left->top = pos;
		pos->left->key = newVal(val);
		_size += 1;

		balanceInsert(pos, val);

		return (find(val.first)._it);
	}
	
	template < class K, class T, class Comp , class Alloc >
	typename map<K, T, Comp, Alloc >::Node*  map<K, T, Comp, Alloc >::placeFirst(const value_type& val)
	{
		Node * end = _bt;

		_bt = newNode();
		_bt->key = newVal(val);
		_size += 1;
		_bt->right = end;
		_bt->right->top = _bt;
		return _bt;
	}
	
	template < class K, class T, class Comp , class Alloc >
	void map<K, T, Comp, Alloc >::delCaseZero(Node * pos) 
	{
		Node * isend = pos->right;
		if (_bt == pos)
		{
			_bt = isend;
			_bt->top = NULL;
		}
		else if (pos->top->right == pos)
		{
			pos->top->right = isend;
		}
		else if (pos->top->left == pos)
			pos->top->left = NULL;
		delNode(pos);
	}

	template < class K, class T, class Comp , class Alloc >
	void map<K, T, Comp, Alloc >::delCaseOne(Node * pos) 
	{
		Node * child;

		if (pos->left)
			child = pos->left;
		else
			child = pos->right;

		if (_bt == pos)
		{
			_bt = child;
			_bt->top = NULL;
		}
		else if (pos->top->right == pos)
		{
			pos->top->right = child;
			child->top = pos->top;
		}
		else if (pos->top->left == pos)
		{
			pos->top->left = child;
			child->top = pos->top;
		}
		delNode(pos);
	}
	
	template < class K, class T, class Comp , class Alloc >
	void map<K, T, Comp, Alloc >::delCaseTwo(Node * pos)
	{
		Node * near;
		{
			iterator it(pos);
			it++;
			near = it._it;
			if (it != end())
			{
				near = it._it;
			}
			else
			{
				iterator it(pos);
				it--;
				near = it._it;
			}
		}
		Node * top = pos->top;
		//detach node
		if (pos->left != near)
		{
			near->left = pos->left;
			if(near->left)
				near->left->top = near;
		}
		if (pos->right != near)
		{
			near->right = pos->right;
			if(near->right)
				near->right->top = near;
		}
		
		if (near->top->left == near)
			near->top->left = NULL;
		else
			near->top->right = NULL;

		//fixe top
		if (top == NULL)
			_bt = near;
		else if (top->left == pos)
			top->left = near;
		else
			top->right = near;
		near->top = top;

		
		delNode(pos);
	}
	
	template < class K, class T, class Comp , class Alloc >
	typename map<K, T, Comp, Alloc >::Node* map<K, T, Comp, Alloc >::map::cloneBinaryTree(Node * root) 
	{
		if (root == NULL)
			return NULL;
		Node * nNode = newNode();
		if (root->key != NULL)
			nNode->key = newVal(*root->key);
		nNode->left = cloneBinaryTree(root->left);
		if (nNode->left)
			nNode->left->top = nNode;
		nNode->right = cloneBinaryTree(root->right);
		if (nNode->right)
			nNode->right->top = nNode;
		return nNode;
	}
	
	template < class K, class T, class Comp , class Alloc >
	void map<K, T, Comp, Alloc >::delNode(Node * pos) 
	{
		_alloc.destroy(pos->key);
		_alloc.deallocate(pos->key, 1);
		delete pos;
		_size -= 1;
	}
	
	template < class K, class T, class Comp , class Alloc >
	typename map<K, T, Comp, Alloc >::Node* map<K, T, Comp, Alloc >::balanceInsert(Node * root, const value_type & val) 
	{
		if (root == NULL)
			return NULL;
		
		
		root->h = 1 + std::max(root->height(root->left), root->height(root->right));
		
		if (root->top != NULL)
		{
			
			int balance = root->getBalance(root->top);

			if (balance > 1 && root->left && _cmp(val.first, root->left->key->first))
				root->rr_rot(root);

			if (balance < -1 && root->right && root->right != _end && !_cmp(val.first, root->right->key->first))
				root->ll_rot(root);

			if (balance > 1 && root->left && root->right != _end && !_cmp(val.first, root->left->key->first))
			{
				if (root->left && root->left->right)
				{	
					root->ll_rot(root->left);
				}
				root->rr_rot(root);
			}
			if (balance < -1 && root->left && root->right && _cmp(val.first, root->left->key->first))
			{
				if (root->right->left)
					root->rr_rot(root->left);
				root->ll_rot(root);
			}
		}
		return root;
	}
	

	/*
		***** Non-memer functions *****
	*/

	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return !(lhs == rhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	
	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return !(rhs < lhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return (rhs < lhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return !(lhs < rhs);
	}

}; // namespace ft

template< class Key, class T, class Compare, class Alloc >
void swap( ft::map<Key,T,Compare,Alloc>& lhs, ft::map<Key,T,Compare,Alloc>& rhs )
{
	lhs.swap(rhs);
}

#endif // __MAP_H__