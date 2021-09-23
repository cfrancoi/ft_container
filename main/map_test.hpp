#ifndef __MAP_TEST_H__
#define __MAP_TEST_H__

#include <iostream>
#include <string>

template<typename Iter>
std::string	printPair(Iter &it)
{
	std::cout << it->first << " => " << it->second;
	return ("");
}

template <typename T_MAP>
void	printSize(T_MAP const &mp, bool print_content = 0)
{
	std::cout << "size: " << mp.size() << std::endl;
	//std::cout << "max_size: " << mp.max_size() << std::endl;
	if (print_content)
	{
		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

template <class MAP>
void test_bound(MAP &mp ,const typename MAP::key_type &k)
{
	typedef typename MAP::iterator iterator;

	iterator it; 
	it = mp.lower_bound(k);
	std::cout << "lower bound = ";
	if (it == mp.end())
		std::cout << "end()";
	else
		printPair(it);
	std::cout << std::endl;

	it = mp.upper_bound(k);
	std::cout << "upper bound = ";
	if (it == mp.end())
		std::cout << "end()";
	else
		printPair(it);
	std::cout << std::endl;

	ft::pair<iterator,iterator> ret;

	ret = mp.equal_range(k);
	std::cout << "equal_range = ";
	if (ret.first == mp.end())
		std::cout << "end()";
	else
		printPair(ret.first);
	std::cout << ", ";
	if (ret.second == mp.end())
		std::cout << "end()";
	else
		printPair(ret.second);

	std::cout << std::endl;
	std::cout << "###############################################" << std::endl;
}


template <class MAP>
void test_const_bound(MAP &mp ,const typename MAP::key_type &k)
{
	typedef typename MAP::const_iterator iterator;

	iterator it; 
	it = mp.lower_bound(k);
	std::cout << "lower bound = ";
	if (it == mp.end())
		std::cout << "end()";
	else
		printPair(it);
	std::cout << std::endl;

	it = mp.upper_bound(k);
	std::cout << "upper bound = ";
	if (it == mp.end())
		std::cout << "end()";
	else
		printPair(it);
	std::cout << std::endl;

	ft::pair<iterator,iterator> ret;

	ret = mp.equal_range(k);
	std::cout << "equal_range = ";
	if (ret.first == mp.end())
		std::cout << "end()";
	else
		printPair(ret.first);
	std::cout << ", ";
	if (ret.second == mp.end())
		std::cout << "end()";
	else
		printPair(ret.second);

	std::cout << std::endl;
	std::cout << "###############################################" << std::endl;
}

template <class MAP>
void	cmp(const MAP &lhs, const MAP &rhs)
{
	std::cout << "eq: " << (lhs == rhs) << " | ne: " << (lhs != rhs) << std::endl;
	std::cout << "lt: " << (lhs <  rhs) << " | le: " << (lhs <= rhs) << std::endl;
	std::cout << "gt: " << (lhs >  rhs) << " | ge: " << (lhs >= rhs) << std::endl;
	std::cout << "###############################################" << std::endl;
}

template <class MAP, class value_type>
void	test_simple_insert(MAP &mp, value_type add)
{
	typedef typename MAP::const_iterator iterator;
	
	ft::pair<iterator, bool> ret_insert;
	ret_insert = mp.insert(add);
	if (ret_insert.first != mp.end())
		std::cout << "value :" << ret_insert.first->first;
	else
		std::cout << "end()";
	std::cout << " is add " << ret_insert.second << '\n';
	ret_insert = mp.insert(add);
	
	if (ret_insert.first != mp.end())
		std::cout << "value :" << ret_insert.first->first;
	else
		std::cout << "end()";
	std::cout << " is add " << ret_insert.second << '\n';
	std::cout << "###############################################" << std::endl;

}

template <class MAP, class ite>
void	test_range_insert(MAP &mp, ite begin, ite end)
{
	mp.insert(begin, end);
	std::cout << "###############################################" << std::endl;

}

//ersase n rand key
template <class MAP>
void	erase_key(MAP &mp, size_t len = 10000)
{
	size_t ret = 0;
	for (size_t i = 0; i != len; i++)
		ret += mp.erase(rand() % 10000);
	std::cout << "erased key :" << ret << std::endl;
	std::cout << "###############################################" << std::endl;
}

#endif // __MAP_TEST_H__