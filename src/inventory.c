#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000

// Structure Definition
struct Product {
    int id;
    char name[50];
    char category[30];
    int quantity;
    float price;
    int active;   // 1 = available, 0 = deleted
};

// Global Variables
struct Product inventory[SIZE];
int indexCount = 0; // Tracks current number of records
int id_counter = 1; // Auto-increment ID

// Helper function to clear input buffer (replaces flushall/fflush)
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Function Prototypes
void printProduct(struct Product p);
void addProduct();
void displayProducts();
void searchProductById();
void sortProductsByPrice();
void updateProductById();
void deleteProductById();
int login();

int main() {
    int choice;
    
    // 1. Perform Login First
    if (!login()) {
        printf("\nMaximum login attempts reached. Terminating program.\n");
        return 1; // Exit with error code
    }

    // 2. Main Menu Loop
    do {
        printf("\n\n===== PRODUCT INVENTORY MANAGEMENT =====");
        printf("\n1. Add Product");
        printf("\n2. Display All Products");
        printf("\n3. Search Product by ID");
        printf("\n4. Sort Products by Price");
        printf("\n5. Update Product By ID");
        printf("\n6. Delete Product By ID");
        printf("\n0. Exit");
        printf("\n========================================");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addProduct(); break;
            case 2: displayProducts(); break;
            case 3: searchProductById(); break;
            case 4: sortProductsByPrice(); break;
            case 5: updateProductById(); break;
            case 6: deleteProductById(); break;
            case 0: 
                printf("\nExiting Program. Goodbye!\n");
                exit(0);
                break;
            default: printf("\nInvalid Choice! Please try again.");
        }
    } while (choice != 0);

    return 0;
}

// --- Login Functionality ---
int login() {
    char username[20];
    char password[20];
    int attempts = 0;

    system("cls"); // Clear screen for login (Windows)
    printf("\n=== SYSTEM LOGIN ===\n");

    while (attempts < 3) {
        printf("Attempt %d/3\n", attempts + 1);
        printf("Username: ");
        scanf("%s", username);
        printf("Password: ");
        scanf("%s", password);

        if (strcmp(username, "admin") == 0 && strcmp(password, "1234") == 0) {
            printf("\nLogin Successful! Welcome, Admin.\n");
            return 1; // Success
        } else {
            printf("Invalid Credentials. Please try again.\n\n");
            attempts++;
        }
    }
    
    printf("\nAccess Denied.\n");
    return 0; // Failed after 3 attempts
}

// --- CRUD Operations ---

void addProduct() {
    struct Product p;
    
    if (indexCount == SIZE) {
        printf("\nInventory is Full!");
        return;
    }

    p.id = id_counter; // Auto-assign ID

    clearInputBuffer(); // Clear buffer to handle string input safely

    printf("\nEnter Product Name: ");
    fgets(p.name, sizeof(p.name), stdin);
    p.name[strcspn(p.name, "\n")] = 0; // Remove newline char

    printf("Enter Category: ");
    fgets(p.category, sizeof(p.category), stdin);
    p.category[strcspn(p.category, "\n")] = 0;

    printf("Enter Quantity: ");
    scanf("%d", &p.quantity);

    printf("Enter Price: ");
    scanf("%f", &p.price);

    p.active = 1; // Mark as available

    inventory[indexCount] = p;
    indexCount++;
    id_counter++;

    printf("\nProduct Added Successfully! ID is: %d\n", p.id);
}

void displayProducts() {
    int i, found = 0;
    
    if (indexCount == 0) {
        printf("\nNo products found in inventory.\n");
        return;
    }

    printf("\n%-5s %-20s %-15s %-10s %-10s", "ID", "Name", "Category", "Qty", "Price");
    printf("\n---------------------------------------------------------------");

    for (i = 0; i < indexCount; i++) {
        if (inventory[i].active == 1) {
            printProduct(inventory[i]);
            found = 1;
        }
    }
    
    if (!found) {
        printf("\nNo active products to display.\n");
    }
    printf("\n---------------------------------------------------------------\n");
}

void searchProductById() {
    int id, i, found = 0;
    printf("\nEnter Product ID to Search: ");
    scanf("%d", &id);

    printf("\n%-5s %-20s %-15s %-10s %-10s", "ID", "Name", "Category", "Qty", "Price");
    printf("\n---------------------------------------------------------------");

    for (i = 0; i < indexCount; i++) {
        if (inventory[i].id == id && inventory[i].active == 1) {
            printProduct(inventory[i]);
            found = 1;
            break;
        }
    }
    printf("\n---------------------------------------------------------------\n");

    if (!found) {
        printf("\nProduct with ID %d not found.\n", id);
    }
}

void updateProductById() {
    int id, i, found = 0;
    printf("\nEnter Product ID to Update: ");
    scanf("%d", &id);

    for (i = 0; i < indexCount; i++) {
        if (inventory[i].id == id && inventory[i].active == 1) {
            printf("\nProduct Found: %s", inventory[i].name);
            printf("\n--- Enter New Details ---");
            
            clearInputBuffer();

            printf("\nEnter New Name: ");
            fgets(inventory[i].name, sizeof(inventory[i].name), stdin);
            inventory[i].name[strcspn(inventory[i].name, "\n")] = 0;

            printf("Enter New Category: ");
            fgets(inventory[i].category, sizeof(inventory[i].category), stdin);
            inventory[i].category[strcspn(inventory[i].category, "\n")] = 0;

            printf("Enter New Quantity: ");
            scanf("%d", &inventory[i].quantity);

            printf("Enter New Price: ");
            scanf("%f", &inventory[i].price);

            printf("\nProduct ID %d Updated Successfully.\n", id);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nProduct with ID %d not found.\n", id);
    }
}

void deleteProductById() {
    int id, i, found = 0;
    printf("\nEnter Product ID to Delete: ");
    scanf("%d", &id);

    for (i = 0; i < indexCount; i++) {
        if (inventory[i].id == id && inventory[i].active == 1) {
            inventory[i].active = 0; // Logical Delete
            printf("\nProduct ID %d has been deleted.\n", id);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nProduct with ID %d not found or already deleted.\n", id);
    }
}

void sortProductsByPrice() {
    struct Product temp;
    int i, j;

    if (indexCount == 0) {
        printf("\nInventory is empty.\n");
        return;
    }

    // Bubble Sort logic
    for (i = 0; i < indexCount; i++) {
        for (j = i + 1; j < indexCount; j++) {
            // Check if both are active before sorting, though typically we sort the whole array
            // Sorting based on Price Ascending
            if (inventory[i].price > inventory[j].price) {
                temp = inventory[i];
                inventory[i] = inventory[j];
                inventory[j] = temp;
            }
        }
    }
    printf("\nProducts sorted by Price (Ascending) successfully.\n");
    displayProducts();
}

void printProduct(struct Product p) {
    printf("\n%-5d %-20s %-15s %-10d %-10.2f", p.id, p.name, p.category, p.quantity, p.price);
}