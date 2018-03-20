/*************************************************************************//**
 * @file
 *
 * @brief Defines the function prototypes for the Belt class. 
 *****************************************************************************/
#include "myqueue.h"

#ifndef __BELT__H__
#define __BELT__H__
/*!
*@brief Contains the dimensions and the number of the box
*/
struct box
{
    /*! Number of the box*/
    int boxNumber;
    /*! Width of the box*/
    int width;
    /*! Depth of the box*/
    int depth;
    /*!Height of the box*/
    int height;
};

/*!
*@brief Contains the functions required for creating and managing a Belt.
* The private data stores the queue of items on the belt, Dimensions of the belt,
* the identity letter of the belt and the accumulated lenght of the boxes on it.
*/
class belt
{
public:
    /*Intialising the dimensions of the belt*/
    belt(int width , int len, char let);
    /*Destructor of the belt*/
    ~belt();
    /*Add a box to the belt*/
    bool addBox( box b );
    /*Remove a box from the belt*/
    box removeBox();
    /*Check if a box on the belt will drop*/
    bool boxWillDrop();
    /*Clear the belt*/
    bool clear();
    /*Returns the name of the belt*/
    char getname();
    /*Set the width*/
    void setWidth(int width);
    /*Get the width*/
    int getWidth();
private:
    myqueue<box> theBelt; /*!< The packages on the belt */
    int beltWidth; /*!< The width of the belt */
    int beltLength; /*!< The length of the conveyor belt*/
    char beltLetter; /*!< The label for the belt */
    int accumulateLength; /*!< The amount of the belt used */
};

#endif
