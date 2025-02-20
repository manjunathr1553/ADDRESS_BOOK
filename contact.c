#include <stdio.h>
#include<stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"


// Function to list all contacts in the address book
void listContacts(AddressBook *addressBook) 
{
    if(!(addressBook -> contactCount))
    {
        printf("No Cotacts found and addressbook is empty🤷🤷");
        return;
    }
    // Loop through the contacts and print each contact's details
    printf("\nTHERE ARE TOTAL OF %d CONTACTS IN ADDRESSBOOK📜\n",addressBook -> contactCount);
    for(int i = 0; i < addressBook -> contactCount; i++) {
        // Display the contact's number, name, phone, and email
        printf("(%d) Name 👤: %s\tPhone 📞: +91 %s\tEmail 📩: %s\n",i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
}

// Function to create a new contact
void createContact(AddressBook *addressBook)
{
    char number[12], mail[50];
    int validate = 0;

    // Prompt the user to enter the name of the contact
    printf("Enter the name 👤: ");
    scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].name); // Allow spaces in the name
    if(addressBook->contacts[addressBook->contactCount].name[0] >= 97 && addressBook->contacts[addressBook->contactCount].name[0] <= 122)
    {
        addressBook->contacts[addressBook->contactCount].name[0] = addressBook->contacts[addressBook->contactCount].name[0] -32;
    }

    // Validate and ensure the phone number is unique and valid
    do {
        printf("Enter the phone number 📞: ");
        scanf(" %s", number);
        validate = validate_num(number, addressBook);
        if(validate == 1)
            strcpy(addressBook->contacts[addressBook->contactCount].phone, number); // Store the phone number if valid
        else if(validate == 2)
            printf("\n\tThe phone number already exists in the address book ☝️\n"); // Inform if the number already exists
        else
            printf("\n\tInvalid phone number. Please enter a valid one ⛔⛔\n"); // Inform if the number is invalid
    } while(validate != 1);

    validate = 0;

    // Validate and ensure the email is unique and valid
    do {
        printf("Enter the E-mail ID 📩: ");
        scanf(" %s", mail);
        validate = validate_mail(mail, addressBook);
        if(validate == 1)
            strcpy(addressBook->contacts[addressBook->contactCount].email, mail); // Store the email if valid
        else if(validate == 2)
            printf("\t\t>>>>>>>>>The e-mail ID already exists in the address book<<<<<<< ☝️\n"); // Inform if the email already exists
        else
            printf(">>>>>>>>>>>>>Invalid e-mail ID. Please enter a valid one<<<<<<<<<<<< ⛔⛔\n"); // Inform if the email is invalid
    } while(validate != 1);

    (addressBook->contactCount)++; // Increment the contact count after successfully adding the new contact
    printf("✌️✌️✌️......New contact added to addressbook successfully......✌️✌️✌️");
}


// Function to validate email format and check if it's already in the address book
int validate_mail(char* email, AddressBook* addressBook)
{
    int k = 0, at_count = 0, at_ind;
    char check[5] = ".com";  // Predefined domain for checking

    // Checking if the characters in the email are valid (lowercase letters, numbers, and '@' symbol)
    while(email[k] != '\0') {
        if(email[k] > 'z' || email[k] < 'a' ) {
            if(email[k] == '.')
             {
                k++; // Skip the dot (.) as it's valid in email addresses
                continue;
            }
            else if(email[k] >= '0' && email[k] <= '9') 
            {
                k++; // Numbers are allowed in the email
                continue;
            }
            else if(email[k] == '@') 
            {
                at_count++; // Increment counter when '@' is found
                at_ind = k; // Record the position of '@'
            }
            else
                return 0; // Invalid character found
        }
        k++;
    }

    // Ensuring there's exactly one '@' symbol
    if(at_count != 1)
        return 0; // Return 0 if there are no or multiple '@' symbols

    // Ensure that the characters after '@' are valid (letters only)
    if(email[at_ind + 1] < 'a' || email[at_ind + 1] > 'z')
        return 0; // Invalid character after '@'

    // Ensuring that the character before '@' is valid (letters or numbers)
    if((email[at_ind - 1] < '0' || email[at_ind - 1] > '9') && (email[at_ind - 1] < 'a' || email[at_ind - 1] > 'z'))
        return 0; // Invalid character before '@'

    // Checking if the email contains the valid domain ".com"
    if(strstr(email, check) == NULL)
        return 0; // Invalid domain if ".com" is not found

    // Checking if the email is already in the address book
    for(int j = 0; j < addressBook->contactCount; j++) {
        if(strcmp(email, addressBook->contacts[j].email) == 0)
            return 2; // Email already exists in the address book
    }

    return 1; // Email is valid and does not exist in the address book
}

// Function to validate phone number format and check if it's already in the address book
int validate_num(char* str, AddressBook* addressBook) 
{
    int i = 0;

    // Ensuring that the phone number consists only of digits
    while(str[i] != '\0') {
        if(str[i] > '9' || str[i] < '0')
            return 0; // Invalid character found
        i++;
    }

    // Checking if the phone number has exactly 10 digits
    if(i != 10)
        return 0; // Invalid phone number if it doesn't have 10 digits

    // Checking if the phone number already exists in the address book
    for(int index = 0; index < addressBook->contactCount; index++) {
        if(strcmp(str, addressBook->contacts[index].phone) == 0)
            return 2; // Phone number already exists in the address book
    }

    return 1; // Phone number is valid and does not exist in the address book
}

// Function to search for a contact by phone, name, or email
int searchContact(AddressBook *addressBook) 
{
    printf("\n(1) Search by phone📞\n(2) Search by Name 👤\n(3) Search by email📩\n\tChoice : ");
    int choice;
    __fpurge(stdin);
    scanf("%d", &choice);  // Prompt the user to select the search option

    // Search by phone number
    if(choice == 1) 
    {
        char mob[11];
        printf("Enter the mobile📞: ");
        getchar(); // Clear the input buffer
        scanf("%s", mob);  // Read the phone number input

        // Search through the contacts for the phone number
        for(int i = 0; i < addressBook->contactCount; i++) {
            if(strcmp(addressBook->contacts[i].phone, mob) == 0) {
                printf("\n..........*Contact Found*............🙌🙌\n");
                return i;  // Return the index of the matching contact
            }
        }
        return -2;  // Return -2 if contact not found
    }
    // Search by name
    else if(choice == 2) 
    {
        char name[100];
        int arr[100];
        int count = 0;
        printf("Enter the name: ");
        getchar(); // Clear the input buffer
        scanf("%s", name);  // Read the name input
        if(name[0] >= 97 && name[0] <=122)
        {
            name[0]=name[0]-32;
        }

        // Search through the contacts for the name
        for(int i = 0; i < addressBook->contactCount; i++) {
            if(strcmp(addressBook->contacts[i].name, name) == 0) {
                arr[count] = i;  // Store the index of contacts with the matching name
                count++;
            }
        }
        if(count == 0)
        {
            return -2;
        }
        // Handle cases where one or more contacts have the same name
        else if(count == 1 && count != 0) 
        {
            printf("\n..........*Contact Found*............🙌🙌\n");
            return arr[0];  // Return the index if only one contact is found
        }
        else 
        {
            printf("\n..........%d Contacts Found with the same name '%s'..............😖😖😖\n", count, name);
            for(int i = 0; i < count; i++) {
                print(arr[i], addressBook);  // Print all contacts with the same name
            }
            int choice;
            printf("Enter the roll number of the contact you are searching for below ⤵️⤵️:  ");
            scanf("%d", &choice);

            // Return the index of the selected contact
            for(int i = 0; i < count; i++) {
                if(choice == arr[i]) {
                    printf("\n..........*Contact Found*..............\n");
                    return arr[i];
                }
            }
        }
        return -2;  // Return -2 if contact not found
    }
    // Search by email
    else if(choice == 3) {
        char mail[50];
        printf("Enter the mail: ");
        getchar(); // Clear the input buffer
        scanf("%s", mail);  // Read the email input

        // Search through the contacts for the email
        for(int i = 0; i < addressBook->contactCount; i++) {
            if(strcmp(addressBook->contacts[i].email, mail) == 0) {
                printf("\n..........*Contact Found*..............\n");
                return i;  // Return the index of the matching contact
            }
        }
        return -2;  // Return -2 if contact not found
    }
    else {
        printf("\n***********🥱Invalid choice ***********");  // If an invalid choice is entered
        return -2;
    }
}


// Function to edit an existing contact
void editContact(AddressBook *addressBook)
{
    printf("\n\nEnter the choice for how you want to search 🔎 the contact to edit 📝📝:\n");
    int k = searchContact(addressBook);  // Search for the contact to edit
    print(k, addressBook);  // Display the found contact's details

    if(k >= 0) {  // If the contact is found
        printf("Enter the number corresponding to the data you want to edit:\n");
        printf("1) Edit Name 👤\n2) Edit Phone Number 📞\n3) Edit Email 📩\nChoice: "); 
        int ch;
        scanf("%d", &ch);

        if(ch == 1) {
            // Edit name
            printf("Enter the new name👤: ");
            getchar();  // Clear the buffer
            scanf("%[^\n]%*c", addressBook->contacts[k].name);  // Read the new name
            // Capitalize the first letter of the name if it's lowercase
            if(addressBook->contacts[k].name[0] >= 'a' && addressBook->contacts[k].name[0] <= 'z') {
                addressBook->contacts[k].name[0] -= 32;
                printf(">>>>>> CONTACT AFTER EDITING 📝<<<<<<<<<<");
                print(k,addressBook);
            }
        }
        else if(ch == 2) {
            // Edit phone number
            char number[11];
            int validation = 0;
            do {
                printf("Enter the new phone number 📞: ");
                getchar();  // Clear the buffer
                scanf("%s", number);  // Read the new phone number
                validation = validate_num(number, addressBook);
                if(validation == 1) {
                    strcpy(addressBook->contacts[k].phone, number);  // Update the phone number
                    printf(">>>>>> CONTACT AFTER EDITING 📝<<<<<<<<<<");
                    print(k,addressBook);
                }
                else if(validation == 2) {
                    // If the number already exists in the address book, ask the user to enter a different one
                    if(strcmp(addressBook->contacts[k].phone, number) != 0) {
                        printf("\n\tNumber already exists in the Addressbook, Enter a different one🌀🌀\n");
                    } else {
                        strcpy(addressBook->contacts[k].phone, number);  // If it's the same number, no need to change
                        printf(">>>>>> CONTACT AFTER EDITING 📝<<<<<<<<<<");
                        print(k,addressBook);
                        validation = 1;
                    }
                }
                else {
                    printf("\nInvalid phone number, please enter a valid one ❌📞\n");
                }
            } while(validation != 1);  // Loop until a valid phone number is entered
        }
        else if(ch == 3) {
            // Edit email
            char email[100];
            int validation = 0;
            do {
                printf("Enter the new email 📩: ");
                getchar();  // Clear the buffer
                scanf("%s", email);  // Read the new email
                validation = validate_mail(email, addressBook);
                if(validation == 1) {
                    strcpy(addressBook->contacts[k].email, email);  // Update the email
                    printf(">>>>>> CONTACT AFTER EDITING 📝<<<<<<<<<<");
                    print(k,addressBook);
                }
                else if(validation == 2) {
                    // If the email already exists in the address book, ask the user to enter a different one
                    if(strcmp(addressBook->contacts[k].email, email) != 0) {
                        printf("\n\tEmail already exists in the Addressbook, Enter a different one🌀🌀\n");
                    } else {
                        strcpy(addressBook->contacts[k].email, email);  // If it's the same email, no need to change
                        printf(">>>>>> CONTACT AFTER EDITING 📝<<<<<<<<<<");
                        print(k,addressBook);
                        validation = 1;
                    }
                }
                else {
                    printf("Invalid email, please enter a valid one ❌📩\n");
                }
            } while(validation != 1);  // Loop until a valid email is entered
        }
        else 
        {
            printf("Invalid choice, please try again.🔁\n");
        }    
    }
    else 
    {
        printf("⭕⭕ Unable to edit contact⭕⭕\n");  // If the contact was not found
    }
}


// Function to delete an existing contact
void deleteContact(AddressBook *addressBook, AddressBook *Trashbin)
{
    printf("Enter the choice for searching the data to delete 🔴🔴: ");
    int k = searchContact(addressBook);  // Search for the contact to delete
    print(k, addressBook);  // Display the found contact's details

    if(k >= 0) {
        // Move the contact to the trashbin before deletion
        Trashbin->contacts[Trashbin->contactCount] = addressBook->contacts[k];
        Trashbin->contactCount++;

        // Shift the contacts to remove the deleted contact from the address book
        for(int i = k; i < (addressBook->contactCount - 1); i++) {
            addressBook->contacts[i] = addressBook->contacts[i + 1];
        }
        addressBook->contactCount--;  // Decrease the contact count
        printf("\n\t\t\t>>>>>>> Data is deleted from address book 🗑🗑<<<<<<< \n");
    }
    else {
        printf("Contact not found, unable to delete 😡😡\n");
    }
}

// Function to list all deleted contacts from the trashbin
void deletedContacts(AddressBook *Trashbin) 
{
    // Loop through the deleted contacts and print their details
    printf("\nTHERE ARE TOTAL OF %d CONTACTS IN ADDRESSBOOK📜\n",Trashbin -> contactCount);
    for(int i = 0; i < Trashbin->contactCount; i++) {
        printf("(%d) Name 👤: %s\tPhone 📞: +91 %s\tEmail 📩: %s\n", i + 1, Trashbin->contacts[i].name, Trashbin->contacts[i].phone, Trashbin->contacts[i].email);
    }
}

// Function to retrieve a contact from the trashbin
void retrieve_contact(AddressBook *addressBook, AddressBook *Trashbin)
{
    printf("\tChoose how you want to retrieve the contact:\n");
    printf("\t\t 1) Search by name, phone number, or email 👤📞📩\n");
    printf("\t\t 2) Choose from the list of all deleted contacts 📃📃\n");
    printf("\t\tEnter a valid choice, or enter '0' to stop retrieval ▶️▶️\n");
    
    int choice;
    do
    {
        printf("\tEnter the option 👤📞📩: ");
        scanf("%d", &choice);
        
        if(choice == 1)
        {
            int k = searchContact(Trashbin);  // Search for the contact in the trashbin
            print(k,Trashbin);
            if(k >= 0) {
                addressBook->contacts[addressBook->contactCount] = Trashbin->contacts[k];  // Move the contact back to the address book
                addressBook->contactCount++;
                // Shift contacts in the trashbin to remove the retrieved contact
                for(int i = k; i < (Trashbin->contactCount - 1); i++) {
                    Trashbin->contacts[i] = Trashbin->contacts[i + 1];
                }
                Trashbin->contactCount--;  
                printf("\n\t>>>>>>> Data is removed from the Trashbin and added to the address book <<<<<<<<↪️↪️ \n");
            }
        }
        else if(choice == 2)
        {
            deletedContacts(Trashbin);  // List all deleted contacts
            printf("\nEnter the Roll number of the contact from the above list 🔢🔢: ");
            int option;
            scanf("%d", &option);
            option--;  // Adjust for 0-based indexing
            
            if(option >= 0 && option < Trashbin->contactCount)
            {
                addressBook->contacts[addressBook->contactCount] = Trashbin->contacts[option];  // Move the contact back to the address book
                addressBook->contactCount++;
                // Shift contacts in the trashbin to remove the retrieved contact
                for(int i = option; i < (Trashbin->contactCount - 1); i++) {
                    Trashbin->contacts[i] = Trashbin->contacts[i + 1];
                }
                Trashbin->contactCount--; 
                printf("\n\t>>>>>>>Below data is removed from the Trashbin and added to the address book <<<<<<<< ↪️↪️ ");
                print(option,Trashbin);
                printf("<<<<<<<< Retrival is successfull >>>>>>>>✌️✌️✌️✌️\n");
            }
        }
        else if(choice == 0)
        {
            printf("\n~~~~~~~~~ Retrieval is stopped ~~~~~~~~~~~🔚🔚\n");
            return;
        }
        else
        {
            printf("\n\t\t....Please enter a valid choice....👿👿👿👿\n");
        }
    } while(choice < 0 || choice > 2);  // Keep asking until a valid choice is entered
}

// Function to print contact details for debugging purposes
void print(int i, AddressBook *addressBook)
{
    if(i >= 0) 
    {
        // If the contact exists, display its details
        printf("\nRoll number %d \n\t(1) Name 👤: %s\n\t(2) Phone Number 📞: +91 %s\n\t(3) Email 📩: %s\n", 
               i, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    else 
    {
        // If the contact does not exist
        printf("\n \t....*Contact Not Found*....🤪🤪🤪\n>>>>>>>>>>>>>>>>> SEARCHING IS STOPPED <<<<<<<<<<<<<<<<🚫🚫\n");
    }
}

// Function to save contacts to file and exit the program
void saveAndExit(AddressBook *addressBook, AddressBook *Trashbin) 
{
    saveContactsToFile(addressBook);  // Save contacts in the address book to a file
    saveContacts_deleted_ToFile(Trashbin);  // Save deleted contacts in the trashbin to a file
    exit(EXIT_SUCCESS);  // Exit the program
}
