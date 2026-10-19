/* 
NAME        : Divya kuntumalla
Date        :
Description : Project AddressBook 
              (Creating Contact, Searching Contact, Editing Contact, Deleting Contact,
               Listing Contacts, Saving Contacts, and Exit)

*/


#include<stdio.h>
#include "contact.h"
int main() 
{
    int choice;
    AddressBook addressBook;
    //addressBook.contactCount = 0;
    initialize(&addressBook); // Initialize the address book

    do {   //Display menu                                  
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save contacts\n");		
        printf("7. Exit\n");
        printf("Enter your choice: ");//Read menu choice
        scanf(" %d", &choice);
        
        switch (choice) {
            case 1: 
            {   //Create contacts
                int n;    
                printf("How many contacts do you want to add: ");   // Number of contacts to add
                scanf(" %d", &n);               
                for (int i = 0; i < n; i++) //Running loop upto n
                {
                printf("\n--- Enter Contact %d ---\n", i + 1);
                createContact(&addressBook);
                }
                break;
            }
            case 2:                     //Search for a contact
                searchContact(&addressBook);
                break;
            case 3:                      //edit contact
                editContact(&addressBook);
                break;
            case 4:                     //delete contact
                deleteContact(&addressBook);
                break;
            case 5:                      //list all contacts
                printf("Select sort criteria:\n");
                printf("1. Sort by name\n");
                printf("2. Sort by phone\n");
                printf("3. Sort by email\n");
                printf("4. Exit\n");
                printf("Enter your choice");
                int sortCriteria;
                scanf("%d",&sortCriteria);
                listContacts(&addressBook,sortCriteria);
                break;
            case 6:                     //save contacts to file
                printf("Saving and Exiting...\n");
                saveContactsToFile(&addressBook);
                break;
            default:                    //Invalid choice
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7); // Keep looping until user chooses Exit
    
       return 0;        //end program
}
