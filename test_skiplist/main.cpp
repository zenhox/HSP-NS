#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include "Time.h"
#include <shared_mutex>
using namespace std;

void eventProcessDelay(Time time){
  clock_t start=clock(); 
  clock_t delay= static_cast<double>(time.getValue()) / 1000000000000 * CLOCKS_PER_SEC;
  while(clock()-start < delay);                                                                 
}

void test()
{

	// map<int,int> mp;
	// mp.insert(make_pair(1,1));
	// auto it = mp.begin();
	// mp.insert(make_pair(2,2));
	// it++;
	// mp.insert(make_pair(3,3));
	// mp.insert(make_pair(3,3));
	// mp.insert(make_pair(3,3));
	// mp.insert(make_pair(3,3));
	// mp.insert(make_pair(3,3));
	// mp.insert(make_pair(3,3));
	// mp.insert(make_pair(3,3));
	// mp.insert(make_pair(3,3));
	// mp.insert(make_pair(3,3));
	// mp.insert(make_pair(3,3));
	// mp.insert(make_pair(4,4));
	// cout << it->first << endl;
	// cout << (++it)->first << endl;

}
int main()
{
	test();
}

	/*shared_mutex mtx;
	vector<int> vec(10000000, 1);
	map<int,int> mp;
	for(int i=0; i< 10000000; ++i)
		mp.insert(make_pair(i, i+1));
	clock_t b1 = clock();
	for(auto it = vec.begin(); it != vec.end(); ++it)
	{
	}
	clock_t e1 = clock();
	cout << "vec: " << e1 - b1 << endl;
	clock_t b2 = clock();
	for(auto it = mp.begin(); it != mp.end(); ++it)
	{
	}
	clock_t e2 = clock();
	cout << "mp : " << e2 - b2 << endl;

	*/
