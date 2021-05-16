#include<iostream>
#include<fstream>
#include<tuple>
#include<string>

#include<cmath>
#include<ctime>
#include<cstdlib>

#include"Airport.h"

#ifdef __linux__
#define CLEAR "clear"
#elif _WIN32
#define CLEAR "cls"
#endif

using std::ofstream;
using std::tuple;
using std::string;
using std::vector;
using std::to_string;
using std::get;
using std::cout;
using std::cin;
using std::endl;

bool fuel_flag;
const double pi = 3.1415926;
ofstream myout;

unsigned int rp;

void build_new_runway(Airport& myairport);
void Ini(Airport& myairport, unsigned int& time, double& e1, double& e2, bool& rand_flag, bool& fuel_flag);
void print(int t, Airport myairport, tuple<bool, vector<Plane>, vector<Plane>>);
void print_err(Airport myairport);
void usercontrol(unsigned int &m, unsigned int &n);
int possion(long double E);
int norm(double i, double j);


int main()
{
	srand(time(0));
	rp = rand() % time(0) % 101099951;

	Airport myairport;
	unsigned int time = 0;		//
	double e1, e2;				//e1-land,e2-take off;
	bool rand_flag;				//using random number or not;
								//
	unsigned num_plane = 1000;

	Ini(myairport, time, e1, e2, rand_flag, fuel_flag);
	system(CLEAR);
	myout.open("log.txt", std::ios::app);
	build_new_runway(myairport);

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
				myairport.message(false, num_plane++, norm(5000, 250000), norm(800, 80000));
			}
			else
			{
				myairport.message(false, num_plane++);
			}
		}
		for (int i = 0; i < count_take_off; ++i)
		{

			myairport.message(true, num_plane++);
		}
		tuple<bool, vector<Plane>, vector<Plane>> result = myairport.Order();
		bool error_flag = get<0>(result);
		if (error_flag == true)
		{
			cout << "ERROR!!!\n";
			print_err(myairport);
			break;
		}
		else
		{
			print(t, myairport, result);
		}
		cout << "\n";
	    int temp_ok = 1;
		if (temp_ok)
		{
			cout << "\nWould you want to build a new runway?\n"
				<< "0-No\n"
				<< "1-Yes\n";
			cin >> temp_ok;
			if (temp_ok == 1)
			{
				build_new_runway(myairport);
			}
		}

	}
	myout.close();
	return 0;

 } 

void build_new_runway(Airport& myairport)
{
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
				<< "1-Yes\n"
				<< "0-No\n";
			cin >> tag;
		}
		else
		{
			break;
		}
		myairport.buildRunway(flag, tag);
	}
	system(CLEAR);
	return;
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
	myout << str << endl;

}

void print_err(Airport myairport)
{
	string str;

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
	myout << str << endl;
}
void Ini(Airport& myairport, unsigned int& time, double& e1, double& e2, bool& rand_flag, bool& fuel_flag)
{
	cout << "Welcome to Guangzhou 319 International Airport\n";
	cout << "Please enter the following parameters to build a new airport\n"
		<< "Running time? \n";
	cin >> time;
	cout << "\n";
	cout << "Use random number or not?\n"
		<< "0-No\n"
		<< "1-Yes\n";
	cin >> rand_flag;
	cout << "\n";
	if (rand_flag)
	{
		cout << "Please enter Lambda_1 (expected number of arrivals)\n";
		cin >> e1;
		cout << "\nPlease enter Lambda_2 (expected number of departures)\n";
		cin >> e2;
	}
	cout << "\nConsider the fuel level or not?\n"
		<< "0-No\n"
		<< "1-Yes\n";
	cin >> fuel_flag;
	cout << "\nPlease enter the size of taking off queue\n";
	int temp1;
	cin >> temp1;
	myairport.setSize_queue_takeoff(temp1);
	cout << "\nPlease enter the size of landing queue\n";
	int temp2;
	cin >> temp2;
	myairport.setSize_queue_land(temp2);
	myout.open("log.txt");
	myout << "Welcome to Guangzhou 319 International Airport\n"
		<< "Expected running time: " << time << endl;
	if (rand_flag)
		myout << "Use random number." << endl
		<< "λ1 (expected number of arrivals)\t" << e1 << endl
		<< "λ2 (expected number of departures)\t" << e2 << endl;
	if (fuel_flag)
		myout << "Consider the fuel level" << endl;
	myout << "The size of taking off queue: " << temp2 << endl;
	myout << "The size of landing queue: " << temp1 << endl;
	myout << "\n";
	myout.close();
	

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
				srand(rand() + rp++);
                u = (float)(rand() % 100) / 100;
                p *= u;
                k++;
        }

        return k-1;
}


int norm(double i,double j)
{
	srand(rand() + rp++);
	double u1=double(rand()%1000)/1000,u2=double(rand()%1000)/1000,r;
	static unsigned int seed=0;
	r=i+sqrt(j)*sqrt(-2.0*(log(u1)/log(exp(1.0))))*cos(2*pi*u2);
	return r;
}
