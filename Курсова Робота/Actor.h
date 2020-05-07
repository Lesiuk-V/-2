#pragma once

enum Sex
{
	male,
	female
};

class Actor
{
private:
	char name[50];
	char surname[40];
	char patronymic[40];
	char dateOfBirth[11];
	Sex sex;
	int id;

public:
	void create();
	void setSex();
	void getSex();
	void showData();
	int count();
	void setId(int);
};

