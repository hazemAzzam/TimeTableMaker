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

	
	int getCountOfLectures();

public:
	void assignDefaultValues(MYSQL* connection, int userID, int tableID);
	void addLecture();
	void deleteLecture();
	void deleteLectures(int);// delete all lectures of time table id
	void displayAllLectures();
	int getNextLectureID();
	void addLecturesFromFile();
};

