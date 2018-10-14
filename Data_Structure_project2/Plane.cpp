#include "Plane.h"


Plane::Plane(){
	flag = true;
	fuel_level = 100000000;
	fuel_consumption = 0;
	wait_time = 0;
}
Plane::Plane(bool flag, int num, int fuel_level, int fuel_consumption){
	this->flag = flag;
	this->num = num;
	wait_time = 0;
	this->fuel_level = fuel_level;
	this->fuel_consumption = fuel_consumption;
}
bool Plane::update(){
	++wait_time;
	if(flag==false)
	{
		fuel_level-=fuel_consumption;
		if( fuel_consumption<0 ) 
			return false;
	}

	return true;
}

void Plane::setFlag(bool flag){
	this->flag = flag;
} 
bool Plane::getFlag() const{
	return flag;
}
int Plane::getNum() const{
	return num;
}
int Plane::getFuel() const{
	return fuel_level;
}
int Plane::getTime() const{
	return wait_time;
}

void Plane::setrunway(int ele)
{
	runway_num = ele;
}
int Plane::getrunway()
{
	return runway_num;
}
	
Plane::~Plane(){
	flag = true;
	fuel_level = 100000000;
	fuel_consumption = 0;
	wait_time = 0;
}

bool operator<(Plane a, Plane b)
{
	if (a.getFlag())
	return a.getTime() < b.getTime();
	if (a.fuel_consumption == 0 || b.fuel_consumption == 0)
	return a.getTime() < b.getTime();
	else 
	return (double)a.fuel_level/a.fuel_consumption < (double)b.fuel_level / b.fuel_consumption;
}

int Plane::last() const
{
	return fuel_level/fuel_consumption;
}
