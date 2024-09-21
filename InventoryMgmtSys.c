#include "InventoryMgmtSys.h"

int main(void)
{
	char fileName[STRING_LEN] = "../inventory.bin";
	char userInput[STRING_LEN] = "";
	int id = 0;
	char newName[STRING_LEN] = "";
	char newCategory[STRING_LEN] = "";
	int newQuant = 0;
	double newPrice = 0;
	int menuChoice = 0;

	while (menuChoice != 4)
	{
		printf("Select an option for file access:\n\n\t1. Sequential Access\t2. Random Access\t3. Delimited File Access\t4. Exit\n\nEnter a number corresponding with the option you want to select: ");
		strcpy(userInput, getUserInput(userInput));
		if (strlen(userInput) == 0)
		{
			printf("Error: you must input a value. Input cannot be empty.\n\n");  
			continue;
		}
		printf("\n\n");
		menuChoice = atoi(userInput);
		if (menuChoice == 0)
		{
			printf("Invalid menu selection, must enter a number option showing on the menu.\n\n");
			continue;
		}
		strcpy(userInput, "");

		switch (menuChoice)
		{
		case 1:
			printf("Select a CRUD operation you want to perform:\n\n\t1.Create Record\t2. Read Record\t3. Update Record\t4. Delete Record\n\nEnter a number corresponding with the option you want to select: ");
			strcpy(userInput, getUserInput(userInput));
			if (strlen(userInput) == 0)
			{
				printf("Error: you must input a value. Input cannot be empty.\n\n");
				continue;
			}
			printf("\n\n");
			menuChoice = atoi(userInput);
			if (menuChoice == 0)
			{
				printf("Invalid menu selection, must enter a number option showing on the menu.\n\n");
				continue;
			}
			strcpy(userInput, "");


			menuChoice = 0;
			strcpy(userInput, "");
			break;

		case 2:
			while (menuChoice != 5)
			{
				printf("Select a CRUD operation you want to perform:\n\n\t1.Create Record\t2. Read Record\t3. Update Record\t4. Delete Record\t5. Back\n\nEnter a number corresponding with the option you want to select: ");
				strcpy(userInput, getUserInput(userInput));
				if (strlen(userInput) == 0)
				{
					printf("Error: you must input a value. Input cannot be empty.\n\n");
					continue;
				}
				printf("\n\n");
				menuChoice = atoi(userInput);
				if (menuChoice == 0)
				{
					printf("Invalid menu selection, must enter a number option showing on the menu.\n\n");
					continue;
				}
				strcpy(userInput, "");

				switch (menuChoice)
				{
				case 1:
					printf("Enter a value for ProductId (this is the primary key): ");
					strcpy(userInput, getUserInput(userInput));
					id = atoi(userInput);
					if (id <= 0)
					{
						printf("Invalid ProductId value, must enter a positive and non-zero integer.\n\n");
						continue;
					}
					if (checkRecExists(fileName, id) != -1)
					{
						printf("A record with this ProductId already exists. No duplicated IDs allowed.\n\n");
						continue;
					}
					printf("\n\n");
					printf("Enter a value for Name: ");
					strncpy(newName, getUserInput(newName), STRING_LEN - 1);
					printf("\n\n");
					printf("Enter a value for Category: ");
					strncpy(newCategory, getUserInput(newCategory), STRING_LEN - 1);
					printf("\n\n");
					printf("Enter a value for Quantity: ");
					strcpy(userInput, getUserInput(userInput));
					newQuant = validateQuant(userInput);
					if (newQuant == -1)
					{
						continue;
					}
					printf("\n\n");
					printf("Enter a value for Price: ");
					strcpy(userInput, getUserInput(userInput));
					newPrice = validatePrice(userInput);
					if (newPrice == -1)
					{
						continue;
					}
					printf("\n\n");
					rndAccessCreateRec(id, newQuant, newPrice, newName, newCategory, fileName);
					break;

				case 2:
					printf("Enter the ProductId of the record you would like to read: ");
					strcpy(userInput, getUserInput(userInput));
					printf("\n\n");
					id = atoi(userInput);
					if (id <= 0)
					{
						printf("Invalid ProductId value, must enter a positive and non-zero integer.\n\n");
						continue;
					}
					if (checkRecExists(fileName, id) == -1)
					{
						printf("No such record exists with the corresponding ProductId.\n");
						continue;
					}
					rndAccessReadRec(fileName, id);
					break;

				case 3:
					printf("Enter the ProductId of the record you would like to update: ");
					strcpy(userInput, getUserInput(userInput));
					printf("\n\n");
					id = atoi(userInput);
					if (id <= 0)
					{
						printf("Invalid ProductId value, must enter a positive and non-zero integer.\n\n");
						continue;
					}
					if (checkRecExists(fileName, id) == -1)
					{
						printf("No such record exists with the corresponding ProductId.\n");
						continue;
					}
					strcpy(userInput, "");
					printf("Select which attribute you would like to update:\n\n\t1. Name\t2. Category\t3. Quantity\t4. Price\n\nEnter a number corresponding with the option you want to select: ");
					strcpy(userInput, getUserInput(userInput));
					if (strlen(userInput) == 0)
					{
						printf("Error: you must input a value. Input cannot be empty.\n\n");
						continue;
					}
					printf("\n\n");
					menuChoice = atoi(userInput);
					if (menuChoice == 0)
					{
						printf("Invalid menu selection, must enter a number option showing on the menu.\n\n");
						continue;
					}
					strcpy(userInput, "");
					switch (menuChoice)
					{
					case 1:
						printf("Enter a value for the name: ");
						strncpy(userInput, getUserInput(userInput), STRING_LEN - 1);
						printf("\n\n");
						rndAccessUpdtRec(fileName, id, menuChoice, userInput);
						strcpy(userInput, "");
						break;

					case 2:
						printf("Enter a value for the category: ");
						strncpy(userInput, getUserInput(userInput), STRING_LEN - 1);
						printf("\n\n");
						rndAccessUpdtRec(fileName, id, menuChoice, userInput);
						strcpy(userInput, "");
						break;

					case 3:
						printf("Enter a value for the quantity: ");
						strncpy(userInput, getUserInput(userInput), STRING_LEN - 1);
						if (validateQuant(userInput) == -1)
						{
							continue;
						}
						printf("\n\n");
						rndAccessUpdtRec(fileName, id, menuChoice, userInput);
						strcpy(userInput, "");
						break;

					case 4:
						printf("Enter a value for the price: ");
						strncpy(userInput, getUserInput(userInput), STRING_LEN - 1);
						if (validatePrice(userInput) == -1)
						{
							continue;
						}
						printf("\n\n");
						rndAccessUpdtRec(fileName, id, menuChoice, userInput);
						strcpy(userInput, "");
						break;
					}
					break;

				case 4:
					printf("Enter the ProductId of the record you would like to delete: ");
					strcpy(userInput, getUserInput(userInput));
					printf("\n\n");
					id = atoi(userInput);
					if (id <= 0)
					{
						printf("Invalid ProductId value, must enter a positive and non-zero integer.\n\n");
						continue;
					}
					if (checkRecExists(fileName, id) == -1)
					{
						printf("No such record exists with the corresponding ProductId.\n");
						continue;
					}
					rndAccessDltRec(fileName, id);
					break;

				default:
					break;
				}
			}
			menuChoice = 0;
			strcpy(userInput, "");
			break;

		case 3:
			printf("Select a CRUD operation you want to perform:\n\n\t1.Create Record\t2. Read Record\t3. Update Record\t4. Delete Record\n\nEnter a number corresponding with the option you want to select: ");
			strcpy(userInput, getUserInput(userInput));
			if (strlen(userInput) == 0)
			{
				printf("Error: you must input a value. Input cannot be empty.\n\n");
				continue;
			}
			printf("\n\n");
			menuChoice = atoi(userInput);
			if (menuChoice == 0)
			{
				printf("Invalid menu selection, must enter a number option showing on the menu.\n\n");
				continue;
			}
			strcpy(userInput, "");


			menuChoice = 0;
			strcpy(userInput, "");
			break;

		case 4:
			printf("Exiting...");
			break;

		default:
			printf("Invalid menu selection, must enter a number option showing on the menu.\n\n");
			break;
		}
	}
	return 0;
}