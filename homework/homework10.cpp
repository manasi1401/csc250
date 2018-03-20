/******************************************************************************
* Name: Paste, Manasi
* ID: 7404855
* Section: M0002
* Homework 10
*****************************************************************************/
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main()
{
	ifstream fin;
	ofstream fout;
	fin.open("doublehw10.data",ios::in| ios::binary);
	fout.open("doubleSortedhw10.data", ios::out| ios::trunc| ios::binary);

	if (!fin)
	{
		cout << "Error: could not open the input file" << endl;
		cout << "Exiting" << endl;
		return 1;
	}
	if (!fout)
	{
		cout << "Error: could not open the output file" << endl;
		cout << "Exiting" << endl;
		return 1;
	}

	int count; 
	double *ptr;
	fin.seekg(0,ios::end);
	count = fin.tellg() / sizeof(double);
	ptr = new(nothrow) double[count]; 
	fin.seekg(0,ios::beg);
	fin.read((char*)ptr, sizeof(double)*count);

	sort(ptr, ptr+count);
	fout.write((char*)ptr, sizeof(double) * count);

	cout << "Sample Size: " << count;
	cout<< "10 smallest in increasing order " << endl;
	for (int i = 0; i < 10; i++)
	{
		cout <<fixed<< ptr[i] << endl;
	}

	cout << endl
		<< "10 largest in decreasing order" << endl;

	for (int k = 1; k <= 10; k++)
	{
		cout << ptr[count - k] << endl;
	}
	fin.close();
	delete[]ptr;
	fout.close();
	return 0;
}