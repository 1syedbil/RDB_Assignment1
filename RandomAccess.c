/*
* FILE          : RandomAccess.c
* PROJECT       : Relational Databases Assignment 1
* PROGRAMMERS   : Bilal Syed, Morgan Tabor, Quang Minh Vu
* FIRST VERSION : 2024-09-13
* DESCRIPTION   : This file contains all of the function definitions for the random access
*                 CRUD operations. It also contains the definitions for the getUserInput(),
*                 validateString(), validateInt(), validateDouble(), calculateOffset(),
*                 and checkRecExists() functions. All of the code in this file was written
*                 by Bilal Syed.
*/

#include "InventoryMgmtSys.h"


/*
* FUNCTION    : rndAccessCreateRecord()
* PROGRAMMERS : Bilal Syed
* DESCRIPTION : This function is used to create a brand new record and append it to the end of
*               the file. The function starts by getting the user to input the values they want
*               for each of the attributes of the new record. It starts with ID and checks if the
*               user's input for the new record's ID doesn't already exist in another record that's
*               already in the file. If a record with the ID already exists then the function returns 
*               to main. Otherwise, the function continues to get the user's input for the rest of 
*               the attributes. Once all of the values have been retreived from the user, the binary
*               file is opened for appending and the new record is written into the file. After this
*               the file is closed and the function ends.
* PARAMETERS  :
*   char fileName[STRING_LEN] - String to hold the file name. 
* RETURNS     :
*   void
*/
void rndAccessCreateRecord(char fileName[STRING_LEN])
{
    char userInput[STRING_LEN] = "";
    RndAccessRecord rec = { 0, "", "", 0, 0 };

    printf("Enter a ProductId for the new product: ");
    strcpy(userInput, getUserInput(userInput));
    if (!validateInt(userInput))
    {
        printf("Error: invalid input. Must be a non-zero and positive integer.\n\n");
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
        printf("Error: invalid input. Must be a non-zero and positive integer.\n\n");
        return;
    }
    rec.quantity = atoi(userInput);

    printf("Enter a Price for the new product: ");
    strcpy(userInput, getUserInput(userInput));
    if (!validateDouble(userInput))
    {
        printf("Error: invalid input. Must be a positive and non-zero number.\n\n");
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

/*
* FUNCTION    : rndAccessReadRec()
* PROGRAMMERS : Bilal Syed
* DESCRIPTION : This function is used to display the contents of a specific record in the file in order for it 
*               to be read by the user. First the function gets the user input for the ID of the record they
*               would like to read. After this the binary file is opened for reading and the ID is used to seek
*               to the position of the record to be read, within the file. Then, the contents of that record are
*               read into a RndAccessRecord save variable. From here, the save record is printed out onto the
*               console using printf and then the file is closed.
* PARAMETERS  :
*   char fileName[STRING_LEN] - String to hold the file name.
* RETURNS     :
*   void
*/
void rndAccessReadRec(char fileName[STRING_LEN])
{
    char userInput[STRING_LEN] = "";
    int id = 0;
    RndAccessRecord saveRec = { 0, "", "", 0, 0 };

    printf("Enter the ID of the record you would like to read: ");
    strcpy(userInput, getUserInput(userInput));
    if (!validateInt(userInput))
    {
        printf("Error: invalid input. Must be a non-zero and positive integer.\n\n");
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

/*
* FUNCTION    : rndAccessUpdtRec()
* PROGRAMMERS : Bilal Syed
* DESCRIPTION : This function is used to update a specific attribute of a specific record. It
*               first gets the ID of the record to be updated from the user. Then, it opens the 
*               binary file for reading and writing. After this, it seeks to the position of the 
*               record to be updated within the file and reads that record into a RndAccessRecord 
*               save variable. Once the record is saved, the file pointer seeks back to the beginning 
*               of the record to be updated within the file. From here the function enters a loop 
*               that first gets the user's decision for which member of the record they would like to
*               update, and then enters a switch-case statement based on their choice. The function
*               then gets the user's input for the new value that they want to give to the record's 
*               specific member and then the loop is broken out of. Finally, the updated save record
*               will overwrite the original record in the file.
* PARAMETERS  :
*   char fileName[STRING_LEN] - String to hold the file name.
* RETURNS     :
*   void
*/
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
        printf("Error: invalid input. Must be a non-zero and positive integer.\n\n");
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
            printf("Error: invalid input. Must be a non-zero and positive integer.\n\n");
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
                if (fclose(rndAccessFile) != 0)
                {
                    printf("There was an error while closing the file.\n\n");
                    return;
                }
                return;
            }
            break;

        case 2:
            printf("Enter a Category for the new product: ");
            strncpy(saveRec.category, getUserInput(saveRec.category), STRING_LEN - 1);
            if (!validateString(saveRec.category))
            {
                if (fclose(rndAccessFile) != 0)
                {
                    printf("There was an error while closing the file.\n\n");
                    return;
                }
                return;
            }
            break;

        case 3:
            printf("Enter a Quantity for the new product: ");
            strcpy(userInput, getUserInput(userInput));
            if (!validateInt(userInput))
            {
                printf("Error: invalid input. Must be a non-zero and positive integer.\n\n");
                if (fclose(rndAccessFile) != 0)
                {
                    printf("There was an error while closing the file.\n\n");
                    return;
                }
                return;
            }
            saveRec.quantity = atoi(userInput);
            break;

        case 4:
            printf("Enter a Price for the new product: ");
            strcpy(userInput, getUserInput(userInput));
            if (!validateDouble(userInput))
            {
                printf("Error: invalid input. Must be a positive and non-zero number.\n\n"); 
                if (fclose(rndAccessFile) != 0)
                {
                    printf("There was an error while closing the file.\n\n");
                    return;
                }
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

/*
* FUNCTION    : rndAccessDltRecord()
* PROGRAMMERS : Bilal Syed
* DESCRIPTION : This function deletes a specific record from the file by using its productId. First
*               the function gets input from the user for what record they would like to delete by 
*               asking them for the record's corresponding ID. Validate the user input for ID and then
*               open a brand new binary file for appending. This new binary file will hold the contents
*               of the current file minus the record being deleted. After this, the function opens the 
*               current file and reads its entire contents into an array of RndAccessRecord. Inside of 
*               the loop reading through the entire contents of the current file, an int variable to hold
*               the number of indices (aka the total number of records in the file) is incremented. From
*               here the function enters a loop that keeps looping as long as the current index of the 
*               array holding the file contents is not greater than the last index of the array. The loop 
*               first checks to see if the current index of the array doesn't hold the record being deleted.
*               If it doesn't hold the record, then fseek() is used to move the file pointer to the file 
*               position of the record in the current file. Then the file pointer of the save file is moved
*               to that same position and then the record is written into the save file. After that the current
*               index is incremented. Next, if the current index does contain the record being deleted and if 
*               it is not the last record, then the record that comes after the record to be deleted is written
*               into the save file and the current index is increased by 2. This skips the record being deleted 
*               so it is not saved in the save file. Next, if the current index contains the record being deleted
*               and that record also happens to be the last record, then nothing is written into the save file 
*               and the loop gets broken out of. Finally, now that the contents of the file (not including the
*               deleted record) have been saved to the save file, the original file can be deleted and the save
*               file can be renamed to have the same name as the original file. This way the record has been 
*               deleted.
* PARAMETERS  :
*   char fileName[STRING_LEN] - String to hold the fileName.
* RETURNS     :
*   void
*/
void rndAccessDltRecord(char fileName[STRING_LEN])
{
    char userInput[STRING_LEN] = "";
    int id = 0;
    RndAccessRecord save[ARRAY_SIZE] = { NULL }; 
    int numIndices = 0; 
    int index = 0;

    printf("Enter the ID of the record you would like to delete: ");
    strcpy(userInput, getUserInput(userInput));
    if (!validateInt(userInput))
    {
        printf("Error: invalid input. Must be a non-zero and positive integer.\n\n"); 
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

    while (fread(&save[numIndices], sizeof(RndAccessRecord), 1, rndAccessFile))
    {
        if (ferror(rndAccessFile) != 0)
        {
            printf("Error occurred in fread().\n\n");
            return;
        }

        numIndices++; 
    }

    while (index <= (numIndices - 1))
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
        else if ((index + 1) <= (numIndices - 1))
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
        else if ((index + 1) > (numIndices - 1)) 
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

/*
* FUNCTION    : getUserInput()
* PROGRAMMERS : Bilal Syed
* DESCRIPTION : This function gets the user input from their keyboard by calling fgets()
*               and storing the value in the input parameter. After storing the user input
*               in the input parameter, an if-statement is used to remove the newline character
*               that fgets() appends to the end when storing input in a variable.
* PARAMETERS  :
*   char input[STRING_LEN] - String to hold the user input.
* RETURNS     :
*   char* - Returns the user input after the newline is removed.
*/
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

/*
* FUNCTION    : calculateOffset()
* PROGRAMMERS : Bilal Syed
* DESCRIPTION : This function calculates the offset position of a specific record in the file 
*               from the beginning of the file. It first checks to see if the record corresponding
*               with the id parameter even exists, and holds the return value of the checkRecExists()
*               function in an int variable. If the record does exist, then calculate the offset by
*               multiplying the sizeof(RndAccessRecord) by the index of the record which was returned and
*               saved in a local variable by the checkRecExists() function. 
* PARAMETERS  :
*   char fileName[STRING_LEN] - String to hold the filename.
*   int id                    - The id of the record whose offset is being calculated.
* RETURNS     :
*   long - Returns the calculated offset as a long value because that is the datatype
*          used for the fseek() offset parameter. Returns -1 if the record doesn't exist
*          (this won't ever happen because all functions that call this function already
*          check to see if the record exists beforehand).
*/
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

/*
* FUNCTION    : checkRecExists()
* PROGRAMMERS : Bilal Syed
* DESCRIPTION : This function is used to check if a record corresponding with the ID that a user
*               inputs actually exists in a file. It does this by first opening a binary file 
*               (named after the fileName) for appending and reading. This way, if there is already
*               a file in the current directory corresponding with the fileName parameter, the file
*               will be opened for reading. If the file doesn't exist, then it will simply be created
*               in the current directory. After it has been opened, read the entire contents of the 
*               file into an array of RndAccessRecord and then close the file. Now the function will be
*               able to search through the array in a loop to see if the productId member of any of the
*               indices matches the id parameter. The loop also increments a variable to keep track of
*               the number of indices. If a record corresponding with the id parameter passed into the 
*               function does exist (i.e. the productId member of the current index matches the id param), 
                return the variable holding the number of indices. If it does not exist, return -1. 
* PARAMETERS  :
*   char fileName[STRING_LEN] - String to hold the filename.
*   int id                    - The id of the record being checked to see if it exists in the file or not.
* RETURNS     :
*   int - Returns the number of indices in the struct array (which is equivalent to the number of
*         records in the file) if record does exist. If the record doesn't exist, return -1.
*/
int checkRecExists(char fileName[STRING_LEN], int id)
{
    RndAccessRecord fileContents[ARRAY_SIZE] = { NULL };
    int arraySize = 0;
    int index = 0;

    FILE* rndAccessFile = fopen(fileName, "ab+");
    if (rndAccessFile == NULL)
    {
        printf("fopen() failed.\n\n");
        return -1;
    }

    while (fread(&fileContents[arraySize], sizeof(RndAccessRecord), 1, rndAccessFile))
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
        return -1;
    }

    while (index <= (arraySize - 1))
    {
        if (fileContents[index].productId == id) 
        {
            return index;
        }
        index++;
    }

    return -1;
}

/*
* FUNCTION    : validateString()
* PROGRAMMERS : Bilal Syed
* DESCRIPTION : This function validates the user input for the name and category attributes of a
*               product entry in the file. It first checks to see if the input is impty, then it 
*               checks to see if the input exceeds the character limit, and lastly it checks to see
*               if the user input is a number. 
* PARAMETERS  :
*   char input[STRING_LEN] - Holds the user input string.
* RETURNS     :
*   bool - Returns true if all validations are passed. Returns false
*          if any validations are failed.
*/
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

    if (validateInt(input) || validateDouble(input))
    {
        printf("Error: input cannot contain numeric values.\n\n");
        return false;  
    }

    return true;
}

/*
* FUNCTION    : validateInt()
* PROGRAMMERS : Bilal Syed
* DESCRIPTION : This function validates the user input for the quantity and productId attributes
*               of a product entry in the file. It also validates the user input for a menu option
*               selection. It first checks to see if the input is empty, then it checks to see if 
*               the input exceeds the character limit. After this checks to see if atoi() and atof()
*               don't return the same value (means the input isn't an actual whole number), or if 
*               atof() returns less than/equal to zero (means the input wasn't an actual number or
*               is negative).
* PARAMETERS  :
*   char input[STRING_LEN] - Holds the user input string.
* RETURNS     :
*   bool - Returns true if all validations are passed. Returns false
*          if any validations are failed.
*/
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
        return false;
    }

    return true;
}

/*
* FUNCTION    : validateDouble()
* PROGRAMMERS : Bilal Syed
* DESCRIPTION : This function validates the user input for the price attribute of 
*               a product entry in the file. It first checks to see if the input is 
*               empty, then it checks to see if the input exceeds the character limit,
*               and lastly it checks to see if atof() returns a value less than/equal to
*               zero (means that the user input isn't an actual number or is negative). 
* PARAMETERS  :
*   char input[STRING_LEN] - Holds the user input string. 
* RETURNS     :
*   bool - Returns true if all validations are passed. Returns false if any
*          validations are failed.
*/
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
        return false;
    }

    return true;
}