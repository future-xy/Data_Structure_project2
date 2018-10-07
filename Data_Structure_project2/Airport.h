#pragma once

#include<tuple>
#include<vector>
#include<queue>
#include<map>

#include"Plane.h"
#include"Runway.h"

const int MAXSIZE = 1000;

class Airport
{
public:
	Airport();
	Airport(int size_queue_takeoff, int size_queue_land);
	~Airport() = default;

	bool buildRunway(bool flag);
	bool setSize_queue_takeoff(int size);
	bool setSize_queue_land(int size);

	void Order();
	std::tuple<bool, int, int> request() const;
	std::vector<Plane> show_takeoff();
	std::vector<Plane> show_land();
private:
	bool error_flag = false;//�����־
	int count_runway;		//�ܵ���
	int size_queue_takeoff;	//��ɶ�����
	int size_queue_land;	//���������
	int num_takeoff;		//������ɵķɻ����
	int num_land;			//���ڽ���ķɻ����
	std::map<int, Runway> runway;				//��������ܵ�
	std::priority_queue <Plane> queue_takeoff;	//��ɶ���
	std::priority_queue <Plane> queue_land;		//�������

};

