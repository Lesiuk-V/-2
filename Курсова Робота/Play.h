#pragma once
class Play
{
private:	
	int id;
	char name[40];
	char ganre[20];
	char writer[40];
	char description[500];

public:
	int search(int);
	void write();
	void create(int);
	void showData();
	void deleted();
	static int count();
	void read(int);
	void edit();
	int setId();
};

