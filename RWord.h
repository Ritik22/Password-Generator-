#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

class RWord
{
private:
	map<string, vector<string> >mp;
	vector<string>V;
	string Answer;
	string Category;
	string Word;
	int CatNum = 0;
	int Version;
	void AutoFill();
	void UserFill();
	


public:
	
	RWord():V { "" }, Word{ "" }, Answer{ "" }, Category{ "" }, CatNum{ 0 }, Version{ 10 } {};
	
	void SetMap();
	void GetMap();
	string GetCategory();
	string RandomWord(string&Word1);
	
	~RWord() {};
	
};

