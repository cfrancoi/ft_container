#ifndef __MAP_H__
# define __MAP_H__
# include <functional>
# include <utility>
# include <memory>

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>, class alloc = std::allocator< std::pair<const Key, T> > >
	class map
	{
		public:

			// Member types
			typedef Key		key_type;
			typedef T		mapped_type;
			typedef std::pair<const Key, T> value_type;
			typedef Compare			key_compare;

			typedef	alloc	allocator_type;
			typedef allocator_type::reference 		reference;
			typedef allocator_type::const_reference const_reference;
			typedef allocator_type::pointer 		pointer;
			typedef allocator_type::const_pointer 	const_pointer;

			typedef Map_iterator 								iterator;
			typedef Const_Map_iterator 							const_iterator;
			typedef ft::reverser_iterator<Map_iterator> 		reverse_iterator;
			typedef ft::reverser_iterator<Const_Map_iterator> 	const_reverse_iterator;

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
				** Element acces
			*/

	};
	

} // namespace ft

#endif // __MAP_H__