#include<tuple>
#include<vector>
#include<queue>
#include<map>

#include"Plane.h"
#include"Runway.h"
using std::vector;

const int MAXSIZE = 1000;

class Airport
{
public:
	//pre 
	Airport();
	Airport(int size_queue_takeoff, int size_queue_land);
	~Airport() = default;
	bool buildRunway(bool flag);
	bool setSize_queue_takeoff(int size);
	bool setSize_queue_land(int size);
	
	//cur
	bool message(bool flag, int num, int fuel = 10000000, int v = 0); // 起飞/降落，飞机编号, 
	void Take_Land();
	std::tuple<bool, vector<Plane>, vector<Plane> > request() const;
	std::vector<Plane> show_takeoff();
	std::vector<Plane> show_land();
	bool dispatch();
	bool compare();
	tuple<bool, vector<Plane>, vector<Plane>  Order(); //order可以认为是机场内部的函数
	//post
	
private:
	bool error_flag = false;//错误标志
	int count_runway;		//跑道数
 
	int size_queue_takeoff;	//起飞飞机总数
	int size_queue_land;	//降落飞机总数
	std::map<int, Runway> runway;				//用来存放跑道
	std::priority_queue <Plane> queue_takeoff;	//起飞总队列
	std::priority_queue <Plane> queue_land;		//降落总队列
	
	vector <Plane> Taking;  //当前可起飞飞机队列 
	vector <Plane> Landing; //当前可降落飞机队列	

};

