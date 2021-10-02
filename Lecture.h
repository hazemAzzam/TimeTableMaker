#pragma once
#include <iostream>
#include <mysql.h>

using namespace std;
class Lecture
{
protected:
	int lectureID;
	int userID;
	int tableID;
	int countOfLectures;
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;

	void assignDefaultValues(MYSQL* connection, int userID, int tableID);
	int getCountOfLectures();
public:
	void addLecture();
	void deleteLecture();
	void displayAllLectures();
	int getNextLectureID();
	void addLecturesFromFile();
};

