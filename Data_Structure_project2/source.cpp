#include<iostream>
#include<fstream>
#include<tuple>

#include"Airport.h";

//Áô¸ø´óÀÐµÄ
using std::tuple;

int main()
{
	//testing_begin
	Airport myairport;
	myairport.setSize_queue_land(10);
	myairport.setSize_queue_takeoff(20);
	myairport.buildRunway(true);
	/*while (true)
	{*/
	myairport.message(false, 1001, 0, 10);
//	}
	myairport.Take_Land();
	myairport.Order();
	tuple<bool, vector<Plane>, vector<Plane>> temp = myairport.request();

	return 0;
	//testing_end
 } 



//random and keyboard
#include <cmath>
#include <ctime>
#include <cstdlib>



void usercontrol(int &m, int &n)
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

