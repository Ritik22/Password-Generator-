#pragma once
#include <iostream>

using namespace std;
 
class RSign
{private:
	char ArrSigns[6] = { '!','%','$','@','&','*' };
	int j = 0;
	
public:
	RSign(){};
	char RandomSign(char&Sign1);
	~RSign() {};
};

