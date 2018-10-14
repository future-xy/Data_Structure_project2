#include<iostream>
#include<fstream>
#include<tuple>
#include<string>

#include <cmath>
#include <ctime>
#include <cstdlib>

#include"Airport.h";

using std::tuple;
using std::string;
using std::to_string;
using std::get;
using std::cout;
using std::cin;
using std::endl;

bool fuel_flag;

void Ini(Airport& myairport, unsigned int& time, double& e1, double& e2, bool& rand_flag, bool& fuel_flag);
void print(int t, Airport myairport, tuple<bool, vector<Plane>, vector<Plane>>);


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
			cout << "�������ܵ�����"
				<< "0-���\n"
				<< "1-����\n";
			cin >> flag;
			cout << "�ܵ������Ƿ���Ը���"
				<< "0-��"
				<< "1-��";
			cin >> tag;
		}
		myairport.buildRunway(flag, tag);
	}

	for (int t = 0; t < time; ++t)
	{
		unsigned count_take_off, count_land;
		if (rand_flag)
		{
			count_land = possion(e1);
			count_take_off = possion(e2);
		}
		else
		{
			usercontrol(count_land, count_take_off);
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
			print(t, myairport, result);
		}

	}

	return 0;

 } 

void print(int t, Airport myairport, tuple<bool, vector<Plane>, vector<Plane>> result)
{
	vector<Plane> taking = get<1>(result);
	vector<Plane> landing = get<2>(result);
	string str;
	str += to_string(t) + ":\n";
	for (auto item : taking)
	{
		string temp = "\t";
		temp += "�ɻ�" + to_string(item.getNum()) + "��" + to_string(item.getrunway()) + "���ܵ�����\t";
		temp += "�ȴ�ʱ��\t" + to_string(item.getTime());
		str += temp + "\n";
	}
	for (auto item : landing)
	{
		string temp = "\t";
		temp += "�ɻ�" + to_string(item.getNum()) + "��" + to_string(item.getrunway()) + "���ܵ����\t";
		temp += "�ȴ�ʱ��\t" + to_string(item.getTime());
		str += temp + "\n";
	}
	vector<Plane> takeoff = myairport.show_takeoff();
	str += "\n�ȴ���ɶ���:\n";
	for (auto item : takeoff)
	{
		string temp = "�����\t";
		temp += to_string(item.getNum());
		temp += "\t" + to_string(item.getTime());
		temp += "\n";
		str += temp;
	}

	vector<Plane> land = myairport.show_land();
	str += "\n�ȴ��������:\n";
	for (auto item : land)
	{
		string temp = "�����\t";
		temp += to_string(item.getNum());
		temp += "\t" + to_string(item.getTime());
		temp += "\n";
		str += temp;
	}
}

//random and keyboard



void usercontrol(unsigned int &m,unsigned int &n)
{
	cout << "Input the number of taking off planes right now: ";
	cin >> n;
	cout << "\nInput the number of landing planes right now: ";
	cin >> m;
	cout << endl; 
}

int possion(int E)
{
        int Lambda = E, k = 0;
        long double p = 1.0;
        long double l=exp(-Lambda); 
        while (p>=l)
        {
                double u;
                srand((unsigned)time(NULL));
                u = (float)(rand() % 100) / 100;
                p *= u;
                k++;
        }
        return k-1;
}

