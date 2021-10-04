#include <iostream>
#include <mysql.h>
#include "Program.h"

using namespace std;

Program program;
int main()
{
	MYSQL* conn;
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "root", "timetable", 3306, NULL, 0);

	if (conn) {
		program.setup(conn);
		while(true)
			program.run();
	}
	else {
		cout << "Error.(0)\n";
	}
}