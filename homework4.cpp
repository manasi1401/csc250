/******************************************************************************
* Name: Paste, Manasi
* ID: 7404855
* Section: M0002
* Homework 4
*****************************************************************************/
#include <iostream>
#include <iomanip>

using namespace std;


int main()
{
	float x, average=0.0, sum=0.00;

	float min, max;

	int count = 1;
	
	while (cin >> x)
	{
		//sum of the input numbers
		sum += x;
		cout << "Count = " << count << endl;
		//average of the numbers inputed
		average = sum / count;

		if (count == 1)
		{
			min = x;
			max = x;
		}
		//adjusting the min
		if (min >= x)
			min = x;
		
		//adjusting the max
		if (max <= x)
			max = x;

		//output the min, max, sum and average
		cout <<setprecision(3)<<fixed<<"Minimum = " << min << setw(20) << "Maximum = " << max << endl
			<< "Sum = " << sum << setw(20) << "Average = " << average << endl << endl;
		count++;
	}
	return 0;
}

