#include "Program.h"
#include <iostream>

using namespace std;

void Program::setup(MYSQL* connection)
{
	conn = connection;
	User::assignDefaultValues(connection);
}

void Program::run() 
{
	system("cls");
	cout << "--> Welcome.\n";
	cout << "1) Login.\n"
			"2) Create Account.\n";

	int choice = 0;
	cout << "[?]> "; cin >> choice;
	switch (choice)
	{
	case 1:
		if (User::login()) {
			TimeTable::assignDefaultValues(conn, User::ID);
			dashboard();
		}
		break;
	case 2:
		User::newUser();
		TimeTable::assignDefaultValues(conn, User::ID);
		dashboard();
		break;
	default:
		break;
	}
}

void Program::dashboard()
{
	system("cls");
	cout << "--> Welcome, " << User::firstName << " " << User::lastName << endl;
	cout << "1) Time Tables.\n"
			"2) edit Account.\n"
			"0) exit.\n";
	int choice = 0;
	cout << "[?]> "; cin >> choice;

	switch (choice)
	{
	case 1:
		timeTableScreen();
		break;
	case 2:
		editAccountScreen();
		break;
	case 0:
		exit(0);
	default:
		break;
	}
	dashboard();
}

void Program::timeTableScreen()
{
	system("cls");
	cout << "### Your Time Tables\n";
	if (TimeTable::title == "") {
		cout << "### Plase Select table first.\n\n";
	}
	else {
		cout << "### Table: " << TimeTable::title << endl << endl;
	}
	cout << 
		"1) Select Table.\n"
		"2) New Table.\n";

	int choice = 0;
	cout << "[?]> "; cin >> choice;
	switch (choice)
	{
	case 1:
		if (TimeTable::selectTableV2()) {
			Lecture::assignDefaultValues(conn, User::ID, TimeTable::tableID);
			editTimeTable();
		}
		break;
	case 2:
		TimeTable::newTable();
		Lecture::assignDefaultValues(conn, User::ID, TimeTable::tableID);
		editTimeTable();
		break;
	default:
		timeTableScreen();
	}
	timeTableScreen();
}

void Program::editTimeTable()
{
	system("cls");
	cout <<
		"Table: " + TimeTable::title + "\n"
		"1) Add Lecture.\n"
		"2) Delete Lecture.\n"
		"3) Display All.\n"
		"4) Generate HTML.\n"
		"5) Add lectures from file.\n"
		"0) backward.\n";
	int choice = 0;
	cout << "[?]> "; cin >> choice;
	switch (choice)
	{
	case 0:
		timeTableScreen();
	case 1:
		Lecture::addLecture();
		break;
	case 2:
		Lecture::deleteLecture();
		break;
	case 3:
		Lecture::displayAllLectures();
		system("pause");
		break;
	case 4:
		TimeTable::generateTable();
		break;
	case 5:
		Lecture::addLecturesFromFile();
		break;
	default:
		editTimeTable();
	}
	editTimeTable();
}

void Program::editAccountScreen()
{

}