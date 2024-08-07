#include <iostream>
#include <string>
#include <fstream>
#include "Header.h"

using namespace std;

void deposit() {
	float deposit_amount;

	cout << "--------------------" << endl << endl;
	cout << "Please enter an amount you would like to deposit: ";
	cin >> deposit_amount;
	cout << endl;

	if (deposit_amount > 0) {
		//user_account.checking_value += deposit_amount;
		//account_entry();
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
		//user_account.checking_value -= withdraw_amount;
		//account_entry();
	}
	else {
		cout << "Amount invalid. Please try again." << endl << endl;
	}
}

void account_entry(string name) {
	string selection;

	do {
		// check if user is logged in
		// if not, call returning_user()
		// if so, call account_entry()
		cout << "--------------------" << endl << endl;
		cout << "Welcome, " << name << endl << endl;

		//cout << user_account.checking << user_account.checking_value << endl << endl;

		cout << "1 - Deposit  |  2 - Withdraw  |  3 - Login/Logout" << endl << endl;
		cout << "Selection: ";
		cin >> selection;
		cout << endl;

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

void login() {
	string username_input;
	string password_input;
	string name_file;
	string username_file;
	string password_file;

	cout << "--------------------" << endl << endl;
	cout << "RETURNING USER" << endl << endl;

	cout << "Username: ";
	cin >> username_input;

	cout << "Password: ";
	cin >> password_input;
	cout << endl;

	ifstream user_list("user_list.txt");
	bool isloggedin = false;

	if (user_list.is_open()) {
		while (getline(user_list, name_file, ',') && getline(user_list, username_file, ',') && getline(user_list, password_file, '\n')) {
			if (username_file == username_input && password_file == password_input) {
				isloggedin = true;
				break;
			}
		}
		user_list.close();

		if (isloggedin) {
			cout << "Login successful." << endl << endl;

			account_entry(name_file);
		}
		else {
			cout << "Invalid username or password. Please try again." << endl << endl;
			login();
		}
	}
}

void create_account() {
	string name_create;
	string username_create;
	string password_create;
	float starting_balance = 0;

	cout << "--------------------" << endl << endl;
	cout << "NEW USER" << endl << endl;

	cout << "First Name: ";
	cin >> name_create;

	cout << "Username: ";
	cin >> username_create;

	cout << "Password: ";
	cin >> password_create;
	cout << endl;

	ofstream user_list("user_list.txt", ios::app);
	if (user_list.is_open()) {
		user_list << name_create << "," << username_create << "," << password_create << endl;
		user_list.close();
	}
	else {
		cout << "Unable to Create account." << endl;
	}
}

int main() {
    string selection;

    cout << "- MERCURY BANK -" << endl << endl;

	do {
		cout << "Please select an option from the menu below." << endl << endl;
		cout << "1 - Log In  |  2 - Create an Account  |  3 - Exit" << endl << endl;
		cout << "Selection: ";
		cin >> selection;
		cout << endl;

		if (selection == "1") {
			login();
			cout << endl;
		}
		else if (selection == "2") {
			create_account();
			cout << endl;
		}
		else if (selection == "3") {
			exit(0);
		}
		else {
			cout << "Invalid selection. Please try again." << endl << endl;
		}
	} while (selection != "3");

    cout << endl;
    return 0;
}