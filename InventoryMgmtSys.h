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

//STRUCT DEFINITIONS
typedef struct
{

	int productId;
	char name[STRING_LEN];
	char category[STRING_LEN];
	int quantity;
	double price;

} RndAccessRecord; 

//THIS FILE IS WHERE ALL OF THE FUNCTION PROTOTYPES WILL GO 

//Random Access
/*
- function to create an entry

- function to read out entries

- function to update an entry

- function to delete entries

- any other functions necessary...
*/

void rndAccessCreateRec(int id, int quant, double price, char name[STRING_LEN], char cat[STRING_LEN], char fileName[STRING_LEN]);

void rndAccessReadRec(char fileName[STRING_LEN], int id); 

void rndAccessUpdtRec(char fileName[STRING_LEN], int id, int newVal); 

int calculateOffset(int id);

//Sequential Access
/*
- function to create an entry

- function to read out entries

- functiom to update an entry

- function to delete entries

- any other functions necessary...
*/

//Delimited File
/*
- function to create an entry

- function to read out entries

- functiom to update an entry

- function to delete entries

- any other functions necessary...
*/


#endif


