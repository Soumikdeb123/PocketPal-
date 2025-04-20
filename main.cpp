#include <iostream>
#include <conio.h>
#include <cstdlib>
#include "phonebook.h"
using namespace std;

void menu() {
    int ch;
    intro();
    do {
        system("cls");
        cout<<"............................................\n";
        cout<<"           PHONE BOOK MANAGEMENT\n";
        cout<<"............................................\n\n";
        cout<<"::::::::::::::: PROGRAM MENU :::::::::::::::\n";
        cout<<"1. Save New Phone Record\n";
        cout<<"2. Display All Saved Records\n";
        cout<<"3. Search Specific Record\n";
        cout<<"4. Delete Specific Record\n";
        cout<<"5. Modify Existing Record\n";
        cout<<"6. Exit\n";
        cout<<"Enter Your Choice : ";
        cin>>ch;
        system("cls");
        switch(ch) {
            case 1: AddNumber(); break;
            case 2: DisplayRecords(); break;
            case 3: SearchBySrNo(); break;
            case 4: deleteRecord(); break;
            case 5: modifyRecord(); break;
            case 6:
                cout<<"\n Thank You for using Phonebook Management system !!!";
                exit(0);
            default:
                cout<<"\a\n ERROR !!! Wrong Choice...";
        }
        getch();
    } while(ch);
}

int main() {
    menu();
    return 0;
}
