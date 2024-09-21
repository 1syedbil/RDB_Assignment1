#include "InventoryMgmtSys.h"


//THIS IS WHERE THE DEFINITIONS FOR ALL OF THE FUNCTIONS RELATED TO RANDOM ACCESS WILL GO

void rndAccessCreateRec(int id, int quant, double price, char name[STRING_LEN], char cat[STRING_LEN], char fileName[STRING_LEN])
{
	RndAccessRecord rec = { 0, "", "", 0, 0 };

	rec.productId = id;
	rec.quantity = quant;
	rec.price = price;
	strcpy(rec.name, name);
	strcpy(rec.category, cat);

	FILE* rndAccessFile = fopen(fileName, "ab");
	if (rndAccessFile == NULL)
	{
		printf("There was an error in opening the file.\n\n");
		return;
	}

	if (fwrite(&rec, sizeof(RndAccessRecord), 1, rndAccessFile) < 1)
	{
		printf("There was an error writing to the file.\n\n");
		return;
	}

	if (fclose(rndAccessFile) != 0)
	{
		printf("There was an error while closing the file.\n\n");
		return;
	}

	printf("New record added to file.\n\n");
}

void rndAccessReadRec(char fileName[STRING_LEN], int id)
{
	RndAccessRecord saveRec = { 0, "", "", 0, 0 };

	FILE* rndAccessFile = fopen(fileName, "rb");
	if (rndAccessFile == NULL)
	{
		printf("There was an error in opening the file.\n\n");
		return;
	}

	if ((fseek(rndAccessFile, (calculateOffset(fileName, id)), SEEK_CUR)) != 0)
	{
		printf("The fseek() function failed.\n\n");
		return;
	}

	if ((fread(&saveRec, sizeof(RndAccessRecord), 1, rndAccessFile)) == 0)
	{
		if (ferror(rndAccessFile) != 0)
		{
			printf("Error occurred in fread().\n\n");
			return;
		}

		if (feof(rndAccessFile) != 0)
		{
			printf("End of file.\n\n");
			return;
		}
	}

	printf("Here is record %d:\n\n|  ProductId : %d  |  Name : %s  |  Category : %s  |  Quantity : %d  |  Price : %.2f  |\n\n", saveRec.productId, saveRec.productId, saveRec.name, saveRec.category, saveRec.quantity, saveRec.price);

	if (fclose(rndAccessFile) != 0)
	{
		printf("There was an error while closing the file.\n\n");
		return;
	}
}

void rndAccessUpdtRec(char fileName[STRING_LEN], int id, int choice, char input[STRING_LEN])
{
	RndAccessRecord saveRec = { 0, "", "", 0, 0 };

	FILE* rndAccessFile = fopen(fileName, "rb+");
	if (rndAccessFile == NULL)
	{
		printf("There was an error in opening the file.\n\n");
		return;
	}

	if ((fseek(rndAccessFile, (calculateOffset(fileName, id)), SEEK_SET)) != 0)
	{
		printf("The fseek() function failed.\n\n");
		return;
	}

	if ((fread(&saveRec, sizeof(RndAccessRecord), 1, rndAccessFile)) == 0)
	{
		if (ferror(rndAccessFile) != 0)
		{
			printf("Error occurred in fread().\n\n");
			return;
		}

		if (feof(rndAccessFile) != 0)
		{
			printf("End of file.\n\n");
			return;
		}
	}

	if ((fseek(rndAccessFile, (calculateOffset(fileName, id)), SEEK_SET)) != 0)
	{
		printf("The fseek() function failed.\n\n");
		return;
	}

	switch (choice)
	{
	case 1:
		strncpy(saveRec.name, input, STRING_LEN);
		break;

	case 2:
		strncpy(saveRec.category, input, STRING_LEN);
		break;

	case 3:
		saveRec.quantity = atoi(input);
		break;

	case 4:
		saveRec.price = atof(input);
		break;
	}

	if (fwrite(&saveRec, sizeof(RndAccessRecord), 1, rndAccessFile) < 1)
	{
		printf("There was an error writing to the file.\n\n");
		return;
	}

	if (fclose(rndAccessFile) != 0)
	{
		printf("There was an error while closing the file.\n\n");
		return;
	}

	if ((fread(&saveRec, sizeof(RndAccessRecord), 1, rndAccessFile)) == 0)
	{
		if (ferror(rndAccessFile) != 0)
		{
			printf("Error occurred in fread().\n\n");
			return;
		}

		if (feof(rndAccessFile) != 0)
		{
			printf("End of file.\n\n");
			return;
		}
	}

	printf("Here is your updated record:\n\n");

	rndAccessReadRec(fileName, id);
}

void rndAccessDltRec(char fileName[STRING_LEN], int id)
{
	FILE* saveFile = fopen("../save.bin", "ab");
	if (saveFile == NULL)
	{
		printf("There was an error in opening the file.\n\n");
		return;
	}

	FILE* rndAccessFile = fopen(fileName, "rb+");
	if (rndAccessFile == NULL)
	{
		printf("There was an error in opening the file.\n\n");
		return;
	}

	RndAccessRecord save[50] = { NULL };
	int arraySize = 0;

	while (fread(&save[arraySize], sizeof(RndAccessRecord), 1, rndAccessFile))
	{
		if (ferror(rndAccessFile) != 0)
		{
			printf("Error occurred in fread().\n\n");
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
				printf("The fseek() function failed.\n\n");
				return;
			}

			if ((fseek(saveFile, ftell(rndAccessFile), SEEK_CUR)) != 0)
			{
				printf("The fseek() function failed.\n\n");
				return;
			}

			if (fwrite(&save[index], sizeof(RndAccessRecord), 1, saveFile) < 1)
			{
				printf("There was an error while closing the file.\n\n");
				return;
			}
			index++;
		}
		else if ((index + 1) <= (arraySize - 1))
		{
			if ((fseek(rndAccessFile, (calculateOffset(fileName, (save[index].productId))), SEEK_CUR)) != 0)
			{
				printf("The fseek() function failed.\n\n");
				return;
			}

			if ((fseek(saveFile, ftell(rndAccessFile), SEEK_CUR)) != 0)
			{
				printf("The fseek() function failed.\n\n");
				return;
			}

			if (fwrite(&save[index + 1], sizeof(RndAccessRecord), 1, saveFile) < 1)
			{
				printf("There was an error while closing the file.\n\n");
				return;
			}
			index += 2;
		}
		else if ((index + 1) > (arraySize - 1))
		{
			break;
		}
	}

	if (fclose(rndAccessFile) != 0)
	{
		printf("There was an error while closing a file.\n\n");
		return;
	}

	if (fclose(saveFile) != 0)
	{
		printf("There was an error while closing a file.\n\n");
		return;
	}

	if (remove("../inventory.bin") != 0)
	{
		printf("Unable to delete file.\n\n");
		return;
	}

	if (rename("../save.bin", fileName) != 0)
	{
		printf("Unable to rename file.\n\n");
		return;
	}

	printf("Record %d has been deleted.\n\n", id);
}

long calculateOffset(char fileName[STRING_LEN], int id)
{
	int index = checkRecExists(fileName, id);
	if (index == -1)
	{
		return index;
	}

	long offset = (sizeof(RndAccessRecord)) * (index);

	return offset;
}

void displayAllRecs(char fileName[STRING_LEN])
{
	FILE* rndAccessFile = fopen(fileName, "rb");
	if (rndAccessFile == NULL)
	{
		printf("There was an error in opening the file.\n\n");
		return;
	}

	RndAccessRecord a = { 0, "", "", 0, 0 };

	printf("Here are all the records in the file currently:\n\n");

	while (fread(&a, sizeof(RndAccessRecord), 1, rndAccessFile))
	{
		if (ferror(rndAccessFile) != 0)
		{
			printf("Error occurred in fread().\n");
			return;
		}

		printf("|  ProductId : %d  |  Name : %s  |  Category : %s  |  Quantity : %d  |  Price : %.2f  |\n\n", a.productId, a.name, a.category, a.quantity, a.price);
	}

	if (feof(rndAccessFile) != 0)
	{
		printf("\nEnd of file reached. All records have been printed.\n\n");
	}

	if (fclose(rndAccessFile) != 0)
	{
		printf("There was an error while closing the file.\n\n");
	}
}

int checkRecExists(char fileName[STRING_LEN], int id)
{
	RndAccessRecord a[50] = { NULL };
	int arraySize = 0;
	int index = 0;

	FILE* rndAccessFile = fopen(fileName, "rb");
	if (rndAccessFile == NULL)
	{
		printf("The file is empty or has not been created yet.\n\n");
		return -1;
	}

	while (fread(&a[arraySize], sizeof(RndAccessRecord), 1, rndAccessFile))
	{
		if (ferror(rndAccessFile) != 0)
		{
			printf("Error occurred in fread().\n\n");
			return;
		}

		arraySize++;
	}

	if (fclose(rndAccessFile) != 0)
	{
		printf("There was an error while closing the file.\n\n");
		return -1;
	}

	while (index <= (arraySize - 1))
	{
		if (a[index].productId == id)
		{
			return index;
		}

		index++;
	}

	return -1;
}

char* getUserInput(char input[STRING_LEN])
{
	if (fgets(input, STRING_LEN, stdin) == NULL)
	{
		printf("There was an error with the fgets() function.\n\n");
		return NULL;
	}

	if (input[strlen(input) - 1] == '\n')
	{
		input[strlen(input) - 1] = '\0';
	}

	return input;
}