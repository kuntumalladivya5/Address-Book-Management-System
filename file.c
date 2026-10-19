#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook)  // Function to save contacts into a CSV file
{
    FILE *fp= fopen("contacts.txt", "w");  //Open file in write mode
    if (fp == NULL) 
    {
        printf("Error: Could not open file for writing!\n");   // Error if file can't be opened
        return;
    }
    // Save total number of contacts at top
    fprintf(fp, "%d\n", addressBook->contactCount);
    // Save all contacts with numbering
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        fprintf(fp, "%d.%s,%s,%s\n",
                i + 1,
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(fp);  //close file after writing file
}

void loadContactsFromFile(AddressBook *addressBook)   // Function to load contacts into a CSV file
{
    FILE *fp = fopen("contacts.txt", "r"); //open file in read mode
    if (fp == NULL) 
    {
        printf("No previous contacts found.\n");
        addressBook->contactCount = 0;
        return;
    }

    int totalContacts = 0;
    fscanf(fp, "%d\n", &totalContacts);   // Read total number of contacts from first line

    //addressBook->contactCount = 0;

    for (int i = 0; i < totalContacts && i < MAX_CONTACTS; i++)  // Loop through contacts and read them
    {
        // Skip numbering before dot (like "1.")
        fscanf(fp, "%*d."); 

        if (fscanf(fp, "%[^,],%[^,],%[^\n]\n",
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email) == 3) 
        {
            addressBook->contactCount++;  // Increase count only if all 3 fields are read
        }
    }

    fclose(fp);//close file after reading file
}