#include<iostream>
#include<fstream>
#include<tuple>
#include<string>

#include <cmath>
#include <ctime>
#include <cstdlib>
#include<cstdlib>

#include"Airport.h"

using std::tuple;
using std::string;
using std::vector;
using std::to_string;
using std::get;
using std::cout;
using std::cin;
using std::endl;

bool fuel_flag;

void Ini(Airport& myairport, unsigned int& time, double& e1, double& e2, bool& rand_flag, bool& fuel_flag);
void print(int t, Airport myairport, tuple<bool, vector<Plane>, vector<Plane>>);
void usercontrol(unsigned int &m, unsigned int &n);
int possion(long double E);


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
	system("cls");
	while (true)
	{
		int ok = 0;
		cout << "\nWould you like to build a runway?\n"
			<< "0 to end\n"
			<< "1 to build\n";
		cin >> ok;
		bool flag;
		bool tag;
		if (ok)
		{
			cout << "\nInput property of the runway\n"
				<< "0-take off\n"
				<< "1-land\n";
			cin >> flag;
			cout << "\nCan the property be changed\n"
				<< "0-Yes\n"
				<< "1-No\n";
			cin >> tag;
		}
		else
		{
			break;
		}
		myairport.buildRunway(flag, tag);
	}
	system("cls");

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
			if (fuel_flag)
			{
				//myairport.message(false, num_plane++, norm(), norm());
			}
			else
			{
				myairport.message(false, num_plane++);
			}
		}
		for (int i = 0; i < count_take_off; ++i)
		{
			if (fuel_flag)
			{
				//myairport.message(true, num_plane++, norm(), norm());
			}
			else
			{
				myairport.message(true, num_plane++);
			}
		}
		tuple<bool, vector<Plane>, vector<Plane>> result = myairport.Order();
		bool error_flag = get<0>(result);
		if (error_flag == true)
		{
			cout << "ERROR!!!\n";
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
		temp += "Flight " + to_string(item.getNum()) + " is taking off on Runway " + to_string(item.getrunway()) + "\t";
		temp += "Waiting time\t" + to_string(item.getTime());
		str += temp + "\n";
	}
	for (auto item : landing)
	{
		string temp = "\t";
		temp += "Flight " + to_string(item.getNum()) + " is landing on Runway " + to_string(item.getrunway()) + "\t";
		temp += "Waiting time\t" + to_string(item.getTime());
		str += temp + "\n";
	}
	vector<Plane> takeoff = myairport.show_takeoff();
	str += "\nThe waiting queue of planes to take off:\n";
	str += "Flight\tWaiting time\n";
	for (auto item : takeoff)
	{
		string temp;
		temp += to_string(item.getNum());
		temp += "\t" + to_string(item.getTime());
		temp += "\n";
		str += temp;
	}

	vector<Plane> land = myairport.show_land();
	str += "\nThe waiting queue of planes to land:\n";
	str += "Flight\tWaiting time\n";
	for (auto item : land)
	{
		string temp;
		temp += to_string(item.getNum());
		temp += "\t" + to_string(item.getTime());
		temp += "\n";
		str += temp;
	}
	cout << str << endl;
	std::ofstream myout("log.txt", std::ios::app);
	myout << str << endl;
	myout.close();
}

void Ini(Airport& myairport, unsigned int& time, double& e1, double& e2, bool& rand_flag, bool& fuel_flag)
{
	cout << "Welcome to Guangzhou 319 Internation Airport\n";
	cout << "Please enter the following parameters to build a new airport\n"
		<< "Running time? \n";
	cin >> time;
	cout << "\n";
	cout << "Using random number? \n"
		<< "0-No\n"
		<< "1-Yes\n";
	cin >> rand_flag;
	cout << "\n";
	if (rand_flag)
	{
		cout << "Please enter λ1 (expected number of arrivals)\n";
		cin >> e1;
		cout << "\nPlease enter λ2 (expected number of departures)\n";
		cin >> e2;
	}
	cout << "\nConsider the fuel level or not?\n"
		<< "0-No\n"
		<< "1-Yes\n";
	cin >> fuel_flag;
	cout << "\nPlease enter the size of taking off queue\n";
	int temp;
	cin >> temp;
	myairport.setSize_queue_takeoff(temp);
	cout << "\nPlease enter the size of landing queue\n";
	cin >> temp;
	myairport.setSize_queue_land(temp);
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

int possion(long double E)
{
        long double Lambda = E;
		int k = 0;
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

#define pi 3.1415926
int norm(double i,double j)
{
	srand( (unsigned)time( NULL ) );
	double u1=double(rand()%1000)/1000,u2=double(rand()%1000)/1000,r;
	static unsigned int seed=0;
	r=i+sqrt(j)*sqrt(-2.0*(log(u1)/log(exp(1.0))))*cos(2*pi*u2);
	return r;
}
