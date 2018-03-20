/*************************************************************************//**
 * @file
 *
 * @brief Contains the main program that peforms the correct list operations
 *
 * @mainpage Program #2 - List Mania
 * 
 * @section course_section Course Information
 *
 * @author Team 20 - Remington Thurber, Manasi Paste, Harry Kramer
 * 
 * @date March 27
 * 
 * @par Professor:
 *         Roger Schrader
 * 
 * @par Course:
 *         CSC250 - M002 - 1:00-1:50 PM
 * 
 * @par Location:
 *         McLaury - 313
 *
 * @section program_section Program Information 
 * 
 * @details
 * List Mania! This program contains various implementations of linked lists. \n
 * One of these is an ordered list class, which will automatically sort any \n
 * inserted integer into the correct place in the list. The other linked list \n
 * implementation is an unordered list class, which will only insert integers \n
 * at the front or end of the list. Both of these classes are singly linked \n
 * lists, with a 'headptr' that points to the first element. All of the nodes \n
 * in the lists are protected in the private section of their respective \n
 * classes. \n
 *
 * These nodes are the structs that represent each element in the list. These \n
 * nodes contain two data members: a pointer to the next node called 'next', \n
 * and an integer value called 'n'. \n
 *
 * All of this code works together to implement severals rules. In short, three \n
 * lists are created. The first is ordered, the second is unordered, and the \n
 * thirds is also unordered. The rules for insertion into these lists are as \n
 * follows: \n
 * 1. Once a number has been put in a list, go to the next number. \n
 * 2. If the number is not in list 1, insert it. \n
 * 3. Otherwise, remove the number from list 1, and place it in the front of \n
 * list 2 if it is not already present in list 2. \n
 * 4. Otherwise, remove the number from list 2, and place at the end of list 3, \n
 * if it is not already present in list 3. \n
 * 5. Otherwise, remove the number from list 3, and place it back at the front \n
 * of list 3. \n
 *
 * Finally, to run this program, do 'prog2.exe numbers.txt result.txt', \n
 * where 'numbers.txt' is a text file with a list of whitespace delimited \n
 * numbers to be inserted into lists, and 'result.txt' is a text file in \n
 * which you want the results to be outputted to. \n
 *
 * @section compile_section Compiling and Usage 
 *
 * @par Compiling Instructions: 
 *      Build and Run with Visual Studio
 * 
 * @par Usage:
   @verbatim
   C:\Users\7329549\Documents\mines\prog2\Debug\prog2.exe numbers.txt result.txt
   @endverbatim
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 * @par Modifications and Development Timeline:
   https://gitlab.mcs.sdsmt.edu/csc250s17prog2/team20/commits/master
 *
 *****************************************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>

#include "Orderedlist.h"
#include "Unorderedlist.h"

using namespace std;

/**************************************************************************//**
 * @author Remington Thurber, Manasi Paste, Harry Kramer
 * 
 * @par Description:
 *
 * This function parses the command line arguments provided. It then opens
 * the input numbers file, and output result file. It reads in each number
 * from the input file and places it into the correct linked list. At the end,
 * it outputs the results to the result file.
 *
 *
 * @param[in] argc - Integer holding the number of command line arguments.
 * @param[in] argv - Array of character arrays, holding command line arguments.
 * 
 * @returns 0 - The program ran successfully.
 * @returns 2 - Incorrect command line argument usage.
 * @returns 3 - There was an error opening the input file.
 * @returns 4 - There was an error opening the output file.
 *****************************************************************************/
int main( int argc, char* argv[] )
{
    orderedlist list1;
    unorderedlist list2;
    unorderedlist list3;
    
    int num;
    int i = 0;
    //check if correct number of arguments are passed into the main function
    if ( argc != 3 )
    {
        //print out the error and the correct usage if wrong no. of arg. passed
        cout << "Incorrect amount of command line arguments." << endl
             << "Usage: prog2.exe numbers.txt result.txt\n" << endl;
        return 2;
    }

    ifstream numbers( argv[1] );
    ofstream results( argv[2] );
    //if the input file fails to open print out error.
    if ( !numbers )
    {
        cout << "Failed to open the input file" << endl;
        return 3;
    }
    //if the out put file fails to open print out error
    if ( !results )
    {
        cout << "Failed to open the output file" << endl;
        return 4;
    }
    //reading in one intger at a time from the file
    while ( numbers >> num )
    {
        //if the number doesn't exists in list1 insert it
        if ( !list1.find(num) )
        {
            list1.insert( num );
        }
        //if it exists remove it from list1
        else
        {
            list1.remove( num );
            //if the number doesn't exists in list2 insert it
            if ( !list2.find( num ) )
            {
                list2.insertBegin( num );
            }
            //if it does exist remove it from list2
            else
            {
                list2.remove( num );
                //if the number doesn't exist in list3 insert it
                if ( !list3.find( num ) )
                {
                    list3.insertEnd( num );
                }
                //if it does exist remove it and add it in the begining of the list3
                else
                {
                    list3.remove( num );
                    list3.insertBegin( num );
                }
            }
        }
        i++;
    }
    //print out list1
    results << "List 1: size = " << list1.size() << endl << setw( 10 );
    list1.print( results );
    //print out list2
    results << "List 2: size = " << list2.size() << endl << setw( 10 );
    list2.print( results );
    //print out list3
    results << "List 3: size = " << list3.size() << endl << setw( 10 );
    list3.print( results );
    //close the input file
    numbers.close();
    //close the output file
    results.close();

    return 0;
}