#include <iostream>
#include <string>
#include <mutex>
#include <condition_variable>
#include <random>
#include "RSign.h"

extern condition_variable cv;
extern mutex mutexS;

using namespace std;



char RSign::RandomSign(char&Sign1)
{
	for (int i = 0; i < 5; i++) {
		mt19937 gen(random_device().operator()());
		uniform_int_distribution<int> uid(0, 5);
		int j = uid(gen);
		unique_lock<mutex>lk(mutexS);
		cv.wait(lk);
		Sign1=RSign::ArrSigns[j];
		lk.unlock();
	}
		return RSign::ArrSigns[j];
}

