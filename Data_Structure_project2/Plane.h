class Plane
{
public:
	Plane();
	Plane(bool flag, int num, int fuel_level = 100000000, int fuel_consumption = 0);
	bool update();//油量不足就返回false 
	void setFlag(bool flag);
	bool getFlag() const;
	int getNum() const;
	int getFuel() const;//return fuel_level
	int last() const;
	int getTime() const;
	void setrunway(int ele);
	int getrunway();
	
	~Plane();
	
	friend bool operator<(Plane, Plane);
private:
	bool flag;//takeoff/land true待起飞 false待降落
	int num;//飞机编号
	int wait_time;
	int fuel_level;//剩余油量
	int fuel_consumption;//单位时间耗油量
	int runway_num; //前往机场编号 
};

