#include <iostream>
#include <string>
#include <vector>

#ifndef NS //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <utility>
	namespace ft = std;
#else
	#include <map.hpp>
	#include <other/utility.hpp>
#endif

#ifndef SEED
	# define SEED 10
#endif

#ifndef LEN
	# define LEN rand() % 1000000
#endif

#include "map_test.hpp"

int main(void)
{
	srand(SEED);

	{
		ft::map<int, int> mymap;
		ft::map<int, int> mymap2;
		size_t len = LEN;
		for( size_t i = 0; i < len; i++)
		{
			mymap.insert(ft::pair<int, int>(rand(), (int)rand()));
			mymap2.insert(ft::pair<int, int>(rand(), (int)rand()));
		}
		cmp(mymap, mymap2);
		cmp(mymap2, mymap);
		printSize(mymap);
		printSize(mymap2);

		erase_key(mymap2);
		erase_key(mymap);

		for (size_t i =0; i < 10; i++)
			test_bound(mymap, rand());

		cmp(mymap, mymap2);
		cmp(mymap2, mymap);
		printSize(mymap);
		printSize(mymap2);

		ft::map<int, int> clear_map;

		mymap.swap(clear_map); //mymy is clear

		printSize(mymap);

		clear_map.clear();
		mymap.clear(); //clear clear map

		printSize(mymap);
		printSize(clear_map);

	}

	//iterator compile
	{
		std::vector<ft::pair<int, int> > arr;

		for (int i = 0; i != 100; i++)
			arr.push_back(ft::make_pair(rand(), rand()));
	

		ft::map<int, int> mymap(arr.begin(), arr.end());


		ft::map<int, int>::iterator a; //default
		
		a = mymap.begin(); //operator=
		
		ft::map<int, int>::iterator b(a++); //copy

		std::cout << "b == a " << (b == a) << std::endl;
		std::cout << "b != a " << (b != a) << std::endl;

		std::cout << b->first << " => " << (*b).second << std::endl; // a-> *a

		++b;
		b++;

		std::cout << (*b).first << " => " << (*b++).second << std::endl; 
		std::cout << b->first << " => " << (*b).second << std::endl;

		--b;
		b--;
		std::cout << "b == a " << (*b-- == *a) << std::endl;

		b->second = rand();
		std::cout << b->first << " => " << (*b).second << std::endl;
		//*b = ft::make_pair<const int, int>(rand(), rand()); error


		ft::map<int, int>::const_iterator ca;

		ca = a;

		ft::map<int, int>::const_iterator cb(b);

		std::cout << cb->first << " => " << (*cb).second << std::endl;
		
	}
	return 0;
}