#include "InventoryMgmtSys.h"


//THIS IS WHERE THE DEFINITIONS FOR ALL OF THE FUNCTIONS RELATED TO DELIMITED FILE WILL GO

const char kDelimFile[8] = "FileCSV";

/// <summary>
/// Creates a text file named "FileCSV"
/// </summary>
/// <returns>Pointer to created file</returns>
FILE* fileStarter() 
{
	FILE *delimFile = NULL;
	delimFile = fopen(kDelimFile, "rw");
	
	//Checks if file opened correctly
	if (delimFile = NULL) 
	{
		printf("File unable to open\n");
	}
	else
	{
		printf("File opened successfully.\n");
	}

	fclose(delimFile);
	return delimFile;
}

/// <summary>
/// Opens FileCSV in write-only mode to write to.
/// </summary>
/// <param name="pointer"> </param>
/// <returns></returns>
FILE* writeToFile(FILE* pointer) 
{
	FILE* delimFile = pointer;
	delimFile = fopen("FileCSV", "w");


}
