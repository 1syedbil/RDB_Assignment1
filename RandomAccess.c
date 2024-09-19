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

	printf("New record added to file.\n\n");

	if (fclose(rndAccessFile) != 0)
	{
		printf("There was an error while closing the file.\n");
		return ;
	}
} 

void rndAccessReadRec(char fileName[STRING_LEN], int id)
{
	RndAccessRecord a[50] = { NULL };

	FILE* rndAccessFile = fopen(fileName, "rb"); 
	if (rndAccessFile == NULL) 
	{
		printf("There was an error in opening the file.\n");
		return;
	}

	if ((fseek(rndAccessFile, (calculateOffset(fileName, id)), SEEK_CUR)) != 0)       
	{
		printf("The fseek() function failed.\n");
		return;
	}

	if ((fread(&a[0], sizeof(RndAccessRecord), 1, rndAccessFile)) == 0)
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

void rndAccessUpdtRec(char fileName[STRING_LEN], int id, double newVal)
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

	if ((fseek(rndAccessFile, (calculateOffset(fileName, id)), SEEK_CUR)) != 0)   
	{
		printf("The fseek() function failed.\n");
		return;
	}

	long offset = name + cat + quant + price;     

	if ((fseek(rndAccessFile, offset, SEEK_CUR)) != 0)   
	{
		printf("The fseek() function failed.\n");
		return;
	}

	double newPrice = newVal ;

	if (fwrite(&newPrice, sizeof(double), 1, rndAccessFile) < 1)
	{
		printf("There was an error writing to the file.\n");
		return;
	}

	if (fclose(rndAccessFile) != 0) 
	{
		printf("There was an error while closing the file.\n");
		return;
	}

	printf("Price of record %d was updated.\n", id); 
}

void rndAccessDltRec(char fileName[STRING_LEN], int id)
{
	FILE* saveFile = fopen("../save.bin", "ab");
	if (saveFile == NULL) 
	{
		printf("There was an error in opening the file.\n");
		return;
	}

	printf("Save file created successfully.\n");

	FILE* rndAccessFile = fopen(fileName, "rb+"); 
	if (rndAccessFile == NULL)
	{
		printf("There was an error in opening the file.\n");
		return;
	}

	RndAccessRecord save[50] = { NULL }; 
	int arraySize = 0;

	while (fread(&save[arraySize], sizeof(RndAccessRecord), 1, rndAccessFile))
	{
		if (ferror(rndAccessFile) != 0)
		{
			printf("Error occurred in fread().\n");
			return;
		}

		arraySize++;
	}

	int index = 0;

	while (index <= (arraySize - 1)) 
	{
		if (save[index].productId != id) 
		{
			if ((fseek(rndAccessFile, (calculateOffset(fileName, (save[index].productId))), SEEK_CUR)) != 0)
			{
				printf("The fseek() function failed.\n");
				return;
			}

			if ((fseek(saveFile, ftell(rndAccessFile), SEEK_CUR)) != 0) 
			{
				printf("The fseek() function failed.\n");
				return;
			}

			if (fwrite(&save[index], sizeof(RndAccessRecord), 1, saveFile) < 1)
			{
				printf("There was an error while closing the file.\n");
				return;
			}
			index++; 
		}
		else if ((index + 1) <= (arraySize - 1))
		{
			if ((fseek(rndAccessFile, (calculateOffset(fileName, (save[index].productId))), SEEK_CUR)) != 0) 
			{
				printf("The fseek() function failed.\n");
				return;
			}

			if ((fseek(saveFile, ftell(rndAccessFile), SEEK_CUR)) != 0) 
			{
				printf("The fseek() function failed.\n"); 
				return;
			} 

			if (fwrite(&save[index + 1], sizeof(RndAccessRecord), 1, saveFile) < 1) 
			{
				printf("There was an error while closing the file.\n");
				return;
			}
			index += 2; 
		}
		else if ((index + 1) > (arraySize - 1))
		{
			break;
		}
	}

	printf("Records saved to save file successfully.\n");

	if (fclose(rndAccessFile) != 0)
	{
		printf("There was an error while closing a file.\n");
		return;
	}

	if (fclose(saveFile) != 0) 
	{
		printf("There was an error while closing a file.\n");
		return;
	}

	if (remove("../inventory.bin") != 0)
	{
		printf("Unable to delete file.\n");
		return;
	}

	printf("Original file deleted successfully.\n");

	if (rename("../save.bin", fileName) != 0)
	{
		printf("Unable to rename file.\n");
		return;
	}

	printf("Save file renamed successfully.\n");

}

long calculateOffset(char fileName[STRING_LEN], int id) 
{
	RndAccessRecord a[50] = { NULL }; 
	int arraySize = 0;
	int index = 0;

	FILE* rndAccessFile = fopen(fileName, "rb");
	if (rndAccessFile == NULL)
	{
		printf("There was an error in opening the file.\n");
		return -1;
	}

	while (fread(&a[arraySize], sizeof(RndAccessRecord), 1, rndAccessFile))  
	{
		if (ferror(rndAccessFile) != 0) 
		{
			printf("Error occurred in fread().\n");
			return;
		}

		arraySize++; 
	}

	if (fclose(rndAccessFile) != 0)
	{
		printf("There was an error while closing the file.\n");
		return -1;
	}

	while (index <= (arraySize - 1))
	{
		if (a[index].productId == id) 
		{
			break;
		}

		index++;
	}

	long offset = (sizeof(RndAccessRecord)) * index; 

	return offset;
} 

void displayAllRecs(char fileName[STRING_LEN])
{
	FILE* rndAccessFile = fopen(fileName, "rb");
	if (rndAccessFile == NULL)
	{
		printf("There was an error in opening the file.\n");
		return;
	}

	RndAccessRecord a = {0, "", "", 0, 0}; 

	printf("Here are all the records in the file currently:\n\n");

	while (fread(&a, sizeof(RndAccessRecord), 1, rndAccessFile))  
	{
		if (ferror(rndAccessFile) != 0)
		{
			printf("Error occurred in fread().\n");
			return;
		}

		printf("|  ProductId : %d  |  Name : %s  |  Category : %s  |  Quantity : %d  |  Price : %.2f  |\n", a.productId, a.name, a.category, a.quantity, a.price);
	}

	if (feof(rndAccessFile) != 0)
	{
		printf("\nEnd of file reached. All records have been printed.\n");
	}

	if (fclose(rndAccessFile) != 0) 
	{
		printf("There was an error while closing the file.\n");
	}
}

bool checkRecExists(char fileName[STRING_LEN], int id) 
{

}