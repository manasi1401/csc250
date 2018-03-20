/*************************************************************************//**
 * @file
 *
 * @brief Defines the function prototypes for the unordered list class. 
 *****************************************************************************/
#include <iostream>
#include <iomanip>

#ifndef _UNORDEREDLIST_H
#define _UNORDEREDLIST_H

using namespace std;

//team 20, Harry Kramer, Manasi Paste, Remington Thurber
/*!
*@brief Contains the functions required for creating and managing a undorderd linked lists.
* The private data stores the items of the list and the addresses to access the list.
*/
class unorderedlist
{
public:

    /*Create a list*/
    unorderedlist();
    /*Free up all the nodes in the list*/
    ~unorderedlist();

    /*Insert an integer at the beginning of the list*/
    bool insertBegin(int x);
    /*Insert an integer at the end of the list*/
    bool insertEnd(int x);
    /*Remove an integer from the list*/
    bool remove(int x);
    /*Print the entire list to the screen*/
    void print(ostream &out);
    /*Find the given intger in the list*/
    bool find(int x);
    /*Gets the size of the list*/
    int size();
    /*Check if the list is empty*/
    bool isempty();

private:
    /*!Number of items in the list*/
    int count;
    /*!
    *@brief Contains the integer and the address to the next node
    */
    struct node
    {
        /*!integer stored in the list*/
        int n;
        /*!pointer to the next node*/
        node * next;
    };
    /*!Address to the first node*/
    node *headptr;
};

#endif