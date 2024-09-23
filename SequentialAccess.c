/*
* FILE          : SequentialAccess.c
* PROJECT       : Relational Databases Assignment 1
* PROGRAMMERS   : Bilal Syed, Morgan Tabor, Quang Minh Vu
* FIRST VERSION : 2024-09-13
* DESCRIPTION   : This file contains the function definitions for all of the sequential
*                 access CRUD operations. All of the code in this file was written by 
*                 Quang Minh Vu and Bilal Syed.
*/

#include "InventoryMgmtSys.h"


/*
* FUNCTION    : addProduct()
* PROGRAMMERS : Quang Minh Vu and Bilal Syed
* DESCRIPTION : This function is used to add a new product to the file. First the file is 
*               opened for appending and reading, and each product in the file is read into 
*               an array of Product structs. The products are read in a loop and a counter is
*               incremented at the end of each loop to keep track of the total number of products
*               in the file. After this the file is closed and the function gets the user input
*               for the values they want the attributes of the new product to have. It first gets ID
*               and uses a for-loop to loop through the array of products in order to check if any 
*               of the products already have the ID that the user entered. If the ID already exists 
*               then the user cannot use the ID they entered to make a new product, and the function
*               returns to main. Otherwise, the function proceeds to get the rest of the values for 
*               the new product from the user input. The new product is then added to the end of the
*               array of products. The file is opened once again but this time it's for write only. This
*               way the file will be wiped clean from its current contents. Then, the array of products
*               (including the new product) are written into the file in order using a loop. Once every
*               product in the array is written into the file, the file is closed.
* PARAMETERS  :
*	char fileName[STRING_LEN] - String to hold the file name.
* RETURNS     :
*	void
*/
void addProduct(char fileName[STRING_LEN])
{
	char userInput[STRING_LEN] = "";
	Product fileProducts[ARRAY_SIZE] = { NULL };
	Product newProduct = { 0, "", "", 0, 0 };
	int counter = 0; 

	FILE* sequentialFile = fopen(fileName, "a+");
	if (sequentialFile == NULL)
	{
		printf("fopen() failed.\n\n");
		return;
	}

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
		printf("Error: invalid input. Must be a non-zero and positive integer.\n\n");
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
		printf("Error: invalid input. Must be a non-zero and positive integer.\n\n");
		return;
	}
	newProduct.quantity = atoi(userInput);

	printf("Enter a Price for the new product: ");
	strcpy(userInput, getUserInput(userInput));
	if (!validateDouble(userInput))
	{
		printf("Error: invalid input. Must be a positive and non-zero number.\n\n"); 
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

/*
* FUNCTION    : displayProducts()
* PROGRAMMERS : Quang Minh Vu and Bilal Syed
* DESCRIPTION : This is an extremely simple function that displays each product in the file to the
*               user in the order that it appears in within the file. First the file is opened for 
*               reading only. Then, it reads through the file line by line in a loop. Each loop
*               reads the current product into a variable to hold that product and then prints that 
*               variable out onto the console using printf. Once every line in the file has been read,
*               the file is closed.
* PARAMETERS  :
*	char fileName[STRING_LEN] - String to hold the file name.
* RETURNS     :
*	void
*/
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

/*
* FUNCTION    : updateProduct()
* PROGRAMMERS : Quang Minh Vu and Bilal Syed
* DESCRIPTION : This function is used to update a specific product in the file. First the function
*               gets the user input for the ID corresponding with the product that they want to update. 
*               After this the file is opened only for reading and the entire contents of the file are
*               read into an array of Product structs. This is done in a loop where it first checks if 
*               the current product being read has an ID matching the one that the user inputted. If it does
*               match then a bool variable representing whether the ID exists or not is set true. After 
*               this a counter variable representing the number of products in the file is incremented at
*               the end of each loop. Once every line in the file has been read into the array, the loop is
*               exited and the file is closed. Then the function checks if the bool variable is true or not.
*               If it ends up being false then the function returns to main since the product corresponding
*               to the ID that the user inputted does not exist. From here, the function gets the user input
*               for the values that they want to assign to each attribute of the updated product. The file is
*               opened once again, only this time it is for writing only, this way the file is wiped clean and the
*               contents of the file including the updated product can be written back into the file in order.
*               The products saved inside the array are wrriten into the file in a for-loop that keeps looping
*               as long as the last index is not reached. The loop first checks to see if the ID of the current
*               product in the array matches the ID of the updated product. If it does match then the product
*               in the array is set equal to the updated product and then it is written into the file. Otherwise
*               it just writes the current product in the array into the file as is. Once all products have been
*               written back into the file, the function exits the loop and closes the file.
* PARAMETERS  :
*	char fileName[STRING_LEN] - String to hold the file name.
* RETURNS     :
*	void
*/
void updateProduct(char fileName[STRING_LEN])
{
	char userInput[STRING_LEN] = "";
	Product fileProducts[ARRAY_SIZE] = { NULL }; 
	Product newProduct = { 0, "", "", 0, 0 };
	int counter = 0;
	bool idExists = false;

	printf("Enter the ProductId of the product you want to update: ");
	strcpy(userInput, getUserInput(userInput));
	if (!validateInt(userInput))
	{
		printf("Error: invalid input. Must be a non-zero and positive integer.\n\n");
		return;
	}
	newProduct.id = atoi(userInput);

	FILE* sequentialFile = fopen(fileName, "r");
	if (sequentialFile == NULL)
	{
		printf("fopen() failed.\n\n");
		return;
	}

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
		printf("Error: invalid input. Must be a non-zero and positive integer.\n\n");
		return;
	}
	newProduct.quantity = atoi(userInput);

	printf("Enter a Price for the product: ");
	strcpy(userInput, getUserInput(userInput));
	if (!validateDouble(userInput))
	{
		printf("Error: invalid input. Must be a positive and non-zero number.\n\n"); 
		return;
	}
	newProduct.price = atof(userInput);

	sequentialFile = fopen(fileName, "w"); 
	if (sequentialFile == NULL) 
	{
		printf("fopen() failed.\n\n"); 
		return;
	}

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

/*
* FUNCTION    : deleteProduct()
* PROGRAMMERS : Quang Minh Vu and Bilal Syed
* DESCRIPTION : This function is used to delete a specific product from the file. First the function
*               gets the user input for the ID of the product that they would like to delete. Then
*               the file is opened only for reading and the entire contents of the file are read into
*               an array of Product structs via a loop. Upon each loop the function first checks to 
*               see if the ID that the user inputted matches the ID of the current product being read.
*               If it does match, then a bool variable meant to confirm if the product corresponding to 
*               the ID exists or not, is set equal to true. And a counter variable to hold the number of
*               products in the file is incremented at the end of each loop. Once the loop is exited, the file is
*			    closed. Then the function checks if the bool variable is true or not, if it is false then the function 
*			    exits because no such product exists with the corresponding ID. After this the file is opened
*			    once again but this time its for only writing, this way the file is wiped clean. Now that the
*			    file is empty, the contents of the array used to save the contents of the file gets rewritten 
*			    into the file via a loop. The loop first checks if the ID of the product in the current index matches the
*			    ID of the product being deleted. If it does match, then the loop skips writing the product into
*			    the file and moves to the next index. Once all of the products in the array (except for the one
*			    being deleted) have been written back into the file, the loop ends and the files closes.
* PARAMETERS  :
*	char fileName[STRING_LEN] - String to hold the file name.
* RETURNS     :
*	void
*/
void deleteProduct(char fileName[STRING_LEN])
{
	char userInput[STRING_LEN] = "";
	Product fileProducts[ARRAY_SIZE] = { NULL }; 
	int id = 0;
	int counter = 0;
	bool idExists = false;

	printf("Enter the ProductId of the product you want to delete: ");
	strcpy(userInput, getUserInput(userInput));
	if (!validateInt(userInput))
	{
		printf("Error: invalid input. Must be a non-zero and positive integer.\n\n"); 
		return;
	}
	id = atoi(userInput);

	FILE* sequentialFile = fopen(fileName, "r");
	if (sequentialFile == NULL)
	{
		printf("fopen() failed.\n\n");
		return;
	}

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