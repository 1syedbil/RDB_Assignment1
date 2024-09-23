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
#define MAX_PRODUCTS 120

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

bool validateString(char input[STRING_LEN]);
bool validateInt(char input[STRING_LEN]);
bool validateDouble(char input[STRING_LEN]);
char* getUserInput(char input[STRING_LEN]); 

//THIS FILE IS WHERE ALL OF THE FUNCTION PROTOTYPES WILL GO 

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
/*
- function to create an entry

- function to read out entries

- functiom to update an entry

- function to delete entries

- any other functions necessary...
*/


#endif


