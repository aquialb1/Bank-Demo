#include <iostream>
#include <string>
#include <list>
#include "Header.h"

using namespace std;

int main()
{
    string selection;

    cout << "- Mercury Bank -" << endl << endl;

    cout << "Please select an option from the menu below." << endl << endl;
    cout << "1 - Log In  |  2 - Exit" << endl << endl;
    cout << "Selection: ";
    cin >> selection;
    cout << endl;

    if (selection == "1") {
        returning_user();
        cout << endl;
    }
    else if (selection == "2") {
        exit(0);
    }
    else {
        cout << "Invalid selection. Please try again." << endl << endl;
        main();
    }

    cout << endl;
    return 0;
}