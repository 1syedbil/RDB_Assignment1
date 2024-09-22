#include "InventoryMgmtSys.h"

//
// Function       : ReadProduct
// Description    :Open the file and if we can open the file it will return a error message.It will read all the information in the file with fread function
// Parameter      :
//      Struct Product: products[]: the struct to hold all the data from the file and from the user change
// Return         :
//      int times: the amount of tiimes of reading


int readProducts(struct Product products[]) {
    FILE* sequentialFile = NULL;
    sequentialFile = fopen("sampleData.txt", "r");
    if (!sequentialFile) {
        perror("Error:Unable to open file");
        return 0;
    }

    int times = 0;
    while (fscanf(sequentialFile, "%d,%49[^,],%29[^,],%d,%f\n",
        &products[times].id, products[times].name,
        products[times].category,
        &products[times].quantity,
        &products[times].price) == 5) {
        times++;
    }
    fclose(sequentialFile);
    return times;
}

//
// Function       : WriteProduct
// Description    : Open the file and if we can open the file it will return a error message. And it will write in the file
// Parameter      :
//      Struct Product: products[]: the struct to hold all the data from the file and from the user change
//      int           : times     : the amount of times it will store the information
// Return         :
//      None

void writeProducts(struct Product products[], int times) {
    FILE* sequentialFile = NULL;
    sequentialFile = fopen("sampleData.txt", "w");
    if (!sequentialFile) {
        perror("Error:Unable to open file");
        return;
    }

    for (int i = 0; i < times; i++) {
        fprintf(sequentialFile, "%d%s%s%d%.2f\n",
            products[i].id, products[i].name,
            products[i].category,
            products[i].quantity,
            products[i].price);
    }
    fclose(sequentialFile);
}
//
// Function       : AddProduct
// Description    :First I will checkk the times of product that i have add if it is overflow, it will return is the empty.I will take the id of the product that the user want to update by scanf 
//                 and after that I will use a loop to find where is that struct . If the id is not valid (id is smaller or equal to zero), it will return a message if invalid id please enter a 
//                 positive integer.After validate the id, I will use a loop to find where is that struct.After that, we will validate the name,category,quantity and the price of the product.
//                 Especially with the id I will check that do i have that id before . if the id have already existed, it will return an error message if the user enter no word it will return a error
// Parameter      :
//      Struct Product: products[]: the struct to hold all the data from the file and from the user change
//      int           : times     : the amount of times it will store the information
// Return         :
//      None

void addProduct(struct Product products[], int* times) {
    if (*times >= MAX_PRODUCTS) {
        printf("Error:Inventory full!\n");
        return;
    }

    struct Product newProduct;
    printf("Enter product ID: ");
    while (scanf("%d", &newProduct.id) != 1 || newProduct.id < 0)
    {
        printf("Error:Invalid ID. Please enter a positive integer: ");
        while (getchar() != '\n');
    }


    for (int i = 0; i < *times; i++) {
        if (products[i].id == newProduct.id) {
            printf("Error:Product with ID %d already exists.\n", newProduct.id);
            return;
        }
    }

    printf("Enter product name: ");
    if (scanf(" %[^\n]s", newProduct.name) == EOF)
    {
        printf("Error with scanf().\n\n");
        return;
    }
    while (strlen(newProduct.name) == 0) {
        printf("Error:Name cannot be empty. Please enter product name: ");
        if (scanf(" %[^\n]s", newProduct.name) == EOF)
        {
            printf("Error with scanf().\n\n");
            return;
        }
    }

    printf("Enter product category: ");
    if (scanf(" %[^\n]s", newProduct.category) == EOF)
    {
        printf("Error with scanf().\n\n");
        return;
    }
    while (strlen(newProduct.category) == 0) {
        printf("Error:Category cannot be empty. Please enter product category: ");
        if (scanf(" %[^\n]s", newProduct.category) == EOF)
        {
            printf("Error with scanf().\n\n");
            return;
        }
    }

    printf("Enter product quantity: ");
    while (scanf("%d", &newProduct.quantity) != 1 || newProduct.quantity < 0) {
        printf("Error:Invalid quantity. Please enter a non-negative integer: ");
        while (getchar() != '\n');
    }

    printf("Enter product price: ");
    while (scanf("%f", &newProduct.price) != 1 || newProduct.price < 0.0) {
        printf("Error:Invalid price. Please enter a non-negative number: ");
        while (getchar() != '\n');
    }
    printf("Add product complete\n");

    products[*times] = newProduct;
    (*times)++;
    writeProducts(products, *times);
}

//
// Function       : UpdateProduct
// Description    :This function will take the id of the product that the user want to update by scanf and after that I will use a loop to find where is that struct. If the id is not valid 
//                 (id is smaller or equal to zero), it will return a message if invalid id please enter a positive integer.After validate the id, I will use a loop to find where is that struct.
//                 After that, we will validate the id,name,category,quantity and the price of the product. Especially with the id I will check that do i have that id before . if the id have 
//                 already existed, it will return an error message. if the user enter no word it will return a error
// Parameter      :
//      Struct Product: products[]: the struct to hold all the data from the file and from the user change
//      int           : times     : the amount of times it will store the information
// Return         :
//      None

void updateProduct(struct Product products[], int times) {
    int id = 0;
    printf("Enter product ID to update: ");
    while (scanf("%d", &id) != 1 || id <= 0) {
        printf("Error:Invalid ID. Please enter a positive integer: ");
        while (getchar() != '\n');
    }

    for (int i = 0; i < times; i++) {
        if (products[i].id == id) {
            printf("Enter new name: ");
            if (scanf(" %[^\n]s", products[i].name) == EOF)
            {
                printf("Error with scanf().\n\n");
                return;
            }
            while (strlen(products[i].name) == 0) {
                printf("Error:Name cannot be empty. Please enter new product name: ");
                if (scanf(" %[^\n]s", products[i].name) == EOF)
                {
                    printf("Error with scanf().\n\n");
                    return;
                }
            }

            printf("Enter new category: ");
            if (scanf(" %[^\n]s", products[i].category) == EOF)
            {
                printf("Error with scanf().\n\n");
                return;
            }
            while (strlen(products[i].category) == 0) {
                printf("Error:Category cannot be empty. Please enter new product category: ");
                if (scanf(" %[^\n]s", products[i].category) == EOF)
                {
                    printf("Error with scanf().\n\n");
                    return;
                }
            }

            printf("Enter new quantity: ");
            while (scanf("%d", &products[i].quantity) != 1 || products[i].quantity < 0) {
                printf("Error:Invalid quantity. Please enter a non-negative integer: ");
                while (getchar() != '\n');
            }

            printf("Enter new price: ");
            while (scanf("%f", &products[i].price) != 1 || products[i].price < 0.0) {
                printf("Error:Invalid price. Please enter a non-negative number: ");
                while (getchar() != '\n');
            }

            writeProducts(products, times);
            printf("Update product complete\n");
            return;
        }
    }
    printf("Error:Product not found.\n");
}
//
// Function       : DeleteProduct
// Description    :This function will take the id of the product that the user want to delete by scanf and after that I will use a loop to find where is that struct. After that 
//                  we will make the one more loop to remove the all the product behind to the previous index so that will delete the product that user want. After all we will return o
//                  message of the work has been done or not
// Parameter      :
//      Struct Product: products[]: the struct to hold all the data from the file and from the user change
//      int           : times     : the amount of times it will store the information
// Return         :
//      None

void deleteProduct(struct Product products[], int* times) {
    int id = 0;
    printf("Enter product ID to delete: ");
    if (scanf("%d", &id) == EOF)
    {
        printf("Error with scanf().\n\n");
        return;
    }

    for (int i = 0; i < *times; i++) {
        if (products[i].id == id) {
            for (int j = i; j < *times - 1; j++) {
                products[j] = products[j + 1];
            }
            (*times)--;
            writeProducts(products, *times);
            printf("Delete product complete.\n");
            return;
        }
    }
    printf("Error:Product not found.\n");
}
//
// Function       : DisplaysProducts
// Description    : It will display all the data about the final version before display of the product to a table with full information
//                  
// Parameter      :
//      Struct Product: products[]: the struct to hold all the data from the file and from the user change
//      int           : times     : the amount of times it will store the information
// Return         :
//      None
void displayProducts(struct Product products[], int times) {
    printf("\nProductID | Name         | Category   | Quantity | Price\n");
    printf("---------------------------------------------------------\n");
    for (int i = 0; i < times; i++) {
        printf("%-10d | %-12s | %-10s | %-8d | %.2f\n", products[i].id, products[i].name, products[i].category, products[i].quantity, products[i].price);
    }
}