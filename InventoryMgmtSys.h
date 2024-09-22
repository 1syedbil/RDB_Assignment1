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
typedef struct {
    int productId;
    char name[STRING_LEN];
    char category[STRING_LEN];
    int quantity;
    double price;
} RndAccessRecord;

//for sequential access
struct Product {
	int id;
	char name[STRING_LEN];
	char category[STRING_LEN]; 
	int quantity;
	float price;
}Product;


//THIS FILE IS WHERE ALL OF THE FUNCTION PROTOTYPES WILL GO 

//Random Access

void rndAccessCreateRec(int id, int quant, double price, char name[STRING_LEN], char cat[STRING_LEN], char fileName[STRING_LEN]);

void rndAccessReadRec(char fileName[STRING_LEN], int id);

void rndAccessUpdtRec(char fileName[STRING_LEN], int id, int choice, char input[STRING_LEN]);

void rndAccessDltRec(char fileName[STRING_LEN], int id);

long calculateOffset(char fileName[STRING_LEN], int id);

void displayAllRecs(char fileName[STRING_LEN]);

int checkRecExists(char fileName[STRING_LEN], int id);

char* getUserInput(char input[STRING_LEN]);

int validateQuant(char input[STRING_LEN]);

double validatePrice(char input[STRING_LEN]);

//Sequential Access

int readProducts(struct Product products[]);
void writeProducts(struct Product products[], int times);
void addProduct(struct Product products[], int* times);
void updateProduct(struct Product products[], int times);
void deleteProduct(struct Product products[], int* times);
void displayProducts(struct Product products[], int times);

//Delimited File
/*
- function to create an entry

- function to read out entries

- functiom to update an entry

- function to delete entries

- any other functions necessary...
*/


#endif


