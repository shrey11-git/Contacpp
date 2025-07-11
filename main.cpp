//// mains.cpp
//#include <iostream>
//#include <limits>
//#include "db.h"
//#include "gui.h"
//
//using namespace std;
//
//int main() {
//    if (!initDatabase()) {
//        cout << "Failed to initialize database. Exiting...\n";
//        return 1;
//    }
//
//    int choice;
//    string name;
//    long long phone;
//
//    while (true) {
//        printBanner();
//        showMenu();
//        cin >> choice;
//        cin.ignore(numeric_limits<streamsize>::max(), '\n');
//
//        switch (choice) {
//        case 1:
//            cout << "Enter Name: ";
//            getline(cin, name);
//
//            if (contactExists(name)) {
//                cout << "Contact already exists. Try updating instead.\n";
//                break;
//            }
//
//            cout << "Enter Phone Number: ";
//            while (!(cin >> phone)) {
//                cout << "Invalid input. Enter digits only: ";
//                cin.clear();
//                cin.ignore(numeric_limits<streamsize>::max(), '\n');
//            }
//            cin.ignore(numeric_limits<streamsize>::max(), '\n');
//
//            if (addContactToDB(name, phone))
//                cout << "Contact added!\n";
//            else
//                cout << "Error adding contact.\n";
//            break;
//
//
//        case 2:
//            cout << "Enter Name to Update: ";
//            getline(cin, name);
//            cout << "Enter New Phone Number: ";
//            cin >> phone;
//            if (updateContactInDB(name, phone))
//                cout << "Contact updated!\n";
//            else
//                cout << "Update failed.\n";
//            break;
//
//        case 3:
//            cout << "Enter Name to Delete: ";
//            getline(cin, name);
//            if (deleteContactFromDB(name))
//                cout << "Contact deleted!\n";
//            else
//                cout << "Contact not found.\n";
//            break;
//
//        case 4:
//            cout << "Enter Name to Search: ";
//            getline(cin, name);
//            searchContactsInDB(name);
//            break;
//
//
//        case 5:
//            displayAllContacts();
//            break;
//
//        case 6:
//            int sortChoice;
//            cout << "Sort by:\n1. Name\n2. Phone\nEnter choice: ";
//            cin >> sortChoice;
//            cin.ignore(numeric_limits<streamsize>::max(), '\n');
//            if (sortChoice == 1 || sortChoice == 2)
//                sortContactsInDB(sortChoice);
//            else
//                cout << "Invalid sort option.\n";
//            break;
//
//
//        case 7:
//            cout << "Exiting...\n";
//            return 0;
//
//        default:
//            cout << "Invalid choice. Try again.\n";
//        }
//
//        waitForKey();
//        system("cls"); // or system("clear"); on Linux/macOS
//    }
//
//    return 0;
//}

// main.cpp
#include "app_gui.h"

int main() {
    runAppGUI(); // GUI-driven entry point
    return 0;
}
