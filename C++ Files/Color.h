#pragma once
#include <iostream>
#include <string>
#include <mysql.h>
#include <fstream>

using namespace std;

class Color
{
protected:
	/*
		first -> background and the color of the font of the current lecture
		second -> header of the table
		third -> the background of all lectures in the current day
		fourth -> background color of the current lecture
	*/
	string first, second, third, fourth;
public:
	void getColors();
	void putColors();
};

