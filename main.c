#include <stdio.h>
#include <string.h>

// Holds information related to a customer
struct Customer {
    char name[50];
    char phoneNumber[20];
    float usage;
    float totalBill;
};

// Command constants for menu options
typedef enum {
    CMD_ADD = 1,
    CMD_VIEW,
    CMD_MODIFY,
    CMD_PAYMENT,
    CMD_SEARCH,
    CMD_DELETE,
    CMD_QUIT
} Command;

// Global list of customer entries
struct Customer customers[100];

// Global variable to keep track of the number of customers
int customerCount = 0;

// Function for registering a new customer
void addRecord()
{
    if (customerCount < 100) {
        // Enter Name
        printf("\nEnter your name: ");
        fgets(customers[customerCount].name, sizeof(customers[customerCount].name), stdin);
        customers[customerCount].name[strcspn(customers[customerCount].name, "\n")] = '\0';

        // Enter Phone Number
        printf("Enter your phone number: ");
        fgets(customers[customerCount].phoneNumber, sizeof(customers[customerCount].phoneNumber), stdin);
        customers[customerCount].phoneNumber[strcspn(customers[customerCount].phoneNumber, "\n")] = '\0';

        // Enter Usages Minutes
        printf("Enter usage(in minutes): ");
        scanf("%f", &customers[customerCount].usage);

        // Calculate total bill
        customers[customerCount].totalBill = customers[customerCount].usage * 0.1;

        // Registered one more customer in the system
        customerCount++;

        printf("Record added successfully!\n");
    }
    else {
        printf("Maximum number of records reached!\n");
    }
}
// Shows the list of all registered customers
void viewRecords()
{
    printf("\nName\tPhone Number\tUsage(min)\tTotal "
           "Bill($)\n");
    
    for (int i = 0; i < customerCount; i++){
        printf("%s\t%s\t%.2f\t\t%.2f\n", customers[i].name, \
        customers[i].phoneNumber, customers[i].usage, \
        customers[i].totalBill);
    }
}

// Updates an existing customer record
void modifyRecord(char phoneNumber[])
{
    for (int i = 0; i < customerCount; i++){
        if (strcmp(customers[i].phoneNumber, phoneNumber) == 0){
            printf("\nEnter new usage (in minutes) for %s: ", \
            customers[i].name);

            scanf("%f", &customers[i].usage);
            customers[i].totalBill = customers[i].usage * 0.1;
            
            printf("\nRecord modified successfully!\n");
            return;
        }
    }
    printf("\nRecord not found!\n");
}

// Displays payment information for a customer
void viewPayment(char phoneNumber[])
{
    for (int i = 0; i < customerCount; i++){
        if (strcmp(customers[i].phoneNumber, phoneNumber) == 0){
            printf("\nTotal Bill for %s: $%.2f\n", 
                customers[i].name, customers[i].totalBill);
                return;
        }
    }
    printf("\nRecord not found!\n");
}
// Search customer records by phone number
void searchRecord(char phoneNumber[])
{
    printf("\nName\tPhone Number\tUsage(min)\tTotal Bill($)\n");
    for (int i = 0; i < customerCount; i++){
        if (strcmp(customers[i].phoneNumber, phoneNumber) == 0){
            printf("%s\t%s\t%.2f\t\t%.2f\n", customers[i].name, \
            customers[i].phoneNumber, customers[i].usage, \
            customers[i].totalBill);
            return; 
        }
    }
    printf("\nRecord not found!\n");
}

// Delete customer records by phone number
void deleteRecord(char phoneNumber[])
{
    for (int i = 0; i < customerCount; i++){
        if (strcmp(customers[i].phoneNumber, phoneNumber) == 0){
            for (int j = i; j < customerCount - 1; j++)
                customers[j] = customers[j + 1];
            customerCount--;
            printf("\nRecord deleted successfully!\n");
            return;    
            
        }
    }
    printf("\nRecord not found!\n");
}

// Function to display menu options
void displayMenu()
{
    printf("\n1. Add New Record\n");
    printf("2. View List of Records\n");
    printf("3. Modify Record\n");
    printf("4. View Payment\n");
    printf("5. Search Record\n");
    printf("6. Delete Record\n");
    printf("7. Quit\n");
}

// Saves current customer data to a binary file
void saveToFile()
{
    FILE *fp = fopen("customers.dat", "wb");
    if (!fp) {
        printf("Error saving file.\n");
        return;
    }
    fwrite(&customerCount, sizeof(int), 1, fp);
    fwrite(customers, sizeof(struct Customer), customerCount, fp);
    fclose(fp);
}

// Loads customer data from a binary file at program startup
void loadFromFile()
{
    FILE * fp = fopen("customers.dat", "rb");
    if (!fp) {
        customerCount = 0;
        return;
    }

    fread(&customerCount, sizeof(int), 1, fp);
    fread(customers, sizeof(struct Customer), customerCount, fp);
    fclose(fp);
}
int main(void)
{   
    loadFromFile();
    int choice;
    char phoneNumber[20];

    while (1){
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}


        switch ((Command)choice) {
            case CMD_ADD:
                addRecord();
                break;
            case CMD_VIEW:
                viewRecords();
                break;
            case CMD_MODIFY:
                printf("\nEnter phone number to modify record: ");
                scanf("%s", phoneNumber);
                modifyRecord(phoneNumber);
                break;
            case CMD_PAYMENT:
                printf("\nEnter phone number to view payment: ");
                scanf("%s", phoneNumber);
                viewPayment(phoneNumber);
                break;
            case CMD_SEARCH:
                printf("\nEnter phone number to search record: ");
                scanf("%s", phoneNumber);
                searchRecord(phoneNumber);
                break;
            case CMD_DELETE:
                printf("\nEnter phone number to delete record: ");
                scanf("%s", phoneNumber);
                deleteRecord(phoneNumber);
                break;
            case CMD_QUIT:
                saveToFile();
                return 0;
            default:
                printf("\nInvalid choice! Please try again.\n");
        }   
    }

    return 0;
}