#include <iostream>
#include <string>
#include <mysql.h>
#include <vector>
using namespace std;

struct LectureData
{
	string subject;
	string start;
	string finish;
	string place;
};

int countOfLecturesInDay(MYSQL* connection, int user_id, int table_id, string day);
void getLectureDataInDay(MYSQL* connection, int user_id, int table_id, string day, vector<LectureData> &lectureData);
float changeToProperTime(string time); // change time string to float
string base12(string time); // convert to 12-hour base
float changeTime(float time); // get time minus 15 minutes
