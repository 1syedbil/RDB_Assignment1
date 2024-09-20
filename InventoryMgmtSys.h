#pragma once


#ifndef INVENTORY_MGMT_SYS_H
#define INVENTORY_MGMT_SYS_H 

#define MAX_PRODUCTS 120
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



//STRUCTURE TO HOLD DATA
struct Product {
	int id;
	char name[50];
	char category[20];
	int quantity;
	float price;
}Product;

 //FUNCTION PROTOTYPE
int ReadProducts(struct Product products[]);
void WriteProducts(struct Product products[], int times);
void AddProduct(struct Product products[], int* times);
void UpdateProduct(struct Product products[], int times);
void DeleteProduct(struct Product products[], int* times);
void DisplayProducts(struct Product products[], int times);

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


