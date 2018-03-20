#include<iostream>
#include<string>

using namespace std;

//prototypes of the funtions

void lastFirstMiddle(string full, string &first, string &middle, string &last);
void firstMiddleLast(string full, string &first, string &middle, string &last);

int main()
{
	//declaring string variables
	string fullname;
	string first;
	string middle;
	string last;

	while (cout << "Enter the name: " && getline(cin, fullname))
	{
		
		// if there is no comma then the format is first , middle , last
		string::size_type id = fullname.find(",");
		if (id== string::npos)
			firstMiddleLast(fullname, first, middle, last);

		//if there is a comma then the format is last, first, middle
		if (id != string::npos)
		lastFirstMiddle(fullname, first, middle, last);
			
		//output on the screen
		cout << endl;
		cout << "\t"<< "First name: " << first << endl;
		cout << "\t"<<"Middle name: " << middle << endl;
		cout <<"\t"<< "Last name: " << last << endl << endl;

	}
	return 0;
}

//if the the order of the name is first name, middle name, last name
void firstMiddleLast(string full, string &first, string &middle, string &last)
{
	string::size_type id = full.find(" ");
	first = full.substr(0, id);
	string::size_type idx = full.find(" ", id+1);
	middle = full.substr(id+1, idx-id);
	last = full.substr(idx+1);
	
}
//if the order of the name is last name,first name, middle name
void lastFirstMiddle(string full, string &first, string &middle, string &last)
{
	string::size_type en = full.find(",");
	last = full.substr(0, en);
	string::size_type enx = full.find(" ", en + 2);
	first = full.substr(en + 2, enx - en-2);
	middle = full.substr(enx + 1);

}