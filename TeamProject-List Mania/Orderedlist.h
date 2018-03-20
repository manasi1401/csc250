/*************************************************************************//**
 * @file
 *
 * @brief Defines the function prototypes for the ordered list class. 
 *****************************************************************************/
#include <iostream>
#include <iomanip>

#ifndef _ORDEREDLIST_H
#define _ORDEREDLIST_H

using namespace std;

//team 20, Harry Kramer, Manasi Paste, Remington Thurber
/*!
*@brief Contains the functions required for creating and managing a ordered linked lists.
* The private data stores the items of the list and the addresses to access the list.
*/
class orderedlist
{
public:

    /*Create a list*/
    orderedlist();
    /*Frees up all the nodes in the list*/
    ~orderedlist();
    
    /*Inserts the integer to the list*/
    bool insert(int x);
    /*Removes an integer from the list*/
    bool remove(int x);
    /*Print the entire list to the screen*/
    void print(ostream &out);
    /*Finds the given intger*/
    bool find(int x);
    /*Returns the size of the list*/
    int size();
    /*Check if the list is empty*/
    bool isempty();

private:
    /*!Number of items in the list*/
    int count;
    /*!
    *@brief Contains the integers and the address to the next node
    */
    struct node
    {
        /*!Integer stored in the list*/
        int n;
        /*!Pointer to the next node*/
        node * next;
    };
    /*!Address to the first node*/
    node *headptr;
};
#endif

