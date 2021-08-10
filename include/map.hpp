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
	};



	/*
		** Constructer & destructor
	*/
	template < class Key, class T, class Compare , class Alloc >
	map<Key, T, Compare, Alloc >::map(const key_compare & cmp, const allocator_type & alloc) : _cmp(cmp), _alloc(alloc), _bt(NULL), _size(0)
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

		while (pt->right != NULL)
			pt = pt->right;

		return iterator(pt);
	}
	
	template < class K, class T, class Comp , class Alloc >
	typename map<K, T, Comp, Alloc >::iterator map<K, T, Comp, Alloc >::end() 
	{
		Node *pt = _bt;

		while (pt->left != NULL)
			pt = pt->left;

		return iterator(pt);
	}

	/*
		** Modifiers
	*/

	template < class Key, class T, class Compare , class Alloc >
	ft::pair<typename map<Key, T, Compare, Alloc >::iterator, bool> map<Key, T, Compare, Alloc >::insert(const value_type& val) 
	{
		if (_bt == NULL)
		{
			_bt = newNode();
			_bt->key = newVal(val);
			_size += 1;
			return ft::pair<iterator, bool>();
		}

		Node *pt = _bt;

		while(1)
		{
			std::cout << "top:" << pt->key->first << std::endl;
			if (_cmp(pt->key->first, val.first))
			{
				if (pt->left == NULL)
				{
					pt->left = newNode();
					pt->top = pt;
					pt->left->key = newVal(val);
					_size += 1;
					return ft::pair<iterator, bool>();
				}
				else
					pt = pt->left;
			}
			else
			{
				if (pt->right == NULL)
				{
					pt->right = newNode();
					pt->top = pt;
					pt->right->key = newVal(val);
					_size += 1;
					return ft::pair<iterator, bool>();
				}
				else
					pt = pt->right;
			}

		}
		
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
	
	

} // namespace ft

#endif // __MAP_H__