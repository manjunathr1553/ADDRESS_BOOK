#include <stdio.h>
#include "file.h"

// Function to save contacts from the address book to a file
void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fptr;
    if ((fptr = fopen("contacts.csv", "w")) == NULL)
    {
       printf("\t\t ⚠️...Not able to open the file...⚠️\n");
        return;
    }
    // Write the number of contacts to the file
    fprintf(fptr, "%d\n", addressBook->contactCount);
    // Write each contact's details to the file
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fptr, "%s,%s,%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    fclose(fptr);  // Close the file
}

// Function to load contacts from a file into the address book
void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fp;
    if ((fp = fopen("contacts.csv", "r")) == NULL)
    {
       printf("\t\t ⚠️...Not able to open the file...⚠️\n");
        addressBook->contactCount = 0;  // Set contact count to 0 if file cannot be opened
        return;
    }
    fscanf(fp, "%d\n", &addressBook->contactCount);  // Read the number of contacts
    if (addressBook->contactCount == 0)
        printf("\n❌...Address book is empty...❌\n");
    else
    {
        // Read each contact's details
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            fscanf(fp, "%[^,] %*c %[^,] %*c %[^\n] ", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        }
    }
    fclose(fp);  // Close the file
}

// Function to save deleted contacts from the trash bin to a file
void saveContacts_deleted_ToFile(AddressBook *Trashbin)
{
    FILE *fptr;
    if ((fptr = fopen("deleted_contacts.csv", "w")) == NULL)
    {
        printf("\t\t ⚠️...Not able to open the file...⚠️\n");
        return;
    }
    // Write the number of deleted contacts to the file
    fprintf(fptr, "%d\n", Trashbin->contactCount);
    // Write each deleted contact's details to the file
    for (int i = 0; i < Trashbin->contactCount; i++)
    {
        fprintf(fptr, "%s,%s,%s\n", Trashbin->contacts[i].name, Trashbin->contacts[i].phone, Trashbin->contacts[i].email);
    }
    fclose(fptr);  // Close the file
}

// Function to load deleted contacts from a file into the trash bin
void loadContacts_deleted_From_File(AddressBook *Trashbin)
{
    FILE *fp;
    if ((fp = fopen("deleted_contacts.csv", "r")) == NULL)
    {
        printf("\n>>>>>>There is no file with deleted contacts..❗⚠️\n");
        Trashbin->contactCount = 0;  // Set contact count to 0 if file cannot be opened
        return;
    }
    fscanf(fp, "%d\n", &Trashbin->contactCount);  // Read the number of deleted contacts
    if (Trashbin->contactCount == 0)
        printf("\n\t\t\t❌...Trashbin is empty...❌\n");
    else
    {
        // Read each deleted contact's details
        for (int i = 0; i < Trashbin->contactCount; i++)
        {
            fscanf(fp, "%[^,] %*c %[^,] %*c %[^\n] ", Trashbin->contacts[i].name, Trashbin->contacts[i].phone, Trashbin->contacts[i].email);
        }
    }
    fclose(fp);  // Close the file
}
