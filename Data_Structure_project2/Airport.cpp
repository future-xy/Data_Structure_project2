#include"Airport.h" 

using std::vector;
using std::tuple;
using std::map;

extern bool fuel_flag;

Airport::Airport()
{
	count_runway = 0;
	size_queue_land = 0;
	size_queue_takeoff = 0;
}

Airport::Airport(int size_queue_takeoff, int size_queue_land)
{
	this->size_queue_land = size_queue_land;
	this->size_queue_takeoff = size_queue_takeoff;
}

bool Airport::buildRunway(bool flag, bool tag)
{
	Runway temp(count_runway, flag, tag);
	runway[count_runway] = temp;
	count_runway++;

	return true;
}

bool Airport::setSize_queue_land(int size)
{
	size_queue_land = size;
	return true;
}

bool Airport::setSize_queue_takeoff(int size)
{
	size_queue_takeoff = size;
	return true;
}

bool Airport::message(bool flag, int num, int fuel, int v)//the simple condition
{
	Plane P(flag, num, fuel, v);
	if (flag == true)
	{
		if (queue_takeoff.size() < size_queue_takeoff) {
			queue_takeoff.push(P);
			return true;
		}
		else
		{
			error_flag = true;
			return false;
		}
	}
	else {
		if (queue_land.size() < size_queue_land) {
			queue_land.push(P);
			return true;
		}
		else 
		{
			error_flag = true;
			return false;
		}
	}
}



void Airport::Take_Land()
{
	Taking.clear();
	Landing.clear();

	if (runway.size() == 1) {
		if (!queue_takeoff.size())    runway[0].setFlag(false);
		else {
			bool temp = compare();
			if (fuel_flag) {//P5
				if (!dispatch()) runway[0].setFlag(false);
				else runway[0].setFlag(temp);
			}
			else {
				runway[0].setFlag(temp);
			}
		}
	}
	else if (runway.size() == 2) {
		if (runway[0].getTag()) {//P3
			if (!queue_takeoff.size() && !queue_land.size()) {}
			else if (!queue_takeoff.size() && queue_land.size()) {
				runway[0].setFlag(false);
				runway[1].setFlag(false);
			}
			else if (queue_takeoff.size() && !queue_land.size()) {
				runway[0].setFlag(true);
				runway[1].setFlag(true);
			}
			else {
				runway[0].setFlag(true);
				runway[1].setFlag(false);
			}
		}
	}
	else {//P4
		for (auto iter : runway) {
			if (iter.second.getTag()) {
				if (queue_land.size()) {
					iter.second.setFlag(true);
				}
			}
		}
	}
	for (auto iter : runway)
	{
		if (iter.second.getFlag() && queue_takeoff.size())
		{

			Plane p = queue_takeoff.top();
			p.setrunway(iter.first);
			Taking.push_back(p);
			queue_takeoff.pop();

		}
		else if (queue_land.size())
		{
			Plane p = queue_land.top();
			p.setrunway(iter.first);
			Landing.push_back(p);
			queue_land.pop();
		}
	}
}
bool Airport::dispatch() {
	show_takeoff();
	for (int i = 0; i < Landing.size(); ++i) {
		if (Landing[i].last() <= i) return false;
	}
	return true;
}
bool Airport::compare() {
	int temp = queue_takeoff.size()*size_queue_land - queue_land.size()*size_queue_takeoff;
	if (temp >= 0) return true;
	return false;
}

tuple<bool, vector<Plane>, vector<Plane> > Airport::Order()
{
	Take_Land();
	vector<Plane> temp;
	while (!queue_takeoff.empty())
	{
		Plane temp_Plane = queue_takeoff.top();
		temp_Plane.update();
		temp.push_back(temp_Plane);
		queue_takeoff.pop();
	}
	for (auto item : temp)
	{
		queue_takeoff.push(item);
	}

	temp.clear();

	while (!queue_land.empty())
	{
		Plane temp_Plane = queue_land.top();
		temp.push_back(temp_Plane);
		queue_land.pop();
	}
	for (auto item : temp)
	{
		if (!item.update())
		{
			error_flag = true;
			break;
		}
		queue_land.push(item);
	}
	return request();
}


tuple<bool, vector<Plane>, vector<Plane> > Airport::request() const
{
	tuple<bool, vector<Plane>, vector<Plane> > temp(error_flag, Taking, Landing);
	return temp;
}

vector<Plane> Airport::show_takeoff()
{
	vector<Plane> temp;
	while (!queue_takeoff.empty())
	{
		Plane temp_Plane = queue_takeoff.top();
		temp.push_back(temp_Plane);
		queue_takeoff.pop();
	}
	for (auto item : temp)
	{
		queue_takeoff.push(item);
	}
	return temp;
}

vector<Plane> Airport::show_land()
{
	vector<Plane> temp;
	while (!queue_land.empty())
	{
		Plane temp_Plane = queue_land.top();
		temp.push_back(temp_Plane);
		queue_land.pop();
	}
	for (auto item : temp)
	{
		queue_land.push(item);
	}
	return temp;
}
