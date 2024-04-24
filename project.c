#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[100];
    float price;
    int quantity;
} Product;

typedef struct {
    int id;
    int product_id;
    int customer_id;
    int quantity;
} Order;

typedef struct {
    int id;
    char name[100];
    char contact[100];
} Customer;

// Function Declarations
void addProduct();
void viewProducts();
void updateProduct();
void addOrder();
void viewOrders();
void addCustomer();
void viewCustomers();
void deleteProduct();

int main() {
    int choice;
    while(1) {
        printf("\n1. Add Product\n");
        printf("2. View Products\n");
        printf("3. Update Product\n");
        printf("4. Add Order\n");
        printf("5. View Orders\n");
        printf("6. Add Customer\n");
        printf("7. View Customers\n");
        printf("8. Delete Product\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addProduct(); break;
            case 2: viewProducts(); break;
            case 3: updateProduct(); break;
            case 4: addOrder(); break;
            case 5: viewOrders(); break;
            case 6: addCustomer(); break;
            case 7: viewCustomers(); break;
            case 8: deleteProduct(); break;
            case 0: exit(0);
            default: printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

// Define each function, ensuring to handle file I/O

void addProduct() {
    Product p;
    FILE *fp = fopen("products.dat", "ab+");
    if (!fp) {
        printf("Unable to open file!\n");
        return;
    }

    printf("Enter Product ID: ");
    scanf("%d", &p.id);
    printf("Enter Product Name: ");
    scanf(" %[^\n]s", p.name);
    printf("Enter Product Price: ");
    scanf("%f", &p.price);
    printf("Enter Quantity: ");
    scanf("%d", &p.quantity);

    fwrite(&p, sizeof(p), 1, fp);
    fclose(fp);
    printf("Product added successfully!\n");
}

void viewProducts() {
    Product p;
    FILE *fp = fopen("products.dat", "rb");
    if (!fp) {
        printf("Unable to open file!\n");
        return;
    }

    printf("ID\tName\t\tPrice\tQuantity\n");
    while(fread(&p, sizeof(p), 1, fp)) {
        printf("%d\t%s\t\t%.2f\t%d\n", p.id, p.name, p.price, p.quantity);
    }
    fclose(fp);
}

void updateProduct() {
    int id, found = 0;
    Product p;
    FILE *fp = fopen("products.dat", "rb+");
    if (!fp) {
        printf("Unable to open file!\n");
        return;
    }

    printf("Enter Product ID to update: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(p), 1, fp) && !found) {
        if (p.id == id) {
            found = 1;
            printf("Enter new Product Name: ");
            scanf(" %[^\n]s", p.name);
            printf("Enter new Product Price: ");
            scanf("%f", &p.price);
            printf("Enter new Quantity: ");
            scanf("%d", &p.quantity);
            
            fseek(fp, -sizeof(p), SEEK_CUR);
            fwrite(&p, sizeof(p), 1, fp);
            printf("Product updated successfully.\n");
        }
    }

    if (!found) {
        printf("Product not found!\n");
    }

    fclose(fp);
}

void deleteProduct() {
    int id, found = 0;
    Product p;
    FILE *fp, *fpTemp;

    fp = fopen("products.dat", "rb");
    if (!fp) {
        printf("Unable to open file!\n");
        return;
    }

    fpTemp = fopen("temp.dat", "wb");
    if (!fpTemp) {
        printf("Unable to open temporary file!\n");
        fclose(fp);
        return;
    }

    printf("Enter Product ID to delete: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(p), 1, fp)) {
        if (p.id == id) {
            found = 1;  // Product found and will be skipped
        } else {
            fwrite(&p, sizeof(p), 1, fpTemp);  // Write to temp file
        }
    }

    fclose(fp);
    fclose(fpTemp);

    if (found) {
        remove("products.dat");              // Delete the original file
        rename("temp.dat", "products.dat");  // Rename temp file to original file name
        printf("Product deleted successfully.\n");
    } else {
        remove("temp.dat");  // Remove temp file if product not found
        printf("Product not found!\n");
    }
}


void addOrder() {
    Order o;
    FILE *fp = fopen("orders.dat", "ab+");
    if (!fp) {
        printf("Unable to open file!\n");
        return;
    }

    printf("Enter Order ID: ");
    scanf("%d", &o.id);
    printf("Enter Product ID: ");
    scanf("%d", &o.product_id);
    printf("Enter Customer ID: ");
    scanf("%d", &o.customer_id);
    printf("Enter Quantity: ");
    scanf("%d", &o.quantity);

    fwrite(&o, sizeof(o), 1, fp);
    fclose(fp);
    printf("Order added successfully!\n");
}


void viewOrders() {
    Order o;
    FILE *fp = fopen("orders.dat", "rb");
    if (!fp) {
        printf("Unable to open file!\n");
        return;
    }

    printf("Order ID\tProduct ID\tCustomer ID\tQuantity\n");
    while(fread(&o, sizeof(o), 1, fp)) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", o.id, o.product_id, o.customer_id, o.quantity);
    }
    fclose(fp);
}


void addCustomer() {
    Customer c;
    FILE *fp = fopen("customers.dat", "ab+");
    if (!fp) {
        printf("Unable to open file!\n");
        return;
    }

    printf("Enter Customer ID: ");
    scanf("%d", &c.id);
    printf("Enter Customer Name: ");
    scanf(" %[^\n]s", c.name);
    printf("Enter Contact Details: ");
    scanf(" %[^\n]s", c.contact);

    fwrite(&c, sizeof(c), 1, fp);
    fclose(fp);
    printf("Customer added successfully!\n");
}


void viewCustomers() {
    Customer c;
    FILE *fp = fopen("customers.dat", "rb");
    if (!fp) {
        printf("Unable to open file!\n");
        return;
    }

    printf("Customer ID\tName\t\tContact Details\n");
    while(fread(&c, sizeof(c), 1, fp)) {
        printf("%d\t\t%s\t\t%s\n", c.id, c.name, c.contact);
    }
    fclose(fp);
}


