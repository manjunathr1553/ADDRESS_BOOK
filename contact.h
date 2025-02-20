/*Documentation
Name : Manjunath R
DATE :06/01/2025
DISCRIPTION : Address Book is a small application written in C language. It keeps track of names and telephone/mobile numbers and e-mail addresses.*/
#ifndef CONTACT_H
#define CONTACT_H

// Maximum number of contacts in the address book
#define MAX_CONTACTS 100

// Structure to store contact details (Name, Phone, Email)
typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

// Structure for the address book that holds an array of contacts and the contact count
typedef struct {
    Contact contacts[MAX_CONTACTS];  // Array to store contacts
    int contactCount;                // Number of contacts in the address book
} AddressBook;

// Function prototypes

// Function to create a new contact and add it to the address book
void createContact(AddressBook *addressBook);

// Function to search for a contact by phone, name, or email
int searchContact(AddressBook *addressBook);

// Function to edit an existing contact in the address book
void editContact(AddressBook *addressBook);

// Function to delete an existing contact from the address book and move it to Trashbin
void deleteContact(AddressBook *addressBook, AddressBook *Trashbin);

// Function to list all contacts in the address book
void listContacts(AddressBook *addressBook);

// Function to save the contacts to a file and exit the program
void saveAndExit(AddressBook *addressBook, AddressBook *Trashbin);

// Function to validate the format of an email and check if it's already in the address book
int validate_mail(char* email, AddressBook* addressBook);

// Function to validate the format of a phone number and check if it's already in the address book
int validate_num(char* phone, AddressBook* addressBook);

// Function to print the details of a contact by its index
void print(int index, AddressBook *addressBook);

// Function to list all contacts in the Trashbin (deleted contacts)
void deletedContacts(AddressBook *Trashbin);

// Function to retrieve a contact from the Trashbin (deleted contacts) back to the address book
void retrieve_contact(AddressBook *addressBook, AddressBook *Trashbin);

#endif

