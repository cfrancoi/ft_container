#ifndef __MAP_H__
# define __MAP_H__
# include <functional>
# include <utility>
# include <memory>
# include <iterator.hpp>

namespace ft
{
	template < class _Tp >
	class const_map_iterator;

	template < class _Tp >
	class map_iterator;



	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator< std::pair<const Key, T> > >
	class map
	{
		public:

			// Member types
			typedef Key		key_type;
			typedef T		mapped_type;
			typedef std::pair<const Key, T> value_type;
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
			std::pair<iterator, bool> insert(const value_type& val);
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

	};
	

} // namespace ft

#endif // __MAP_H__