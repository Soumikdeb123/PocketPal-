#include <iostream>
#include <fstream>
#include "phonebook.h"
using namespace std;

PhoneBook b;

// Method to get the serial number of a record
int PhoneBook::getSrNo() { 
    return srno; 
}

// Method to store a new record
void PhoneBook::storeData() {
    cout << "\n----------------------------------------------------" << endl;
    cout << "              CREATE NEW PHONE RECORD              " << endl;
    cout << "----------------------------------------------------\n";

    cout << "\nPlease enter the following details:\n";

    cout << "\nSerial Number      : "; 
    cin >> srno; 
    cin.ignore();

    cout << "\nRecord Name        : "; 
    cin.getline(name, 25);

    cout << "\nMobile Number      : "; 
    cin.getline(mobile, 15);

    cout << "\nE-Mail I.D.        : "; 
    cin.getline(email, 30);

    cout << "\nRecord Group       : "; 
    cin.getline(group, 20);

    cout << "\n----------------------------------------------------" << endl;
    cout << "       New Phone Record Has Been Successfully Created!" << endl;
    cout << "----------------------------------------------------\n\n";
}

// Method to display a record
void PhoneBook::showData() {
    cout << "\n----------------------------------------------------" << endl;
    cout << "               PHONE BOOK RECORD                   " << endl;
    cout << "----------------------------------------------------\n";

    cout << "\nRecord Details:\n";
    cout << "----------------------------------------------------" << endl;

    cout << "\nSerial Number     : " << srno << endl;
    cout << "Name              : " << name << endl;
    cout << "Mobile Number     : " << mobile << endl;
    cout << "Email ID          : " << email << endl;
    cout << "Group             : " << group << endl;

    cout << "\n----------------------------------------------------" << endl;
    cout << "              End of Record Display               " << endl;
    cout << "----------------------------------------------------\n\n";
}

// Function to add a new record
void AddNumber() {
    ofstream fout("data/PhoneBook.dat", ios::binary | ios::app);
    if (!fout) {
        cout << "\nError opening the file. Please try again later.\n";
        return;
    }

    cout << "\n----------------------------------------------------" << endl;
    cout << "              ADDING A NEW PHONE RECORD            " << endl;
    cout << "----------------------------------------------------\n";
    b.storeData();
    fout.write((char*)&b, sizeof(b));
    fout.close();

    cout << "\n----------------------------------------------------" << endl;
    cout << "              Record Saved to File Successfully!   " << endl;
    cout << "----------------------------------------------------\n\n";
}

// Function to display all records
void DisplayRecords() {
    ifstream fin("data/PhoneBook.dat", ios::binary);
    if (!fin) {
        cout << "\nError opening the file. Please try again later.\n";
        return;
    }

    cout << "\n----------------------------------------------------" << endl;
    cout << "              DISPLAYING PHONE BOOK RECORDS        " << endl;
    cout << "----------------------------------------------------\n";

    bool fileHasRecords = false;

    while(fin.read((char*)&b, sizeof(b))) {
        b.showData();
        fileHasRecords = true;
    }

    fin.close();

    if (!fileHasRecords) {
        cout << "\nNo records found in the file...\n";
    } else {
        cout << "\n----------------------------------------------------" << endl;
        cout << "         Reading of Data File Completed Successfully!" << endl;
        cout << "----------------------------------------------------\n";
    }
}

// Function to search a record by Serial Number
void SearchBySrNo() {
    ifstream fin("data/PhoneBook.dat", ios::binary);
    if (!fin) {
        cout << "\nError opening the file. Please try again later.\n";
        return;
    }

    int n, flag = 0;
    cout << "\n----------------------------------------------------" << endl;
    cout << "             SEARCH RECORD BY SERIAL NUMBER        " << endl;
    cout << "----------------------------------------------------\n";
    cout << "Enter Serial Number of Record to Display: ";
    cin >> n;

    while(fin.read((char*)&b, sizeof(b))) {
        if(n == b.getSrNo()) {
            b.showData();
            flag++;
            cout << "\n----------------------------------------------------" << endl;
            cout << "               Record Found and Displayed!         " << endl;
            cout << "----------------------------------------------------\n";
            break;
        }
    }

    fin.close();

    if(flag == 0) {
        cout << "\n----------------------------------------------------" << endl;
        cout << "The Record with Serial Number " << n << " was not found in the file.\n";
        cout << "----------------------------------------------------\n";
    }
}

// Function to delete a record by Serial Number
void deleteRecord() {
    ifstream fin("data/PhoneBook.dat", ios::binary);
    ofstream fout("data/temp.dat", ios::binary);

    if (!fin || !fout) {
        cout << "\n⚠️ Error accessing file. Please try again.\n";
        return;
    }

    int n, flag = 0;
    cout << "\n----------------------------------------------------" << endl;
    cout << "                 DELETE PHONE RECORD                " << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "Enter Serial Number of Record to Delete: ";
    cin >> n;

    while (fin.read((char*)&b, sizeof(b))) {
        if (n == b.getSrNo()) {
            cout << "\n📛 The following record will be deleted:\n";
            b.showData();
            flag++;
        } else {
            fout.write((char*)&b, sizeof(b));
        }
    }

    fin.close();
    fout.close();

    remove("data/PhoneBook.dat");
    rename("data/temp.dat", "data/PhoneBook.dat");

    if (flag == 0) {
        cout << "\n❌ No record found with Serial Number " << n << ".\n";
    } else {
        cout << "\n✅ Record deleted successfully!\n";
    }

    cout << "----------------------------------------------------\n";
}

// Function to modify a record
void modifyRecord() {
    fstream fio("data/PhoneBook.dat", ios::in | ios::out | ios::binary);
    if (!fio) {
        cout << "\n⚠️ Error accessing file. Please ensure the data file exists.\n";
        return;
    }

    int n, flag = 0;
    long pos;

    cout << "\n----------------------------------------------------" << endl;
    cout << "                 MODIFY PHONE RECORD                " << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "Enter Serial Number of Record to Modify: ";
    cin >> n;

    while (fio.read((char*)&b, sizeof(b))) {
        pos = fio.tellg();
        if (n == b.getSrNo()) {
            cout << "\n✏️ Existing record found:\n";
            b.showData();

            cout << "\n🔁 Enter new details to modify the record:\n";
            b.storeData();

            fio.seekp(pos - sizeof(b));
            fio.write((char*)&b, sizeof(b));

            cout << "\n✅ Record updated successfully!\n";
            flag++;
            break;
        }
    }

    fio.close();

    if (flag == 0) {
        cout << "\n❌ No record found with Serial Number " << n << ".\n";
    }

    cout << "----------------------------------------------------\n";
}

// Function to display the intro screen
void intro() {
    cout << "\n\n====================================================";
    cout << "\n             📱 PHONE BOOK MANAGEMENT SYSTEM";
    cout << "\n====================================================\n";
    cout << "\n            Organize. Access. Simplify. 📇";
    cout << "\n\n      Developed with ❤️  by Soumik Deb";
    cout << "\n====================================================\n";
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}
