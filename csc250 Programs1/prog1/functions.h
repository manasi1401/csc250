/***********************************************************//**
*@file
*@brief header file required for functions.cpp
***************************************************************/
#pragma pack(1)

#define  _CRT_SECURE_NO_WARNINGS
#include< iostream>
#include <fstream>
#include<iomanip>
#include<cstring>
#include <cctype>
#ifndef __FUNCTIONS__H__ 
#define __FUNCTIONS__H__

#endif

using namespace std;
/*!
*@brief Holds the information about a student
*/
struct Record
{ 
	/*!The Name of the Worker*/
	char name[30];   
	/*!The Address of the worker*/
	char address[30];  
	/*! The city */
	char city[28];
	/*! The State*/
	char state[2]; 
	/*! The Zipcode*/
	unsigned int zipCode;   
	/*! Birthday */
	unsigned int birthDate;
	/*! The License Date*/
	unsigned int licensedDate;     
	/*! The Expiration Date*/
	unsigned int expirationDate;
	/*! The Radio Class*/
	char radioClass;   
	/*! The Call Sign*/
	char callSign[5]; 
	}; 
/*!
*@brief Holds the Zipcode
*/
struct Zipcode
{
	/*! Holds the 5 digit Zipcode*/
	int zip5;
	/*! Holds the 4 digit Zipcode*/
	int zip4;
};

/*!
*@brief Holds any Date
*/
struct Date
{
	/*! Holds the day*/
	int day;
	/*! Holds the month*/
	int month;
	/*! Holds the year*/
	int year;
};
/**************************************************************************//**
*                         Function Prototypes
******************************************************************************/
void writestruct(Record data, ofstream &file, Zipcode num, 
	Date birthday, Date Licenced, Date expirationd);
void extractzip(Record data, Zipcode& num);
void extractdate(int day, Date& birthday);
bool name(char a[]);
bool address(char a[]);
bool stateer(char b[]);
bool statevar(char b[], char statecode[][3]);
bool zip4error(int n);
bool zip5error(int n);
bool checkyear(int y);
bool checkday(int d, int m);
bool checkmonth(int m);
bool checkexl(int y1, int y2);
bool checkclass(char a, char b[]);
bool checkcalsg1(Record data);
bool checkcalsg245(Record data);
bool checkdigit(Record data);
bool checkcase(Record data);
void fiilar(bool error[], Record data, Zipcode num, Date birthday, 
	Date Licenced, Date expirationd, char statecode[][3], char calsg[]);
void printerrors(bool error[], ofstream &file);
bool checkarr(bool error[]);