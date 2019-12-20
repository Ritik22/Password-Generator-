
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <random>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "RWord.h"
#include "RSign.h"

mutex mutexS, mutexW, mutexN; 
condition_variable cv,cvN,cvW,cvx;


using namespace std;


char RandomNumber(char& Number)                     //Creating random numbers
{
	for (int i = 0; i < 5; i++) {
		mt19937 gen(random_device().operator()());
		uniform_int_distribution<int> uid(0, 9);
		int Num = uid(gen);
		unique_lock<mutex>lk(mutexN);       //Blocking the acess to the Number variable
		cvN.wait(lk);
		Number = (Num + '0');
		lk.unlock();
		}
	return Number;
}
void Password( string&Word1 , char&Sign1 ,  char&Number) {          
	for (int i = 0; i < 6; i++) {
		unique_lock<mutex>lW(mutexW);
		string SW = Word1;                          //In order to less block the Word1, we create a new string type variable
		lW.unlock();
		cvW.notify_one();

		size_t WordSize = SW.size();                //Randomly choosing the places for the random number and sign
		srand(time(0));
		int SignPlace = (rand() % WordSize);
		int NumberPlace = (rand() % WordSize);

		unique_lock<mutex>lS(mutexS);
		SW.insert(SignPlace, 1, Sign1);
		lS.unlock();
		cv.notify_one();

		unique_lock<mutex>lN(mutexN);
		SW.insert(NumberPlace, 1, Number);
		lN.unlock();
		cvN.notify_one();
		
		cout << SW << endl<<endl;        //exept of printing the passwords can stringht be inserted in the set to avoid 
		                                 //the same password appearence
		

	}
}



int main()
{
	
	char Sign1;
    char Number;
	string Word1 = "";

	RWord A;                         //Setting the map, asking the user to select the category and then filling the map
	A.SetMap();
	A.GetCategory();
	RSign B;
	
	Number = '1';                     //This variable we need to activate the thread t3, couse it is the main blocking thread
	Sign1 = '@';
	Word1 = "September";
	
	thread t1(&RWord::RandomWord, A,ref(Word1));
	thread t2(&RSign::RandomSign, B,ref(Sign1));
	thread t4(RandomNumber, ref(Number));
	thread t3(Password, ref(Word1), ref(Sign1), ref(Number));
	t1.join();
	t2.join();
	t4.join();
	t3.join();
	
	

	return 0;
}

