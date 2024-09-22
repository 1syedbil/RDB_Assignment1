#include "InventoryMgmtSys.h"

int main(void)
{
	struct Product products[MAX_PRODUCTS] = { NULL }; 
	int times = readProducts(products);
	char rndAccFileName[STRING_LEN] = "../inventory.bin"; 
	char userInput[STRING_LEN] = "";
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int id = 0;
	char newName[STRING_LEN] = "";
	char newCategory[STRING_LEN] = ""; 
	int newQuant = 0;
	double newPrice = 0; 

	do
	{
		printf("File Access Program Menu:\n\n     1. Sequential Access     2. Random Access     3. Delimited File     4. Exit\n\n");
		printf("Enter a number corresponding with your menu selection: ");
		strcpy(userInput, getUserInput(userInput));  
		printf("\n\n");    
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
				choice2 = atoi(userInput);

				switch (choice2)
				{
				case 1:
					addProduct(products, &times);
					break;

				case 2:
					displayProducts(products, times); 
					break;

				case 3:
					updateProduct(products, times);
					break;

				case 4:
					deleteProduct(products, &times);
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
				printf("Select a CRUD operation you want to perform:\n\n\t1.Create Record\t2. Read Record\t3. Update Record\t4. Delete Record\t5. Back\n\nEnter a number corresponding with the option you want to select: ");
				strcpy(userInput, getUserInput(userInput));
				if (strlen(userInput) == 0)
				{
					printf("Error: you must input a value. Input cannot be empty.\n\n");
					continue;
				}
				printf("\n\n");
				choice2 = atoi(userInput);
				if (choice2 == 0)
				{
					printf("Invalid menu selection, must enter a number option showing on the menu.\n\n");
					continue;
				}
				strcpy(userInput, "");

				switch (choice2)
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
					if (checkRecExists(rndAccFileName, id) != -1)
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
					rndAccessCreateRec(id, newQuant, newPrice, newName, newCategory, rndAccFileName); 
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
					if (checkRecExists(rndAccFileName, id) == -1)
					{
						printf("No such record exists with the corresponding ProductId.\n");
						continue;
					}
					rndAccessReadRec(rndAccFileName, id);
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
					if (checkRecExists(rndAccFileName, id) == -1)
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
					choice3 = atoi(userInput);  
					if (choice3 == 0)
					{
						printf("Invalid menu selection, must enter a number option showing on the menu.\n\n");
						continue;
					}
					strcpy(userInput, "");
					switch (choice3)
					{
					case 1:
						printf("Enter a value for the name: ");
						strncpy(userInput, getUserInput(userInput), STRING_LEN - 1);
						printf("\n\n");
						rndAccessUpdtRec(rndAccFileName, id, choice3, userInput);
						strcpy(userInput, "");
						break;

					case 2:
						printf("Enter a value for the category: ");
						strncpy(userInput, getUserInput(userInput), STRING_LEN - 1);
						printf("\n\n");
						rndAccessUpdtRec(rndAccFileName, id, choice3, userInput);
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
						rndAccessUpdtRec(rndAccFileName, id, choice3, userInput);
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
						rndAccessUpdtRec(rndAccFileName, id, choice3, userInput);
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
					if (checkRecExists(rndAccFileName, id) == -1)
					{
						printf("No such record exists with the corresponding ProductId.\n");
						continue;
					}
					rndAccessDltRec(rndAccFileName, id);
					break;

				default:
					break;
				}
			} while (choice2 != 5);
			choice2 = 0;
			strcpy(userInput, "");
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