/******************************************************************************
* Name: Paste, Manasi
* ID: 7404855
* Section: M0002
* Homework 3
*****************************************************************************/
#include <iostream>
using namespace std;

/* Prototypes*/
int compressedDate(int m, int d, int y);

void extractDate(int date, int &m, int &d, int &y);

/* Main funtions*/
int main()
{
	int m, d, y;
	//Prompt the user for the date
	cout << "Enter tne date(m d y): ";
	cin >> m >> d >> y;
	
	int date = compressedDate(m, d, y);
	cout << endl << "The compressed date: " << date << endl << endl;

	//resetting m, d, y to 0
	m = 0;
	d = 0;
	y = 0;

	extractDate(date, m, d, y);
	cout << "The extracted date is: " << m << " /" << d << " /" << y << endl;
	
	return 0;
}

/* Funtion definations*/
int compressedDate(int m, int d, int y)
{
	int date = 0;
	date = y;
	//shift the date left by 4 bits to maask it with the month
	date = date << 4;
	
	//mask the date with the month
	date = date | m;
	//shfit the date left by 6 bits to mask it with the date
	date = date << 6;
	// mask the date with the day
	date = date | d;
	return date;
}

void extractDate(int date, int &m, int &d, int &y)
{
	int daymask = 63;
	int monthmask = 15;
	int yearmask = 4095;
	//mask with date with daymask , monthmask and yearmask to extracte the day, month and year resp.
	d = date & daymask;
	date = date >> 6;

	m = date & monthmask;
	date = date >> 4;

	y = date & yearmask;
}