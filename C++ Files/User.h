#pragma once
#include <iostream>
#include <string>
#include <mysql.h>

using namespace std;

class User
{
protected:
	int           ID;
	string firstName;
	string  lastName;

	MYSQL      *conn;
	MYSQL_ROW    row;
	MYSQL_RES   *res;

	// email and username must be unique, so check each one of them while making new account
	bool checkAccountEmail(string email);
	bool checkAccountUsername(string username);

	// check if cred is true when logging in.
	bool checkAccount(string username, string password);

	// oh you stuck ?!, don't worry my man will help you ;)
	int getAccountID(string username, string password);
	
	int getCountOfUsers();
public:
	void assignDefaultValues(MYSQL* connection);
	bool login();
	void newUser();
};