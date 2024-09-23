#include "InventoryMgmtSys.h"


//THIS IS WHERE THE DEFINITIONS FOR ALL OF THE FUNCTIONS RELATED TO RANDOM ACCESS WILL GO

void rndAccessCreateRecord(char fileName[STRING_LEN])
{
    char userInput[STRING_LEN] = "";
    RndAccessRecord rec = { 0, "", "", 0, 0 };

    printf("Enter a ProductId for the new product: ");
    strcpy(userInput, getUserInput(userInput));
    if (!validateInt(userInput))
    {
        return;
    }
    rec.productId = atoi(userInput);
    if (checkRecExists(fileName, rec.productId) != -1)
    {
        printf("A product with this ID already exists. No duplicate IDs allowed.\n\n");
        return;
    }

    printf("Enter a Name for the new product: ");
    strcpy(rec.name, getUserInput(rec.name));
    if (!validateString(rec.name))
    {
        return;
    }

    printf("Enter a Category for the new product: ");
    strcpy(rec.category, getUserInput(rec.category));
    if (!validateString(rec.category))
    {
        return;
    }

    printf("Enter a Quantity for the new product: ");
    strcpy(userInput, getUserInput(userInput));
    if (!validateInt(userInput))
    {
        return;
    }
    rec.quantity = atoi(userInput);

    printf("Enter a Price for the new product: ");
    strcpy(userInput, getUserInput(userInput));
    if (!validateDouble(userInput))
    {
        return;
    }
    rec.price = atof(userInput);

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

    printf("New record (ID: %d) added to file.\n\n", rec.productId);
}

void rndAccessReadRec(char fileName[STRING_LEN])
{
    char userInput[STRING_LEN] = "";
    int id = 0;
    RndAccessRecord saveRec = { 0, "", "", 0, 0 };

    printf("Enter the ID of the record you would like to read: ");
    strcpy(userInput, getUserInput(userInput));
    if (!validateInt(userInput))
    {
        return;
    }
    id = atoi(userInput);
    if (checkRecExists(fileName, id) == -1)
    {
        printf("No such product corresponding with this ID exists.\n\n");
        return;
    }

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

    printf("\n\n");
    printf("| %-10s | %-20s | %-20s | %-10s | %-10s |\n", "ProductId", "Name", "Category", "Quantity", "Price");
    printf("--------------------------------------------------------------------------------------\n");
    printf("| %-10d | %-20s | %-20s | %-10d | %-10.2f |\n", saveRec.productId, saveRec.name, saveRec.category, saveRec.quantity, saveRec.price);
    printf("\n\n");

    if (fclose(rndAccessFile) != 0)
    {
        printf("There was an error while closing the file.\n\n");
        return;
    }
}

void rndAccessUpdtRec(char fileName[STRING_LEN])
{
    char userInput[STRING_LEN] = "";
    int choice = 0;
    int id = 0;
    RndAccessRecord saveRec = { 0, "", "", 0, 0 };

    printf("Enter the ID of the record you would like to update: ");
    strcpy(userInput, getUserInput(userInput));
    if (!validateInt(userInput))
    {
        return;
    }
    id = atoi(userInput);
    if (checkRecExists(fileName, id) == -1)
    {
        printf("No such product corresponding with this ID exists.\n\n");
        return;
    }

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

    do
    {
        printf("Update Menu:\n\n     1. Update Name     2. Update Category     3. Update Quantity     4. Update Price\n\n");
        printf("Enter a number corresponding with your menu selection: ");
        strcpy(userInput, getUserInput(userInput));
        if (!validateInt(userInput))
        {
            continue;
        }
        printf("\n\n");
        choice = atoi(userInput);

        switch (choice)
        {
        case 1:
            printf("Enter a Name for the product: ");
            strncpy(saveRec.name, getUserInput(saveRec.name), STRING_LEN - 1);
            if (!validateString(saveRec.name))
            {
                return;
            }
            break;

        case 2:
            printf("Enter a Category for the new product: ");
            strncpy(saveRec.category, getUserInput(saveRec.category), STRING_LEN - 1);
            if (!validateString(saveRec.category))
            {
                return;
            }
            break;

        case 3:
            printf("Enter a Quantity for the new product: ");
            strcpy(userInput, getUserInput(userInput));
            if (!validateInt(userInput))
            {
                return;
            }
            saveRec.quantity = atoi(userInput);
            break;

        case 4:
            printf("Enter a Price for the new product: ");
            strcpy(userInput, getUserInput(userInput));
            if (!validateDouble(userInput))
            {
                return;
            }
            saveRec.price = atof(userInput);
            break;

        default:
            printf("Error: invalid menu selection.\n\n");
            break;
        }
    } while (choice <= 0 || choice > 4);

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

    printf("Record %d has been updated.\n\n", id);
}

void rndAccessDltRecord(char fileName[STRING_LEN])
{
    char userInput[STRING_LEN] = "";
    int id = 0;

    printf("Enter the ID of the record you would like to delete: ");
    strcpy(userInput, getUserInput(userInput));
    if (!validateInt(userInput))
    {
        return;
    }
    id = atoi(userInput);
    if (checkRecExists(fileName, id) == -1)
    {
        printf("No such product corresponding with this ID exists.\n\n");
        return;
    }

    FILE* saveFile = fopen("save.bin", "ab");
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

    if (remove(fileName) != 0)
    {
        printf("Unable to delete file.\n\n");
        return;
    }

    if (rename("save.bin", fileName) != 0)
    {
        printf("Unable to rename file.\n\n");
        return;
    }

    printf("Record %d has been deleted.\n\n", id);
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

int checkRecExists(char fileName[STRING_LEN], int id)
{
    RndAccessRecord a[50] = { NULL };
    int arraySize = 0;
    int index = 0;

    FILE* rndAccessFile = fopen(fileName, "ab+");
    if (rndAccessFile == NULL)
    {
        printf("fopen() failed.\n\n");
        return -1;
    }

    while (fread(&a[arraySize], sizeof(RndAccessRecord), 1, rndAccessFile))
    {
        if (ferror(rndAccessFile) != 0)
        {
            printf("Error occurred in fread().\n\n");
            return -1;
        }
        arraySize++;
    }

    if (fclose(rndAccessFile) != 0)
    {
        printf("fclose() failed.\n\n");
        return -2;
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

bool validateString(char input[STRING_LEN])
{
    if (strlen(input) == 0)
    {
        printf("Error: invalid input. Cannot be empty.\n\n");
        return false;
    }

    if (strlen(input) >= (STRING_LEN - 1))
    {
        printf("Error: input is too many characters long.\n\n");
        return false;
    }

    return true;
}

bool validateInt(char input[STRING_LEN])
{
    if (strlen(input) == 0)
    {
        printf("Error: invalid input. Cannot be empty.\n\n");
        return false;
    }

    if (strlen(input) >= (STRING_LEN - 1))
    {
        printf("Error: input is too many characters long.\n\n");
        return false;
    }

    if (atoi(input) != atof(input) || atof(input) <= 0)
    {
        printf("Error: invalid input. Must be a non-zero and positive integer.\n\n");
        return false;
    }

    return true;
}

bool validateDouble(char input[STRING_LEN])
{
    if (strlen(input) == 0)
    {
        printf("Error: invalid input. Cannot be empty.\n\n");
        return false;
    }

    if (strlen(input) >= (STRING_LEN - 1))
    {
        printf("Error: input is too many characters long.\n\n");
        return false;
    }

    if (atof(input) <= 0)
    {
        printf("Error: invalid input. Must be a positive and non-zero number.\n\n");
        return false;
    }

    return true;
}