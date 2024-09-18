#include "InventoryMgmtSys.h"


//THIS IS WHERE THE DEFINITIONS FOR ALL OF THE FUNCTIONS RELATED TO RANDOM ACCESS WILL GO

void rndAccessCreateRec(int id, int quant, double price, char name[STRING_LEN], char cat[STRING_LEN], char fileName[STRING_LEN])
{
	RndAccessRecord rec = { 0, 0, 0, "", ""};
	RndAccessRecord a[100] = {NULL}; 

	rec.productId = id;
	rec.quantity = quant;
	rec.price = price;
	strcpy(rec.name, name);
	strcpy(rec.category, cat);

	FILE* rndAccessFile = fopen(fileName, "ab");
	if (rndAccessFile == NULL)
	{
		printf("There was an error in opening the file.\n");
		return ;
	}

	if (fwrite(&rec, sizeof(RndAccessRecord), 1, rndAccessFile) < 1)
	{
		printf("There was an error writing to the file.\n");
		return ;
	}

	if (fclose(rndAccessFile) != 0)
	{
		printf("There was an error while closing the file.\n");
		return ;
	}

	printf("New record added to file.\n\n");
} 

void rndAccessReadRec(char fileName[STRING_LEN], int id)
{
	RndAccessRecord a[20] = { NULL };

	FILE* rndAccessFile = fopen(fileName, "rb"); 
	if (rndAccessFile == NULL) 
	{
		printf("There was an error in opening the file.\n");
		return;
	}

	if ((fseek(rndAccessFile, (calculateOffset(id)), SEEK_SET)) != 0)  
	{
		printf("The fseek() function failed.\n");
		return;
	}

	if ((fread(a, sizeof(a[0]), 1, rndAccessFile)) == 0) 
	{
		if (ferror(rndAccessFile) != 0)
		{
			printf("Error occurred in fread().\n");
			return;
		}

		if (feof(rndAccessFile) != 0)
		{
			printf("End of file.\n");
			return;
		}
	}

	printf("|  ProductId : %d  |  Name : %s  |  Category : %s  |  Quantity : %d  |  Price : %.2f  |\n", a[0].productId, a[0].name, a[0].category, a[0].quantity, a[0].price); 

	if (fclose(rndAccessFile) != 0)
	{
		printf("There was an error while closing the file.\n");
		return;
	}
}

void rndAccessUpdtRec(char fileName[STRING_LEN], int id, int newVal)
{
	size_t prodId = sizeof(int);
	size_t name = sizeof(char) * STRING_LEN; 
	size_t cat = sizeof(char) * STRING_LEN;
	size_t quant = sizeof(int);
	size_t price = sizeof(double);  

	FILE* rndAccessFile = fopen(fileName, "rb+");
	if (rndAccessFile == NULL)
	{
		printf("There was an error in opening the file.\n");
		return;
	}

	if ((fseek(rndAccessFile, (calculateOffset(id)), SEEK_SET)) != 0) 
	{
		printf("The fseek() function failed.\n");
		return;
	}

	long offset = name + cat + quant;    

	if ((fseek(rndAccessFile, offset, SEEK_CUR)) != 0)  
	{
		printf("The fseek() function failed.\n");
		return;
	}

	int newQuant = newVal ;

	if (fwrite(&newQuant, sizeof(int), 1, rndAccessFile) < 1)
	{
		printf("There was an error writing to the file.\n");
		return;
	}

	if (fclose(rndAccessFile) != 0) 
	{
		printf("There was an error while closing the file.\n");
		return;
	}

	printf("Quantity was updated.\n");
}

long calculateOffset(int id)
{
	long offset = (sizeof(RndAccessRecord)) * (id - 1);

	return offset;
} 