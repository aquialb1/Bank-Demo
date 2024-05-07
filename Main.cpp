#include <iostream>

using namespace std;

string username = "MercuryBank";
string password = "12345";

string username_input;
string password_input;

int main()
{
    cout << "Welcome to Mercury Bank! Please log in using your username and password." << endl;
    cout << endl;

    cout << "Username: ";
    cin >> username_input;

    cout << "Password: ";
    cin >> password_input;
    cout << endl;

    if (username_input == username && password_input == password) {
        cout << "Yes";
    }
    else {
        cout << "No";
    }
}