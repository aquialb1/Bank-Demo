#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include "Header.h"

using namespace std;

Account user_account;
fstream user_list;

void deposit() {
	float deposit_amount;

	cout << "--------------------" << endl << endl;
	cout << "Please enter an amount you would like to deposit: ";
	cin >> deposit_amount;
	cout << endl;

	if (deposit_amount > 0) {
		user_account.checking_value += deposit_amount;
		// account_entry();
	}
	else {
		cout << "Invalid amount. Please try again." << endl << endl;
	}
}

void withdraw() {
	float withdraw_amount;

	cout << "--------------------" << endl << endl;
	cout << "Please enter an amount you would like to withdraw: ";
	cin >> withdraw_amount;
	cout << endl;

	if (withdraw_amount > 0) {
		user_account.checking_value -= withdraw_amount;
		// account_entry();
	}
	else {
		cout << "Amount invalid. Please try again." << endl << endl;
	}
}

void account_entry() {
	string selection;

	do {
		// check if user is logged in
		// if not, call returning_user()
		// if so, call account_entry()
		cout << "--------------------" << endl << endl;
		cout << "Welcome, " << user_account.name << endl << endl;

		cout << user_account.checking << user_account.checking_value << endl << endl;

		cout << "1 - Deposit  |  2 - Withdraw  |  3 - Login/Logout" << endl << endl;
		cout << "Selection: ";
		cin >> selection;
		cout << endl;

		// return selection to controller(); remove 76-81
		if (selection == "1") {
			deposit();
		}
		else if (selection == "2") {
			withdraw();
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

void account_creation() {
	user_list.open("user_list.txt", ios::app);
	
	string name_create;
	string username_create;
	string password_create;

	cout << "--------------------" << endl << endl;
	cout << "New User" << endl << endl;
	cout << "Please create your username and password in the fields below." << endl << endl;

	// cout << "First Name: ";
	// cin >> name_create;

	cout << "Username: ";
	cin >> username_create;

	cout << "Password: ";
	cin >> password_create;
	cout << endl;

	string users[100] = { username_create, password_create };

	user_list << username_create;
	user_list << password_create;

	user_list.close();

}

int main()
{
    string selection;

    cout << "- Mercury Bank -" << endl << endl;

	do {
		cout << "Please select an option from the menu below." << endl << endl;
		cout << "1 - Log In  |  2 - Create an Account  |  3 - Exit" << endl << endl;
		cout << "Selection: ";
		cin >> selection;
		cout << endl;

		if (selection == "1") {
			returning_user();
			cout << endl;
		}
		else if (selection == "2") {
			account_creation();
			cout << endl;
		}
		else if (selection == "3") {
			// user_list.close();
			exit(0);
		}
		else {
			cout << "Invalid selection. Please try again." << endl << endl;
		}
	} while (selection != "3");

    cout << endl;
    return 0;
}