#ifndef FILE_H
#define FILE_H

#include "contact.h"   // Include contact definitions (AddressBook, Contact)

// Function prototypes for file operations
void saveContactsToFile(AddressBook *addressBook);  // Save contacts to CSV file
void loadContactsFromFile(AddressBook *addressBook); // Load contacts from CSV file

#endif
