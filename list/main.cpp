#include <string>
#include <iostream>
#include <list>

#include "list.hpp"


int main(int argc, const char** argv)
{	
	int len = 1;
	ft::list<int> de(len, 45);
	std::list<int> std(len, 10);

	std::list<int> empty;

	de.push_front(72);
	std.push_front(85);
	de.push_front(2);
	de.push_front(1);
	de.push_front(5);
	de.push_front(5);
	de.pop_front();
	de.pop_front();
	de.push_back(42);
	de.push_back(78);
	de.push_back(42);
	de.pop_back();
	de.pop_back();
	std.push_front(85);



	auto its = std.begin();
	ft::list<int>::iterator it = de.begin();
	

	std::cout << "front :"<< de.front() << std::endl;
	std::cout << "back :"<< de.back() << std::endl;

	while(it != de.end())
	{
		std::cout << "ft : " << *it++ << "|" << de.size() << std::endl;
		//std::cout << "std: " << *++its << std::endl;
		//std::cout << "Empty :" << *empty.end();
		//std::cout << "Empty :" << *empty.begin();
	} 
	return 0;
}
