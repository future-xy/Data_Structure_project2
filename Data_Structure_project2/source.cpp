#include<iostream>
#include<fstream>
#include<tuple>
#include<string>

#include"Airport.h";

//留给大佬的
using std::tuple;
using std::string;
using std::to_string;
using std::get;
using std::cout;
using std::cin;
using std::endl;

void Ini(Airport& myairport, unsigned int& time, double& e1, double& e2, bool& rand_flag, bool& fuel_flag);
bool fuel_flag;

int main()
{
	//testing_begin
	Airport myairport;
	unsigned int time = 0;		//
	double e1, e2;				//e1-land,e2-take off;
	bool rand_flag;				//using random number or not;
								//
	unsigned num_plane = 1000;

	Ini(myairport, time, e1, e2, rand_flag, fuel_flag);

	while (true)
	{
		int ok = 0;
		cout << "Would you like to build a runway?\n"
			<< "0 to end\n"
			<< "1 to build\n";
		cin >> ok;
		bool flag;
		bool tag;
		if (ok)
		{
			cout << "请输入跑道属性"
				<< "0-起飞\n"
				<< "1-降落\n";
			cin >> flag;
			cout << "跑道属性是否可以更改"
				<< "0-是"
				<< "1-否";
			cin >> tag;
		}
		myairport.buildRunway(falg, tag);
	}

	for (int t = 0; t < time; ++t)
	{
		unsigned count_take_off, count_land;
		if (rand_flag)
		{
			count_land = randf(e1);
			count_take_off = randf(e2);
		}
		else
		{
			f(count_land, count_take_off);
		}

		for (int i = 0; i < count_land; ++i)
		{
			myairport.message(false, num_plane++);
		}
		for (int i = 0; i < count_take_off; ++i)
		{
			myairport.message(true, num_plane++);
		}
		tuple<bool, vector<Plane>, vector<Plane>> result = myairport.Order();
		bool error_flag = get<0>(result);
		if (error_flag = true)
		{
			cout << "error";
			break;
		}
		else
		{
			vector<Plane> taking = get<1>(result);
			vector<Plane> landing = get<2>(result);
			string str;
			str += to_string(t) + ":\n";
			for (auto item : taking)
			{

			}
		}

	}

	return 0;

 } 
