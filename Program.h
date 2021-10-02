#pragma once
#include <iostream>
#include "User.h"
#include "TimeTable.h"
#include "Lecture.h"

using namespace std;
class Program : private User, private TimeTable, private Lecture
{
private:
	int userID;
	int tableID;
	MYSQL* conn;
public:
	// assign default values.
	void setup(MYSQL* connection);

	// display main screen.
	void run();

	// display Dashboard.
	void dashboard();

	// time tables
	void timeTableScreen();

	// add or remove to selected table.
	void editTimeTable();

	void editAccountScreen();
};

