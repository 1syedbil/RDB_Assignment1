#include "InventoryMgmtSys.h"

const char kDelimFileString[12] = "FileCSV.txt";

/// <summary>
/// Creates a text file named "FileCSV" to read, write, and append.
/// </summary>
/// <returns>Pointer to created file</returns>
FILE* CSVFileStarter() 
{
	FILE *delimFile = NULL;
	delimFile = fopen(kDelimFileString, "w+");
	
	//Checks if file opened correctly
	if (delimFile == NULL) 
	{
		printf("File unable to open\n");
	}
	else
	{
		printf("File created successfully.\n");
		fprintf(delimFile, "ProductId,Name,Category,Quantity,Price\n");
		fclose(delimFile);
	}

	return delimFile;
}



/// <summary>
/// Opens FileCSV in append-only mode to write to the end of the file.
/// </summary>
/// <param name="pointer"> File pointer for use in the </param>
void CSVWriteToFile(FILE* delimFile) 
{
	char	validatedInput[200] = "";
	

	delimFile = fopen(kDelimFileString, "w+");
	if ((delimFile == NULL)||(ferror(delimFile)))
	{
		printf("File could not be opened.\n");
		return;
	}

	strcpy(validatedInput, CSVInputValidation(delimFile));
	printf("New line is %s", validatedInput);
	if (strcmp(validatedInput, "error") == 0)
	{
		if (ferror(delimFile))
		{
			printf("Could not print to file.\n");
			fclose(delimFile);
			return;
		}
	}
	fprintf(delimFile, validatedInput);
	fclose(delimFile);
	return;
}



/// <summary>
/// Prints the contents of the CSV file
/// </summary>
/// <param name="pointer">pointer to the file to be open </param>
void CSVReadFile(FILE* delimFile)
{
	char fileLine[200] = "";

	delimFile = fopen(kDelimFileString, "r");	//Opens delimFile in read-only mode.
	
	if ((delimFile == NULL) || (ferror(delimFile)))	//Ensures file was opened properly
	{
		printf("File could not be opened.\n");
		return;
	}
	else
	{
		while (feof(delimFile) == 0)	// Loops until the end of file is reached
		{
			fgets(fileLine, sizeof(fileLine), delimFile);	//Stores line of file in string
			printf("%s", fileLine);	//Prints line of file
		}

		printf("\nEnd of File reached.\n");
		fclose(delimFile);
	}
	return;
}




char* CSVInputValidation(FILE* openFile)
{
	char delimInput[40] = "";
	char output[200] = "";
	char* validator = NULL;

	printf("Please input item ID:\n");
	fgets(delimInput, sizeof(delimInput), stdin);
	validator = strchr(delimInput, ',');	//checks if there is a comma in the input
	if (validator != NULL)
	{
		printf("Commas cannot be used in CSV values.\n");
		return "error";
	}
		
	CSVFileSeek(openFile, delimInput);
	if (feof(openFile) != 0)
	{
		printf("Items cannot have duplicate IDs.\n");
		return "error";
	}
		
	strcpy(output, delimInput);	//Writes input into the output string
	strcat(output, ",");	//Appends value with a comma

	printf("Please enter the item name:\n");
	fgets(delimInput, sizeof(delimInput), stdin);
	validator = strchr(delimInput, ',');
	if (validator != NULL)
	{
		printf("Commas cannot be used in CSV values.\n");
		return "error";
	}

	delimInput[strlen(delimInput) - 1] = '\0';	//truncates line break off the end of the string
	strcat(output, delimInput);
	strcat(output, ",");

	printf("Please enter the item category:\n");
	fgets(delimInput, sizeof(delimInput), stdin);
	validator = strchr(delimInput, ',');
	if (validator != NULL) 
	{
		printf("Commas cannot be used in CSV values.\n");
		return "error";
	}

	delimInput[strlen(delimInput) - 1] = '\0';	
	strcat(output, delimInput);
	strcat(output, ",");

	printf("Please enter the item quantity:\n");
	fgets(delimInput, sizeof(delimInput), stdin);
	validator = strchr(delimInput, ',');
	if (validator != NULL)
	{
		printf("Commas cannot be used in CSV values.\n");
		return "error";
	}

	delimInput[strlen(delimInput) - 1] = '\0';
	strcat(output, delimInput);
	strcat(output, ",");

	printf("Please enter the item price:\n");
	fgets(delimInput, sizeof(delimInput), stdin);
	validator = strchr(delimInput, ',');
	if (validator != NULL)
	{
		printf("Commas cannot be used in CSV values.\n");
		return "error";
	}

	strcat(output, delimInput);	//No truncation so that the line ends in a carriage return, No appending with a comma as it's the end of the file.
	return output;
}




/// <summary>
/// Searches for an item ID in a file and sets the pointer to the beginning of the line.
/// </summary>
/// <param name="opened"> Pointer to an opened file</param>
/// <param name="ID"> String containing item ID</param>
void CSVFileSeek(FILE* opened, char* ID)
{
	ID[strlen(ID) - 1] = '\0';	//Truncates the line break from entered ID

	char fileIDline[200] = "";
	char* stringFinder = NULL;

	//SOMETHING IS WRONG WITH THIS LOOP AND IT'S INFINITE
	//FILE ERROR BEING CONSISTENTLY ENCOUNTERED
	while (feof(opened) ==0) //loops until end of file
	{
		fgets(fileIDline, sizeof(ID), opened);	//gets string the length of the inputted ID
		stringFinder = strstr(fileIDline,ID);
		if (stringFinder != NULL)
		{
			opened -= sizeof(fileIDline);	//Backs up pointer to beginning of line in file
			printf("ID %s found.",ID);
			return;
		}

		if (ferror(opened))
		{
			printf("File error encountered.\n");
			return;
		}
	}
	printf("End of file reached, %s was not found,\n", ID);
	return;
}



/// <summary>
/// Calls CSVFileSeek to find a specific line, and overwrites the line with a null terminator
/// </summary>
/// <param name="delimFile"></param>
void CSVFileDeleteLine(FILE* delimFile)
{
	char lineToDelete[200];
	char idInput[40] = "";
	int i = 0;
	
	delimFile = fopen(kDelimFileString, "rw");	//opens file at pointer for reading and writing
	if (delimFile == NULL)
	{
		printf("File could not be opened.\n");
		return;
	}

	printf("Please input the ID of the item you would like to delete.");
	fgets(idInput, sizeof(idInput), delimFile);
	CSVFileSeek(delimFile,idInput);
	if (feof(delimFile) != 0)
	{
		printf("ID was not found.\n");
		fclose(delimFile);
		return;
	}
	else
	{
		fgets(lineToDelete, sizeof(lineToDelete), delimFile); //Stores line in a string
		delimFile -= sizeof(lineToDelete); //Backs up the file pointer to the beginning of line
		for (i = 0; i != strlen(lineToDelete); i++) //Loops as long as the string, printing spaces to get rid of existing line.
		{
			fprintf(delimFile, " ");
		}
		return;
	}
}

void CSVFileUpdate(FILE* delimFile)
{
	char idInput[40] = "";
	char validatedInput[200] = "";

	delimFile = fopen(kDelimFileString, "rw");	//opens file at pointer for reading and writing
	if ((delimFile == NULL) || (ferror(delimFile)))
	{
		printf("File could not be openedn");
		fclose(delimFile);
		return;
	}

	printf("Please input the ID of the item you would like to update:\n");
	fgets(idInput, sizeof(idInput), delimFile);
	CSVFileSeek(delimFile, idInput);
	if (feof(delimFile) == 0)
	{
		fclose(delimFile);
		return;
	}
	else
	{
		strcpy(validatedInput, CSVInputValidation(delimFile));
		if (strcmp(validatedInput, "error") == 0)
		{
			fprintf(delimFile, validatedInput);
			if (ferror(delimFile))
			{
				printf("Could not print to file.\n");
				fclose(delimFile);
				return;
			}
		}
	}
}