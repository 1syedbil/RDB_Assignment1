#include "InventoryMgmtSys.h"

int main(void)
{
	/*GENERAL LAYOOUT OF MAIN:
	* 
	- menu showing options for which kind of file 
	the user can perform the CRUD operations on

	- get user input for their choice from the menu

	- use switch-case statement for the different menu options 
	that the user can choose

	- they have three options: 1. random accsess, 2. sequential access, 3. delimited file
	
	- once they make a selection another menu will show up. It will have 4 different options for CRUD.
	the same CRUD menu will show up no matter which file type is chosen
	
	- another switch-case statement for the CRUD menu options
	
	- this is where the CRUD functions will be called. each file type will have its own dedicated CRUD functions. 
	create function, read function, update function, and delete function for each respective file type.
	this means that each file type will have, at minimum, 4 different functions
	
	- for create and update let the user input what new values they want to add. for delete let them decide which entry 
	they would like to delete.
	*
	*/

	FILE* myFile = NULL;
	myFile = CSVFileStarter();
	CSVReadFile(myFile);
	CSVWriteToFile(myFile);

	return 0;
}