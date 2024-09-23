#pragma once


#ifndef INVENTORY_MGMT_SYS_H
#define INVENTORY_MGMT_SYS_H 

#pragma warning(disable : 4996)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//THIS FILE IS WHERE ALL OF THE FUNCTION PROTOTYPES WILL GO 

//Random Access
/*
- function to create an entry

- function to read out entries

- functiom to update an entry

- function to delete entries

- any other functions necessary...
*/

//Sequential Access
/*
- function to create an entry

- function to read out entries

- functiom to update an entry

- function to delete entries

- any other functions necessary...
*/

//Delimited File
FILE* CSVFileStarter();
void CSVWriteToFile(FILE* delimFile);
void CSVReadFile(FILE* delimFile);
char* CSVInputValidation();
void CSVFileDeleteLine(FILE* delimFile);
void CSVFileUpdate(FILE* delimFile);
void CSVFileSeek(FILE* opened, char* ID);

#endif


