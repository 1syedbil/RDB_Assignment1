#include "InventoryMgmtSys.h"



int ReadProducts(struct Product products[]) {
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


void WriteProducts(struct Product products[], int times) {
    FILE* sequentialFile = NULL;
    sequentialFile = fopen("sampleData.txt", "r");
    if (!sequentialFile) {
        perror("Error:Unable to open file");
        return ;
    }

    for (int i = 0; i < times; i++) {
        fprintf(sequentialFile, "%d,%s,%s,%d,%.2f\n",
            products[i].id, products[i].name,
            products[i].category,
            products[i].quantity,
            products[i].price);
    }
    fclose(sequentialFile);
}


void AddProduct(struct Product products[], int* times) {
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
    scanf(" %[^\n]s", newProduct.name);
    while (strlen(newProduct.name) == 0) {
        printf("Error:Name cannot be empty. Please enter product name: ");
        scanf(" %[^\n]s", newProduct.name);
    }

    printf("Enter product category: ");
    scanf(" %[^\n]s", newProduct.category);
    while (strlen(newProduct.category) == 0) {
        printf("Error:Category cannot be empty. Please enter product category: ");
        scanf(" %[^\n]s", newProduct.category);
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

    products[*times] = newProduct;
    (*times)++;
    WriteProducts(products, *times);
}



void UpdateProduct(struct Product products[], int times) {
    int id=0;
    printf("Enter product ID to update: ");
    while (scanf("%d", &id) != 1 || id <= 0) {
        printf("Error:Invalid ID. Please enter a positive integer: ");
        while (getchar() != '\n');
    }

    for (int i = 0; i < times; i++) {
        if (products[i].id == id) {
            printf("Enter new name: ");
            scanf(" %[^\n]s", products[i].name);
            while (strlen(products[i].name) == 0) {
                printf("Error:Name cannot be empty. Please enter new product name: ");
                scanf(" %[^\n]s", products[i].name);
            }

            printf("Enter new category: ");
            scanf(" %[^\n]s", products[i].category);
            while (strlen(products[i].category) == 0) {
                printf("Error:Category cannot be empty. Please enter new product category: ");
                scanf(" %[^\n]s", products[i].category);
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

            WriteProducts(products, times);
            printf("Error:Update product complete\n");
            return;
        }
    }
    printf("Error:Product not found.\n");
}


void DeleteProduct(struct Product products[], int* times) {
    int id = 0;
    printf("Enter product ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < *times; i++) {
        if (products[i].id == id) {
            for (int j = i; j < *times - 1; j++) {
                products[j] = products[j + 1];
            }
            (*times)--;
            WriteProducts(products, *times);
            printf("Product deleted.\n");
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
void DisplayProducts(struct Product products[], int times) {
    printf("\nProductID | Name         | Category   | Quantity | Price\n");
    printf("---------------------------------------------------------\n");
    for (int i = 0; i < times; i++) {
        printf("%-10d | %-12s | %-10s | %-8d | %.2f\n", products[i].id, products[i].name,products[i].category, products[i].quantity,products[i].price);
    }
}


int main() {
    struct Product products[MAX_PRODUCTS];
    int times = ReadProducts(products);

    int choice;
    do {
        printf("\nInventory Management System\n");
        printf("1. Add Product\n");
        printf("2. Update Product\n");
        printf("3. Delete Product\n");
        printf("4. Display Products\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: 
            AddProduct(products, &times);
            break;
        case 2: 
            UpdateProduct(products, times); 
            break;
        case 3: 
            DeleteProduct(products, &times); 
            break;
        case 4: 
            DisplayProducts(products, times); 
            break;
        case 5: 
            printf("Exiting...\n"); 
            break;
        default: 
            printf("Invalid choice!\n"); 
            break;
        }
    } while (choice != 5);

    return 0;
}
