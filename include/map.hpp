#ifndef __MAP_H__
# define __MAP_H__
# include <functional>
# include <utility>
# include <memory>
# include <iterator/map_iterator.hpp>
# include <iterator/iterator.hpp>
# include <other/utility.hpp>


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
			typedef int value_compare;

			typedef	Alloc	allocator_type;
			typedef typename allocator_type::reference 		reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer 		pointer;
			typedef typename allocator_type::const_pointer 	const_pointer;

			typedef map_iterator<value_type>					iterator;
			typedef const_map_iterator<value_type>				const_iterator;
			typedef ft::reverse_iterator<iterator> 		reverse_iterator;
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
			void insert(InputIt first, InputIt last);
			
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
			
			/*
				** Allocation
			*/
			private:
				Node	*newNode(void);
				void	delNode(Node *pt);

				pointer	newVal(const value_type& val);
				bool	placeRight(Node * pos, const value_type& val);
				bool	placeLeft(Node * pos, const value_type& val);
				bool	placeFirst(const value_type& val);

				void	delCaseZero(Node * pos);
				void 	delCaseOne(Node * pos);
				void	delCaseTwo(Node * pos);

				void	printNode(Node *pos);


	};



	/*
		** Constructer & destructor
	*/
	template < class Key, class T, class Compare , class Alloc >
	map<Key, T, Compare, Alloc >::map(const key_compare & cmp, const allocator_type & alloc) : _cmp(cmp), _alloc(alloc), _bt(newNode()), _size(0)
	{
		
	}
	
	template < class K, class T, class Comp , class Alloc >
	map<K, T, Comp, Alloc >::~map() 
	{
		
	}

	/*
		** Iterator
	*/

	template < class K, class T, class Comp , class Alloc >
	typename map<K, T, Comp, Alloc >::iterator map<K, T, Comp, Alloc >::begin() 
	{
		Node *pt = _bt;

		while (pt->left != NULL)
			pt = pt->left;

		return iterator(pt);
	}
	
	template < class K, class T, class Comp , class Alloc >
	typename map<K, T, Comp, Alloc >::iterator map<K, T, Comp, Alloc >::end() 
	{
		Node *pt = _bt;

		while (pt->right != NULL)
			pt = pt->right;

		return iterator(pt);
	}

	/*
		** Modifiers
	*/

	template < class Key, class T, class Compare , class Alloc >
	ft::pair<typename map<Key, T, Compare, Alloc >::iterator, bool> map<Key, T, Compare, Alloc >::insert(const value_type& val) 
	{
		// empty map
		if (begin() == end())
		{	
			placeFirst(val);
			return ft::pair<iterator, bool>();
		}

		Node *pt = _bt;
		while(1)
		{
			if (!_cmp(pt->key->first, val.first))
			{
				if (pt->left == NULL)
				{
					placeLeft(pt, val);
					return ft::pair<iterator, bool>();
				}
				else
					pt = pt->left;
			}
			else
			{
				if (pt->right == NULL)
				{
					placeRight(pt, val);
					return ft::pair<iterator, bool>();
				}
				else
					pt = pt->right;
			}
		}
	}

	template < class Key, class T, class Compare , class Alloc >
	void map<Key, T, Compare, Alloc >::erase(iterator position)
	{
		Node * p = position._it;
		
		if (_size == 0)
			return;
		// no child
		if ((!p->right || p->right == end()) && !p->left)
		{
			std::cout << "case 0\n";
			delCaseZero(p);
			return ;
		}
		// one child
		if (((!p->right || p->right == end()) && p->left) || ((p->right && p->right != end()) && !p->left))
		{
			std::cout << "case 1\n";
			delCaseOne(p);
			return;
		}
		// two child
		if ((p->right && p->right != end()) && p->left)
		{
			std::cout << "case 2\n";
			delCaseTwo(p);
			return;
		}
	}
	
	/*template < class Key, class T, class Compare , class Alloc >
	typename map<Key, T, Compare, Alloc >::size_type map<Key, T, Compare, Alloc >::erase(const key_type& k) 
	{
		
	}
	
*/
	/*
		** Operations
	*/

	template < class Key, class T, class Compare , class Alloc >
	typename map<Key, T, Compare, Alloc >::iterator map<Key, T, Compare, Alloc >::find(const key_type& k) 
	{
		iterator it = begin();

		while (it != end())
		{
			if (it->first == k)
				return it;
			++it;
		}
		return it;
	}

	/*
		** Allocation
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
	bool map<K, T, Comp, Alloc >::placeRight(Node * pos, const value_type& val) 
	{
		Node * end = NULL;

		iterator it(pos->right);
		if (it == this->end())
			end = pos->right;

		pos->right = newNode();
		pos->right->top = pos;
		pos->right->key = newVal(val);
		pos->right->right = end;
		_size += 1;
		return true;
	}
	
	template < class K, class T, class Comp , class Alloc >
	bool map<K, T, Comp, Alloc >::placeLeft(Node * pos, const value_type& val) 
	{
		pos->left = newNode();
		pos->left->top = pos;
		pos->left->key = newVal(val);
		_size += 1;
		return true;
	}
	
	template < class K, class T, class Comp , class Alloc >
	bool map<K, T, Comp, Alloc >::placeFirst(const value_type& val)
	{
		Node * end = _bt;

		_bt = newNode();
		_bt->key = newVal(val);
		_size += 1;
		_bt->right = end;
		_bt->right->top = _bt;

		return true;
	}
	
	template < class K, class T, class Comp , class Alloc >
	void map<K, T, Comp, Alloc >::delCaseZero(Node * pos) 
	{
		Node * isend = pos->right;

		if (pos->top->right == pos)
		{
			pos->top->right = isend;
		}
		else if (pos->top->left == pos)
			pos->top->left = NULL;
		_alloc.destroy(pos->key);
		_alloc.deallocate(pos->key, 1);
		_size -= 1;
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
		printNode(pos->top);
		printNode(pos);
		printNode(child);
		_alloc.destroy(pos->key);
		_alloc.deallocate(pos->key, 1);
		_size -= 1;
	}
	
	template < class K, class T, class Comp , class Alloc >
	void map<K, T, Comp, Alloc >::delCaseTwo(Node * pos)
	{
		Node *near;
		Node * left;
		Node * right;
		{
			iterator it(pos);
			it++;
			if (it != end())
			{
				near = it._it;
				left = pos->left;
				right = near->right;
			}
			else
			{
				iterator it(pos);
				it--;
				near = it._it;
				left = near->left;
				right = pos->right;
			}
			if (near->top->right == near)
				near->top->right = NULL;
			else if (near->top->left == near)
				near->top->left = NULL;
		}
		near->top = pos->top;
		near->left = left;
		if (near->left)
			near->left->top = near;
		near->right = right;
		if (near->right)
			near->right->top = near;
		_alloc.destroy(pos->key);
		_alloc.deallocate(pos->key, 1);
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