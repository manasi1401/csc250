/***********************************************************//**
*@file
*@brief All the functions neccesary to find the errors and write to files
***************************************************************/

#pragma pack(1)
#include "functions.h"

/**************************************************************************//**
 * @author Manasi Paste
 *
 * @par Description:
 * This Function writes the records with errors to the text file.
 *
 * @param[in]  data- the Structure Record variable which
					holds the information of the individual
 * @param[out]  file- the ofstream file which is already open and
					 ready to be written to
 * @param[in]  num - Zipcode vairable which holds the zipcode
 * @param[in]  birthday- Date variable that holds the extracted birthday
 * @param[in]  Licenced - Date variable which holds the extracted license date
 * @param[in] expirationd- Date variable that holds the extracted expiration date
 *
 * @return none
 *****************************************************************************/

void writestruct(Record data, ofstream &file, Zipcode num, 
	Date birthday, Date Licenced, Date expirationd)
{
	char state1[3];
	char callsign1[6];
	strncpy(state1, data.state,2);
	
	strncpy(callsign1, data.callSign,5);
	callsign1[5] = '\0';
	state1[2] = '\0';

	file << setw(20) << left << "Name:" << data.name << endl
		<< setw(20) << "Address:" << data.address << endl
		<< setw(20) << "City State Zip:" << data.city << ", "
		<<state1 << " ";
	file << num.zip5 << " - "  << num.zip4 << endl;
	file<< setw(20)<< "Birthdate:" << birthday.month<<"/"<<birthday.day<<"/"
		<< birthday.year << endl << setw(20) << "Licensing Dates:" 
		<< Licenced.month << "/" << Licenced.day << "/" << Licenced.year
		<< " - "<< expirationd.month << "/" << expirationd.day << "/" 
		<< expirationd.year << endl << setw(20) << "Class - Callsign:" 
		<< data.radioClass << " - " << callsign1 << endl << endl;
}

/***************************************************************************//**
 * @author Manasi Paste
 *
 * @par Description:
 * This function extracts the zipcode 
 *
 * @param[out] num - The zipcode varible that stores the extracted zipcode
 * @param[in] data - the record varible that holds the binary zipcode
 *
 * @returns none
 ******************************************************************************/

void extractzip(Record data, Zipcode& num)
{
	int zip4mask = 16383;
	int zip5mask=262143;
	int z = data.zipCode;

	num.zip4 = z & zip4mask;
	z=z >> 14;
	num.zip5 = z & zip5mask;	
}

/***************************************************************************//**
 * @author Manasi Paste
 *
 * @par Description:
 * This function extracts a date
 *
 * @param[in] day - the integer that holds the birhtdate
 * @param[out] birthday - the date varible that stores the extracted birthday
 *
 * @returns none
 ******************************************************************************/

void extractdate(int day, Date& birthday)
{	
		int daymask = 63;
		int monthmask = 15;
		int yearmask = 65535;
	
		birthday.day = day & daymask;
		day = day >> 6;
		birthday.month = day & monthmask;
		day=day >> 6;
		birthday.year =day & yearmask;	
}

/***************************************************************************//**
 * @author Manasi Paste
 *
 * @par Description:
 * This function checks if the name field has only A-Z, a-z, space and period.
 *
 * @param[in] a - a charachter array containing the name
 *
 * @returns true -If the name has valid charachters
 * @returns false - If the name field has invalid charchters
 ******************************************************************************/
bool name(char a[])
{
	int alp, sp;
	for (unsigned int i = 0; i < strlen(a); i++)
	{
		alp = isalpha(a[i]);
		sp = isblank(a[i]);
		if (alp == 0 && sp == 0 && a[i] != '.')
			return false;
	}
	return true;
}
/***************************************************************************//**
 * @author Manasi Paste
 *
 * @par Description:
 * This function checks if the address field has only A-Z, a-z, 0-9,
 *  space, pound # and period.
 *
 * @param[in] a - a charachter array containing the address
 *
 * @returns true -If the address field has valid charachters
 * @returns false - If the address field has invalid charchters
 ******************************************************************************/

bool address(char a[])
{
	int alp, sp;
	for (unsigned int i = 0; i < strlen(a); i++)
	{
		alp = isalnum(a[i]);
		sp = isblank(a[i]);
		if (alp == 0 && sp == 0 && a[i] != '.' && a[i] != '#')
			return false;
	}
	return true;
}

/***************************************************************************//**
 * @author Manasi Paste
 *
 * @par Description:
 * This function checks if the first charchter of the state code in 
 * Upper case
 *
 * @param[in] b - first charchter of the state code
 *
 * @returns true -If the frist charchter is in upper case
 * @returns false - If the first charchter is not in upper case
 ******************************************************************************/

bool stateer(char b[])
{
	int check = isupper(b[0]);
	if (check == 0)
		return false;
	return true;
}

/***************************************************************************//**
 * @author Manasi Paste
 *
 * @par Description:
 * This function checks if the state code is a valid statecode
 * by comparing it with vaild statecodes. If it does not match any of the
 * valid stateodes then it is said to be invalid statecode
 *
 * @param[in] b - a cstring containing the statecode
 * @param[in] statecode - a cstring array containing all the
 * possible valid statecodes
 *
 * @returns true -If the statecode is valid
 * @returns false - If the state code is invalid
 ******************************************************************************/

bool statevar(char b[], char statecode[][3])
{
	unsigned int k;
	char a[3];
	strncpy(a, b,2);
	a[2] = '\0';
	
	for (k = 0; k < 51; k++)
	{
		if (_stricmp(a, statecode[k]) == 0)
			return true;

	}
	return false;
}

/***************************************************************************//**
 * @author Manasi Paste
 *
 * @par Description:
 * This function checks if the 5 digit zipcode is valid. that is 
 * it is between 99999 and 10000.
 *
 * @param[in] n - the integer containing the extracted 5 digit zipcode
 *
 * @returns true -If the 5 digit zipcode is valid
 * @returns false - If the 5 digit zipcode is invalid
 ******************************************************************************/

bool zip5error(int n)
{ 
	if (n >= 10000 && n <= 99999)
		return true;
	return false;
}

/***************************************************************************//**
 * @author Manasi Paste
 *
 * @par Description:
 * This function checks if the 4 digit zipcode is valid. that is 
 * it is between 9999 and 1000 or 0.
 *
 * @param[in] n - the integer containing the extracted 4 digit zipcode
 *
 * @returns true -If the 4 digit zipcode is valid
 * @returns false - If the 4 digit zipcode is invalid
 ******************************************************************************/

bool zip4error(int n)
{
	if (n == 0)
		return true;
	if (n >= 1000 && n <= 9999)
		return true;
	return false;
}

/***************************************************************************//**
 * @author Manasi Paste
 *
 * @par Description:
 * This function checks if the month is valid. i.e. it is between 1 and 12. 
 *
 * @param[in] m - the integer containing the extracted month
 *
 * @returns true -If the month is valid
 * @returns false - If the month is invalid
 ******************************************************************************/

bool checkmonth(int m)
{
	if (m > 12 || m < 1)
		return false;
	return true;
}

/***************************************************************************//**
 * @author Manasi Paste
 *
 * @par Description:
 * This function checks if the day is valid.
 *  i.e. it is between 1 and 30 for month 4, 6,9 and 11. 
 * between 1 and 28 for month 2
 * between 1 and 31 for rest of the months 
 *
 * @param[in] m - the integer containing the extracted month
 * @param[in] d - the integer containing the extracted day
 *
 * @returns true -If the day is valid
 * @returns false - If the month is invalid
 ******************************************************************************/

bool checkday(int d, int m)
{
	if (m == 2){
		if (d < 1 || d>28)
			return false;
		return true;
	}
	if (m == 4 || m == 6 || m == 9 || m== 11){
		if (d < 1 || d>30)
			return false;
		return true;
	}
	if (d < 1 || d>31)
			return false;
		return true;

}

/***************************************************************************//**
 * @author Manasi Paste
 *
 * @par Description:
 * This function checks if the year is valid. 
 * i.e. it is between 1900 and 2017
 *
 * @param[in] y - the integer containing the extracted year
 *
 * @returns true -If the year is valid
 * @returns false - If the year is invalid
 ******************************************************************************/

bool checkyear(int y)
{
	if (y< 1900 || y>2017)
		return false;
	return true;
}

/***************************************************************************//**
 * @author Manasi Paste
 *
 * @par Description:
 * This function checks if the expiration date is greater than 
 * license date
 *
 * @param[in] y1 - the integer containing the expiration date
 * @param[in] y2 - the integer containing the license date
 *
 * @returns true -If the expiration date is after the license date
 * @returns false - If the expiration date is before the license date
 ******************************************************************************/

bool checkexl(int y1, int y2)
{
	if (y1 > y2)
		return true;
	return false;
}

/***************************************************************************//**
 * @author Manasi Paste
 *
 * @par Description:
 * This function checks if the Radio class is valid.
 * it checks if the Radio call matches with any of the valid Radio Calls
 *
 * @param[in] a - charachter containing the Radio Class
 * @param[in] b - charachter array containing the possible valid Radio Class
 *
 * @returns true -If the Radio class is valid
 * @returns false - If the Radio class is invalid
 ******************************************************************************/

bool checkclass(char a, char b[])
{
	toupper(a);
	for (unsigned int i = 0; i < strlen(b); b++)
	{
		if (a == b[i])
			return true;
	}
	return false;
}

/***************************************************************************//**
 * @author Manasi Paste
 *
 * @par Description:
 * This function checks if the first charchter of the Call Sign is either K or W or N
 *
 * @param[in] data - The Record varible which holds the information of the individual
 *
 * @returns true -If the Call Sign is valid
 * @returns false - If the Call Sign is invalid
 ******************************************************************************/

bool checkcalsg1(Record data)
{
	char callsign1[6];
	strncpy(callsign1, data.callSign, 5);
	callsign1[5] = '\0';
	if (callsign1[0] == 'K' || callsign1[0] == 'W' || callsign1[0] == 'N')
		return true;
	return false;
}

/***************************************************************************//**
 * @author Manasi Paste
 *
 * @par Description:
 * This function checks if the second, fourth and fifth charchter of the Call Sign 
 * are alphabets A-z or a-z.
 *
 * @param[in] data - The Record vairble which holds the information of the individual
 *
 * @returns true -If the second, fourth and fifth Call Sign charachters are valid
 * @returns false - If the second, fourth and fifth Call Sign charachters are invalid
 ******************************************************************************/

bool checkcalsg245(Record data)
{
	char callsign1[6];
	strncpy(callsign1, data.callSign, 5);
	callsign1[5] = '\0';

	if (isalpha(callsign1[1]) == 0 || isalpha(callsign1[3]) == 0 || 
		isalpha(callsign1[4]) == 0)
		return false;
	return true;
}

/***************************************************************************//**
 * @author Manasi Paste
 *
 * @par Description:
 * This function checks if the third charchter of the Call Sign is a digit 0-9
 *
 * @param[in] data - The Record varible which holds the information of the individual
 *
 * @returns true -If the third Call Sign charachters is a digit
 * @returns false - If the third Call Sign charachters is not a digit
 ******************************************************************************/

bool checkdigit(Record data)
{
	char callsign1[6];
	strncpy(callsign1, data.callSign, 5);
	callsign1[5] = '\0';
	if (isdigit(callsign1[2]) == 0)
		return false;
	return true;
}

/***************************************************************************//**
 * @author Manasi Paste
 *
 * @par Description:
 * This function checks if the first, second, fourth and fifth charchter of the Call Sign 
 * are in upper case
 *
 * @param[in] data - The Record varible which holds the information of the individual
 *
 * @returns true -If the second, fourth and fifth Call Sign charachters are valid
 * @returns false - If the second, fourth and fifth Call Sign charachters are invalid
 ******************************************************************************/

bool checkcase(Record data)
{
	char c[6];
	strncpy(c, data.callSign, 5);
	c[5] = '\0';
	if (isupper(c[0])==0|| isupper(c[1])==0 || isupper(c[3]) ==0 
		||isupper(c[4])==0)
		return false;
	return true;
}

/***************************************************************************//**
 * @author Manasi Paste
 *
 * @par Description:
 * This function fills up the boolean array after checking for the errors
 *
 * @param [out] error - the array to be processed
 * @param[in] data - The Record vairble which holds the information of the individual
 * @param[in] num- The Zipcode variable containing the extracted zipcode
 * @param[in] birthday - the date variable containing the extracted birhtdate
 * @param[in] Licenced - the date variable containing the extracted license date
 * @param[in] expirationd - the date variable containing the the extracted expiration date
 * @param[in] statecode - the cstring array containing the list of valid statecodes
 * @param[in] calsg - the charachter array containing the list of valid 
 * first chrachters of the call sign
 *
 * @returns none
 ******************************************************************************/

void fiilar(bool error[], Record data, Zipcode num, Date birthday, Date Licenced, 
	Date expirationd, char statecode[][3], char calsg[])
{
	error[0] = name(data.name);
	error[1] = address(data.address);
	error[2] = name(data.city);
	error[3] = statevar(data.state, statecode);
	error[4] = stateer(data.state);
	error[5] = zip5error(num.zip5);
	error[6] = zip4error(num.zip4);
	error[7] = checkmonth(birthday.month);
	error[8] = checkday(birthday.day, birthday.month);
	error[9] = checkyear(birthday.year);
	error[10] = checkmonth(Licenced.month);
	error[11] = checkday(Licenced.day, Licenced.month);
	error[12] = checkyear(Licenced.year);
	error[13] = checkmonth(expirationd.month);
	error[14] = checkday(expirationd.day, expirationd.month);
	error[15] = checkyear(expirationd.year);
	error[16] = checkexl(expirationd.year, Licenced.year);
	error[17] = checkclass(data.radioClass, calsg);
	error[18] = checkcalsg1(data);
	error[19] = checkcalsg245(data);
	error[20] = checkdigit(data);
	error[21] = checkcase(data);
}

/***************************************************************************//**
 * @author Manasi Paste
 *
 * @par Description:
 * This function that prints out appropriate error message
 *
 * @param [in] error - the array to be processed
 * @param[out] file - the already opened ofstream file to which errors are to written
 *
 * @returns none
 ******************************************************************************/

void printerrors(bool error[], ofstream &file)
{
	if (error[0] == false)
		file << "Invalid character in the name field" << endl;;
	if (error[1] ==false)
		file << "Invalid character in the address field " << endl;
	if (error[2] == false)
		file << "Invalid character in the city field " << endl;
	if (error[3] == false)
		file << "Invalid State code " << endl;
	if (error[4] == false)
		file << "First character of State code is not upper case " << endl;
	if (error[5] == false)
		file << "Invalid 5 digit zip code" << endl;
	if (error[6] == false)
		file << "Invalid 4 digit zip code " << endl;
	if (error[7] == false)
		file << "Invalid month in Birthday " << endl;
	if (error[8] == false)
		file << "Invalid day in Birthday" << endl;
	if (error[9] == false)
		file << "Invalid year in Birthday " << endl;
	if (error[10] == false)
		file << "Invalid month in License " << endl;
	if (error[11] == false)
		file << "Invalid day in License " << endl;
	if (error[12] == false)
		file << "Invalid year in License" << endl;
	if (error[13] == false)
		file << "Invalid month in Expiration " << endl;
	if (error[14] == false)
		file << "Invalid day in Expiration " << endl;
	if (error[15] == false)
		file << "Invalid year Expiration" << endl;
	if (error[16] == false)
		file << "Expiration Date is not after the License Date" << endl;
	if (error[17] == false)
		file << "Radio Class code is invalid" << endl;
	if (error[18] == false)
		file << "Invalid first character in call sign " << endl;
	if (error[19] == false)
		file << "Invalid second, fourth or fifth character in call sign " 
		<< endl;
	if (error[20] == false)
		file << "Invalid digit in call sign" << endl;
	if (error[21] == false)
		file << "Call Sign not upper case" << endl;
}
/***************************************************************************//**
 * @author Manasi Paste
 *
 * @par Description:
 * This function checks if there are any errors detected
 *
 * @param [in] error - the array to be processed
 *
 * @returns true - even if a single error is found
 * @returns false - If no error is found
 ******************************************************************************/
bool checkarr(bool error[])
{
	for (unsigned int i = 0; i < 22; i++)  
	{
		if (error[i] == false)
			return false;
	}
	return true;
}