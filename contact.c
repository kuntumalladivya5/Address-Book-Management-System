#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
// List all contacts
void listContacts(AddressBook *addressBook,int sortCriteria)
{
    switch(sortCriteria)

{
    case 1: printf("Sorting by name : \n"); //sorting by name
    for(int i = 0; i < addressBook-> contactCount-1; i++)
    {
        for(int j = 0;j<addressBook->contactCount -i-1;j++)
        {
            if(strcmp(addressBook->contacts[j].name,addressBook-> contacts[j+1].name) > 0)
            {
                    Contact temp = addressBook->contacts[j];
                    addressBook->contacts[j] =addressBook->contacts[j+1]; 
                    addressBook->contacts[j+1] = temp;
            }
        }
    }
    printf("Index No  \tName\t\tPhone\t\tEmail\n");
   for(int i = 0; i < addressBook-> contactCount; i++)
   {
    printf("%d\t%s\t%s\t%s",i+1, addressBook-> contacts[i].name, addressBook-> contacts[i].phone, addressBook-> contacts[i].email);

   
   }
   break;

     case 2: printf("Sorting by phone : \n"); //sorting by phone
    for(int i = 0; i < addressBook-> contactCount-1; i++)
    {
        for(int j = 0;j<addressBook->contactCount -i-1;j++)
        {
            if(strcmp(addressBook->contacts[j].phone,addressBook-> contacts[j+1].phone) > 0)
            {
                    Contact temp = addressBook->contacts[j];
                    addressBook->contacts[j] =addressBook->contacts[j+1]; 
                    addressBook->contacts[j+1] = temp;
            }
        }
    }
    printf("Index No\tName\t\tPhone\t\tEmail\n");
   for(int i = 0; i < addressBook-> contactCount; i++)
   {
   printf("%d\t%s\t%s\t%s",i+1,addressBook-> contacts[i].name,addressBook-> contacts[i].phone,addressBook-> contacts[i].email);

  
   }
   break;

   

    case 3: printf("Sorting by email : \n"); //sorting by email
    for(int i = 0; i < addressBook-> contactCount-1; i++)
    {
        for(int j = 0;j<addressBook->contactCount -i-1;j++)
        {
            if(strcmp(addressBook->contacts[j].email,addressBook-> contacts[j+1].email)>0)
            {
                    Contact temp = addressBook->contacts[j];
                    addressBook->contacts[j] =addressBook->contacts[j+1]; 
                    addressBook->contacts[j+1] = temp;
            }
        }
    }
    printf("Index No\tName\t\tPhone\t\tEmail\n");
   for(int i = 0; i < addressBook-> contactCount; i++)
   { 
    printf("%d\t%s\t%s\t%s",i+1,addressBook-> contacts[i].name,addressBook-> contacts[i].phone,addressBook-> contacts[i].email);
   
   }
   break;
   case 4:
        return;

   default:
   printf("Error: Invalid choice\n");
}
}
   
    // printf("----------------------------------------------------------------------------------------");
    // printf("\n                               --- Contact List ---                                 \n");
    // printf("--------------------------------------------------------------------------------------\n");
    // printf("%-5s %-20s %-15s %-30s\n", "S.No", "\tNAME", "\tPHONE NO", "\tEMAIL");
    // printf("--------------------------------------------------------------------------------------\n");
    // for (int i = 0; i < addressBook->contactCount; i++) 
    // {
    //     printf("%-5d %-25s %-15s %-30s\n",
    //            i + 1,
    //            addressBook->contacts[i].name,
    //            addressBook->contacts[i].phone,
    //            addressBook->contacts[i].email);
    // }
  //  printf("-----------------------------------------------------------------------------------------\n");

// Initialize address book (set count = 0 and load from file)
void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0; // Reset count
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}
// Save contacts and exit the program
void saveAndExit(AddressBook *addressBook) 
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}
int name_validate(char name[]) // Validate name 
{
  int len=strlen(name),i;
  if(len==0)
  return 0;
  for(i=0;i<len;i++)
  {
    // Only alphabets and spaces allowed
    if(!(isalpha(name[i]) || name[i] == ' '))
    {
      return 0; // Invalid character found
    }
  }
  return 1;//valid name
}
int phone_validate(char phone[])  //validate phone number (must be exactly 10 digits)
{
  int len=strlen(phone),i,count=0;
  for(i=0;i<len;i++)
  {
   if(isdigit(phone[i]) && !(isalpha(phone[i])))
   {
      count++;   // Count digits only
   }
  }
  if(len==count && len==10)
  {
    return 1;//valid phone number
  }
  else
  {
    return 0; //Invalid phone number
  }
}
int email_validate(char email[])  // Validate email 
{
    int len = strlen(email);

    // Must end with ".com"
    if (len < 5 || strcmp(email + len - 4, ".com") != 0)
        return 0;

    // Check ".com" appears only once
    char *firstDotCom = strstr(email, ".com");
    char *lastDotCom  = email + len - 4;
    if (firstDotCom != lastDotCom)
        return 0;   // another ".com" found before the last one

    char *at = strchr(email, '@'); // must contain @
    if (!at) 
        return 0;

    if (at == email) // if nothing is present before @
        return 0; 

    if (strchr(at + 1, '@') != NULL)
        return 0;   // more than one @

    // Validate each character
    for (int i = 0; i < len; i++) 
    {
        if (email[i] == ' ') 
            return 0;  // no spaces

        // only lowercase letters, digits, @, _, .
        if (!(islower(email[i]) || isdigit(email[i]) || email[i] == '@' || email[i] == '_' || email[i] == '.'))
            return 0;

        // first char cannot be digit, '_' or '.'
        if (i == 0 && (isdigit(email[i]) || email[i] == '_' || email[i] == '.'))
            return 0;

        // consecutive dots not allowed
        if (i > 0 && email[i] == '.' && email[i - 1] == '.')
            return 0;
    }

    // Domain (after @) must not be empty or start with '.'
    char *domain = at + 1;
    if (domain[0] == '.')
        return 0;  // empty domain

    // Domain can only have lowercase letters before ".com"
    int domainLen = (lastDotCom - domain); // part between @ and .com
    for (int i = 0; i < domainLen; i++) 
    {
        if (!islower(domain[i]))
            return 0;  // only lowercase letters allowed
    }

    return 1; // valid email-id
}
//check if ph.no is unique
int isPhoneUnique(AddressBook *addressBook, char phone[]) 
{
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(addressBook->contacts[i].phone, phone) == 0) {
            return 0;
        }
    }
    return 1; 
}
//check if email is unique
int isEmailUnique(AddressBook *addressBook, char email[]) 
{
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(addressBook->contacts[i].email, email) == 0) {
            return 0;
        }
    }
    return 1;
}
// Create a new contact
void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    char name[20];
    char phone[11];
    char email[30];
    // Input and validate name
    do{
     printf("Enter the name :"); //asking user to enter a name
     scanf(" %[^\n]",name);
     //name validate
     if (name_validate(name)) //success
      {
           break;
      }
     else
     {
          printf("Enter the valid name\n");
        //   failure  -> print error msg
     }
    }while(1);

    // Input and validate phone
    do{
     printf("Enter the phone number :");
     scanf(" %[^\n]",phone);
      if (!phone_validate(phone)) //success
      { 
        printf("Enter the valid phone number\n");
      }
      else if (!isPhoneUnique(addressBook, phone)) 
      {
        printf("This phone number already exists! Enter a unique phone number.\n"); //   failure  -> print error msg
      } 
      else
     {
        break;
     }

    }while(1);
     // Input and validate email
    do{
     printf("Enter the mail id :");
     scanf(" %[^\n]",email);
    
    if (!email_validate(email)) //success
    {
      printf("Enter the valid mailid\n");  
    }
    else if (!isEmailUnique(addressBook, email)) 
    {
      printf("This email id already exists! Enter a unique email id.\n"); //   failure  -> print error msg
    }
    else
     {
         break;  
        
     }
    }while(1);
    strcpy(addressBook->contacts[addressBook->contactCount].name,name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email,email);
    addressBook->contactCount++;
}
// Search for a contact
void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    if (addressBook->contactCount == 0) {
        printf("No contacts available to search!\n");  // If no contacts exist
        return;
    }
    int choice;
    char search[50];
    int found = 0;  // Flag to track matches
    do {
        // Show search menu
        printf("\n--- Search Menu ---\n");
        printf("1. Search by Name\n");
        printf("2. Search by Phone Number\n");
        printf("3. Search by Email ID\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
            { // Search by Name
                printf("Enter the name to search: ");
                scanf(" %[^\n]", search); 
                int matchedIndices[50]; // store all matches
                int matchCount = 0;
                // Find all contacts matching the name
                for (int i = 0; i < addressBook->contactCount; i++) 
                {
                    if (strcmp(addressBook->contacts[i].name, search) == 0)
                    {
                      matchedIndices[matchCount++] = i;
                    }
                }
                if (matchCount == 0)  // No matches found
                {
                  printf("Name not found!\n");
                } 
                else if (matchCount == 1)   // Exactly one match found
                {
                  int idx = matchedIndices[0];
                  printf("\nContact Found:\n");   //printing the matched name, phone number,email-id
                  printf("Name : %s\n", addressBook->contacts[idx].name);
                  printf("Phone: %s\n", addressBook->contacts[idx].phone);
                  printf("Email: %s\n", addressBook->contacts[idx].email);
                } 
                else   // Multiple matches found → refine search
                {
                  printf("\nMultiple contacts found with the same name:\n");
                  for (int j = 0; j < matchCount; j++)
                  {
                    int idx = matchedIndices[j];
                    printf("%d. %s | %s | %s\n", j + 1,addressBook->contacts[idx].name,addressBook->contacts[idx].phone,addressBook->contacts[idx].email);
                  }
                  // Refine by phone or email
                  printf("\nEnter phone number or email ID to refine search: ");
                  char refine[50];
                  scanf(" %[^\n]", refine); //asking user to enter the phone.no or email-id
                  int refinedFound = 0;
                  for (int j = 0; j < matchCount; j++)
                  {
                    int idx = matchedIndices[j];
                    if (strcmp(addressBook->contacts[idx].phone, refine) == 0 ||
                            strcmp(addressBook->contacts[idx].email, refine) == 0) 
                        {
                            printf("\nExact Contact Found:\n");  //printing the matched name, phone number,email-id
                            printf("Name : %s\n", addressBook->contacts[idx].name);
                            printf("Phone: %s\n", addressBook->contacts[idx].phone);
                            printf("Email: %s\n", addressBook->contacts[idx].email);
                            refinedFound = 1;
                            break;
                        }
                  }
                  if (!refinedFound)
                  {
                    printf("No contact matched the refinement!\n");   //not found printing error message
                  }
                }
              break;
            }

            case 2:
            { // Search by Phone
                printf("Enter the phone number to search: "); //asking user to enter the phone number to search
                scanf(" %[^\n]", search);
                for (int i = 0; i < addressBook->contactCount; i++)
                {
                    if (strcmp(addressBook->contacts[i].phone, search) == 0)
                    {
                        printf("\nContact Found:\n");   //printing the matched name, phone number,email-id
                        printf("Name : %s\n", addressBook->contacts[i].name);
                        printf("Phone: %s\n", addressBook->contacts[i].phone);
                        printf("Email: %s\n", addressBook->contacts[i].email);
                        found = 1;
                        break;
                    }
                }
                if (!found)
                {
                  printf("Phone number not found!\n"); //if it is not found printing error message
                }
                found = 0; //reset flag
                break;
            }
            case 3:
            { // Search by Email
                printf("Enter the email ID to search: "); //asking user to enter the email-id to search
                scanf(" %[^\n]", search);
                for (int i = 0; i < addressBook->contactCount; i++)
                {
                    if (strcmp(addressBook->contacts[i].email, search) == 0)
                    {
                        printf("\nContact Found:\n");          //if it is found printing name,phone number,email-id
                        printf("Name : %s\n", addressBook->contacts[i].name);
                        printf("Phone: %s\n", addressBook->contacts[i].phone);
                        printf("Email: %s\n", addressBook->contacts[i].email);
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    printf("Email not found!\n"); //if it is not found printing error message
                }
                found = 0; //reset flag
                break;
            }
            case 4:
                printf("Exiting search menu...\n");  // Exit search menu
                break;
            default:
                printf("Invalid choice! Please try again.\n");  //invalid input
        }
    } while (choice != 4);  // Repeat until user exits
}
//  Edit a contact
void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
  if (addressBook->contactCount == 0)
  {
    printf("No contacts available to edit!\n"); // If no contacts exist
    return;
  }
    int choice, idx;
    char temp[50];
    do {
        //display edit menu
        printf("\n--- Edit Contact Menu ---\n");
        printf("1. Edit Name\n");
        printf("2. Edit Phone Number\n");
        printf("3. Edit Email\n");
        printf("4. Exit\n");
        printf("Enter your choice: "); //enter user choice 
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Edit Name
                listContacts(addressBook,1);
                printf("Select contact index to edit name: "); //asking user to enter index to edit name
                scanf("%d", &idx);
                idx--;
                if (idx < 0 || idx > addressBook->contactCount) {
                    printf("Invalid index!\n"); //invalid index
                    break;
                }
                printf("Enter new name: ");//asking user to enter a new name
                scanf(" %[^\n]", temp);

                if (name_validate(temp)) //validate new name
                {
                    strcpy(addressBook->contacts[idx].name, temp);  
                    printf("Name updated successfully!\n"); //printing name is updated
                } else {
                    printf("Invalid name!\n"); //invalid name
                }
                break;

            case 2: // Edit Phone
                listContacts(addressBook, 1);
                printf("Select contact index to edit phone: "); //asking user to enter index to edit phone number
                scanf("%d", &idx);
                idx--;
                if (idx < 0 || idx > addressBook->contactCount) {
                    printf("Invalid index!\n");//invalid index
                    break;
                }
     
                do {
                    printf("Enter new phone number: ");//asking user to enter a new phone number
                    scanf(" %[^\n]", temp);

                    if (!phone_validate(temp))//validate new phone number
                    {
                      printf("Invalid phone number! Try again.\n");//invalid phone number
                    }
                    else if (!isPhoneUnique(addressBook, temp) && strcmp(addressBook->contacts[idx].phone, temp) != 0) //checking unique phone number or not
                    {
                      printf("This phone number already exists! Try again.\n");//if it is already exit printing error message
                    }
                    else 
                    {
                      strcpy(addressBook->contacts[idx].phone, temp);  //coping new phone number
                      printf("Phone updated successfully!\n");
                      break;
                    }
                } while (1);
                break;

            case 3: // Edit Email
                listContacts(addressBook, 1);
                printf("Select contact index to edit email: ");//asking user to enter index to edit email-id
                scanf("%d", &idx);
                idx--;
                if (idx < 0 || idx > addressBook->contactCount)
                {
                  printf("Invalid index!\n");//Invalid index
                  break;
                }
                
                do {
                    printf("Enter new email: "); //asking user to enter a new email-id
                    scanf(" %[^\n]", temp);

                    if (!email_validate(temp)) //validate new email-id
                    {
                      printf("Invalid email! Try again.\n");
                    }
                    else if (!isEmailUnique(addressBook, temp) && strcmp(addressBook->contacts[idx].email, temp) != 0) //checking unique email-id or not
                    {
                      printf("This email already exists! Try again.\n");//if it is already exit printing error message
                    }
                    else
                    {
                      strcpy(addressBook->contacts[idx].email, temp); //coping new email-id
                      printf("Email updated successfully!\n");
                      break;
                    }
                } while (1);
                break;

            case 4:
                printf("Exiting edit menu...\n"); // Exit edit menu
                break;

            default:
                printf("Invalid choice! Please try again.\n"); //invalid input 
        }
    } while (choice != 4); // Repeat until user exits
    
}
// delete a contact
void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    if (addressBook->contactCount == 0) {
        printf("No contacts available to delete!\n"); // If no contacts exist
        return;
    }

    int choice;
    char search[50];
    int found = 0;

    do {
        //display delete menu
        printf("\n--- Delete Contact Menu ---\n");
        printf("1. Delete by Name\n");
        printf("2. Delete by Phone Number\n");
        printf("3. Delete by Email ID\n");
        printf("4. Exit\n");
        printf("Enter your choice: "); //asking user to enter a choice 
        scanf("%d", &choice);

        switch (choice) {
            case 1: { // Delete by Name
                printf("Enter the name to delete: "); 
                scanf(" %[^\n]", search);

                int matchedIndices[50]; // Store indices of matching contacts
                int matchCount = 0;
                 // Find all contacts matching the name
                for (int i = 0; i < addressBook->contactCount; i++) {
                    if (strcmp(addressBook->contacts[i].name, search) == 0) {
                        matchedIndices[matchCount++] = i;
                    }
                }

                if (matchCount == 0) // No contact matched
                {
                    printf("Name not found!\n");
                } 
                else if (matchCount == 1)  // Single match found → delete directly
                {
                    int idx = matchedIndices[0];
                    printf("Deleting contact: %s | %s | %s\n",
                           addressBook->contacts[idx].name,
                           addressBook->contacts[idx].phone,
                           addressBook->contacts[idx].email);

                    // Shift contacts
                    for (int j = idx; j < addressBook->contactCount - 1; j++) {
                        addressBook->contacts[j] = addressBook->contacts[j + 1];
                    }
                    addressBook->contactCount--;
                    printf("Contact deleted successfully!\n");
                } 
                else // Multiple matches found
                {
                    printf("\nMultiple contacts found with the same name:\n");
                    for (int j = 0; j < matchCount; j++) {
                        int idx = matchedIndices[j];
                        printf("%d. %s | %s | %s\n", j + 1,
                               addressBook->contacts[idx].name,
                               addressBook->contacts[idx].phone,
                               addressBook->contacts[idx].email);
                    }
                    // Ask user for phone/email to refine deletion
                    printf("\nEnter phone number or email ID to refine deletion: ");
                    char refine[50];
                    scanf(" %[^\n]", refine);
                    int refinedIndex = -1;
                    // Match refinement input
                    for (int j = 0; j < matchCount; j++) 
                    {
                        int idx = matchedIndices[j];
                        if (strcmp(addressBook->contacts[idx].phone, refine) == 0 ||
                            strcmp(addressBook->contacts[idx].email, refine) == 0) {
                            refinedIndex = idx;
                            break;
                        }
                    }

                    if (refinedIndex != -1)  // Delete refined contact
                    {
                        printf("Deleting contact: %s | %s | %s\n",
                               addressBook->contacts[refinedIndex].name,
                               addressBook->contacts[refinedIndex].phone,
                               addressBook->contacts[refinedIndex].email);

                        // Shift contacts
                        for (int j = refinedIndex; j < addressBook->contactCount - 1; j++) {
                            addressBook->contacts[j] = addressBook->contacts[j + 1];
                        }
                        addressBook->contactCount--;
                        printf("Contact deleted successfully!\n");
                    } else {
                        printf("No contact matched refinement!\n");
                    }
                }
                break;
            }

            case 2: { // Delete by Phone
                printf("Enter the phone number to delete: ");
                scanf(" %[^\n]", search);
                 // Search by phone
                int idx = -1;
                for (int i = 0; i < addressBook->contactCount; i++) {
                    if (strcmp(addressBook->contacts[i].phone, search) == 0) {
                        idx = i;
                        break;
                    }
                }

                if (idx == -1) 
                {
                    printf("Phone number not found!\n");
                } 
                else // Delete contact by phone
                {
                    printf("Deleting contact: %s | %s | %s\n",
                           addressBook->contacts[idx].name,
                           addressBook->contacts[idx].phone,
                           addressBook->contacts[idx].email);

                    for (int j = idx; j < addressBook->contactCount - 1; j++) {
                        addressBook->contacts[j] = addressBook->contacts[j + 1];
                    }
                    addressBook->contactCount--;
                    printf("Contact deleted successfully!\n");
                }
                break;
            }

            case 3: { // Delete by Email
                printf("Enter the email ID to delete: ");
                scanf(" %[^\n]", search);
                 // search by email-id
                int idx = -1;
                for (int i = 0; i < addressBook->contactCount; i++) {
                    if (strcmp(addressBook->contacts[i].email, search) == 0) {
                        idx = i;
                        break;
                    }
                }

                if (idx == -1) 
                {
                    printf("Email not found!\n");
                } 
                else 
                {   //Delete contact by email-id
                    printf("Deleting contact: %s | %s | %s\n",
                           addressBook->contacts[idx].name,
                           addressBook->contacts[idx].phone,
                           addressBook->contacts[idx].email);

                    for (int j = idx; j < addressBook->contactCount - 1; j++) {
                        addressBook->contacts[j] = addressBook->contacts[j + 1];
                    }
                    addressBook->contactCount--;
                    printf("Contact deleted successfully!\n");
                }
                break;
            }

            case 4:
                printf("Exiting delete menu...\n"); //exit delete menu
                break;

            default:
                printf("Invalid choice! Try again.\n"); //invalid input
        }
    } while (choice != 4); // Repeat until user exits


}

