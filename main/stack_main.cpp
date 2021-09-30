#include <iostream>
#include <string>
#include <stdlib.h>

#ifndef NS //CREATE A REAL STL EXAMPLE
	#include <stack>
	#include <utility>
	#include <vector>
	namespace ft = std;
#else
	#include <vector.hpp>
	#include <stack.hpp>
	#include <other/utility.hpp>
#endif

#ifndef SEED
	# define SEED 10
#endif

#ifndef LEN
	# define LEN rand() % 1000000
#endif

#include "stack_test.hpp"
#include <deque>
#include <list>

int main()
{
	srand(SEED);


	{
		ft::stack<int, ft::vector<int> > stack_int;
		ft::stack<int, ft::vector<int> > stack_int2;

		printSize(stack_int);
		printSize(stack_int2);
		
		for (size_t i = 0; i != LEN; i++)
		{
			stack_int.push(rand());
			stack_int2.push(rand());
		}

		printSize(stack_int);
		printSize(stack_int2);

		printfb(stack_int);		
		printfb(stack_int2);

		cmp(stack_int2, stack_int);		

	}


	{
		ft::stack<int, std::deque<int> > stack_int;
		ft::stack<int, std::deque<int> > stack_int2;

		printSize(stack_int);
		printSize(stack_int2);
		
		for (size_t i = 0; i != LEN; i++)
		{
			stack_int.push(rand());
			stack_int2.push(rand());
		}

		printSize(stack_int);
		printSize(stack_int2);

		printfb(stack_int);		
		printfb(stack_int2);

		cmp(stack_int2, stack_int);		

	}

	{
		ft::stack<int, std::list<int> > stack_int;
		ft::stack<int, std::list<int> > stack_int2;

		printSize(stack_int);
		printSize(stack_int2);
		
		for (size_t i = 0; i != LEN; i++)
		{
			stack_int.push(rand());
			stack_int2.push(rand());
		}

		printSize(stack_int);
		printSize(stack_int2);

		printfb(stack_int);		
		printfb(stack_int2);

		cmp(stack_int2, stack_int);		

	}

		{
		ft::stack<char, ft::vector<char> > stack_int;
		ft::stack<char, ft::vector<char> > stack_int2;

		printSize(stack_int);
		printSize(stack_int2);
		
		for (size_t i = 0; i != LEN; i++)
		{
			stack_int.push((char)rand());
			stack_int2.push((char)rand());
		}

		printSize(stack_int);
		printSize(stack_int2);

		printfb(stack_int);		
		printfb(stack_int2);

		cmp(stack_int2, stack_int);		

	}
	return 0;
}