// Including libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Defining stucture for beer
typedef struct{
    char name[10]; //beers name, max 10 characters, based on typical beer name lengths
    float price; // rice of the beer
    int rating; // rating of the beer
}Beer;

//Function to transform string to lowercase for comparison
void lowercase_transform(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    } 
}

//Adding beer to the inventory
void addbeer(Beer **inventory, int *ammount) {
    int extra; //This upper compartment is for adding the amount of beer
    printf("How many beers to add? "); 
    scanf("%d", &extra);
    getchar();

    //Reallocating memory for the new beers
    Beer *tmp = realloc(*inventory, (*ammount + extra) * sizeof(Beer));
    // here we make sure that the reallocation will go otherwise it returns
    if (tmp == NULL) { 
        printf("Memory reallocation failed.\n");
        return;
    }
    *inventory = tmp; //Refreshing 
    // Asking for the beer details
    for (int i = 0; i < extra; i++) {

        while (1){
            printf("Beer name: ");
            fgets((*inventory)[*ammount + i].name, 10, stdin);
            (*inventory)[*ammount + i].name[strcspn((*inventory)[*ammount + i].name, "\n")] = 0;
            if (strlen((*inventory)[*ammount + i].name) == 0) {
                printf("Invalid name. Please enter a non-empty name.\n");
                continue; // Prompt for the beer details again
            }
            else if (strlen((*inventory)[*ammount + i].name) >= 10) {
                printf("Invalid name. Please enter a name with less than 10 characters.\n");
                continue; // Prompt for the beer details again
            }
            char user_input_name[10];
            strcpy(user_input_name, (*inventory)[*ammount + i].name);
            lowercase_transform(user_input_name);

            char existing_name[10];
            //Check for duplicate names
            for (int j = 0; j < *ammount + i; j++) {
                strcpy(existing_name, (*inventory)[j].name);
                lowercase_transform(existing_name);
                if (strcmp(existing_name, user_input_name) == 0) {

                    break; // Break the check if duplicates
                }
            }
            //if there are duplicates ask user again for name of beer
            if (strcmp(existing_name, user_input_name) == 0) {
                printf("Beer name already exists. Please enter a different name.\n");
                continue;
            }
            //if name has passed all criteria exit name prompt
            else {
                break; // Exit the loop if name is valid and unique
            }
        
    }

        while (1){
            printf("Price per liter: "); // asking the price and the adding
            scanf("%f", &(*inventory)[*ammount + i].price);
            if ((*inventory)[*ammount + i].price < 0) {
                printf("Invalid price. Please enter a non-negative value.\n");
                getchar(); // Clear the newline character from the input buffer
                continue; // Prompt for the beer details again
            }
            break; // Exit the loop if price is valid
        }

        while (1){
            printf("Rating (1-5): "); // asking the rating and the adding
            scanf("%d", &(*inventory)[*ammount + i].rating);
            if ((*inventory)[*ammount + i].rating < 1 || (*inventory)[*ammount + i].rating > 5) {
                printf("Invalid rating. Please enter a value between 1 and 5.\n");
                getchar(); // Clear the newline character from the input buffer
                continue; // Prompt for the beer details again
            }
            break; // Exit the loop if rating is valid
        }
        getchar(); // Clear the newline character from the input buffer
    }

    *ammount += extra;
    printf("Beers added.\n");
}

//Removing beer from the inventory
void removebeer(Beer **inventory, int *ammount) {
    if (*ammount == 0) { // making sure that the inventory is not empyt
        printf("Inventory is empty.\n");
        return;
    }

    //Here asking the beer name and also checking that will find it
    char name[10];
    printf("Enter beer name to remove: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;
    //Transforming to lowercase for comparison
    lowercase_transform(name);
    //Check if the beer is in the inventory
    for (int i = 0; i < *ammount; i++) { //moving the athter cells into right place
        char temp_name[10];
        strcpy(temp_name, (*inventory)[i].name);
        lowercase_transform(temp_name);
        if (strcmp(temp_name, name) == 0) {
            printf("Beer '%s' removed.\n", (*inventory)[i].name);
            memmove(&(*inventory)[i], &(*inventory)[i + 1], (*ammount - i - 1) * sizeof(Beer));
            (*ammount)--; // Decrease the amount of beer
            Beer *tmp = realloc(*inventory, (*ammount) * sizeof(Beer));
            if (tmp == NULL && *ammount > 0) { 
                printf("Memory reallocation failed.\n");
                return;
            }
            *inventory = tmp; //Refreshing
            return;
        }
    }

    printf("Beer not found.\n"); // if beer not found it will call
}
//Here we print and check the inventory
void listbeer(Beer *inventory, int ammount) {
    if (ammount == 0) { // checking inventoryh not empty
        printf("Inventory is empty.\n");
        return;
    }
    //Listing the inventory
    printf("\n--- Inventory ---\n");
    for (int i = 0; i < ammount; i++)
        printf("%d. %s, %.2f euro (rating = %d)\n", i + 1, inventory[i].name, inventory[i].price, inventory[i].rating);
}

// Menu
int main() {
    //Making sure that the inventory is empty 
    Beer *inventory = NULL;
    int ammount = 0; //amount of beer in the inventory
    int choice; //choice for the menu
    //Menu loop till user wants to exit
    while (1) {
        printf("---- The amazing beer inventory for academic use only----\n1. Add beer\n2. Remove beer\n3. List beer\n4. Exit\nMake your choice between (1-4): ");
        scanf("%d", &choice); //Users decision
        getchar();//Deleting the left emptynes
        //Based on users choice we call the function
        switch (choice) {
            case 1: 
                addbeer(&inventory, &ammount); 
                break;
            case 2: 
                removebeer(&inventory, &ammount); 
                break;
            case 3: 
                listbeer(inventory, ammount); 
                break;
            case 4: 
                free(inventory); 
                printf("Program closed.\nThank you for using the program.\n");
                return 0;
            default: 
                printf("Invalid input.\n");
                break;
        }
    }
    return 0;
}