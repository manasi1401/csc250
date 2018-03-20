#include <iostream>

using namespace std;
//Prototypes 
int min(int ptr[], int n);
int max(int ptr[], int n);
int main()
{
	int i=0;

	//initializing the pointer to to null
	int *ptr = nullptr; 
	int size;
	int minval, maxval;

	//prompt the user for the size of the array
	cout << "Enter the number of elements of data set: ";
	cin >> size;

	//allocating a 1D array of the size guvn by the user
	ptr = new (nothrow) int[size];

	//fill in the array from the keyboard
	for (i; i < size; i++)
	{
		cin >> ptr[i];
	}

	//minimum
	minval = min(ptr, size);
	//maximum
	maxval = max(ptr, size);
	
	cout << "The Min is " << minval << endl;
	cout << "The Max is " << maxval << endl;
	//deleting the memory allocated to the pointer
	delete[]ptr;
	return 0;
}
//function to find the minimum
int min(int ptr[], int n)
{
	int min = 0;
	for (int i = 1; i < n; i++)
		if (ptr[min]>ptr[i])
			min = i;
	return ptr[min];
}
//function to find the maximum
int max(int ptr[], int n)
{
	int max = 0;
	for (int i = 1; i < n; i++)
		if (ptr[max] < ptr[i])
			max = i;
	return ptr[max];
}