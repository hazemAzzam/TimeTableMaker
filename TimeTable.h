#pragma once
#include <string>
#include <mysql.h>
#include "resources.h"
#include "Color.h"
#include "Lecture.h"
using namespace std;
class TimeTable : private Color
{
protected:
	int userID;
	int tableID;
	string title;
	 
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;

    // by reaching to this function, we will be storing userID, so we use it now to retrieve all his tables;
	void assignDefaultValues(MYSQL* conn, int userID);

	// we will show all the time ables of the user, so he can select the one.
	void showTables();

	// when selecting the needed table, we still need to store its title.
	void getTableTitle();
	bool getTableTitleV2();

	// get number of tables, for some improvments
	int getNumberOfTables();

	int getNextTableID();
public:
	void selectTable();

	bool selectTableV2();

	// if user has no tables.
	void safeSelectTable();

	// edit the title of the table.
	void editTable();

	// generate the html page.
	void generateTable();

	// construct new table.
	void newTable();

	void deleteTable();
};