#include "InventoryMgmtSys.h"

void addProduct(char fileName[STRING_LEN])
{
	char userInput[STRING_LEN] = "";
	Product fileProducts[20] = { NULL };
	Product newProduct = { 0, "", "", 0, 0 };

	FILE* sequentialFile = fopen(fileName, "a+");
	if (sequentialFile == NULL)
	{
		printf("fopen() failed.\n\n");
		return;
	}

	int counter = 0;
	while (fscanf(sequentialFile, "%d %s %s %d %lf", &fileProducts[counter].id, fileProducts[counter].name, fileProducts[counter].category, &fileProducts[counter].quantity, &fileProducts[counter].price) != EOF)
	{
		counter++;
	}

	if (fclose(sequentialFile) != 0)
	{
		printf("fclose() failed.\n\n");
		return;
	}

	printf("Enter a ProductId for the new product: ");
	strcpy(userInput, getUserInput(userInput));
	if (!validateInt(userInput))
	{
		return;
	}
	newProduct.id = atoi(userInput);

	for (int i = 0; i < counter; i++)
	{
		if (newProduct.id == fileProducts[i].id)
		{
			printf("A product with this ID already exists. No duplicate IDs allowed.\n\n");
			return;
		}
	}

	printf("Enter a Name for the new product: ");
	strcpy(newProduct.name, getUserInput(newProduct.name));
	if (!validateString(newProduct.name))
	{
		return;
	}

	printf("Enter a Category for the new product: ");
	strcpy(newProduct.category, getUserInput(newProduct.category));
	if (!validateString(newProduct.category))
	{
		return;
	}

	printf("Enter a Quantity for the new product: ");
	strcpy(userInput, getUserInput(userInput));
	if (!validateInt(userInput))
	{
		return;
	}
	newProduct.quantity = atoi(userInput);

	printf("Enter a Price for the new product: ");
	strcpy(userInput, getUserInput(userInput));
	if (!validateDouble(userInput))
	{
		return;
	}
	newProduct.price = atof(userInput);

	fileProducts[counter] = newProduct;

	sequentialFile = fopen(fileName, "w");

	for (int i = 0; i <= counter; i++)
	{
		fprintf(sequentialFile, "%d %s %s %d %.2f\n", fileProducts[i].id, fileProducts[i].name, fileProducts[i].category, fileProducts[i].quantity, fileProducts[i].price);
	}

	if (fclose(sequentialFile) != 0)
	{
		printf("fclose() failed.\n\n");
		return;
	}

	printf("New product added successfully.\n\n");
}

void displayProducts(char fileName[STRING_LEN])
{
	Product holdProduct = { 0, "", "", 0, 0 };

	FILE* sequentialFile = fopen(fileName, "r");
	if (sequentialFile == NULL)
	{
		printf("fopen() failed.\n\n");
		return;
	}

	printf("| %-10s | %-20s | %-20s | %-10s | %-10s |\n", "ProductId", "Name", "Category", "Quantity", "Price");
	printf("--------------------------------------------------------------------------------------\n");

	while (fscanf(sequentialFile, "%d %s %s %d %lf", &holdProduct.id, holdProduct.name, holdProduct.category, &holdProduct.quantity, &holdProduct.price) != EOF)
	{
		printf("| %-10d | %-20s | %-20s | %-10d | %-10.2f |\n", holdProduct.id, holdProduct.name, holdProduct.category, holdProduct.quantity, holdProduct.price);
	}

	if (fclose(sequentialFile) != 0)
	{
		printf("fclose() failed.\n\n");
		return;
	}

	printf("\n\n");
}

void updateProduct(char fileName[STRING_LEN])
{
	char userInput[STRING_LEN] = "";
	char fileContents[20][STRING_LEN] = { NULL };
	Product fileProducts[20] = { NULL };
	Product newProduct = { 0, "", "", 0, 0 };
	int counter = 0;
	bool idExists = false;

	FILE* sequentialFile = fopen(fileName, "r");
	if (sequentialFile == NULL)
	{
		printf("fopen() failed.\n\n");
		return;
	}

	printf("Enter the ProductId of the product you want to update: ");
	strcpy(userInput, getUserInput(userInput));
	if (!validateInt(userInput))
	{
		return;
	}
	newProduct.id = atoi(userInput);

	while (fscanf(sequentialFile, "%d %s %s %d %lf", &fileProducts[counter].id, fileProducts[counter].name, fileProducts[counter].category, &fileProducts[counter].quantity, &fileProducts[counter].price) != EOF)
	{
		if (newProduct.id == fileProducts[counter].id)
		{
			idExists = true;
		}
		counter++;
	}

	if (fclose(sequentialFile) != 0)
	{
		printf("fclose() failed.\n\n");
		return;
	}

	if (!idExists)
	{
		printf("A product with the corresponding ProductId does not exist.\n\n");
		return;
	}

	sequentialFile = fopen(fileName, "w");
	if (sequentialFile == NULL)
	{
		printf("fopen() failed.\n\n");
		return;
	}

	printf("Enter a Name for the product: ");
	strcpy(newProduct.name, getUserInput(newProduct.name));
	if (!validateString(newProduct.name))
	{
		return;
	}

	printf("Enter a Category for the product: ");
	strcpy(newProduct.category, getUserInput(newProduct.category));
	if (!validateString(newProduct.category))
	{
		return;
	}

	printf("Enter a Quantity for the product: ");
	strcpy(userInput, getUserInput(userInput));
	if (!validateInt(userInput))
	{
		return;
	}
	newProduct.quantity = atoi(userInput);

	printf("Enter a Price for the product: ");
	strcpy(userInput, getUserInput(userInput));
	if (!validateDouble(userInput))
	{
		return;
	}
	newProduct.price = atof(userInput);

	for (int i = 0; i < counter; i++)
	{
		if (newProduct.id == fileProducts[i].id)
		{
			fileProducts[i] = newProduct;
		}
		fprintf(sequentialFile, "%d %s %s %d %.2f\n", fileProducts[i].id, fileProducts[i].name, fileProducts[i].category, fileProducts[i].quantity, fileProducts[i].price);
	}

	if (fclose(sequentialFile) != 0)
	{
		printf("fclose() failed.\n\n");
		return;
	}

	printf("Product has been updated successfully.\n\n");
}

void deleteProduct(char fileName[STRING_LEN])
{
	char userInput[STRING_LEN] = "";
	Product fileProducts[20] = { NULL };
	int id = 0;
	int counter = 0;
	bool idExists = false;

	FILE* sequentialFile = fopen(fileName, "r");
	if (sequentialFile == NULL)
	{
		printf("fopen() failed.\n\n");
		return;
	}

	printf("Enter the ProductId of the product you want to delete: ");
	strcpy(userInput, getUserInput(userInput));
	if (!validateInt(userInput))
	{
		return;
	}
	id = atoi(userInput);

	while (fscanf(sequentialFile, "%d %s %s %d %lf", &fileProducts[counter].id, fileProducts[counter].name, fileProducts[counter].category, &fileProducts[counter].quantity, &fileProducts[counter].price) != EOF)
	{
		if (id == fileProducts[counter].id)
		{
			idExists = true;
		}
		counter++;
	}

	if (fclose(sequentialFile) != 0)
	{
		printf("fclose() failed.\n\n");
		return;
	}

	if (!idExists)
	{
		printf("A product with the corresponding ProductId does not exist.\n\n");
		return;
	}

	sequentialFile = fopen(fileName, "w");
	if (sequentialFile == NULL)
	{
		printf("fopen() failed.\n\n");
		return;
	}

	for (int i = 0; i < counter; i++)
	{
		if (fileProducts[i].id == id)
		{
			continue;
		}
		fprintf(sequentialFile, "%d %s %s %d %.2f\n", fileProducts[i].id, fileProducts[i].name, fileProducts[i].category, fileProducts[i].quantity, fileProducts[i].price);
	}

	if (fclose(sequentialFile) != 0)
	{
		printf("fclose() failed.\n\n");
		return;
	}

	printf("Product has been deleted successfully.\n\n");
}