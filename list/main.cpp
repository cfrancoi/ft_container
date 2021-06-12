#include <string>
#include <iostream>
#include <list>

#include "list.hpp"


int main(int argc, const char** argv)
{	
	int len = 12;
	ft::list<int> de(len, 10);
	std::list<int> std(len, 10);

	std::list<int> empty;

	//de.push_front(85);
	std.push_front(85);
	//de.push_front(85);
	std.push_front(85);

	auto its = std.begin();
	ft::list<int>::iterator it = de.begin();


	while(it != de.end())
	{

		//std::cout << "std: " << *its++ << std::endl;
		//std::cout << "Empty :" << *empty.end();
		//std::cout << "Empty :" << *empty.begin();
		std::cout << "ft : " << *it++ << "|" << de.size() << std::endl;
	} 
	return 0;
}
