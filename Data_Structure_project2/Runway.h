#pragma once

//�ܵ���ü򵥣������Ǻ����벻��ʲô����������
class Runway
{
public:
	Runway();
	Runway(int num, bool flag);
	~Runway();
	void setFlag(bool flag);
	bool getFlag() const;
	int getNum() const;
private:
	bool flag;	//�ܵ�����ɻ���½ true��� flase��½ 
	int num;	//�ܵ����
};

