#include <stack>
#include <string>
#include <iostream>

#include <stack.hpp>

int main(int argc, char const *argv[])
{
	std::stack<int> stck;

	stck.empty();
	
	ft::stack<int> mst;
	ft::stack<int> foo;


	std::cout << "== :" << mst.empty() << std::endl;
	if (mst == foo)
		std::cout << "true\n";
	
	return 0;
}
