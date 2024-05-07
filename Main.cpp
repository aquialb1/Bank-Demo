#include <iostream>

using namespace std;

int main()
{
    string selection;

    cout << "- Mercury Bank -" << endl;
    cout << endl;

    do {
        cout << "1 - Returning User  |  2 - New User  |  3 - Exit" << endl;
        cout << endl;
        cout << "Please select an option from the menu above and press enter: ";
        cin >> selection;
        cout << endl;

        if (selection == "1") {
            cout << "Returning" << endl;
            cout << endl;
        }
        else if (selection == "2") {
            cout << "New" << endl;
            cout << endl;
        }
        else if (selection == "3") {
            cout << "";
        }
        else {
            cout << "Invalid selection. Please try again." << endl;
            cout << endl;
        }

    } while (selection != "3");

    cout << endl;
    return 0;
}