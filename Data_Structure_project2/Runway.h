#pragma once

//�ܵ���ü򵥣������Ǻ����벻��ʲô����������
class Runway
{
public:
	Runway();
	Runway(int num, bool flag);
	~Runway();
	bool setFlag(bool flag);
private:
	bool flag;	//�ܵ�����ɻ���½
	int num;	//�ܵ����
};

