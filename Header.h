#pragma once
#include <iostream>
#include <string>
#include <list>

using namespace std;

class Account {
public:
	string username = "Username";
	string password = "12345";

	string name = "User";

	string checking = "Mercury Checking: $";
	float checking_value = 0;

	string savings = "Mercury Savings: $";
	float savings_value = 0;
};

void deposit() {
	Account user_account;
	float deposit_amount;

	cout << "Enter the amount you would like to deposit: " << endl;
	cin >> deposit_amount;

	if (deposit_amount > 0) {
		cout << user_account.checking_value + deposit_amount << endl;
	}
	else {
		cout << "Invalid amount. Please try again." << endl << endl;
		deposit();
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

	cout << "1 - Deposit  |  2 - Withdraw  |  3 - Logout" << endl << endl;
	cout << "Selection: ";
	cin >> selection;
	cout << endl;

	if (selection == "1") {
		deposit();
	}
	else if (selection == "2") {
		cout << "Withdraw";
	}
	else if (selection == "3") {
		exit(0);
	}
	else {
		cout << "Invalid selection. Please try again." << endl << endl;
		account_entry();
	}
}

void returning_user() {
	Account user_account;

	string username_input;
	string password_input;

	cout << "--------------------" << endl << endl;
	cout << "Returning User" << endl << endl;

	cout << "Username: ";
	cin >> username_input;

	cout << "Password: ";
	cin >> password_input;
	cout << endl;

	if (username_input == user_account.username && password_input == user_account.password) {
		account_entry();
	}
	else {
		cout << "Invalid username or password. Please try again." << endl << endl;
		returning_user();
	}
}