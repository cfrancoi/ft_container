#ifndef __MAP_H__
# define __MAP_H__
# include <functional>
# include <utility>
# include <memory>
# include <iterator/map_iterator.hpp>
# include <iterator/iterator.hpp>
# include <other/utility.hpp>
# include <other/type_traits.hpp>


#include <iostream>
namespace ft
{

	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator< ft::pair<Key, T> > >
	class map
	{
		public:

			// Member types
			typedef Key		key_type;
			typedef T		mapped_type;
			typedef ft::pair<Key, T> value_type;
			typedef Compare			key_compare;
			typedef int value_compare;

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
			ft::pair<iterator, bool> insert(const value_type& val);
			iterator insert(iterator pos, const value_type& val);
			
			template<class InputIt>
			typename ft::enable_if<ft::is_input_iterator<InputIt>, void >::type
			insert(InputIt first, InputIt last);
			
			//erase
			void erase(iterator position);
			size_type erase(const key_type& k);
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
			std::pair<iterator, iterator> equal_range(const key_type& k);
			std::pair<const_iterator, const_iterator> equal_range(const key_type& k) const;

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
				Node	*newNode(void);
				void	delNode(Node * pos);

				pointer		newVal(const value_type& val);
				iterator	placeRight(Node * pos, const value_type& val);
				iterator	placeLeft(Node * pos, const value_type& val);
				iterator	placeFirst(const value_type& val);

				void	delCaseZero(Node * pos);
				void 	delCaseOne(Node * pos);
				void	delCaseTwo(Node * pos);

			
				void	printNode(Node * pos);


	};

	/*
		** Constructer & destructor
	*/

	//Default Constructor
	template < class Key, class T, class Compare , class Alloc >
	map<Key, T, Compare, Alloc >::map(const key_compare & cmp, const allocator_type & alloc) : _cmp(cmp), _alloc(alloc), _bt(newNode()), _size(0), _end(_bt)
	{
		
	}

	//Copy constructor
	template < class K, class T, class Comp , class Alloc >
	map<K, T, Comp, Alloc >::map(const map<K, T, Comp, Alloc > & x) : _bt(newNode()), _size(0), _end(_bt)
	{
		*this = x;
	}
	
	//Destructor
	template < class K, class T, class Comp, class Alloc >
	map<K, T, Comp, Alloc >::~map() 
	{
		erase(begin(), end());
		delete end()._it;
	}
	
	template < class K, class T, class Comp, class Alloc >
	map<K, T, Comp, Alloc>& map<K, T, Comp, Alloc>::operator=(const map<K, T, Comp, Alloc >& x) 
	{
		this->erase(begin(), end());
		_cmp = x._cmp;
		_alloc = x._alloc;
		this->insert(x.begin(), x.end());
		return *this;
	}

	/*
		** Iterator
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
		Node *pt = _bt;

		while (pt->right != NULL)
			pt = pt->right;

		return const_iterator(pt);
	}
	
	//rbegin
	template < class K, class T, class Comp , class Alloc >
	typename map<K, T, Comp, Alloc >::reverse_iterator map<K, T, Comp, Alloc >::rbegin() 
	{
		return (reverse_iterator(--end()));
	}
	
	//rend
	template < class K, class T, class Comp , class Alloc >
	typename map<K, T, Comp, Alloc >::reverse_iterator map<K, T, Comp, Alloc >::rend() 
	{
		return (reverse_iterator(iterator(begin()._it->left)));
	}
	
	/*
		** Capacity
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
		/*std::cerr << "height :" << _bt->height() << "\n";
		std::cerr << "left height :" << _bt->left->height() << "\n";
		std::cerr << "right height :" << _bt->right->height() << "\n";*/
		return _size;
	}
	
	//max_size
	template < class K, class T, class Comp , class Alloc >
	typename map<K, T, Comp, Alloc >::size_type map<K, T, Comp, Alloc >::max_size() const
	{
		return std::min<size_type>(_alloc.max_size(), std::numeric_limits<difference_type>::max());
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
			return (it._it->key->second);
		//return *(this->insert(ft::).first).second);
		value_type t = ft::make_pair(k, mapped_type());
		return(insert(t).first->second);
	}

	/*
		** Modifiers
	*/

	//insert
	template < class Key, class T, class Compare , class Alloc >
	ft::pair<typename map<Key, T, Compare, Alloc >::iterator, bool> map<Key, T, Compare, Alloc >::insert(const value_type& val) 
	{

		// empty map
		if (_size == 0)
			return ft::pair<iterator, bool>(placeFirst(val), true);
		/*iterator it = find(val.first);
		if (it != end())
			return ft::pair<iterator, bool>(it, false);*/
		Node *pt = _bt;
		while(1)
		{
			
			if (_cmp(pt->key->first, val.first))
			{
				if (pt->right == NULL || pt->right == _end)
				{
					return ft::pair<iterator, bool>(placeRight(pt, val), true);
				}
				else
					pt = pt->right;
			}
			else if (pt->key->first == val.first)
				return ft::pair<iterator, bool>(end(), false);
			else
			{
				if (pt->left == NULL)
				{
					return ft::pair<iterator, bool>(placeLeft(pt, val), true);
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
		return insert(val).first;
	}
	
	//insert Input iterator
	template < class Key, class T, class Compare , class Alloc >
	template <class InputIt>
	typename ft::enable_if<ft::is_input_iterator<InputIt>, void >::type
	map<Key, T, Compare, Alloc >::insert(InputIt first, InputIt last) 
	{
		while (first != last)
		{
			insert(*first++);
			//std::cerr << size() << "\n";
		}
	}

	//erase
	template < class Key, class T, class Compare , class Alloc >
	void map<Key, T, Compare, Alloc >::erase(iterator position)
	{
		Node * p = position._it;
		
		if (_size == 0)
			return;

		Node * end = _end;
		// no child
		if ((!p->right || p->right == end) && !p->left)
		{
			delCaseZero(p);
			return ;
		}
		// one child
		if (((!p->right || p->right == end) && p->left) || ((p->right && p->right != end) && !p->left))
		{
			delCaseOne(p);
			return;
		}
		// two child
		if ((p->right && p->right != end) && p->left)
		{
			delCaseTwo(p);
			return;
		}
	}

	//erase
	template < class Key, class T, class Compare , class Alloc >
	void map<Key, T, Compare, Alloc >::erase(iterator first, iterator last) 
	{
		while (first != last)
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
			erase(pos);
		return (1);
	}
	
	/*
		** Operations
	*/

	//find
	template < class Key, class T, class Compare , class Alloc >
	typename map<Key, T, Compare, Alloc >::iterator map<Key, T, Compare, Alloc >::find(const key_type& k) 
	{
		Node * cur = _bt;

		while (cur->key->first != k)
		{
			if (_cmp(cur->key->first, k))
				cur = cur->right;
			else
				cur = cur->left;
			
			if (cur == NULL)
				return end();
		}
		return (iterator(cur));

	}

	/*
			**  ** Allocation **  **
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

	template < class K, class T, class Comp , class Alloc >
	typename map<K, T, Comp, Alloc >::iterator map<K, T, Comp, Alloc >::placeRight(Node * pos, const value_type& val) 
	{
		Node * end = pos->right;

		pos->right = newNode();
		pos->right->top = pos;
		pos->right->key = newVal(val);
		pos->right->right = end;
		_size += 1;
		return pos->right;
	}
	
	template < class K, class T, class Comp , class Alloc >
	typename map<K, T, Comp, Alloc >::iterator map<K, T, Comp, Alloc >::placeLeft(Node * pos, const value_type& val) 
	{
		pos->left = newNode();
		pos->left->top = pos;
		pos->left->key = newVal(val);
		_size += 1;
		return pos->left;
	}
	
	template < class K, class T, class Comp , class Alloc >
	typename map<K, T, Comp, Alloc >::iterator map<K, T, Comp, Alloc >::placeFirst(const value_type& val)
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
		pointer pt;
		{
			iterator it(pos);
			it++;
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
		pt = near->key;
		near->key = pos->key;
		pos->key = pt;
		erase(iterator(near));
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
	void map<K, T, Comp, Alloc >::printNode(Node * pos)
	{
		if (pos != NULL)
		{
			if (pos != NULL)
			{
				std::cerr << pos->key->first << "\n";
			}
			else 
				std::cerr << "NULL\n";
			if (pos->left)
				std::cerr << pos->left->key->first << " _ _";
			else
				std::cerr << "NULL _ _";
			if (pos->right)
				std::cerr << pos->right->key->first << "\n";
			else
				std::cerr << "NULL\n";
		}
	}
	
	

} // namespace ft

#endif // __MAP_H__