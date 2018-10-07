#pragma once
class Plane
{
public:
	Plane();
	Plane(bool flag, int num, int fuel_level = 100000000, int fuel_consumption = 0);
	bool update();//��������ͷ���false 
	void setFlag(bool flag);
	bool getFlag() const;
	int getNum() const;
	int getFuel() const;//return fuel_level 
	int getTime() const;
	~Plane();
private:
	bool flag;//takeoff/land true����� false������ 
	int num;//�ɻ����
	int wait_time;
	int fuel_level;//ʣ������
	int fuel_consumption;//��λʱ�������
};

