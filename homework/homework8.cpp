/******************************************************************************
* Name: Paste, Manasi
* ID: 7404855
* Section: M0002
* Homework 8
*****************************************************************************/
#include <iostream>
#include<vector>
#include <fstream>
#include <algorithm>
#include <iomanip>
using namespace std;

bool isprime(long long int num);


int main()
{
	ifstream fin;
	ofstream fout, fprime;
	long long int n;
	unsigned int i;
	unsigned int j;
	vector <long long int> data;
	fin.open("numbershw8.txt");
	fout.open("desc.txt");
	fprime.open("prime.txt");
	long long int count=0;

	if (!fin)
	{
		cout << "Error: input file couldnot be opened" << endl;
		cout << "Exiting" << endl;
		return 0;
	}
	if (!fout || !fprime)
	{
		cout << "Error: Could not open the output files" << endl;
		cout << "Exiting" << endl;
		return 0;
	}
	while (fin>>n)
	{
		data.push_back(n);
	}
	fin.close();
	sort(data.rbegin(), data.rend());
	for (i = 0; i < data.size(); i++)
	{
		if (i % 5 == 0 && i != 0)
		{
			fout << endl;
		}
		fout << data[i]  << "    ";
		
	}
	fout.close();
	for (j = 0; j < data.size(); j++)
	{
		if (isprime(data[j]))
		{
			count++;
			
			fprime << data[j] << "    ";
			if (count % 5 == 0)
			{
				fprime << endl;
			}
		} 
	}
	

	fprime.close();
	return 0;
}

bool isprime(long long int num)
{
	if (num <=1)
		return false;
	long long int i;
	if (num == 2 || num == 3 ||num==5)
		return true;
	if (num % 2 == 0)
		return false;
	if (num % 3 == 0)
		return false;
	if (num % 5 == 0)
		return false;
	for (i = 7; i <= sqrt(num)+1; i= i+2)
	{
		if (num% i == 0)
		{
			return false;
		}
	}
	return true;
}