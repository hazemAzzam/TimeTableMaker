#include <iostream>
#include <string>
#include <mysql.h>
#include "resources.h"

using namespace std;

int countOfLecturesInDay(MYSQL* connection, int user_id, int table_id, string day)
{
	MYSQL_ROW row;
	MYSQL_RES* res;
	string query =
		"SELECT COUNT(*) "
		"FROM Lecture L "
		"NATURAL JOIN TTABLE "
		"NATURAL JOIN USER "
		"WHERE L.day = \"" + day + "\" and L.table_id = " + to_string(table_id) + " and user_id = " + to_string(user_id) + ";";
	cout << query << endl;
	const char* q = query.c_str();
	int qstate = mysql_query(connection, q);
	if (!qstate) {
		res = mysql_store_result(connection);
		row = mysql_fetch_row(res);
		return stoi(row[0]);
	}
	else {
		cout << "Error. (401)\n";
		system("pause");
	}
}

void getLectureDataInDay(MYSQL* connection, int user_id, int table_id, string day, vector<LectureData> &lectureData)
{
	MYSQL_ROW row;
	MYSQL_RES* res;
	string query =
		"SELECT name, start_hour, finish_hour, location "
		"FROM Lecture "
		"NATURAL JOIN TTABLE "
		"NATURAL JOIN USER "
		"WHERE "
		"DAY = \"" + day + "\" "
		"and USER_ID = " + to_string(user_id) + " "
		"and table_id = " + to_string(table_id) + " "
		"order by start_hour;";
	cout << query << endl;
	const char* q = query.c_str();

	int qstate = mysql_query(connection, q);

	if (!qstate) 
	{
		res = mysql_store_result(connection);
		int i = 0;
		while (row = mysql_fetch_row(res))
		{
			lectureData[i++] = {
				row[0],
				row[1],
				row[2],
				row[3]
			};
		}
	}
	else 
	{
		cout << "Error. (402)\n";
		system("pause");
	}
}

float changeToProperTime(string time)
{
	string strHours = "", strMinutes = "";
	bool reachedToMinutes = false;

	for (int i = 0; i < 5; i++) {
		if (!isdigit(time[i])) {
			reachedToMinutes = true;
			continue;
		}
		if (!reachedToMinutes)
			strHours += time[i];
		else
			strMinutes += time[i];
	}
	if (reachedToMinutes == false)
		strMinutes += '0';

	float hours = stof(strHours);
	float minutes = stof(strMinutes);

	return hours + (minutes / 100);
}
float changeTime(float t)
{
	return t - ((float)(40 + 20) / 100);
}
string base12(string time)
{
	float hours = changeToProperTime(time);
	bool isPM = false;
	if (hours > 12) {
		hours -= 12;
		isPM = true;
	}
	string timeStr = "";
	if (hours < 10) {
		timeStr += "0";
		timeStr += to_string((int)hours);
	}
	else {
		timeStr += to_string((int)hours);
	}
	timeStr += ":";

	int minutes = round(hours * 100 - (int)hours * 100);
	if (minutes < 10) {
		timeStr += "0";
		timeStr += to_string(minutes);
	}
	else {
		timeStr += to_string(minutes);
	}
	if (isPM)
		timeStr += " PM";
	else
		timeStr += " AM";
	return timeStr;
}
