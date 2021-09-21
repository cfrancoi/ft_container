#include <iostream>
#include <string>

#ifndef NS //CREATE A REAL STL EXAMPLE
	#include <vector>
	#include <utility>
	namespace ft = std;
#else
	#include <vector.hpp>
	#include <other/utility.hpp>
#endif

#ifndef SEED
	# define SEED 10
#endif

#ifndef LEN
	# define LEN rand() % 1000000
#endif

#include "vector_test.hpp"

int main()
{
	srand(SEED);

	/* ********* */ // reserve() cmp() ope=() insert(rand_len) at() exception

	{	
		ft::vector<int> vct; //default const

		try
		{
			for (int i = 0; i < 1000; i++)
			{
				const int idx = rand() % LEN;
				vct.at(idx);
				std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" << std::endl;
			}
		}
		catch(const std::exception& e)
		{
			//NORMAL ! :P
		}

		for(int i =0; i < LEN; i++)
		{
			vct.insert(vct.end(), rand());
		}

		vct.reserve(vct.capacity() + 2);
		printSize(vct);
		ft::vector<int> cpy = vct; // cpy
		printSize(cpy);
		cmp(vct, cpy); // cmp cpy
		cpy.clear();
		cmp(vct, cpy); //cmp with empty
	}

	/* ******** */ // at() swap() empty() capacity() pop_back()...

	{
		ft::vector<int> vct1;
		ft::vector<int> vct2;

		for(int i =0; i < 125; i++)
		{
			vct1.insert(vct1.end(), rand());
		}
		//vct2 = vct1;

		vct2.swap(vct1);

		std::cout << "Now vct1 is clear :" << vct1.empty();

		vct1 = vct2;

		printSize(vct1);
		printSize(vct2);

		cmp(vct1, vct2);

		for(int i =0; i < 25; i++)
		{
			vct2[i] = rand();
		}

		for(int i =25; i < 50; i++)
		{
			vct2.at(i) = rand();
		}

		cmp(vct2, vct1);

		vct2.pop_back();
		vct2.pop_back();
		vct2.pop_back();
		vct2.pop_back();

		cmp(vct2, vct1);

	}

	/* ******** */  //fill_constructor pop_back() push_back() resize() cmp()

	{
		ft::vector<int> vct1(10, rand());
		ft::vector<int> vct2(10, rand());

		cmp(vct2, vct1);
		vct2.pop_back();
		cmp(vct2, vct1);
		vct2.push_back(rand());
		cmp(vct2, vct1);
		vct2.push_back(rand());
		vct2.push_back(rand());
		cmp(vct2, vct1);

		size_t n_len = rand() % 100;
		vct2.resize(n_len, rand());
		vct1.resize(n_len);
		cmp(vct2, vct1);
		printSize(vct2);
		printSize(vct1);
		
	}
	

	/* ******** */ //range_constructor front() back()

	{
		ft::vector<int> vct1;

		for(int i =0; i < LEN; i++)
		{
			vct1.insert(vct1.end(), rand());
		}

		ft::vector<int> vct2(vct1.begin(), vct1.begin() + (rand() % LEN)); // range constructor

		ft::vector<int> vct3(vct1); // cpy constructor
		ft::vector<int> vct4;

		vct3.assign(vct1.begin(), vct1.begin() + (rand() % LEN)); //range

		vct4.assign(rand() % vct3.size(), rand());


		cmp(vct3, vct1);
		cmp(vct3, vct2);
		cmp(vct2, vct1);
		printfb(vct2);
		printfb(vct1);

		vct4.erase(vct4.begin() + (rand() % vct4.size())); //erase pos

		vct3.erase(vct3.begin(), vct3.begin() + (rand() % vct3.size())); //erase range

		vct3.insert(vct3.begin() + (rand() % vct3.size()), rand()); // insert single el 
		vct3.insert(vct3.begin() + (rand() % vct3.size()), rand() % 1000, rand()); // insert fill
		vct3.insert(vct3.end(), vct1.begin(), vct1.begin() + (rand() % vct1.size())); //insert range

		ft::swap(vct3, vct4);


		printSize(vct1);
		printSize(vct2);
		printSize(vct3);
		printSize(vct4);


		print_it(vct4.rbegin(), vct4.rend());
		
		ft::vector<int>::const_iterator first = vct3.begin();
		ft::vector<int>::const_iterator last = vct3.end();
		print_it(first, last);


	}
	//other type

	{
		ft::vector<std::string> vct1;

		std::string str = "A";
		size_t len = rand() % 120;
		for (size_t i = 0; i < len; i++)
		{
			str += static_cast<char>(rand() % 127 + 'A');
			vct1.push_back(str);
		}

		printSize(vct1);

		ft::vector<std::string> vct2(vct1);

		cmp(vct1, vct2);

		ft::vector<std::string> vct3;

		for (size_t i = 0; i < len; i++)
		{
			vct3.push_back(vct2[rand() % vct2.size()]);
		}

		vct2.erase(vct2.begin() + rand() % vct2.size());
		vct2.erase(vct2.begin() + rand() % vct2.size());
		vct2.erase(vct2.begin() + rand() % vct2.size());
		vct2.erase(vct2.begin() + rand() % vct2.size());

		cmp(vct1, vct2);
		
		vct2.clear();

		cmp(vct1, vct2);
		cmp(vct1, vct3);
		cmp(vct3, vct2);

		printSize(vct1);
		printSize(vct2);
		printSize(vct3);


		
	}

	return 0;
}