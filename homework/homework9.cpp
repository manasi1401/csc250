/******************************************************************************
* Name: Paste, Manasi
* ID: 7404855
* Section: M0002
* Homework 9
*****************************************************************************/

#include <iostream>
using namespace std;

int triangle(int row);

int main()
{
	int row;
	int tri,tri1, tri2;
	int row1, row2;
	cout << "Enter the number of rows: ";
	cin >> row;
	tri = triangle(row);
	cout << "There are " << tri << " in your triangle" << endl << endl;

	cout << "Enter two rows: ";
	cin >> row1 >> row2;
	tri1 = triangle(row1-1);
	tri2 = triangle(row2);
	cout << "There are " << tri2 - tri1 << " blocks between rows " << row1 << " and " << row2;
	return 0;
}

int triangle(int row)
{
	if (row == 1)
		return 1;
	if (row <= 0)
		return 0;
	return row + triangle(row - 1);
}