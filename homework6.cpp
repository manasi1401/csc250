#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>

using namespace std;
//prototypes of the funtions
void firstMiddleLast(char fullname[], char first[], char middle[], char last[]);
void lastFirstMiddle(char fullname[], char first[], char middle[], char last[]);
int main()
{
	char name[80];
	char fullname[80];
	char first[40];
	char middle[40];
	char last[40];
	
	while (cout << "Enter the name: " && cin.getline(name,80))
	{
		
		strcpy(fullname, name);
		// if there is no comma then the format is first , middle , last
		if (strchr(fullname, ',') == NULL)
		{
			firstMiddleLast(fullname, first, middle, last);
			
		}
		//if there is a comma then the format is last, first, middle
		if (strchr(fullname, ',') != NULL)
		{
			lastFirstMiddle(fullname, first, middle, last);
		}
		cout << endl;
		cout <<"\t"<< "First name: " << first << endl;
		cout <<'\t'<< "Middle name: " << middle << endl;
		cout <<'\t'<< "Last name: " << last << endl << endl;
		
	}
	return 0;
}

//if the the order of the name is first name, middle name, last name
void firstMiddleLast(char fullname[], char first[], char middle[], char last[])
{
	char *token;
	token = strtok(fullname, " ");
	strcpy(first, token);
	token = strtok(NULL, " ");
	strcpy(middle, token);
	token = strtok(NULL, " ");
	strcpy(last, token);
}
//if the order of the name is last name,first name, middle name
void lastFirstMiddle(char fullname[], char first[], char middle[], char last[])
{
	char *token;
	token = strtok(fullname, ",");
	strcpy(last, token);
	token = strtok(NULL, " ");
	strcpy(first, token);
	token = strtok(NULL, " ");
	strcpy(middle, token);
}