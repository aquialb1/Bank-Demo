#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include "sqlite3.h"
#include "Header.h"

//using namespace std;

void deposit(string name) {
	fstream user_list, new_user_list;
	int no_copy, count = 0;
	float deposit_amount, new_balance;
	string active_user = name, account_name, username, password, balance;

	cout << "--------------------" << endl << endl;
	cout << "DEPOSIT" << endl << endl;

	new_user_list.open("new_user_list.txt", ios::app);
	user_list.open("user_list.txt", ios::in);

	if (user_list) {
		cout << "Enter an amount you would like to deposit: $";
		cin >> deposit_amount;
		cout << endl;

		//Iterate through user_list per line item
		while (getline(user_list, account_name, ',') && getline(user_list, username, ',') && getline(user_list, password, ',') && getline(user_list, balance, '\n')) {
			if (active_user == account_name) {
				if (deposit_amount > 0) {
					new_balance = stof(balance) + deposit_amount;

					//Copy user info to new_user_list w/ updated balance
					new_user_list << account_name << "," << username << "," << password << "," << new_balance << endl;
					count++;
				}
				else {
					cout << "Deposit amount cannot be negative. Please try again." << endl << endl;

					new_user_list << account_name << "," << username << "," << password << "," << balance << endl;
					count++;
				}
			}
			else {
				//Copy user info to new_user_list w/ unchanged balance
				new_user_list << account_name << "," << username << "," << password << "," << balance << endl;
			}
		}
		if (count == 0) {
			cout << "INVALID" << endl << endl;
		}
	}
	user_list.close();
	new_user_list.close();

	//Delete and rename
	remove("user_list.txt");
	rename("new_user_list.txt", "user_list.txt");
}

void withdraw(string name) {
	fstream user_list, new_user_list;
	int no_copy, count = 0;
	float withdraw_amount, new_balance;
	string active_user = name, account_name, username, password, balance;

	cout << "--------------------" << endl << endl;
	cout << "WITHDRAW" << endl << endl;

	new_user_list.open("new_user_list.txt", ios::app);
	user_list.open("user_list.txt", ios::in);

	if (user_list) {
		cout << "Enter an amount you would like to withdraw: $";
		cin >> withdraw_amount;
		cout << endl;

		//Iterate through user_list per line item
		while (getline(user_list, account_name, ',') && getline(user_list, username, ',') && getline(user_list, password, ',') && getline(user_list, balance, '\n')) {
			if (active_user == account_name) {
				if (withdraw_amount >= 0) {
					new_balance = stof(balance) - withdraw_amount;

					//Copy user info to new_user_list w/ updated balance
					new_user_list << account_name << "," << username << "," << password << "," << new_balance << endl;
					count++;
				}
				else if (withdraw_amount > stof(balance)) {
					cout << "Withdraw amount cannot be more than account balance. Please try again." << endl << endl;

					new_user_list << account_name << "," << username << "," << password << "," << balance << endl;
					count++;
				}
				else {
					cout << "Withdraw amount cannot be negative. Please try again." << endl << endl;

					new_user_list << account_name << "," << username << "," << password << "," << balance << endl;
					count++;
				}
			}
			else {
				//Copy user info to new_user_list w/ unchanged balance
				new_user_list << account_name << "," << username << "," << password << "," << balance << endl;
			}
		}
		if (count == 0) {
			cout << "INVALID" << endl << endl;
		}
	}
	user_list.close();
	new_user_list.close();

	//Delete and rename
	remove("user_list.txt");
	rename("new_user_list.txt", "user_list.txt");
}

void account_entry(string name) {
	ifstream user_list;
	string active_user = name;
	string name_file, username_file, password_file, balance_file;
	string selection;

	do {
		user_list.open("user_list.txt");

		if (user_list) {
			while (getline(user_list, name_file, ',') && getline(user_list, username_file, ',') && getline(user_list, password_file, ',') && getline(user_list, balance_file, '\n')) {
				if (active_user == name_file) {
					break;
				}
			}
			user_list.close();
		}

		cout << "--------------------" << endl << endl;
		cout << "Welcome, " << active_user << endl << endl;

		cout << "Balance: $" << balance_file << endl << endl;

		cout << "1 - Deposit  |  2 - Withdraw  |  3 - Logout/Menu" << endl << endl;
		cout << "Selection: ";
		cin >> selection;
		cout << endl;

		if (selection == "1") {
			deposit(active_user);
		}
		else if (selection == "2") {
			withdraw(active_user);
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
	ifstream user_list;
	string username_input, password_input;

	string name_file, username_file, password_file, balance_file;

	cout << "--------------------" << endl << endl;
	cout << "RETURNING USER" << endl << endl;

	cout << "Username: ";
	cin >> username_input;

	cout << "Password: ";
	cin >> password_input;
	cout << endl;

	user_list.open("user_list.txt");
	bool isloggedin = false;

	if (user_list) {
		while (getline(user_list, name_file, ',') && getline(user_list, username_file, ',') && getline(user_list, password_file, ',') && getline(user_list, balance_file, '\n')) {
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
			main();
		}
	}
}

void create_account() {
	sqlite3* DB;
	int rc;
	const char* sql;
	
	string name_create, username_create, password_create;

	rc = sqlite3_open("Users.db", &DB);

	cout << "--------------------" << endl << endl;
	cout << "NEW USER" << endl << endl;

	cout << "Name: ";
	cin >> name_create;

	cout << "Username: ";
	cin >> username_create;

	cout << "Password: ";
	cin >> password_create;
	cout << endl;

	const char* name_char = &name_create[0];
	const char* username_char = &username_create[0];
	const char* password_char = &password_create[0];

	sql = "INSERT INTO Accounts (Name, Username, Password) " \
		  "VALUES (?, ?, ? ); ";

	sqlite3_stmt* stmt;
	sqlite3_prepare_v2(DB, sql, -1, &stmt, NULL);

	sqlite3_bind_text(stmt, 1, name_char, strlen(name_char), SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, username_char, strlen(username_char), SQLITE_STATIC);
	sqlite3_bind_text(stmt, 3, password_char, strlen(password_char), SQLITE_STATIC);

	rc = sqlite3_step(stmt);

	if (rc != SQLITE_DONE) {
		cout << "Unable to create account. Please try again." << endl;
	}
	else {
		cout << "Account created successfully." << endl;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(DB);
}

void all_accounts() {
	sqlite3* DB;
	char* ErrMsg = 0;
	int rc;
	const char* sql;
	const char* data = "Callback function called.";

	rc = sqlite3_open("Users.db", &DB);
	
	cout << "--------------------" << endl << endl;
	cout << "ALL USERS" << endl << endl;

	sql = "SELECT * from Accounts";

	rc = sqlite3_exec(DB, sql, callback, (void*)data, &ErrMsg);

	sqlite3_close(DB);
}

void delete_account() {
	sqlite3* DB;
	char* ErrMsg = 0;
	int rc;
	const char* sql;
	const char* data = "Callback function called.";
	
	string account_name;

	rc = sqlite3_open("Users.db", &DB);

	cout << "--------------------" << endl << endl;
	cout << "DELETE AN ACCOUNT" << endl << endl;

	cout << "Account Name: ";
	cin >> account_name;
	cout << endl;

	const char* delete_char = &account_name[0];

	sql = "DELETE FROM Accounts WHERE Name = ? ";

	sqlite3_stmt* stmt;
	sqlite3_prepare_v2(DB, sql, -1, &stmt, NULL);

	sqlite3_bind_text(stmt, 1, delete_char, strlen(delete_char), SQLITE_STATIC);

	rc = sqlite3_step(stmt);

	if (rc != SQLITE_DONE) {
		cout << "Unable to delete account. Please try again." << endl;
	}
	else {
		cout << "Account deleted successfully." << endl;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(DB);
}

int main() {
	string menu_items[] = { "1", "2", "3", "4", "5" };
	string selection;

    cout << "- MERCURY BANK -" << endl << endl;

	do {
		cout << "Select an option from the menu below." << endl << endl;
		cout << "1 - Log In  |  2 - Create an Account  |  3 - All Users  |  4 - Delete Account  |  5 - Exit" << endl << endl;
		cout << "Selection: ";
		cin >> selection;
		cout << endl;

		if (selection == menu_items[0]) {
			login();
			cout << endl;
		}
		else if (selection == menu_items[1]) {
			create_account();
			cout << endl;
		}
		else if (selection == menu_items[2]) {
			all_accounts();
			cout << endl;
		}
		else if (selection == menu_items[3]) {
			delete_account();
			cout << endl;
		}
		else if (selection == menu_items[4]) {
			cout << "Thank you for using Mercury Bank!" << endl;
			exit(0);
		}
		else {
			cout << "Invalid selection. Please try again." << endl << endl;
		}
	} while (selection != menu_items[4]);

    cout << endl;
    return 0;
}