#include <iostream>
#include <string>
#include <list>
#include "Header.h"

using namespace std;

int main()
{
    string selection;

    cout << "- Mercury Bank -" << endl;
    cout << endl;

    do {
        cout << "Please select an option from the menu below." << endl;
        cout << endl;
        cout << "1 - Log In  |  2 - Exit" << endl;
        cout << endl;
        cin >> selection;
        cout << endl;

        if (selection == "1") {
            returning_user();
            cout << endl;
        }
        else if (selection == "2") {
            cout << "";
        }
        else {
            cout << "Invalid selection. Please try again." << endl;
            cout << endl;
        }

    } while (selection != "2");

    cout << endl;
    return 0;
}