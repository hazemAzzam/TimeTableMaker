#include "Color.h"
#include <iostream>
#include <string>
#include <mysql.h>
#include <fstream>

using namespace std;

void Color::getColors()
{
	ifstream colors("Colors.txt");
	if (colors >> first >> second >> third >> fourth);
	else {
		first = "#212121";
		second = "#323232";
		third = "#0D7377";
		fourth = "#14FFEC";
	}
}

void Color::putColors()
{

}