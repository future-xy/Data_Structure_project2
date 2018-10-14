#include "Runway.h"


Runway::Runway(){ 
	flag = true;
	tag = true;
	num = 0;
}
Runway::Runway(int num, bool flag, bool tag){
	this->num = num;
	this->flag = flag;
	this->tag = tag;
}
Runway::~Runway(){
	flag = true;
	tag = true;
	num = 0;
}
void Runway::setFlag(bool flag){
	this->flag = flag;
}
bool Runway::getFlag() const{
	return flag;
}
int Runway::getNum() const{
	return num;
}
void Runway::setTag(bool tag){
	this->tag = tag;
}
bool Runway::getTag() const{
	return tag;
}
