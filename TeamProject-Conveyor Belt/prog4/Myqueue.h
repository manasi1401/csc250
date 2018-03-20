/*************************************************************************//**
 * @file
 *
 * @brief Defines the function prototypes for the queue class. 
 *****************************************************************************/
#include <iostream>

using namespace std;
//team 20, Harry Kramer, Manasi Paste, Remington Thurber
/*!
*@brief Contains the functions required for creating and managing a queue.
* The private data stores the items of the queue and the addresses to access them.
*/
#ifndef __MYQUEUE__H__
#define __MYQUEUE__H__

template <typename TY>
class myqueue
{
public:
    /*Create a queue*/
    myqueue();
    /*Copy constructor*/
    myqueue( myqueue<TY> &q );
    /*Free up all the nodes in the queue*/
    ~myqueue();
    /*Add items to the queue at one end*/
    bool enque( TY item );
    /*remove item from the queue from opposite end*/
    bool deque( TY &item );
    /*Display the item at the front of the queue*/
    bool front( TY &item );
    /*Check if the queue is empty*/
    bool isEmpty();
    /*Return the size of the queue*/
    int size();

private:
    /*!
    *@brief Contains the item and the address to the next node
    */
    struct node
    {
        /*!Item stored in the list*/
        TY item;
        /*!Pointer to the next node*/
        node* next;
    };
    /*!Address to the last node*/
    node* tailptr;
};

/**************************************************************************//**
 * @author Remington Thurber
 * 
 * @par Description:
 * The constructor sets the list to empty.
 *****************************************************************************/
template <typename TY>
myqueue<TY>::myqueue()
{
    tailptr = nullptr;
}
/**************************************************************************//**
 * @author Remington Thurber
 * 
 * @par Description: 
 * The copy constructor copies the passed in queue into this one.
 *
 * @param[in,out] q - The queue to copy to this one.
 *****************************************************************************/
template <typename TY>
myqueue<TY>::myqueue( myqueue<TY> &q )
{
    node* src = q.tailptr;
    node* dest;

    // Handle src is empty
    if ( src == nullptr )
    {
        tailptr = nullptr;
        return;
    }

    // Make a new node
    node* temp = new (nothrow) node;

    // Check memory allocated correctly
    if ( temp == nullptr )
        return;

    // Set tailptr to the the newly created node
    tailptr = temp;
    // Copy in the item
    tailptr->item = src->item;
    // Make circular
    tailptr->next = tailptr;

    dest = tailptr;
    // Traverse src to the front
    src = src->next;

    // Copy all nodes until src is back to the tailptr 
    while ( src != q.tailptr )
    {
        // Create
        temp = new (nothrow) node;

        // Check memory allocation
        if ( temp == nullptr )
            return;

        // Copy in item
        temp->item = src->item;
        // Make circular
        temp->next = tailptr;
        dest->next = temp;
        
        dest = temp;

        // Traverse down
        src = src->next;
    }
}
/**************************************************************************//**
 * @author Remington Thurber
 * 
 * @par Description:
 * This destructor removes all dynamically allocated items
 * from the queue, freeping up the memory during the process.
 *****************************************************************************/
template <typename TY>
myqueue<TY>::~myqueue()
{
    node* temp = nullptr;

    // Handle empty
    if ( tailptr == nullptr )
        return;

    // Traverse, deleting all nodes
    while ( tailptr != tailptr->next )
    {
        temp = tailptr->next;
        tailptr->next = tailptr->next->next;
        delete temp;
    }

    // Clean up tailptr
    delete tailptr;
}
/**************************************************************************//**
 * @author Harry Kramer
 * 
 * @par Description:
 *
 * This function takes an object of any data type, and inserts it at the
 * end of a FIFO queue of the same data type. 
 *
 * @param[in] item - The item to be added to the queue.
 *
 * @return true - object was succesfully inserted
 * @return false - object was not succesfully inserted
 *****************************************************************************/
template <typename TY>
bool myqueue<TY>::enque( TY item )
{
    node * temp = nullptr;
    temp = new (nothrow) node;
    //Check to see the memory was successfully allocated
    if (temp == nullptr)
    {
        return false;
    }
    //Handles insert if queue is empty
    if (tailptr == nullptr)
    {
        temp->item = item;
        tailptr = temp;
        temp->next = temp;
        return true;
    }

    temp->item = item;
    temp->next = tailptr->next;
    tailptr->next = temp;
    tailptr = temp;
    return true;
}
/**************************************************************************//**
 * @author Manasi Paste
 * 
 * @par Description:
 *
 * This function removes an item from the front of the queue.
 *
 * @param[out] item - stores the item which is dequed
 * 
 * @return true - If it is removed successfully
 * @return false - If the queue is empty
 *****************************************************************************/
template <typename TY>
bool myqueue<TY>::deque( TY &item )
{
    node * temp = nullptr;
    // if the queue is empty
    if (tailptr == nullptr)
        return false;
    temp = tailptr->next;
    
    //if it has only one 
    if (temp->next == temp)
    {
        item = temp->item;
        delete temp;
        tailptr = nullptr;
        return true;
    }
    //if it has more than one item
    item = temp->item;
    //remove from the front of the queue
    tailptr->next = temp->next;
    delete temp;
    return true;
}
/**************************************************************************//**
 * @author Manasi Paste
 * 
 * @par Description:
 *
 * This function shows the item from the front of the queue.
 *
 * @param[out] item - stores the item which is in front of the queue
 * 
 * @return true - If it is successfully
 * @return false - If the queue is empty
 *****************************************************************************/
template <typename TY>
bool myqueue<TY>::front( TY &item )
{
    //if the queue is empty return false
    if (tailptr == nullptr)
        return false;
    //else store the item in the front of the queue
    item = tailptr->next->item;
    return true;

}
/**************************************************************************//**
 * @author Harry Kramer
 * 
 * @par Description:
 *
 * This function checks to see if the queue is empty.
 *
 * @return true - queue is empty
 * @return false - queue is not empty
 *****************************************************************************/
template <typename TY>
bool myqueue<TY>::isEmpty()
{
    if (tailptr == nullptr)
    {
        return true;
    }
    return false;
}
/**************************************************************************//**
 * @author Remington Thurber
 * 
 * @par Description:
 * Returns the size of the queue, by traversing it.
 *
 * @returns count - The size of the queue.
 *****************************************************************************/
template <typename TY>
int myqueue<TY>::size()
{
    // Start at 1 to account for skipping over tailptr in the while loop
    int count = 1;
    node* temp = tailptr->next;

    // Traverse the list and count
    while ( temp != tailptr )
    {
        count++;
        temp = temp->next
    }

    return count;
}

#endif
