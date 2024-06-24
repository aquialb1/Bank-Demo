#include <iostream>
#include <string>
#include <list>
#include "Header.h"

using namespace std;

int main();

void account_entry();

void deposit() {
	Account user_account;
	string selection;
	float deposit_amount;

	cout << "Which account would like to deposit into?: 1 - Checking  |  2 - Savings";
	cin >> selection;
	cout << endl;

	if (selection == "1") {
		cout << "Deposit";
	}
	else if (selection == "2") {
		cout << "Savings" << endl << endl;
	}
	else {
		cout << "Invalid" << endl << endl;
	}
}

void withdraw() {
	Account user_account;
	float withdraw_amount;
}

void account_entry() {
	Account user_account;
	string selection;

	cout << "--------------------" << endl << endl;
	cout << "Welcome, " << user_account.name << endl << endl;

	cout << user_account.checking << user_account.checking_value << endl;
	cout << user_account.savings << user_account.savings_value << endl << endl;

	do {
		cout << "1 - Deposit  |  2 - Withdraw  |  3 - Back" << endl << endl;
		cout << "Selection: ";
		cin >> selection;
		cout << endl;

		if (selection == "1") {
			// deposit();
			cout << "Deposit" << endl;
		}
		else if (selection == "2") {
			cout << "Withdraw" << endl;
		}
		else if (selection == "3") {
			main();
		}
		else {
			cout << "Invalid selection. Please try again." << endl << endl;
		}
	} while (selection != "3");
}

void returning_user() {
	Account user_account;

	string username_input;
	string password_input;

	cout << "--------------------" << endl << endl;
	cout << "Returning User" << endl << endl;

	do {
		cout << "Username: ";
		cin >> username_input;

		cout << "Password: ";
		cin >> password_input;
		cout << endl;

		if (username_input == user_account.username && password_input == user_account.password) {
			account_entry();
		}
		else {
			cout << "The entered username or password is incorrect. Please try again." << endl << endl;
		}
	} while (username_input != user_account.username && password_input != user_account.password);
}

int main()
{
    string selection;

    cout << "- Mercury Bank -" << endl << endl;

	do {
		cout << "Please select an option from the menue below." << endl << endl;
		cout << "1 - Log In  |  2 - Logout" << endl << endl;
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
		}
	} while (selection != "2");

    cout << endl;
    return 0;
}