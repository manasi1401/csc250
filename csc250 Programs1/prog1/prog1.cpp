/*********************************************************//**
*@file
*@brief The main function reads the records, finds the errors 
* and writes them accordingly to binary and text file
*
*@mainpage Program 1
*
*@section course-section Course Information
*
*@author Manasi Paste
*
*@date February 19, 2017
*
*@par Instructor:
*				Dr. Schrader
*
*@par Course: 
*			CSC 250 - Secction 2- 1-2 pm
* @par Location:
*				Mclaury Room 313
*
*@section program_section Program Info
*
* @details This program reads the database in the binary file
* and checks for the errors in the database. If no errors are found
* then it writes the record to a binary file for storing. But if
* any errors is found it writes the record to the text file
* along with information of what the errors are.
*
*
* @section compile_section Compiling and Usage
*
* @par Compiling Instructions:
*      The main functions have arguments. It needs to be compiled using the following usage.
*
* @par Usage:
@verbatim
c:\> csc250s17programs.exe dbham.bin good.bin bad.txt

@endverbatim
*
* @section todo_bugs_modification_section Todo, Bugs, and Modifications
*
* @bug The upper limit for dates does not match with the bintool. The program
* therefore the errors differ when i type 2017/ 2016, which is actually acceptable. 
* I assumed that it is an error with the bintool.
*
*
* @par Modifications and Development Timeline:
@verbatim
Date           Modification
-------------  -------------------------------------------------------------
02-13-2017		Verifying Command Line Argument
02-13-2017		Reading till the end of the file & output to text file
02-13-2017		Extract Zipcode
02-14-2017		All functions completed
02-19-2017		Correction of functions
02-21-2017		Doxygen Documentations
02-25-2017		Final completion

@endverbatim
*

*********************************************************/
#pragma pack(1)
#include "functions.h"

using namespace std;
/**************************************************************************//**
 * @author Manasi Paste
 *
 * @par Description:
 * This function opens up both the binary files and the text file. 
 * It checks if it is opened else exits after showing error message.
 * It initially checks if correct number of command line arguments are passed
 * Then the function reads the input file one record at a time. 
 * it extracts the data and sorts it accordingly to the binary and text output file.
 *
 * @param[in]      argc - a count of the command line arguments used to start
 *                        the program.
 * @param[in]     argv - a 2d character array of each argument.  Each token
 *                        occupies one line in the array.
 *
 * @returns 0 program ran successful.
 * @returns 1 the program fail or there was an error.
 *
 *****************************************************************************/

int main(int argc, char* argv[])
{
	/*The List of valid State codes*/
	char statecode[51][3] = { "AL", "AK", "AZ", "AR", "CA", "CO", "CT", "DE", "FL", 
		"GA", "HI", "ID", "IL", "IN", "IA", "KS", "KY", "LA", "ME", "MD", "MA",
		"MI", "MN", "MS", "MO", "MT", "NE", "NV", "NH", "NJ", "NM", 
		"NY", "NC", "ND", "OH", "OK", "OR", "PA", "RI", "SC",
		"SD", "TN", "TX", "UT", "VT", "VA", "WA", "WV", "WI", "WY" };

	/*The list of valid Call sign first charachters*/
	char calsg[13] = { 'N', 'T', 'P', 'G', 'A', 'X', 'n', 't', 'p', 'g', 'a', 'x' };
	
	/*If 4 arguments are not passed in through the command prompt print
	the command line format and exit*/
	if (argc != 4)
	{
		cout << "Program Usage : myprog.exe inputfile.txt"
			<<"outputfile1.txt outputfile2.txt" << endl << "Exiting" << endl;
		return-1;
	}
	
	/*The input binary file*/
	ifstream fin;
	ofstream good /*the output binary file */, bad /*the output text file*/;
	
	fin.open(argv[1], ios::binary | ios:: in);
	
	//If the input Binary file doesnot open print error.
	if (!fin) 
	{
		cout << "Error" << endl << "Input Binary file didnot open" << endl
			<< "Exiting" << endl;
		return - 1;
	}
	good.open(argv[2], ios::out | ios::binary | ios:: trunc);
	bad.open(argv[3], ios::out |ios::trunc);
	
	//If the ouput binary file doesnot open print error
	if (!good)
	{
		cout << "Error" << endl << "Output binary file didnot open" << endl
			<< "Exiting" << endl;
		return -1;
	}
	
	//If the output text file doesnot open print error
	if (!bad) 
	{
		cout << "Error" << endl << "Output text file didnot open" << endl
			<< "Exiting" << endl;
		return -1;
	}
	
	//Boolean Array to store the errors
	bool error[23];
	//Record variable to store the data read in
	Record data; 
	//a Zipcode variable to store the zipcode
	Zipcode num;
	//Date variables for birthday, License date and expiration date
	Date birthday, Licensed, expirationd; 
	
	//Till it continues to read the binary file
	while (fin.read((char*)&data, sizeof(Record))) 
	{
		/*extract the zipcode from the binary file*/
		extractzip(data, num); 
		//extract the birth date from the binary file
		extractdate(data.birthDate,birthday); 
		//Extract the license Date from the binary file
		extractdate(data.licensedDate, Licensed); 
		//Extract the expiration date from th binary file
		extractdate(data.expirationDate, expirationd);
		//store the errors in the Boolean arrray
		fiilar(error, data, num, birthday, Licensed, expirationd, statecode, calsg); 
		//Check if there are any errors in the record found
		if(checkarr(error)== true) 
			//If no errors are found write the data to a binary file
		good.write((char *)&data, sizeof(Record)); 
		//If any errors is found write the data to Text file
		else 
		{
			//Write to the text file
			writestruct(data, bad, num, birthday, Licensed, expirationd); 
			//Prints out what the errors are
			printerrors(error, bad); 
			bad << "=============================================="
				<<"=======" << endl;
		}
	}
	
	fin.close(); //close the input file
	good.close(); //close the output binary file
	bad.close(); //close the output text file
	return 0;
}
