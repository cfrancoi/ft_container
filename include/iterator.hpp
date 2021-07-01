#ifndef __ITERATOR_H__
#define __ITERATOR_H__

namespace ft
{
    /*
        ** Reverse itarator
    */
    template <class Iter>
    class reverse_iterator
    {       
        public:
            
        	typedef	typename Iter::value_type			    value_type;
			typedef typename Iter::pointer			        pointer;
			typedef typename Iter::reference		        reference;
			typedef typename Iter::iterator_type		    iterator_type;
			typedef typename Iter::iterator_category        iterator_category;
			typedef typename Iter::difference_type          difference_type;
            typedef reverse_iterator<Iter>                  _Self;

            reverse_iterator<Iter>() : _it() {}

            reverse_iterator<Iter>(const Iter & src) : _it(src) {}

            reverse_iterator<Iter>(const _Self & src) { *this = src; }

            ~reverse_iterator<Iter>() {}


            reference	operator*() { return *_it; }
			pointer		operator->() { return _it.operator->(); }
            
            _Self& operator=(const _Self & ref)
			{
				_it = ref._it;
				return *this;
			}

            _Self& operator++()
			{
				--_it;
				return *this;
			}

			_Self operator++(int)
			{
                _it--;
                return *this;
			}

			_Self& operator--()
			{
                ++_it;
				return *this;
			}

			_Self operator--(int)
			{
                _it++;
				return *this;
			}

			friend
			bool operator!=(const _Self& __x, const _Self& __y) { return (__x._it != __y._it); }
			friend
			bool operator==(const _Self& __x, const _Self& __y) { return (__x._it == __y._it); }

            private:
                Iter _it;
    };


};
#endif // __ITERATOR_H__