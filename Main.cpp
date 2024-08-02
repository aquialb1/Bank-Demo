#include <iostream>
#include <string>
#include <fstream>
#include "Header.h"

using namespace std;

Account user_account;
//fstream user_list;

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
	Account user_account;

	string username_input, password_input, username_file, password_file;

	cout << "--------------------" << endl << endl;
	cout << "Returning User" << endl << endl;

	cout << "Username: ";
	cin >> username_input;

	cout << "Password: ";
	cin >> password_input;
	cout << endl;

	ifstream user_list("user_list.txt");
	bool isloggedin = false;

	if (user_list.is_open()) {
		while (user_list >> username_file >> password_file) {
			if (username_file == username_input && password_file == password_input) {
				isloggedin = true;
				break;
			}
		}
		user_list.close();

		if (isloggedin) {
			cout << "Login succesful." << endl;
		}
		else {
			cout << "Invalid username or password. Please try again." << endl;
		}
	}
}

void create_account() {
	string name_create, username_create, password_create;

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

	//user_list.open("user_list.txt", ios::app);
	ofstream user_list("user_list.txt", ios::app);
	if (user_list.is_open()) {
		user_list << username_create << " " << password_create << endl;
		user_list.close();
	}
	else {
		cout << "Unable to Create account." << endl;
	}

	//string user_info[4] = { username_create, " ", password_create, "\n"};

	//for (int i = 0; i < 4; i++) {
	//	user_list << user_info[i];
	//}
}

int main() {
    string selection;

    cout << "- Mercury Bank -" << endl << endl;

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