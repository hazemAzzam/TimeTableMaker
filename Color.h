#pragma once
#include <iostream>
#include <string>
#include <mysql.h>
#include <fstream>

using namespace std;

class Color
{
protected:
	string first, second, third, fourth;
public:
	void getColors();
	void putColors();
};

