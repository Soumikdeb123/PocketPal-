#ifndef PHONEBOOK_H
#define PHONEBOOK_H

class PhoneBook{
    int srno;
    char name[25];
    char mobile[15];
    char email[30];
    char group[20];
public:
    int getSrNo();
    void storeData();
    void showData();
};

// Function declarations
void AddNumber();        // Adds a new contact to the phonebook
void DisplayRecords();   // Displays all saved contact records
void SearchBySrNo();     // Searches for a contact by serial number
void deleteRecord();     // Deletes a contact from the phonebook
void modifyRecord();     // Modifies an existing contact
void intro();            // Displays introductory information or splash screen
void menu();             // Displays the main menu for user interaction


#endif
