#ifndef __VECTOR_ITERATOR_H__
#define __VECTOR_ITERATOR_H__

namespace ft
{
		template < class _Tp, class Reference, class Pointer >
		class vector_iterator
		{
			
			public:
			typedef	vector_iterator<_Tp, Reference, Pointer>			_Self;
			typedef	_Tp								value_type;
			typedef Pointer							pointer;
			typedef Reference							reference;
			typedef _Self							iterator_type;
			typedef std::random_access_iterator_tag iterator_category;
			typedef std::ptrdiff_t 					difference_type;
			typedef size_t							size_type;
			typedef vector_iterator<_Tp, const _Tp&, const _Tp*> 	if_const;
			
			vector_iterator() : _add(NULL) {}

			explicit vector_iterator(pointer src) : _add(src) {}

			vector_iterator(const vector_iterator & src) { *this = src; }

			~vector_iterator() {}

			operator if_const() const { return if_const(_add); }
			
			reference	operator*() const { return *_add; }
			pointer		operator->() const { return _add; }

			reference operator[](size_type n) { return *(_add + n); }
			//const_reference operator[](size_type n) const;

			vector_iterator & operator=(const vector_iterator& ref)
			{
				_add = ref._add;
				return *this;
			}
	

			/* operator + */

			vector_iterator operator+(const difference_type & n) const { return vector_iterator(_add + n); }
			friend vector_iterator operator+(const difference_type n, const vector_iterator &x) { return vector_iterator(x._add + n); }

			/* operator - */
			
			vector_iterator operator-(const difference_type & n) const { return vector_iterator(_add - n); }
			difference_type operator-(const vector_iterator & n) const { return (_add - n._add); }

			
			vector_iterator& operator+=(const difference_type & n) { _add += n;	return *this; }
			vector_iterator& operator-=(const difference_type & n) { _add -= n; return *this; }
			
			/* operator ++ / -- */

			_Self& operator++()
			{
				++_add;
				return *this;
			}

			_Self operator++(int)
			{
				_Self _tmp = *this;
				++*this;
				return _tmp;
			}

			_Self& operator--()
			{
				--_add;
				return *this;
			}

			_Self operator--(int)
			{
				_Self _tmp = *this;
				--*this;
				return _tmp;
			}

			bool operator==(const if_const& x) const { return _add == x._add;}
			bool operator!=(const if_const& x) const { return _add != x._add;}
			bool operator<(const if_const& x) const { return _add < x._add;}
			bool operator>(const if_const& x) const { return _add > x._add;}
			bool operator<=(const if_const& x) const { return _add <= x._add;}
			bool operator>=(const if_const& x) const { return _add >= x._add;}

			public:
				pointer		_add;
		};
}


#endif // __VECTOR_ITERATOR_H__