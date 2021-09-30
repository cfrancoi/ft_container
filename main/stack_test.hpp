#ifndef __STACK_TEST_H__
#define __STACK_TEST_H__


template <typename T_VEC>
void	printfb(T_VEC const &v)
{
	if (v.empty())
	{
		std::cout << "is empty\n";
		return;
	}
	std::cout << "top :" << v.top() << std::endl;
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


template <typename T_STCK>
void	printSize(T_STCK const &mp)
{
	std::cout << "size: " << mp.size() << std::endl;
	std::cout << "empty : " << mp.empty() << std::endl;
	std::cout << "###############################################" << std::endl;
}

#endif // __STACK_TEST_H__