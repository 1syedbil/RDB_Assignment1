/*
* FILE          : InventoryMgmtSys.c
* PROJECT       : Relational Databases Assignment 1
* PROGRAMMERS   : Bilal Syed, Morgan Tabor, Quang Minh Vu
* FIRST VERSION : 2024-09-13
* DESCRIPTION   : This file acts as the main entry point for our inventory management
*                 system program. It performs in a loop so that the user has the choice
*                 to keep performing actions or to leave if they would like to. It 
*                 starts off by showing a menu to the user for which kind of file access
*                 method they would like to use and then prompting them to input their 
*                 choice. After they make a choice the program enters a switch-case.
*                 statement. Case 1 is sequential, case 2 is random, and case 3 is delim.
*                 There is a secondary menu for all of the file access options that once 
*                 again loops within the file access option's respective case. It is in
*                 this nested loop where the user can now choose which CRUD operations to
*                 perform via the file access method they chose from the previous menu. 
*                 the CRUD operations menu uses a smilar switch-case statement as the 
*                 previous menu. 
*/

#include "InventoryMgmtSys.h"

int main(void)
{
	char seqFileName[STRING_LEN] = "sequentialFile.txt";
	char rndFileName[STRING_LEN] = "randomFile.bin";
	char userInput[STRING_LEN] = "";
	int choice1 = 0;
	int choice2 = 0;

	do
	{
		printf("File Access Program Menu:\n\n     1. Sequential Access     2. Random Access     3. Delimited File     4. Exit\n\n");
		printf("Enter a number corresponding with your menu selection: ");
		strcpy(userInput, getUserInput(userInput));   
		printf("\n\n");   
		if (!validateInt(userInput))
		{
			printf("Error: invalid input. Must be a non-zero and positive integer.\n\n");
			continue;
		}
		choice1 = atoi(userInput);  

		switch (choice1) 
		{
		case 1:
			do
			{

				printf("Sequential Access Menu:\n\n     1. Create a Record     2. Read All Records     3. Update a Record     4. Delete a Record     5. Back\n\n"); 
				printf("Enter a number corresponding with your menu selection: "); 
				strcpy(userInput, getUserInput(userInput)); 
				printf("\n\n");
				if (!validateInt(userInput))
				{
					printf("Error: invalid input. Must be a non-zero and positive integer.\n\n");
					continue;
				}
				choice2 = atoi(userInput); 

				switch (choice2) 
				{ 
				case 1:
					addProduct(seqFileName); 
					break;

				case 2:
					displayProducts(seqFileName); 
					break;

				case 3:
					updateProduct(seqFileName);
					break;

				case 4:
					deleteProduct(seqFileName); 
					break;

				case 5:
					printf("Going back...\n\n"); 
					break;

				default:
					printf("Error: invalid menu selection.\n\n");
					break;
				}

			} while (choice2 != 5);

			break;

		case 2:
			do
			{
				printf("Random Access Menu:\n\n     1. Create a Record     2. Read a Record     3. Update a Record     4. Delete a Record     5. Back\n\n");
				printf("Enter a number corresponding with your menu selection: ");
				strcpy(userInput, getUserInput(userInput));
				printf("\n\n");
				if (!validateInt(userInput))
				{
					printf("Error: invalid input. Must be a non-zero and positive integer.\n\n"); 
					continue;
				}
				choice2 = atoi(userInput);

				switch (choice2)
				{
				case 1:
					rndAccessCreateRecord(rndFileName);
					break;

				case 2:
					rndAccessReadRec(rndFileName);
					break;

				case 3:
					rndAccessUpdtRec(rndFileName);
					break;

				case 4:
					rndAccessDltRecord(rndFileName);
					break;

				case 5:
					printf("Going back...\n\n");
					break;

				default:
					printf("Error: invalid menu selection.\n\n");
					break;
				}

			} while (choice2 != 5);

			break;

		case 3:
			do
			{

				printf("Delimited File Menu:\n\n     1. Create a Record     2. Read All Records     3. Update a Record     4. Delete a Record     5. Back\n\n");
				printf("Enter a number corresponding with your menu selection: ");
				strcpy(userInput, getUserInput(userInput));
				printf("\n\n");  
				if (!validateInt(userInput))
				{
					printf("Error: invalid input. Must be a non-zero and positive integer.\n\n");
					continue;
				}
				choice2 = atoi(userInput); 

				switch (choice2)
				{
				case 1:

					break;

				case 2:

					break;

				case 3:

					break;

				case 4:

					break;

				case 5:
					printf("Going back...\n\n");
					break;

				default:
					printf("Error: invalid menu selection.\n\n");
					break;
				}

			} while (choice2 != 5);

			break;

		case 4:
			printf("Exiting...");
			break;

		default:
			printf("Error: invalid menu selection.\n\n");
			break;
		}

	} while (choice1 != 4);

	return 0;
}