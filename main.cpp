
#include "gtt0023_header.h"

int main() {
    bool      repeat;           //control the loop
    int       userChoice;       //input from user: 1 - 6
    MenuChoice choice;           //object type of MenuChoice
    string studentID;

    printInfo();        //my general information

    repeat = false;

    while (!repeat) {
        printMenuChoice();
        
        //prompt user to make the choice using integer value
        cout << "Enter your choice from the menu (1 - 6): ";
        cin  >> userChoice;

        //cast integer user's choice to enum's type
        choice = (MenuChoice) userChoice;

        switch (choice) {
            case Add:
                add_Student();
                repeat = false;
                break;
            case Remove:
                cout << "Enter ID of student to remove: ";
                cin  >> studentID;
                remove_Student(studentID);
                repeat = false;
                break;
            case Display:
                display();
                repeat = false;
                break;
            case Search:
                cout << "Enter ID of student to search: ";
                cin  >> studentID;
                search(studentID);
                repeat = false;
                break;
            case Results:
                exportResults();
                repeat = false;
                break;
            case Quit:
                cout << "Goodbye!" << endl;
                repeat = true;
                break;
            default:
                cout << "Invalid choice. Please enter your choice again." << endl;
                repeat = false;
                break;
        }
    }
    
    return 0;
}
