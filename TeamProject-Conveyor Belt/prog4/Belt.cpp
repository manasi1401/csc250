/*************************************************************************//**
 * @file
 *
 * @brief Defines the functions for the Belt class. 
 *****************************************************************************/
#include "belt.h"

/**************************************************************************//**
 * @author Manasi Paste
 * 
 * @par Description:
 *
 * This constructor function initializes the belt length,
 * width, and letter name. It also sets the accumulate length to zero.
 *
 * @param[in] width - The width of the belt.
 * @param[in] len - The length of the belt.
 * @param[in] let - The letter of the belt.
 *****************************************************************************/
belt::belt(int width, int len, char let)
{
    //set accumulate length to zero
    accumulateLength = 0;
    //set width, length and letter of the belt
    beltWidth = width;
    beltLength = len;
    beltLetter = let;
}

/**************************************************************************//**
 * @author Remington Thurber
 * 
 * @par Description:
 * Destructor for the belt.
 *
 *****************************************************************************/
belt::~belt()
{

}

/**************************************************************************//**
 * @author Remington Thurber
 * 
 * @par Description:
 * This function adds a box to the belt, returning true if
 * it succeeded, and false otherwise.
 *
 * @param[in] b - The box to be added to the belt.
 * 
 * @return true - The box was added successfully.
 * @return false - The box was not added successfully.
 *****************************************************************************/
bool belt::addBox( box b )
{
    if ( theBelt.enque( b ) )
    {
        accumulateLength += b.depth;
        return true;
    }

    return false;
}

/**************************************************************************//**
 * @author Harry Kramer
 * 
 * @par Description:
 *
 * This function will remove the front box from the belt and return the 
 * box.
 *
 * @return box - the box that was removed from the belt
 *****************************************************************************/
box belt::removeBox()
{
    box temp;
    //Find box at front of belt
    theBelt.front(temp);

    //Remove box at front of belt
    theBelt.deque(temp);

    //Update the accumulate length of boxes
    accumulateLength = accumulateLength - temp.depth;

    //Return the box that was removed
    return temp;
}

/**************************************************************************//**
 * @author Harry Kramer
 * 
 * @par Description:
 *
 * This function checks to see if half or more of the front box is hanging 
 * off the belt.
 *
 * @return true - half or more of front box is hanging over
 * @return false - less than half of the box is hanging over
 *****************************************************************************/
bool belt::boxWillDrop()
{
    box temp;
    theBelt.front(temp);
    //Check to see if a box is hanging off a belt
    if (accumulateLength > beltLength)
    {
        //Check to see if half or more of the box is hanging off
        if ((accumulateLength - beltLength) >= (temp.depth) / 2)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

/**************************************************************************//**
 * @author Manasi Paste
 * 
 * @par Description:
 *
 * This function clears all the boxes on the belt and sets the 
 * accumulate length to zero.
 *
 * @return true - If it is successful 
 *****************************************************************************/
bool belt::clear()
{
    box item;
    //while the belt is not empty remove the box
    while (!theBelt.isEmpty())
    {
        theBelt.deque(item);
    }
    //set accumulate length to zero
    accumulateLength = 0;
    return true;
}
/**************************************************************************//**
 * @author Manasi Paste
 * 
 * @par Description:
 *
 * This function gets the charachter name of the belt.
 * 
 * @return beltLetter - the charachter name of hte belt
 *****************************************************************************/
char belt::getname()
{
    return beltLetter;
}
/**************************************************************************//**
 * @author Manasi Paste
 * 
 * @par Description:
 *
 * This function resets the belt width to the given value.
 *
 * @param[in] width - the width to which the belt is to be set

 * @return 
 *****************************************************************************/
void belt::setWidth(int width)
{
    beltWidth = width;
}
/**************************************************************************//**
 * @author Remington Thurber
 * 
 * @par Description:
 * Returns the width of the belt.
 *
 * @return beltWidth - The width of the belt.
 *****************************************************************************/
int belt::getWidth()
{
    return beltWidth;
}