#pragma once
//The static or virtual functions to fill, father class of any majcount system. List all the function in user-level.

#include "person.h"

class reaction
{
public:

	//Person listed in : database (permanent), pool (in one trip), templist (for select into event).

	virtual void newPerson() = 0;								//Create a new person by user into database
	virtual void addPerson() = 0;								//Add a person from database to current pool
	virtual void selectPerson() = 0;							//Add a person from current pool to templist

	virtual void unSelectPerson() = 0;							//Delete a person from templist
	virtual void cancelPerson() = 0;							//Delete a person from current pool so templist
	virtual void deleteSelectedPerson() = 0;					//Delete a person from all list

	virtual void clearSelectedPerson() = 0;						//Erease a person's debt/capital as cleared
	virtual void copyPersonalBill() = 0;						//Copy a person's bill to copyboard.



	//Event listed in pool and templist, no database.

	virtual void newEvent() = 0;								//Create a new event to pool by user, bonded with person in the templist and clear the templist, Triggered by '+'
	virtual void fastNewEvent() = 0;							//Create a new event with minimun info: one person (selected by the right trigger not templist) & receivable  

	virtual void selevtAllEvent() = 0;							
	virtual void selectOneEvent() = 0;

	virtual void unSelectEvent() = 0;
	virtual void deleteSelectedEvent() = 0;


	//Other system function.


	virtual void setExchangeRate() = 0;							//Currency system has only major & minor currency
	virtual void exchange() = 0;								//Exchange all amount by multiply the rate. 
	virtual void reverseExchange() = 0;							//Exchange all amount by divide by the rate. 

	virtual void openConfigPage() = 0;
	virtual void openMainPage() = 0;
	virtual void openEventPage() = 0;
	virtual void openPersonPage() = 0;

	virtual void Undo() = 0;									//Need a stack of all sys, or a stack of function-inversefunction.
	virtual void Redo() = 0;
};

