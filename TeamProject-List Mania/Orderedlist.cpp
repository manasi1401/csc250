/*************************************************************************//**
 * @file
 *
 * @brief Defines the functions for the ordered list class. 
 *****************************************************************************/

#include "Orderedlist.h"

/**************************************************************************//**
 * @author Remington Thurber
 * 
 * @par Description:
 *
 * This constructor function initializes the ordered list class, by setting
 * headptr to nullptr, and count to 0.
 *****************************************************************************/
orderedlist::orderedlist()
{
    headptr = nullptr;
    count = 0;
}

/**************************************************************************//**
 * @author Remington Thurber
 * 
 * @par Description:
 *
 * This destructor function deinitializes the ordered list class, and deletes
 * each node in the list to free up its dynamic memory.
 *****************************************************************************/
orderedlist::~orderedlist()
{
    // Delcare 2 temporary nodes to traverse over the list
    node *curr = headptr;
    node *next;

    // Traverse over the list, deleting all of the nodes
    while ( curr != nullptr )
    {
        next = curr->next;
        delete curr;
        curr = next;
    }
}

/**************************************************************************//**
* @author Harry Kramer
*
* @par Description:
* This function inserts the integer to the correct spot of the ordered linked 
* list. The linked list is ordered in ascending order.
*
* @param[in]  x- The integer to be inserted in the linked list.
*
* @return True - if the integer is inserted successfully
* @return False - if the insert is unsuccessful.
*****************************************************************************/
bool orderedlist::insert(int x)
{
    node * temp = nullptr;
    node * curr;
    node * prev;
    temp = new (nothrow) node;
    if (temp == nullptr)
    {
        return false;
    }
    //If the list is empty, it sets the value as the head pointer
    if (headptr == nullptr)
    {
        temp->n = x;
        temp->next = nullptr;
        headptr = temp;
        count += 1;
        return true;
    }
    //Set previous and current to headptr, getting ready to traverse list
    curr = headptr;
    prev = headptr;
    //Set temp->n equal to the number we have inserted
    temp->n = x;
    //If the value is smaller then the intial value of the list, add to beginning
    if (temp->n <= headptr->n)
    {
        curr = headptr;
        headptr = temp;
        headptr->next = curr;
        count += 1;
        return true;
    }
    curr = headptr;
    //Traverse through the list, till the correct spot is found
    while (curr->next != nullptr && temp->n > curr->n)
    {
        prev = curr;
        curr = curr->next;
    }
    //Insert to the second to last spot in the list
    if (curr->next == nullptr && temp->n < curr->n)
    {
        temp->next = curr;
        prev->next = temp;
        count += 1;
        return true;
    }
    //Insert to last spot in the list
    if (curr->next == nullptr && temp->n > curr->n)
    {
        temp->next = nullptr;
        curr->next = temp;
        count += 1;
        return true;
    }
    //Insert into sorted correct spot
    temp->next = curr;
    prev->next = temp;
    count += 1;
    return true;
}
/**************************************************************************//**
 * @author Manasi Paste
 *
 * @par Description:
 * This Function removes the integer from the linked list.
 *
 * @param[in]  x- The integer to be removed from the list
 * 
 * @return True - if the integer exists in the list and is removed successfully
 * @return False - if the integer doesnot exist in the file or the remove is unsuccessful.
 *****************************************************************************/
bool orderedlist::remove(int x)
{
    //if the list is empty it returns false
    if (headptr == nullptr)
        return false;
    //tracks nodes
    node *temp = headptr;
    //tracks the nodes before temp
    node *xtemp = headptr;
    //until the the item to be removed is not found
    while (temp->n != x && temp->next != nullptr)
    {
        //set xtemp to current temp node
        xtemp = temp;
        //set the temp to the next node
        temp = temp->next;
        
    }
    if (headptr->n == x)
    {
        //updates the size of the list
        count--;
        temp = headptr;
        headptr = headptr->next;
        //frees the headptr memory
        delete temp;
        return true;
    }
    //if you find the integers in the middle or the end
    if (temp->n == x )
    {
        count--;
        xtemp->next = temp->next;
        delete temp;
        return true;
    }
    
    return false;
}

/**************************************************************************//**
 * @author Remington Thurber
 * 
 * @par Description:
 *
 * This function prints the integer contents of the list to the specified
 * ostream object.
 *
 * @param[in,out] out - The ostream object which the list should be printed to.
 *****************************************************************************/
void orderedlist::print(ostream &out)
{
    node *curr = headptr;

    // Check if the list is empty
    if (curr == nullptr)
    {
        out << "The list is empty." << endl;
        return;
    }
    int i = 0;
    // Otherwise, traverse the list, printing the contents of each node
    while (curr != nullptr)
    {
        i++;
        out << setw(10) << curr->n;
        curr = curr->next;
        if (i % 5 == 0)
            out << endl;
    }

    out << endl;
}

/**************************************************************************//**
 * @author Remington Thurber
 * 
 * @par Description:
 *
 * This function searches the list for a specified integer value, returning
 * true if it exists in the list, and false otherwise.
 *
 * @param[in] x - The integer value to be looked for in the list.
 *
 * @returns true - The integer value was found in the list.
 * @returns false - The integer value was not found in the list.
 *****************************************************************************/
bool orderedlist::find(int x)
{
    node * curr = headptr;

    // Traverse the list; return true if the value was found
    while ( curr != nullptr )
    {
        if ( curr->n == x )
        {
            return true;
        }
        curr = curr->next;
    }

    // Otherwise, the number wasn't found, so return false
    return false;
}

/**************************************************************************//**
 * @author Manasi Paste
 * 
 * @par Description:
 *
 * This function returns true if the list is empty, and false otherwise.
 *
 * @returns true - The list is empty.
 * @returns false - The list is not empty.
 *****************************************************************************/
bool orderedlist::isempty()
{
    if (headptr == nullptr)
        return true;
    return false;
}

/**************************************************************************//**
 * @author Remington Thurber
 * 
 * @par Description:
 *
 * This function returns the size of the list.
 *
 * @returns count - The size of the list.
 *****************************************************************************/
int orderedlist::size()
{
    return count;
}
