#pragma once
#include <iostream>
#include <string>
#include <list>

using namespace std;

class Account {
public:
	string username = "User";
	string password = "12345";

	string name = "User";

	string checking = "Mercury Checking: $";
	float checking_value = 0;

	string savings = "Mercury Savings: $";
	float savings_value = 0;

};

void account_options() {
	string selection;
	
	cout << "1 - Deposit  |  2 - Withdraw  |  3 - Transfer" << endl;
}

void account_entry() {
	Account user_account;

	cout << "--------------------" << endl;
	cout << endl;
	cout << "Welcome, " << user_account.name << endl;
	cout << endl;

	cout << user_account.checking << user_account.checking_value << endl;
	cout << user_account.savings << user_account.savings_value << endl;
}

void returning_user() {
	Account user_account;

	string username_input;
	string password_input;

	cout << "Returning User" << endl;
	cout << endl;

	cout << "Username: ";
	cin >> username_input;
	
	cout << "Password: ";
	cin >> password_input;
	cout << endl;

	if (username_input == user_account.username && password_input == user_account.password) {
		account_entry();
	}
	else {
		cout << "Invalid username or password. Please try again." << endl;
		cout << endl;
		returning_user();
	}
}