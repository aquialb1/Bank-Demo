#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include "Header.h"

using namespace std;

void deposit() {
	float deposit_amount;
	string new_balance;

	cout << "--------------------" << endl << endl;
	cout << "Please enter an amount you would like to deposit: ";
	cin >> deposit_amount;
	cout << endl;

	fstream user_list("user_list.txt");
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

void account_entry(string name, string initial) {
	string active_user = name;
	string active_balance = initial;
	string selection;

	do {
		cout << "--------------------" << endl << endl;
		cout << "Welcome, " << active_user << endl << endl;

		cout << "Balance: $" << active_balance << endl << endl;

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
	string balance_file;

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
		while (getline(user_list, name_file, ',') && getline(user_list, username_file, ',') && getline(user_list, password_file, ',') && getline(user_list, balance_file, '\n')) {
			if (username_file == username_input && password_file == password_input) {
				isloggedin = true;
				break;
			}
		}
		user_list.close();

		if (isloggedin) {
			cout << "Login successful." << endl << endl;
			account_entry(name_file, balance_file);
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
	float balance_create = 0;

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
		user_list << name_create << "," << username_create << "," << password_create << ',' << balance_create << endl;
		user_list.close();
	}
	else {
		cout << "Unable to Create account." << endl;
	}
}

void delete_account() {
	fstream user_list, new_user_list;
	int no_copy, count = 0;
	string name, account_name, username, password, balance;

	cout << "--------------------" << endl << endl;
	cout << "DELETE A USER" << endl << endl;

	new_user_list.open("new_user_list.txt", ios::app);
	user_list.open("user_list.txt", ios::in);

	if (user_list) {
		cout << "Please enter the name of the account you would like to delete: ";
		cin >> name;
		cout << endl;

		//Iterating user info from lines
		while (getline(user_list, account_name, ',') && getline(user_list, username, ',') && getline(user_list, password, ',') && getline(user_list, balance, '\n')) {
			//Comparing input name to account name for deletion
			if (name == account_name) {
				//Deleting by not copying to new_user_list
				cout << "Account deleted successfully." << endl << endl;

				count++;
			}
			else {
				//Write account data we want to keep to new file
				new_user_list << account_name << "," << username << "," << password << "," << balance << endl;
			}
		}
		if (count == 0) {
			cout << "Account not found." << endl << endl;
		}

	}
	user_list.close();
	new_user_list.close();

	remove("user_list.txt");
	rename("new_user_list.txt", "user_list.txt");
}

int main() {
    string selection;

    cout << "- MERCURY BANK -" << endl << endl;

	do {
		cout << "Please select an option from the menu below." << endl << endl;
		cout << "1 - Log In  |  2 - Create an Account  |  3 - Delete Account  |  4 - Exit" << endl << endl;
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
			delete_account();
		}
		else if (selection == "4") {
			exit(0);
		}
		else {
			cout << "Invalid selection. Please try again." << endl << endl;
		}
	} while (selection != "4");

    cout << endl;
    return 0;
}