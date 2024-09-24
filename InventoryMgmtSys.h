/*
* FILE          : InventoryMgmtSys.h
* PROJECT       : Relational Databases Assignment 1
* PROGRAMMERS   : Bilal Syed, Morgan Tabor, Quang Minh Vu
* FIRST VERSION : 2024-09-13
* DESCRIPTION   : This is a header file which is included in all other source code files
*                 in this project. It contains definitions for all constants, any necessary
*                 includes, struct definitions, and function prototypes.
*/

#pragma once

#ifndef INVENTORY_MGMT_SYS_H 
#define INVENTORY_MGMT_SYS_H 

#pragma warning(disable : 4996)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


//CONSTANT DEFINITIONS
#define STRING_LEN 50
#define ARRAY_SIZE 50

//STRUCT DEFINITIONS

//for random access
typedef struct 
{
    int productId;
    char name[STRING_LEN];
    char category[STRING_LEN];
    int quantity;
    double price;
} RndAccessRecord;

//for sequential access
typedef struct
{
	int id;
	char name[STRING_LEN];
	char category[STRING_LEN];
	int quantity;
	double price;
}Product;


//FUNCTION PROTOTYPES

bool validateString(char input[STRING_LEN]);
bool validateInt(char input[STRING_LEN]);
bool validateDouble(char input[STRING_LEN]);
char* getUserInput(char input[STRING_LEN]); 

//Random Access
void rndAccessCreateRecord(char fileName[STRING_LEN]);
void rndAccessReadRec(char fileName[STRING_LEN]);
void rndAccessUpdtRec(char fileName[STRING_LEN]);
void rndAccessDltRecord(char fileName[STRING_LEN]);
int checkRecExists(char fileName[STRING_LEN], int id);
long calculateOffset(char fileName[STRING_LEN], int id); 

//Sequential Access
void addProduct(char fileName[STRING_LEN]);
void displayProducts(char fileName[STRING_LEN]);
void updateProduct(char fileName[STRING_LEN]);
void deleteProduct(char fileName[STRING_LEN]);

//Delimited File
FILE* CSVFileStarter();
void CSVWriteToFile(FILE* delimFile);
void CSVReadFile(FILE* delimFile);
char* CSVInputValidation(FILE* openFile);
void CSVFileDeleteLine(FILE* delimFile);
void CSVFileUpdate(FILE* delimFile);
void CSVFileSeek(FILE* opened, char* ID);


#endif




