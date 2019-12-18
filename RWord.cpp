#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <random>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "RWord.h"

using namespace std;

extern condition_variable cvW;
extern mutex mutexW;

void RWord::AutoFill()
{
	RWord::mp["Monthes"] = { "January","December","February","October","March","May","July","June","Augest","September" };
	RWord::mp["Sport"] = { "Wrestling_freestyle","Athletics","Volleyball","Skiing","Swimming","Sailing","Shooting","Fencing","Ice_hockey","Kayak_slalom" };
	RWord::mp["Countries"] = { "England","Russia","United_States_of_America","Iceland","Scotland","Afghanistan","New_Zeland","Luxemburg","Argentina","Australia" };
	RWord::mp["Capitals"] = { "Beijing","Paris","Copenhagen","Athens","Tegucigalpa","Jerusalem","Abidjan","Valetta","Pyongyang","Montevideo" };
	RWord::mp["Artists"] = { "Cezanne","Turner","Repin","Aivazovsky","Da_Vinci","Michelangelo","Titian","Veneziano","Botticelli","Oliver" };
	RWord::mp["Animals"] = { "Hamster","Piranha","Kinkajou","Tarantula","Leopard","Marten","Hedgehog","Squirrel","Salamander","Tamandua" };
	RWord::mp["Planets"] = { "Mercury","Venus","Earth","Mars","Jupiter","Saturn","Uranus","Moon","Neptune","Pluto" };
	RWord::mp["Fairytales"] = { "Thumbelina","Snow_White","Puss_in_Boots","Rapunzel","Mermaid","Cinderella","Tom_Thumb","Little_Red_Riding_Hood","Nutcracker","Aladdin" };
	RWord::mp["Weapons"] = { "Bazooka","Grenade_Launcher","Revolver","Missile","Bullet","Bayonet","Shotgun","Carbine","Dagger","Assault_rifle" };
	RWord::mp["Wonders"] = { "Temple_of_Artemis","Colossus_at_Rhodes","Gardens_of_Babylon","Statue_of_Zeus","Giza_Pyramid","Pharos_of_Alexandria","Mausoleum_of_Halicarnassus","Great_Wall","Colosseum","Tajmahal" };


}

void RWord::UserFill()
{
	cout << "How many categories would you like to set?";
	cin >> RWord::CatNum;
	cout << "How many versions of each category will be made?";
	cin >> RWord::Version;
	int counter = (RWord::CatNum * RWord::Version) + RWord::CatNum;
	pair<string, vector<string> >pr;
	for (int i = 0; i < counter; i++)
	{
		if (i % (RWord::Version + 1) == 0)
		{
			pr.second = RWord::V;
			mp.insert(pr);
			RWord::V.clear();
			cout << "Enter the category: ";
			cin >>RWord::Answer;
			pr.first = RWord::Answer;
		}
		else
		{
			cout << "Enter the version word: ";
			cin >> RWord::Answer;
			RWord::V.push_back(RWord::Answer);
		}
	}

	pr.second = RWord::V;
	RWord::mp.insert(pr);


}

void RWord::SetMap()
{
	cout << "HELLO! Would you like to fill the map yourself? Enter Yes or No" << endl;
	cin >> RWord::Answer;
	int Ans = 0;
	Ans=(RWord::Answer == "Yes") ? 1 : 0;

	switch (Ans) {
	case 1: RWord::UserFill(); break;
	case 0: RWord::AutoFill(); break;
	}


}

void RWord::GetMap()
{
	map<string, vector<string> >::iterator it;
	for (it = RWord::mp.begin(); it != RWord::mp.end(); it++)
	{
		cout << it->first << ": ";
		for (auto it2 : it->second)
		{
			cout << it2 << " ";
		}
		cout << endl;
	}
}

string RWord::GetCategory()
{
	cout << "Please select the category:" << endl;
	map<string, vector<string> >::iterator it;
	for (it = RWord::mp.begin(); it != RWord::mp.end(); it++)
	{
		cout << it->first << endl;
	}
	cin >> RWord::Category;
	return RWord::Category;
}

string RWord::RandomWord(string&Word1)
{
	for (int i = 0; i < 5; i++) {
		int x = 0;
		mt19937 gen(random_device().operator()());
		uniform_int_distribution<int> uid(0, RWord::Version);
        int count = uid(gen);


		if (RWord::mp.find(RWord::Category) != RWord::mp.end())
		{
			for (auto it2 : RWord::mp.find(RWord::Category)->second)
			{
				if (x == count)
				{
					RWord::Word = it2;
					unique_lock<mutex>lw(mutexW);
					cvW.wait(lw);
					Word1 = RWord::Word;
					lw.unlock();
					break;
				}
				x++;
			}
		}
		
	}
	
		return RWord::Word;
	
}

