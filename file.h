#ifndef FILE_H
#define FILE_H

#include "contact.h"

void saveContactsToFile(AddressBook *addressBook);//Function declaration for load the cantacts using file
void loadContactsFromFile(AddressBook *addressBook);//Function declaration for save the cantacts using file

//Aditional feature - which is used to load and save the cantacts using file
void saveContacts_deleted_ToFile(AddressBook *Trashbin);//Function declaration for load the cantacts using file
void loadContacts_deleted_From_File(AddressBook *Trashbin);//Function declaration for save the cantacts using file

#endif
