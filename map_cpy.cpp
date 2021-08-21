#include <iostream>
#include <string>
#include <deque>
#if STD //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	#include <map.hpp>
	#include <stack.hpp>
	#include <vector.hpp>
#endif

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};

#ifndef COUNT
# define COUNT (MAX_RAM / (int)sizeof(Buffer))
#endif

template<typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

int main(int argc, char** argv) {
	
	const int seed =123;
	srand(seed);

	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::stack<int> stack_int;
	ft::vector<Buffer> vector_buffer;
	ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
	ft::map<int, int> map_int;

	/*for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
	ft::vector<Buffer>().swap(vector_buffer);*/


	std::cout << "Map rand insert !" << "\n";
	std::cout << "Max size : " << map_int.max_size() << "\n\n";
	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(ft::make_pair(rand(), rand()));
	}

	
	{
		//ft::map<int, int> copy = map_int;
		ft::map<int, int> cp ;//= map_int;
		/*
		std::cout << "size is : " << map_int.size() << std::endl;
*/		typedef ft::map<int, int>::value_type value_typee;

		for (ft::map<int, int>::iterator it = map_int.begin(); it != map_int.end(); it++)
		{
			//std::cout << it->first << "=>" << it->second << std::endl;
			//cp.insert(cp.begin(), *it);
			//cp.insert(ft::make_pair(rand(), rand()));
			//map_int.upper_bound((*it).first);
			cp.insert(/*cp.begin(),*/ *it);
			//cp.insert(std::make_pair(rand(), i++));
			//cp[it->first] = it->second;
			//value_typee & ref = *it;
			//std::cout << ref.first << "=>" << ref.second << std::endl;
			//std::cout << (*it).first << "=>" << (*it).second << std::endl;
		}
		//cp.insert(map_int.begin(), map_int.end());

		for (ft::map<int, int>::iterator it = cp.begin(); it != cp.end(); it++)
		{
			std::cout << (*it).first << "=>" << (*it).second << std::endl;
		}
		//cp = map_int;
	}
	return (0);
}
