#include <iostream>
#include <string>
#include <stdlib.h>

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

template <class V>
size_t rand_size(const V& v)
{
	if (v.size() == 0)
		return 0;
	size_t ret = rand() % (v.size());

	if ( ret > v.size() )
		return 0;
	return ret;
}

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

		ft::vector<int> vct2(vct1.begin(), vct1.begin() + (rand_size(vct1))); // range constructor

		ft::vector<int> vct3(vct1); // cpy constructor
		ft::vector<int> vct4;

		vct3.assign(vct1.begin(), vct1.begin() + (rand_size(vct1))); //range

		vct4.assign(vct3.size(), rand()); //fill


		cmp(vct3, vct1);
		cmp(vct3, vct2);
		cmp(vct2, vct1);
		printfb(vct2);
		printfb(vct1);

		vct4.erase(vct4.begin() + rand_size(vct4)); //erase pos

		vct3.erase(vct3.begin(), vct3.begin() + rand_size(vct3)); //erase range

		vct3.insert(vct3.begin() + rand_size(vct3), rand()); // insert single el 
		vct3.insert(vct3.begin() + (rand() % vct3.size()), rand() % 1000, rand()); // insert fill
		vct3.insert(vct3.end(), vct1.begin(), vct1.begin() + (rand() % vct1.size())); //insert range

		ft::swap(vct3, vct4);


		printSize(vct1, false);
		printSize(vct2, false);
		printSize(vct3, false);
		printSize(vct4, false);


		print_it(vct4.rbegin(), vct4.rend());
		
		ft::vector<int>::const_iterator first = vct3.begin();
		ft::vector<int>::const_iterator last = vct3.end();
		print_it(first, last);


	}
	
	{
		ft::vector<std::string> vct1;

		
		std::string str = "A";
		size_t len = rand() % 250;
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
			size_t index = rand() % vct2.size();

			std::cout << index << " | " << vct2.size() << std::endl;
			vct3.push_back(vct2[index]);
		}
		erase_rand_el(vct2, rand_size(vct2));

		cmp(vct1, vct2);

		insert_rand_el(vct2, vct1.size() - vct2.size(), "A");

		cmp(vct1, vct2);


		cmp(vct1, vct2);
		cmp(vct1, vct3);
		cmp(vct3, vct2);

		printSize(vct1);
		printSize(vct2);
		printSize(vct3);

	}
 
	// iterator compile test

	{
		std::cout << "######################it#######################" << std::endl;
		ft::vector<int> v(100, 100);

		ft::vector<int>::iterator it, it3; it = v.begin(); //default
		ft::vector<int>::iterator it2(it); // cpy
		it3 = it;

		std::cout << (it == it3) << " " << (it2 != it) << std::endl;
		std::cout << *it << " " << std::endl;

		*it2 = 200;
		it2++;
		++it;
		*it++ = 25;

		it[25] = 756;
		{
			ft::vector<int>::iterator rit = v.begin() + 5;
			*rit = 15;

			rit = 5 + v.begin();
			std::cout << (*rit == 15) << ((rit - 5) == v.begin());
			rit += 15;
			std::cout << (*rit == 15) << ((rit - 5) == v.begin());
			rit -= 12;
			std::cout << (*rit == 15) << ((rit - 5) == v.begin());
		}

		std::cout << "size is : " << v.end() - v.begin() << std::endl;

		cmp(it, it2);

		printSize(v);

		// const_it

		ft::vector<int>::const_iterator cit;

		it = v.begin();
		cit = v.begin();

		std::cout << (it == cit) << std::endl;
		cit += 5;
		std::cout << (it != cit) << std::endl;
		cit -= 3;
		std::cout << *cit << std::endl;

		cit = 5 + v.begin();
		std::cout << *cit << std::endl;
		cit = v.begin() + 3;
		std::cout << *cit << std::endl;
		cit = v.end() - 5;
		std::cout << *cit << std::endl;


		ft::vector<int>::const_iterator cit2(v.end());
		cit = v.begin();
		std::cout << "size is :" << (cit2 - cit) << std::endl;
		
		std::cout << cit[6];
		
		//*cit = 5 // error; 
		cit++;
		++cit;
		std::cout << *cit++ << std::endl;

		cit--;
		--cit;
		std::cout << *cit-- << std::endl;
		cit2 = v.end() - 5;

		cmp(cit, cit2);

		// reverse_it;
		
		std::cout << "######################reverse it#######################" << std::endl;
		ft::vector<int>::reverse_iterator rit(v.rbegin()); //from it
		ft::vector<int>::reverse_iterator rit2; //default

		rit2 = v.rbegin();

		*rit = 55;
		std::cout << *rit << std::endl;

		rit = rit2 + 6;
		std::cout << *rit << std::endl;
		rit = 5 + rit2;


		std::cout << *rit++ << std::endl;
		std::cout << *rit << std::endl;

		rit2 = v.rend() - 6;
		std::cout << *rit2-- << std::endl;
		std::cout << *rit2 << std::endl;

		std::cout << (v.begin())[12] << std::endl;
		
		rit += 5;
		rit -= 3;
		std::cout << *rit << std::endl;

		cmp(rit, rit2);

		ft::vector<int>::const_reverse_iterator rit3(v.rbegin());
		
		cmp(rit, rit3); // cmp const_reverse_it with reverse_it

		std::cout << "size is :" << (v.rend() - v.rbegin()) << std::endl;

	}


	return 0;
}