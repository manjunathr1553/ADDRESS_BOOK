/*Documentation
Name : Manjunath R
DATE :06/01/2025
DISCRIPTION : Address Book is a small application written in C language. It keeps track of names and telephone/mobile numbers and e-mail addresses.*/

#include <stdio.h>
#include "contact.h"
#include "file.h"

int main()
{
    int choice;
    AddressBook addressBook;
    AddressBook Trashbin;

    // Load contacts from files at the start
    loadContactsFromFile(&addressBook);
    loadContacts_deleted_From_File(&Trashbin);

    do {
        // Display the main menu
        printf("\nAddress Book Menu:\n");
        printf("\t1. Create contact 👤\n");//Option to create new contact
        printf("\t2. Search contact 🔎\n");//Option to search a perticular contact
        printf("\t3. Edit contact ✏️\n");//Option to edit a contact
        printf("\t4. Delete contact 🗑\n");//Option to dealete a particular contact
        printf("\t5. List all contacts 📋\n");//Listing all contacts
        printf("\t6. List Deleted contacts(Trash bin) 🗑📋\n");  // Option to view deleted contacts
        printf("\t7. Retrive contact ♻️\n");  // Option to retrieve deleted contact and add it back
        printf("\t8. Save contacts ⬇️  and Exit 🔚\n");  // Option to save and exit the program
        choice = 9;
        printf("Enter your choice🤔: ");
        scanf("%d",&choice);  // Get user input for menu choice
        getchar();  

        // Process the selected option
        switch (choice) {
            case 1:
                createContact(&addressBook);  // Create a new contact
                break;
            case 2:
                printf("\nChoose one choice to search the data 🔍🔎: ");
                int index = searchContact(&addressBook);  // Search for a contact
                print(index, &addressBook);  // Print the found contact
                break;
            case 3:
                editContact(&addressBook);  // Edit an existing contact
                break;
            case 4:
                deleteContact(&addressBook, &Trashbin);  // Delete a contact and move it to the Trashbin
                break;
            case 5:
                listContacts(&addressBook);  // List all contacts in the address book
                break;
            case 6:
                deletedContacts(&Trashbin);  // List all deleted contacts in the trash bin
                break;
            case 7:
                retrieve_contact(&addressBook, &Trashbin);  // Retrieve a contact from the trash bin and add it back
                break;
            case 8:
                printf("\n....Saving and Exiting...💾\n");
                printf("\n\t\t\t....THANK GOD ITS OVER....🥱🥱🥱🥱\n");
                saveAndExit(&addressBook, &Trashbin);  // Save all data and exit
                break;
            default:
                printf("\n\t\t\t❌ Invalid choice. Please try again ❌\n");  // Invalid choice message
        }
    } while (choice != 8);  // Continue looping until the user chooses to exit

    return 0;  // Exit the program
}
