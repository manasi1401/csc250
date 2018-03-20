/*********************************************************//**
*@file
*@brief The main function reads the maze and calls the solve function.
* It then prints out the solved maze with the shortest path.
*
*@mainpage Program 3
*
*@section course-section Course Information
*
*@author Manasi Paste
*
*@date April 13, 2017
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
* @details This program reads in a maze. The maze (map) is the layout of tunnels.
* as indicated by the map you have to reach to the position marked 'E' on the map. 
* You are trapped inside the maze and are required to reach the end 'E' in the 
* shortest possible path. First you have to read in 2 command line. the second 
* argument is the name of the input file which contains all the mazes. You have to 
* read in all the mazes until the end of the file and solve them one at a time. 
* The mazes are of different sizes but its dimensions are given in the file. 
* That means you have to dynamically allocate memory for the maze. 
* You are only allowed to more up, down, left and right. Diagonal moves 
* are not allowed. You are given the starting position and you have to 
* count steps till the 'E' is encounterd. You cant move through '*' - 
* the wall and 'L' - lava. You can move through the blank spaces ' ' and 
* water 'W'. But traversing water costs you an extra step as it slows
* you down. The path on a blank space is marked '-' and through water is marked '='.
* You are allowed to solve only using backtracking algorithm.
*
* @section compile_section Compiling and Usage
*
* @par Compiling Instructions:
*      The main functions have arguments. It needs to be compiled using the following usage.
*
* @par Usage:
@verbatim
c:\> prog3.exe maze.maz

@endverbatim
*
* @section todo_bugs_modification_section Todo, Bugs, and Modifications
*
* @bug 
*
*
* @par Modifications and Development Timeline:
@verbatim
* https://gitlab.mcs.sdsmt.edu/7404855/csc250s17programs/commits/master

@endverbatim
*

*********************************************************/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

/**************************************************************************//**
*                         Function Prototypes
******************************************************************************/
void printmaze(char **m, int row, int column);
int min(vector<int>v);
bool solve(char **& maze, char ** & track, vector <int> &v, int  count, int R, int C, int r, int c);
void freealloc(char **maze, int row, int col);
void clonemaze(char **ormaze, char ** & dupmaze, int row, int col);
bool alloc2d(char **& maze, int row, int col);
/**************************************************************************//**
 * @author Manasi Paste
 *
 * @par Description:
 * This function reads in the maze from a .maz file. It stores the maze in an char 2d 
 * array by dynamically allocating it after reading its dimensions. It calls the solve funtion
 * which allows the main function to call the print funtion to print the shortest path
 * required to print the maze.
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
int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		cout << "Error" << endl
			<< "Program Usage: prog3.exe input.txt" << endl;
		return -1;
	}
	/* the input file containing the mazes*/
	ifstream fin;
	fin.open(argv[1]);
	if (!fin)
	{
		cout << "Unable to open the input file. Exiting" << endl;
		return -1;
	}
	/* Number of rows in a maze*/
	int number_of_rows;
	/* Number of columns in a maze*/
	int number_of_columns;
	/* The row in which the path starts*/
	int starting_row;
	/* The column in which the path starts*/
	int starting_column;
	/* The number of the maze being solved */
	int  mn=0;
	/* The 2D char array to store the maze*/
	char **maze = nullptr;
	/* Stores the number of steps*/
	int countSteps;
	/* Stores the the number of steps of all possible paths*/
	vector <int> totalSteps;
	// resize the vector to zero;
	totalSteps.resize(0);
	/* A 2d char array to store the solution of a maze*/
	char** track = nullptr;
	/*To store the minimum number of steps*/
	int steps;
	//To read until the end of the file
	//Read the number of rows
	while (fin >> number_of_rows)
	{
		//initialize the number of steps to zero
		countSteps = 0;
		//Read the number of columns
		fin >> number_of_columns;
		//read in the starting position
		fin >> starting_row >> starting_column;
		
		//alloc the maze
		alloc2d(maze, number_of_rows, number_of_columns);
		//allocate a maze to keep the store the solution
		alloc2d(track, number_of_rows, number_of_columns);
	
		//keep track of number of mazes solved
		mn++;
		//read in the maze
		fin.ignore();
		for (int k = 0; k < number_of_rows; k++)
		{
			fin.getline(maze[k], number_of_columns + 1);
		}
		totalSteps.push_back(number_of_rows*number_of_columns);
		//to make sure it deosn't count the intial test
		if (maze[starting_row][starting_column] == 'W')
			steps = -1;
		else
			steps = 0;
	    // solve the maze
		solve(maze, track,totalSteps, countSteps, number_of_rows,
			number_of_columns, starting_row, starting_column);
		//print out the details
		cout << "Maze " << mn << ":" << endl;
		cout << "\t" << "Size: " << number_of_rows << "x" << number_of_columns << endl;
		cout << "\t" << "Start Loc: " << starting_row << " " << starting_column << endl;
		steps = steps + min(totalSteps);
		cout << "\t" << "Shortest Path: "<<steps << endl;
		//print the shortest stored path
		printmaze(track, number_of_rows, number_of_columns);
		//clear the vector that stores the number of steps in each possible path
		totalSteps.clear();
		//freeing up the allocated memory for the maze
		freealloc(maze, number_of_rows, number_of_columns);
		//freeing the memory allocated to the copy of the maze
		freealloc(track, number_of_rows, number_of_columns);
		
	}
	//closing the input file
	fin.close();
	return 0;
}

/***************************************************************************//**
 * @author Manasi Paste
 *
 * @par Description:
 * This function finds the number of steps required on the shortest path to the end 
 * the maze
 *
 * @param[in] v - The vector holds the number of steps required for each possible path
 *
 * @returns k - The number of steps on the shortest path

 ******************************************************************************/

int min(vector<int>v)
{
	//find the min number of steps 
	vector <int> ::iterator it = min_element(v.begin(), v.end());
	//store it in an integer
	int k = *it;
	//return the integer
	return k;
}

/***************************************************************************//**
 * @author Manasi Paste
 *
 * @par Description:
 * This function frees the dynamically allocated memory for the 2d char arrays
 *
 * @param[in, out] maze - The char 2d array that contains the maze
 * @param[in] row- the number of rows in the maze
 * @param[in] col- the number of columns in the maze
 *
 * @returns none
 ******************************************************************************/

void freealloc(char **maze, int row, int col)
{
	//delete each allocated char 1d array
	for (int j = 0; j < row; j++)
	{
		delete[] maze[j];
	}
	//delete the pointer to the maze
	delete[] maze;
}
/***************************************************************************//**
 * @author Manasi Paste
 *
 * @par Description:
 * This function allocates the dynamic memory for the 2d char arrays
 *
 * @param[in, out] maze - The pointer to char 2d array 
 * @param[in] row- the number of rows in the maze
 * @param[in] col- the number of columns in the maze
 *
 * @returns true - If the memory is successfully allocated
 * @returns false - if the allocation fails
 ******************************************************************************/
bool alloc2d(char ** & maze, int row, int col){
	//allocate a new 1d array 
	maze = new (nothrow) char *[row];
	//if allocation fails
	if (maze == nullptr)
	{
		//delete the pointer
		delete[] maze;
		//return false
		return false;
	}
	for (int i = 0; i < row; i++)
	{
		//allocate columns for each row
		maze[i] = new (nothrow) char[col + 1];
		//if allocation fails 
		if (maze[i] == nullptr)
		{
			//delete every allocated row so far
			for (int j = 0; j < i; j++)
			{
				delete[] maze[j];
			}
			delete[] maze;
			//return false
			return false;
		}
	}
	//if succeeded return true
	return true;
}
/***************************************************************************//**
 * @author Manasi Paste
 *
 * @par Description:
 * This function prints the maze
 *
 * @param[in] m - The char 2d array that stores the maze
 * @param[in] row- the number of rows in the maze
 * @param[in] column- the number of columns in the maze
 *
 * @returns none
 ******************************************************************************/
void printmaze(char **m, int row, int column)
{
	for (int k = 0; k < row ; k++)
	{
		//a new line after each row is printed out
		cout << endl;
		cout << "\t";
		//printing one row at a time
		for (int h = 0; h < column ; h++)
		{
			cout << m[k][h];
		}
	}
	//a new line after the entire maze is printed
	cout << endl;
}
/***************************************************************************//**
 * @author Manasi Paste
 *
 * @par Description:
 * This function copies the maze solution to another char 2d array
 *
 * @param[in, out] ormaze - The char 2d array that contains the maze in its solution
 * @param[in, out] dupmaze - The char 2d array to which the solution is being copied
 * @param[in] row - the number of rows in the maze
 * @param[in] col - the number of columns in the maze
 *
 * @returns none
 ******************************************************************************/
void clonemaze(char **ormaze, char ** & dupmaze, int row, int col)
{
	//copy each charachter from maze to the 2d array to which it is being copied
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			dupmaze[i][j] = ormaze[i][j];
		}
	}
}
/***************************************************************************//**
 * @author Manasi Paste
 *
 * @par Description:
 * This function solves the maze recursively
 *
 * @param[in, out] maze - The char 2d array that contains the maze in its solution
 * @param[in, out] track - The char 2d array to which the solution is being copied
 * @param[in, out] v - The vector that stores the number of steps for all possible path
 * @param [in, out] count- stores the number of steps in the path
 * @param[in] R - the number of rows in the maze
 * @param[in] C - the number of columns in the maze
 * @param[in, out] r - the starting row of the path
 * @param [in, out] c - the starting column of the path
 *
 * @returns true - If a path is found
 * @returns false - if no path is found
 ******************************************************************************/
bool solve(char **& maze, char ** & track, vector <int>& v, int count,
	int R, int C, int r, int c)
{
	//if the destination is reached
	if (maze[r][c] == 'E')
	{
		
		//insert the count in the vector
		v.push_back(count);
		//check if the next possible path has lesser number of steps
		if (count <= min(v))
			//copy the maze and store it
			clonemaze(maze, track, R, C);
		//printmaze(maze, R, C);
		return true;
	}

	//check if its valid
	else{
		if (r<0 || c<0 || r > R || c> C)
			return false;
		//if its not a movable spot
		if (maze[r][c] != ' ' && maze[r][c] != 'W')
			return false;
		if (count >= min(v))
		{
			return false;
		}

		//if its traversing water 
		if (maze[r][c] == 'W')
		{
			// mark '=' and add two steps
			maze[r][c] = '=';
			count++;
		}
		else {
			//if its a space then '-' and add one step
			maze[r][c] = '-';
		}
		//if the number of steps exceed the number on shortest path 

		//move down
		if (!solve(maze, track, v, count + 1, R, C, r + 1, c))
			// move right
			if (!solve(maze, track, v, count + 1, R, C, r, c + 1))
				//move left
				if (!solve(maze, track, v, count + 1, R, C, r, c - 1))
					//move up
					if (solve(maze, track, v, count + 1, R, C, r - 1, c))
						return true;
		//unmark

		if (maze[r][c] == '=')
		{
			maze[r][c] = 'W';
			count = count - 1;
		}
		else
			if (maze[r][c] = '-')
			{
				maze[r][c] = ' ';
				//count--;
			}
		return false;
	}

}
