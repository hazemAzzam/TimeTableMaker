#include "TimeTable.h"
#include <iostream>
#include <mysql.h>
#include <fstream>
#include <vector>
using namespace std;

void TimeTable::generateTable()
{
	Color::getColors();
	struct Day
	{
		string name;
		string code;
	};
	Day day[7] = {
		{"SAT", "6"},
		{"SUN", "0"},
		{"MON", "1"},
		{"TUE", "2"},
		{"WED", "3"},
		{"THU", "4"},
		{"FRI", "5"}
	};
	ofstream htmlFile(title + ".html");
	htmlFile << "<!DOCTYPE html>\n<html>\n";
	htmlFile << "	<head><meta charset='UTF-8' /><meta name='viewport' content='width = device - width, initial - scale = 1' /> \n";
	htmlFile << "	<style id='webmakerstyle'>:root { --first: " + Color::first + "; --second: " + Color::second + "; --third: " + Color::third + "; --font-color: " + Color::fourth + "; } #body { text-align: center; background-color: var(--first); font-size: 20px; font-family: sans-serif; } table { left: 50%; top: 50%; transform: translate(-50%, -50%); background-color: var(--first); border-collapse: collapse; color: var(--font-color); table-layout: auto; position: absolute; width: 100%; } th { background-color: var(--second); padding: 20px; } td { font-size: 20px; padding: 7px; height: 50px; }</style>\n";
	htmlFile << "	</head>\n";
	htmlFile <<
		"	<body id='body'>\n"
		"		<table id='table'>\n"
		"			<caption id='cb'>" + TimeTable::title + "</caption>\n"
		"			<tr>\n"
		"				<th>DAY</th>\n"
		"				<th>SUBJECT</th>\n"
		"				<th>START</th>\n"
		"				<th>FINISH</th>\n"
		"				<th>PLACE</th>\n"
		"			</tr>\n";

	// there is 7 days.
	for (int i = 0; i < 7; i++)
	{
		// if there is lectures in day
		int numberOfLectures = countOfLecturesInDay(conn, userID, tableID, day[i].name);
		if (numberOfLectures > 0)
		{
			vector<LectureData> ld(numberOfLectures);
			getLectureDataInDay(conn, userID, tableID, day[i].name, ld);

			// then get all its lectures
			for (int j = 0; j < numberOfLectures; j++)
			{
				if (j == numberOfLectures - 1) {
					htmlFile <<
						"			<tr style='border-bottom: 1px solid "+Color::second+";' id=\'" + day[i].code + ld[j].start + "\' class=\'" + day[i].code + "\'>\n";
				}
				else {
					htmlFile <<
						"			<tr id=\'" + day[i].code + ld[j].start + "\' class=\'" + day[i].code + "\'>\n";
				}
				
				if (j == 0) {
					htmlFile <<
						"				<th rowspan=" + to_string(numberOfLectures) + ">" + day[i].name + "</th>\n";
				}
				
				htmlFile <<
					"				<td class=\'" + day[i].code + ld[j].start + " font " + to_string(stoi(day[i].code) + 10) + "\'>" + ld[j].subject + "</td>\n"
					"				<td class=\'" + day[i].code + ld[j].start + " font " + to_string(stoi(day[i].code) + 10) + "\'>" + base12(ld[j].start) + "</td>\n"
					"				<td class=\'" + day[i].code + ld[j].start + " font " + to_string(stoi(day[i].code) + 10) + "\'>" + base12(ld[j].finish) + "</td>\n"
					"				<td class=\'" + day[i].code + ld[j].start + " font " + to_string(stoi(day[i].code) + 10) + "\'>" + ld[j].place + "</td>\n";
			}
			htmlFile <<
				"			</tr>\n";
		}
	}
	htmlFile <<
		"		</table>\n"
		"	</body>\n"
		"</html>\n";

	htmlFile <<
		"<script>\n"
		"setInterval(myTimer, 1000);var second = '"+Color::fourth+"';var third = '"+Color::third+"'; var fourth = '"+Color::fourth+"'; var first = '"+Color::first+"'; var d = new Date(); tday = new Array('Sunday', 'Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday'); var t = d.toLocaleTimeString(); var day = d.getDay(); var hours = d.getHours() + d.getMinutes() / 100; function daySelector() { var galleries = document.getElementsByClassName(day); var len = galleries.length; for (var i = 0; i < len; i++) { galleries[i].style.backgroundColor = third; } var it = 0; while (document.getElementsByClassName(day + 10)[it]) document.getElementsByClassName(day + 10)[it++].style.color = second; }"
		"\nfunction myTimer() {\n"
		"	var sDate = new Date();\n";

	for (int i = 0; i < 7; i++)
	{
		int numberOfLectures = countOfLecturesInDay(conn, userID, tableID, day[i].name);
		if (numberOfLectures > 0)
		{
			htmlFile <<
				"	if (day == " + day[i].code + ") {\n"
				"		daySelector();\n";
			for (int j = 0; j < numberOfLectures; j++)
			{
				vector<LectureData> ld(numberOfLectures);	
				getLectureDataInDay(conn, userID, tableID, day[i].name, ld);
				float start, finish;
				start = changeTime(changeToProperTime(ld[j].start));
				finish = changeTime(changeToProperTime(ld[j].finish));
				htmlFile <<
					"		if (hours >= " + to_string(start) + " && hours < " + to_string(finish) + ") {\n"
					"			document.getElementById(\'" + day[i].code + ld[j].start + "\').style.backgroundColor = fourth;\n"
					"			for (var i = 0; i < 4; i++)\n"
					"				document.getElementsByClassName(\"" + day[i].code + ld[j].start + " font\")[i].style.color = first;\n"
					"		}\n";
				
			}
			htmlFile <<
				"	}\n";
		}
	}
	htmlFile <<
		"}\n</script>";
}


void TimeTable::safeSelectTable()
{
	if (getNumberOfTables() == 0) {
		cout << "--> You have no tables.\n";
		newTable();
	}
	else {
		selectTable();
	}
}
void TimeTable::assignDefaultValues(MYSQL* connection, int user_id)
{
	userID = user_id;
	tableID = 0;
	title = "";
	conn = connection;
}
void TimeTable::showTables()
{
	string query =
		"SELECT table_id, title "
		"FROM USER U "
		"NATURAL JOIN TTABLE T "
		"where user_id = " + to_string(userID) + ";"; 

	const char* q = query.c_str();
	int qstate = mysql_query(conn, q);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			cout << row[0] << "  " << row[1] << endl;
		}
	}
	else
	{
		cout << "Error. (201)\n";
		system("pause");
	}
}
void TimeTable::selectTable()
{
	showTables();
	int choice = 0;
	cout << "[id]> "; cin >> tableID;
	
	getTableTitle();
}
bool TimeTable::selectTableV2()
{
	if (getNumberOfTables() == 0)
		return false;

	showTables();

	int choice = 0;
	cout << "[id]> "; cin >> tableID;

	if (getTableTitleV2())
		return true;
	return false;
}
void TimeTable::getTableTitle()
{
	string query =
		"SELECT title "
		"from TTable "
		"where table_ID = " + to_string(tableID) + " and user_ID = " + to_string(userID) + ";";

	const char* q = query.c_str();
	int qstate = mysql_query(conn, q);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		if (row = mysql_fetch_row(res))
			title = row[0];
	}
	else
	{
		cout << "Error. (202)\n";
		system("pause");
	}
}
bool TimeTable::getTableTitleV2()
{
	string query =
		"SELECT title "
		"from TTable "
		"where table_ID = " + to_string(tableID) + " and user_ID = " + to_string(userID) + ";";

	const char* q = query.c_str();
	int qstate = mysql_query(conn, q);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		if (row = mysql_fetch_row(res)) {
			title = row[0];
			return true;
		}
		else {
			return false;
		}
	}
	else
	{
		cout << "Error. (202)\n";
		system("pause");
		return false;
	}
}
void TimeTable::editTable()
{
	system("cls");
	if (title == "") {
		cout << "[!]>> You must select table first.\n";
		system("pause");
		selectTable();
	}
	cout << "[]> Table Title: " << title << endl;
	cout << "[?] New Title: "; cin.ignore(); getline(cin, title);

	string query =
		"UPDATE TTable "
		"set title = \"" + title + "\" " 
		"where table_ID = " + to_string(tableID) + " and user_ID = " + to_string(userID) + ";";

	const char* q = query.c_str();
	int qstate = mysql_query(conn, q);
	if (!qstate) {
		cout << "[!]> Title been updated!.";
		system("pause");
	}
	else {
		cout << "Error. (203)\n";
		system("pause");
	}
}
void TimeTable::newTable()
{
	cout << "--> Create new TimeTable <--\n";
	cout << "Title: "; cin.ignore(); getline(cin, title);
	tableID = getNextTableID();
	string query =
		"INSERT INTO TTABLE "
		"VALUES"
		"(" + to_string(tableID) + ", " + to_string(userID) + ", \"" + title + "\");";
	
	const char* q = query.c_str();
	int qstate = mysql_query(conn, q);
	if (!qstate) {
		cout << "--> Table been created.\n";
		
		system("pause");
	}
	else {
		cout << "Error. (204)\n";
		cout << query << endl;
		system("pause");
	}
}
int TimeTable::getNumberOfTables()
{
	string query =
		"SELECT count(*)"
		"from ttable "
		"natural join user "
		"where user_ID = " + to_string(userID) + ";";
	const char* q = query.c_str();
	int qstate = mysql_query(conn, q);
	if (!qstate) {
		res = mysql_store_result(conn);
		row = mysql_fetch_row(res);

		return stoi(row[0]);
	}
	else {
		cout << "Error. (205)\n";
		system("pause");
	}
}
int TimeTable::getNextTableID()
{
	string query =
		"SELECT table_id "
		"from ttable "
		"where user_id = " + to_string(userID) + " "
		"order by table_id desc "
		"limit 1;"
		;
	const char* q = query.c_str();
	int qstate = mysql_query(conn, q);
	if (!qstate)
	{
		res = mysql_store_result(conn);
		if (row = mysql_fetch_row(res))
		{
			return stoi(row[0]) + 1;
		}
		return 1;
	}
	else
	{
		cout << "Error. (207)\n";
		cout << query << endl;
		system("pause");
	}
}
void TimeTable::deleteTable()
{
	Lecture l;
	l.assignDefaultValues(conn, userID, 0);
	showTables();
	int choice;
	cout << "\n[?]> "; cin >> choice;
	l.deleteLectures(choice);
	string query = 
		"DELETE FROM TTable "
		"WHERE table_id = " + to_string(choice) + " and user_id = " + to_string(userID) + ";";
	const char* q = query.c_str();
	int qstate = mysql_query(conn, q);
	if (!qstate)
	{
		cout << "--> Table been Deleted.\n";
	}
	else
	{
		cout << "Error. (206)\n";
	}
	system("pause");
}

