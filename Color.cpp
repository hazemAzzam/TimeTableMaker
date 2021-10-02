#include "Color.h"
#include <iostream>
#include <string>
#include <mysql.h>
#include <fstream>

using namespace std;

void Color::getColors()
{
	ifstream colors("Colors.txt");
	colors >> first >> second >> third >> fourth;
}

void Color::putColors()
{

}