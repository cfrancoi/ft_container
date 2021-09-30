#ifndef __VECTOR_TEST_H__
#define __VECTOR_TEST_H__



template <typename T_VEC>
void	printSize(T_VEC const &mp, bool print_content = 1)
{
	std::cout << "size: " << mp.size() << std::endl;
	//std::cout << "max_size: " << mp.max_size() << std::endl;
	std::cout << "capacity :" << mp.capacity() << std::endl;
	std::cout << "empty : " << mp.empty() << std::endl;
	if (print_content && !mp.empty())
	{
		typename T_VEC::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << *it << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

template<class T_VEC>
void	erase_rand_el(T_VEC & v, size_t n)
{
	for (size_t i = 0; i < n; i++)
	{
		v.erase(v.begin() + rand() % v.size());
	}
}

template<class T_VEC, class T>
void	insert_rand_el(T_VEC & v, size_t n, const T & x)
{
	for (size_t i = 0; i < n; i++)
	{
		v.insert(v.begin() + rand() % v.size(), x);
	}
}

template<class IT>
void	print_it(IT first, IT last)
{
	for (; first != last; first++)
	{
		std::cout << *first << std::endl;
	}
	std::cout << "###############################################]" << std::endl;
}

template <typename T_VEC>
void	printfb(T_VEC const &v)
{
	if (v.empty())
	{
		std::cout << "is empty\n";
		return;
	}
	std::cout << "front :" << v.front() << std::endl;
	std::cout << "back :" << v.back() << std::endl;
}

template <class v>
void	cmp(const v &lhs, const v &rhs)
{
	static int i = 0;

	std::cout << "############### [" << i++ << "] ###############"  << std::endl;
	std::cout << "eq: " << (lhs == rhs) << " | ne: " << (lhs != rhs) << std::endl;
	std::cout << "lt: " << (lhs <  rhs) << " | le: " << (lhs <= rhs) << std::endl;
	std::cout << "gt: " << (lhs >  rhs) << " | ge: " << (lhs >= rhs) << std::endl;
}


template <class r, class l>
void	cmp(const r &lhs, const l &rhs)
{
	static int i = 0;

	std::cout << "############### [" << i++ << "] ###############"  << std::endl;
	std::cout << "eq: " << (lhs == rhs) << " | ne: " << (lhs != rhs) << std::endl;
	std::cout << "lt: " << (lhs <  rhs) << " | le: " << (lhs <= rhs) << std::endl;
	std::cout << "gt: " << (lhs >  rhs) << " | ge: " << (lhs >= rhs) << std::endl;
}

#endif // __VECTOR_TEST_H__