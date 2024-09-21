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
	

	delimFile = fopen(kDelimFileString, "a");
	if ((delimFile == NULL)||(ferror(delimFile)))
	{
		printf("File could not be opened.\n");
		return;
	}

	strcpy(validatedInput, CSVInputValidation());
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

	printf("Item written to file");
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



/// <summary>
/// Takes several inputs from a user to format into a csv file
/// </summary>
/// <returns> string formatted as CSV OR "error" if input was invalid</returns>
char* CSVInputValidation()
{
	char delimInput[40] = "";
	char output[200] = "";
	char* validator = NULL;

	printf("Please input item ID:\n");
	fgets(delimInput, sizeof(delimInput), stdin);
	validator = strchr(delimInput, ',');
	if (validator != NULL) //Ensures a comma isn't used, but all other characters are allowed in the string
	{
		printf("Commas cannot be used in a CSV file.\n");
		return "error";
	}
	else
	{
		delimInput[strlen(delimInput) - 1] = "\0";	//truncates the line break from inputting
		strcpy(output, delimInput);	//copies validated input to the output string
		strcat(output, ",");	//Appends a comma to validated input

		printf("Please input item name:\n");
		fgets(delimInput, sizeof(delimInput), stdin);
		validator = strchr(delimInput, ',');
		if (validator != NULL)
		{
			printf("Commas cannot be used in a CSV file.\n");
			return "error";
		}
		else
		{
			delimInput[strlen(delimInput) -1] = "\0";
			strcat(output, delimInput); //appends validatedinput with the new data member
			strcat(output, ",");

			printf("Please input item quantity:\n");
			fgets(delimInput, sizeof(delimInput), stdin);
			validator = strchr(delimInput, ',');
			if (validator != NULL)
			{
				printf("Commas cannot be used in a CSV file.\n");
				return "error";
			}
			else
			{
				delimInput[strlen(delimInput) - 1] = "\0";
				strcat(output, delimInput); //appends validatedinput with the new data member
				strcat(output, ",");

				printf("Please input item price:\n");
				fgets(delimInput, sizeof(delimInput), stdin);
				validator = strchr(delimInput, ',');
				if (validator != NULL)
				{
					printf("Commas cannot be used in a CSV file.\n");
					return "error";
				}
				else
				{
					strcat(output, delimInput); //final append, does not truncate line break
					return output;
				}
			}
		}
	}
}



/// <summary>
/// Searches for an item ID in a file and sets the pointer to the beginning of the line.
/// </summary>
/// <param name="opened"> Pointer to an opened file</param>
/// <param name="ID"> String containing item ID</param>
void CSVFileSeek(FILE* opened, char* ID)
{
	ID[strlen(ID) - 1] = "\0";	//Truncates the line break from entered ID

	int idLen = (strlen(ID));
	char fileIDline[40] = "";

	while (feof(opened) == 0) //loops until end of file
	{
		fgets(fileIDline, idLen, opened);
		if (strcmp(fileIDline, ID) == 0)
		{
			opened -= sizeof(fileIDline);	//Backs up pointer to beginning of line in file
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
		printf("File could not be opened.");
		return;
	}

	printf("Please input the ID of the item you would like to delete.");
	fgets(idInput, sizeof(idInput), delimFile);
	CSVFileSeek(delimFile,idInput);
	if (feof(delimFile) != 0)
	{
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
		printf("File could not be opened.");
		fclose(delimFile);
		return;
	}

	printf("Please input the ID of the item you would like to delete.");
	fgets(idInput, sizeof(idInput), delimFile);
	CSVFileSeek(delimFile, idInput);
	if (feof(delimFile) == 0)
	{
		fclose(delimFile);
		return;
	}
	else
	{
		strcpy(validatedInput, CSVInputValidation());
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