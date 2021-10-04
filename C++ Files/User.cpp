#include "User.h"
#include <iostream>
#include <string>
#include <mysql.h>

using namespace std;

void User::assignDefaultValues(MYSQL* connection)
{
	conn = connection;
	ID = 0;
	firstName = "";
	lastName = "";
}

bool User::checkAccountEmail(string email)
{
	string query =
		"SELECT USER_ID "
		"from USER "
		"where email = \"" + email + "\";";

	const char* q = query.c_str();
	int qstate = mysql_query(conn, q);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		if (row = mysql_fetch_row(res))
		{
			return true;
		}
		return false;
	}
	else
	{
		cout << "Error (101).\n";
		return false;
	}

}
bool User::checkAccountUsername(string username)
{
	string query =
		"SELECT USER_ID "
		"from USER "
		"where username = \"" + username + "\";";

	const char* q = query.c_str();
	int qstate = mysql_query(conn, q);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		if (row = mysql_fetch_row(res))
		{
			return true;
		}
		return false;
	}
	else
	{
		cout << "Error (102).\n";
		return false;
	}

}
bool User::checkAccount(string username, string password)
{
	string query =
		"SELECT User_ID, first_name, last_name "
		"from USER "
		"where username = \"" + username + "\" and password = \"" + password + "\";";

	const char* q = query.c_str();
	int qstate = mysql_query(conn, q);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		if (row = mysql_fetch_row(res)) 
		{
			ID        =  stoi(row[0]);
			firstName =        row[1];
			lastName  =        row[2];
			
			return true;
		}
		return false;
	}
	else
	{
		cout << "Error (103).\n";
		return false;
	}
	
}
int User::getAccountID(string username, string password) 
{
	string query =
		"SELECT User_ID "
		"from USER "
		"where username = \"" + username + "\" and password = \"" + password + "\";";

	const char* q = query.c_str();
	int qstate = mysql_query(conn, q);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		if (row = mysql_fetch_row(res))
		{
			ID = stoi(row[0]);

			return ID;
		}
		return 0;
	}
	else
	{
		cout << "Error (104).\n";
		return 0;
	}
}

bool User::login()
{
	string username;
	string password;

	system("cls");
	cout << "--> Login <--\n";
	cout << "Username: "; cin >> username;
	cout << "Password: "; cin >> password;

	if (checkAccount(username, password)) 
	{
		cout << "--> Login Successfully.\n";
		return true;
	}
	else
	{
		cout << "--> Login Faild.\n";
		return false;
	}
}

void User::newUser()
{
	system("cls");
	cout << "NOTE: If re-asked you to input the same variable, then you can't use the value, and you must change it.\n";
	string username;
	string password;
	string email;
	

	do {
		cout << "Username: "; cin >> username;
	} while (checkAccountUsername(username));
	
	cout << "Password: "; cin >> password;

	do {
		cout << "Email: "; cin >> email;
	} while (checkAccountEmail(email));

	cout << "First Name: "; cin >> firstName;
	cout << "Last Name: "; cin >> lastName;

	string query =
		"INSERT "
		"INTO USER "
		"values "
		"("+ to_string(getCountOfUsers() + 1) +", \"" + username + "\", \"" + email + "\", \"" + password + "\", \"" + firstName + "\", \"" + lastName + "\");";

	const char* q = query.c_str();
	int qstate = mysql_query(conn, q);

	if (qstate) {
		cout << "Error. (105)\n";
	}
	else {
		cout << "--> Account Been Created.\n";
		ID = getAccountID(username, password);
	}
	system("pause");
}

int User::getCountOfUsers()
{
	string query = "SELECT COUNT(*) FROM USER;";
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
		cout << "Error. (106)\n";
		system("pause");
	}
}