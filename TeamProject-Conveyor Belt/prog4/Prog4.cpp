/*************************************************************************//**
 * @file
 *
 * @brief Contains the main program that peforms..
 *
 * @mainpage Program #4 - Conveyor Belt
 * 
 * @section course_section Course Information
 *
 * @author Team 20 - Remington Thurber, Manasi Paste, Harry Kramer
 * 
 * @date April 28
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
 * @details Conveyor Belts! This program consists of incoming boxes
 * and three conveyor belts, "A", "B", and "C". All these belts have varying
 * widths. Each conveyor belt moves in same direction and drops the packages
 * into a bin. You have to keep track of the package number and the belt on
 * which it is placed. \n
 * All packages are six sided boxes with 3 dimensions. The box is stored as a 
 * structure. Each dimension is given in inches. 
 * The proper belt on which the box is to be placed should be the narrowest yet 
 * fits the box. After the belt is chosen the boxes are placed in such a way 
 * that it occupies minimum space on the belt. All three conveyors have same length
 * Once the length of a box over hanging on the belt becomes greater than
 * or equal to half its actual lenght it drops into the bin. \n 
 * You have to read in a file till you encounter 0 0 0 and each simulation 
 * ends when you read in -1 -1 -1. After each simulation you can read in new belt
 * widths. The output should show which box drops of the conveyor belt and 
 * from which belt. The output should be on file called "run.out".
 * .\n Two command line 
 * arguments are passed one the input file and the other is the length of the 
 * belts. Therefore the command line argument is "prog4.exe data.sim [length (number)]"\n
 * 
 * 

 * @section compile_section Compiling and Usage 
 *
 * @par Compiling Instructions: 
 *      Build and Run with Visual Studio
 * 
 * @par Usage:
   @verbatim
   C:\Users\7329549\Documents\mines\prog2\Debug\prog4.exe data.sim [length of the belts (number)]
   @endverbatim
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 * @par Modifications and Development Timeline:
   https://gitlab.mcs.sdsmt.edu/csc250s17prog4/team20/commits/master
 *
 *****************************************************************************/

#include "belt.h"
#include "Myqueue.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

/**************************************************************************//**
*                         Function Prototypes
******************************************************************************/
void check(int arr[3], int bw);
void swapbelts(belt *conveyors[]);

/**************************************************************************//**
 * @author Remington Thurber, Manasi Paste, Harry Kramer
 * 
 * @par Description:
 * Reads in the incoming box and calls the check function to orient the box.
 * It adds the box to the proper belt and calls the fucntions to see which 
 * boxes get dropped and drops the boxes from th conveyor belt. After every simulation 
 * it calls the clear funciton to clear the belts.
 *
 *
 * @param[in] argc - Integer holding the number of command line arguments.
 * @param[in] argv - Array of character arrays, holding command line arguments.
 * 
 * @returns 0 - The program ran successfully.
 * @returns 2 - If the command line argument is incorrect
 * @returns 3 - If the input file didn't open
 * @returns 4 - If the output file doesn't open
 *****************************************************************************/
int main( int argc, char* argv[] )
{
    if ( argc != 3 )
    {
        cout << "Incorrect number of command line arugments." << endl
             << "Usage: prog4.exe data.sim beltLength";
        return 2;
    }

    ifstream fin( argv[1] );
    ofstream fout( "run.out" );

    // check if fin opened
    if ( !fin )
    {
        cout << "Could not open input file." << endl;
        return 3;
    }
    // check if fout opened
    if ( !fout )
    {
        cout << "Could not open output file." << endl;
        return 4;
    }

    int beltLength = atoi(argv[2]);
    int beltWidths[3];
    int currentBoxNumber = 1;
    int currentBelt;
    int caseNumber = 1;

    fin >> beltWidths[0] >> beltWidths[1] >> beltWidths[2];

    belt one( beltWidths[0], beltLength, 'A' );
    belt two( beltWidths[1], beltLength, 'B' );
    belt three(beltWidths[2] , beltLength, 'C');
    belt *conveyors[3] = { &one, &two, &three };
    box incomingBox;
    box fallingBox;

    int boxdim[3];
    
    while ( beltWidths[0] != 0 || beltWidths[1]!= 0 || beltWidths[2] != 0 )
    {
        // Sort conveyor belts by width inside of the array
        swapbelts(conveyors);

        sort(beltWidths, beltWidths + 3);

        // Output the case number
        fout << "Case #" << caseNumber << endl;

        fin >> boxdim[0]>> boxdim[1] >> boxdim[2];
        sort(boxdim, boxdim + 3);

        while (boxdim[0] != -1 || boxdim[1] != -1 || boxdim[2] != -1)
        {
            if (boxdim[0] <= beltWidths[0])
            {
                // use belt 1
                check(boxdim, beltWidths[0]);
                currentBelt = 0;
            }
            else if (boxdim[0] <= beltWidths[1])
            {
                // use belt 2
                check(boxdim, beltWidths[1]);
                currentBelt = 1;
            }
            else
            {
                // use belt 3
                check(boxdim, beltWidths[2]);
                currentBelt = 2;
            }

            // put dimensions into the actual box
            incomingBox.boxNumber = currentBoxNumber;
            incomingBox.width = boxdim[0];
            incomingBox.depth = boxdim[1];
            incomingBox.height = boxdim[2];

            // add box to the conveyor
            conveyors[currentBelt]->addBox( incomingBox );

            // check if box fell off
            while ( conveyors[currentBelt]->boxWillDrop() )
            {
                // remove it from belt if it should fall off
                fallingBox = conveyors[currentBelt]->removeBox();
                // output that it fell off
                fout << "\tBox #" << fallingBox.boxNumber
                    << " fell off Belt " << conveyors[currentBelt]->getname() << endl;
            }

            // read in some more
            fin >> boxdim[0] >> boxdim[1] >> boxdim[2];
            sort(boxdim, boxdim + 3);

            // Increment the number of the current box
            currentBoxNumber++;
        }
        //clear the belts for next simulation
        conveyors[0]->clear();
        conveyors[1]->clear();
        conveyors[2]->clear();
        //read in hte belt widths
        fin >> beltWidths[0] >> beltWidths[1] >> beltWidths[2];
        //set the belts to the new beltwidths
        one.setWidth(beltWidths[0]);
        two.setWidth(beltWidths[1]);
        three.setWidth(beltWidths[2]);
        //set the number of boxes to 1
        currentBoxNumber = 1;
        //increment the case number
        caseNumber++;

        fout << endl;
    }

    fin.close();
    fout.close();
    return 0;
}
/**************************************************************************//**
 * @author Manasi Paste
 * 
 * @par Description:
 *
 * This function sorts the belts in the increasing order of their 
 * belt widths.
 * 
 * @param [in, out] conveyors - the array that stores the belts
 *
 *****************************************************************************/
void swapbelts(belt *conveyors[])
{
    //sorting the belts according to the increasing order 
    //of their belt width.
    if (conveyors[0]->getWidth() > conveyors[1]->getWidth())
    {
        swap(conveyors[0], conveyors[1]);
    }
    if (conveyors[0]->getWidth() > conveyors[2]->getWidth())
    {
        swap(conveyors[0], conveyors[2]);
    }
    if (conveyors[1]->getWidth() > conveyors[2]->getWidth())
    {
        swap(conveyors[1], conveyors[2]);
    }
}

/**************************************************************************//**
 * @author Manasi Paste, Remington Thurber
 * 
 * @par Description:
 *
 * This function orients the box in such a way that it is the perfect fit for
 * the given width of the belt.
 * 
 * @param [in, out] arr - the array that stores the dimesnions of the box
 * @param [in] bw - contains the belt width
 *
 *****************************************************************************/
void check(int arr[3], int bw)
{
    //vector to store the differences
    vector <int> v;
    //the differrence between the dimensions and 
    //belt width
    v.push_back(bw- arr[0]);
    v.push_back(bw - arr[1]);
    v.push_back(bw -arr[2]);

    sort(v.begin(), v.end());
    //the smallest positve difference dimension is set as width
    if (v[0] >= 0)
    {
        arr[0] = v[0];
        v.erase(v.begin() + 0);
    }
    else if (v[1] >= 0)
    {
        arr[0] = v[1];
        v.erase(v.begin() + 1);
    }
    else if (v[2] >= 0)
    {
        arr[0] = v[2];
        v.erase(v.begin() + 2);
    }

    // add belt width back
    arr[0] = bw  - arr[0];
    //length
    arr[1] = bw - v[1] ;
    //height
    arr[2] = bw - v[0] ;
}