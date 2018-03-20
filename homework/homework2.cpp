/******************************************************************************
* Name: Paste, Manasi
* ID: 7404855
* Section: M0002
* Homework 2
*****************************************************************************/

#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	//Prints out the precentage of tax
	cout << setw(15) << "4.5%" << setw(10) << "5.0%" << setw(10) << "6.0%"
		 << setw(10) << "6.5%" << setw(10) << "7.0%" <<  endl;

	//initialize amount on which the tax is applied to 10.00$
	double amount = 10.00;

	//a loop to increase the amount by 0.05$
	for (amount; amount < 15.05; amount += 0.05)
	{
		//prints the calculated tax amount 
		cout << setprecision(2) << fixed << amount
			<< setprecision(2) << fixed << setw(10) << amount*0.045 << setw(10) << amount*0.05 
			<< setw(10) << amount*0.06 << setw(10) << amount*0.065 << setw(10) << amount*0.07 << endl;
	}
}


