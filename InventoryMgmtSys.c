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
