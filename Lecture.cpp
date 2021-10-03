#include "Lecture.h"
#include <iostream>
#include <mysql.h>
#include <string>
#include <fstream>
using namespace std;

void Lecture::assignDefaultValues(MYSQL* connection, int user_id, int table_id)
{
	conn = connection;
	userID = user_id;
	tableID = table_id;
	lectureID = 0;
}

int Lecture::getCountOfLectures()
{
	string query =
		"SELECT COUNT(*) "
		"FROM lecture "
		"NATURAL JOIN ttable "
		"NATURAL JOIN user "
		"WHERE user_id = " + to_string(userID) + " and table_id = " + to_string(tableID) + ";";
	const char* q = query.c_str();
	int qstate = mysql_query(conn, q);
	if (!qstate)
	{
		res = mysql_store_result(conn);
		if (row = mysql_fetch_row(res)) {
			return stoi(row[0]);
		}
		else {
			return 0;
		}
	}
	else
	{
		cout << "Error. (301)\n";
		system("pause");
	}
}

void Lecture::addLecture()
{
	lectureID = getNextLectureID();
	cout << "--> Add Lecture <--\n\n";
	string day, name, location;
	string startHour, finishHour;
	cout << "Day: "; cin >> day;
	cout << "Name: "; cin.ignore(1000,'\n'); getline(cin, name);
	cout << "Location: ";  getline(cin, location);
	cout << "Start Hour(HH:MM): "; cin >> startHour;
	cout << "Finish Hour(HH:MM): "; cin >> finishHour;

	string query =
		"INSERT INTO Lecture "
		"VALUES "
		"(" + to_string(lectureID) + ", " + to_string(tableID) + ", " + to_string(userID) + ", \"" + day + "\", \"" + name + "\", \"" + startHour + "\",\"" + finishHour + "\", \"" + location + "\");";
	cout << query << endl;
	const char* q = query.c_str();
	int qstate = mysql_query(conn, q);
	if (!qstate)
	{
		cout << "Lecture been Added.\n";
	}
	else
	{
		cout << "Error. (302)\n";
	}
	system("pause");
}

void Lecture::deleteLecture()
{
	cout << "--> DELETE LECTURE <--\n\n";
	displayAllLectures();
	int choice;
	cout << "[ID]> "; cin >> choice;
	
	string query =
		"DELETE FROM Lecture "
		"WHERE user_id = " + to_string(userID) + " and table_id = " + to_string(tableID) + " and Lecture_id = " + to_string(choice) + ";";
	const char* q = query.c_str();
	int qstate = mysql_query(conn, q);
	if (!qstate)
	{
		cout << "--> Lecture been Deleted.\n";
	}
	else 
	{
		cout << "Error. (304)\n";
		cout << query << endl;
	}
	system("pause");
}

void Lecture::deleteLectures(int id)
{
	string query =
		"DELETE FROM Lecture "
		"WHERE user_id = " + to_string(userID) + " and table_id = " + to_string(id) + ";";
	const char* q = query.c_str();
	int qstate = mysql_query(conn, q);
	if (!qstate)
	{
		// do no thing
	}
	else
	{
		cout << "Error. (306)\n";
		cout << query << endl;
		system("pause");
	}
}

void Lecture::displayAllLectures()
{
	cout << "###########\n";
	string query =
		"SELECT lecture_id, name, day, location "
		"FROM Lecture "
		"NATURAL JOIN TTABLE "
		"NATURAL JOIN USER "
		"WHERE USER_ID = " + to_string(userID) + " and table_id = " + to_string(tableID) + ";";
	const char* q = query.c_str();
	int qstate = mysql_query(conn, q);
	if (!qstate)
	{
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			for (int i = 0; i < 4; i++) {
				cout << row[i] << "  ";
			}
			cout << endl;
		}
		cout << "###########\n";
	}
	else
	{
		cout << "Error. (303)\n";
		system("pause");
	}
}

int Lecture::getNextLectureID()
{
	string query =
		"SELECT LECTURE_ID "
		"FROM lecture "
		"NATURAL JOIN ttable "
		"NATURAL JOIN user "
		"WHERE user_id = " + to_string(userID) + " and table_id = " + to_string(tableID) + " "
		"order by lecture_id desc "
		"LIMIT 1";
	const char* q = query.c_str();
	int qstate = mysql_query(conn, q);
	if (!qstate)
	{
		res = mysql_store_result(conn);
		if (row = mysql_fetch_row(res)) {
			return stoi(row[0]) + 1;
		}
		else {
			return 1;
		}
	}
	else
	{
		cout << "Error. (305)\n";
		system("pause");
	}
}

void Lecture::addLecturesFromFile()
{
	cout << "--> Add Lectures from file\n## DAY SUBJECT START FINISH PLACE, each in new line.\n\n";
	
	string fileName;
	cout << "--> File Name: "; cin >> fileName;
	ifstream file(fileName);
	string data[5];
	while (getline(file, data[0])) {
		lectureID = getNextLectureID();
		for (int i = 1; i < 5; i++) {
			getline(file, data[i]);
		}
		string query =
			"INSERT INTO Lecture "
			"VALUES "
			"(" + to_string(lectureID) + ", " + to_string(tableID) + ", " + to_string(userID) + ", \"" + data[0] + "\", \"" + data[1] + "\", \"" + data[2] + "\",\"" + data[3] + "\", \"" + data[4] + "\");";
		cout << query << endl;
		const char* q = query.c_str();
		int qstate = mysql_query(conn, q);
		if (!qstate)
		{
			cout << "Lecture been Added.\n";
		}
		else
		{
			cout << "Error. (302)\n";
		}
	}
	system("pause");
}