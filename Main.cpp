#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include "sqlite3.h"
#include "Header.h"

using namespace std;

void deposit() {
	sqlite3* DB;
	char* ErrMsg = 0;
	int rc;
	const char* sql;
	const char* data = "Callback function called.";
	
	string account_name, deposit_amount;
	bool is_valid_balance = false;

	rc = sqlite3_open("Users.db", &DB);

	cout << "--------------------" << endl << endl;
	cout << "DEPOSIT" << endl << endl;

	cout << "Enter the Account Name: ";
	cin >> account_name;
	cout << endl;

	cout << "Deposit Amount: ";
	cin >> deposit_amount;
	cout << endl;

	for (int i = 0; i < deposit_amount.length(); i++) {
		if (isdigit(deposit_amount[i])) {
			is_valid_balance = true;
			continue;
		}
		else {
			cout << "Deposit can only have positive numbers." << endl;
			is_valid_balance = false;
			break;
		}
	}

	if (is_valid_balance) {
		const char* deposit_char = &deposit_amount[0];
		const char* name_char = &account_name[0];

		sql = "UPDATE Accounts set Balance = Balance + ? WHERE Name = ? ";

		sqlite3_stmt* stmt;
		sqlite3_prepare_v2(DB, sql, -1, &stmt, NULL);

		/*sqlite3_bind_text(stmt, 2, username_char, strlen(username_char), SQLITE_STATIC);*/
		sqlite3_bind_text(stmt, 1, deposit_char, strlen(deposit_char), SQLITE_STATIC);
		sqlite3_bind_text(stmt, 2, name_char, strlen(name_char), SQLITE_STATIC);

		rc = sqlite3_step(stmt);
		sqlite3_finalize(stmt);

		if (rc != SQLITE_DONE) {
			cout << "Fail." << endl;
		}
		else {
			cout << "Success." << endl;

			sql = "SELECT Username, Balance FROM Accounts WHERE Name = ? ";

			sqlite3_stmt* stmt_1;
			sqlite3_prepare_v2(DB, sql, -1, &stmt_1, NULL);

			sqlite3_bind_text(stmt_1, 1, name_char, strlen(name_char), SQLITE_STATIC);

			while ((rc = sqlite3_step(stmt_1)) == SQLITE_ROW) {
				double new_balance = sqlite3_column_double(stmt_1, 0);
				cout << "Balance: " << new_balance << endl;
			}

			//rc = sqlite3_step(stmt_1);
			sqlite3_finalize(stmt_1);
		}

		sqlite3_close(DB);
	}
}

void withdraw() {
	sqlite3* DB;
	char* ErrMsg = 0;
	int rc;
	const char* sql;
	const char* data = "Callback function called.";

	string account_name, withdraw_amount;
	bool is_valid_withdraw = false;

	rc = sqlite3_open("Users.db", &DB);

	cout << "--------------------" << endl << endl;
	cout << "WITHDRAW" << endl << endl;

	cout << "Enter the Account Name: ";
	cin >> account_name;
	cout << endl;

	cout << "Withdraw Amount: ";
	cin >> withdraw_amount;
	cout << endl;

	for (int i = 0; i < withdraw_amount.length(); i++) {
		if (isdigit(withdraw_amount[i])) {
			is_valid_withdraw = true;
			continue;
		}
		else {
			cout << "Whithdraw can only have positive numbers." << endl;
			is_valid_withdraw = false;
			break;
		}
	}

	if (is_valid_withdraw) {
		const char* withdraw_char = &withdraw_amount[0];
		const char* name_char = &account_name[0];

		sql = "UPDATE Accounts set Balance = Balance - ? WHERE Name = ? ";

		sqlite3_stmt* stmt;
		sqlite3_prepare_v2(DB, sql, -1, &stmt, NULL);

		/*sqlite3_bind_text(stmt, 2, username_char, strlen(username_char), SQLITE_STATIC);*/
		sqlite3_bind_text(stmt, 1, withdraw_char, strlen(withdraw_char), SQLITE_STATIC);
		sqlite3_bind_text(stmt, 2, name_char, strlen(name_char), SQLITE_STATIC);

		rc = sqlite3_step(stmt);
		sqlite3_finalize(stmt);

		if (rc != SQLITE_DONE) {
			cout << "Fail." << endl;
		}
		else {
			cout << "Success." << endl;

			sql = "SELECT Balance FROM Accounts WHERE Name = ? ";

			sqlite3_stmt* stmt_1;
			sqlite3_prepare_v2(DB, sql, -1, &stmt_1, NULL);

			sqlite3_bind_text(stmt_1, 1, name_char, strlen(name_char), SQLITE_STATIC);

			while ((rc = sqlite3_step(stmt_1)) == SQLITE_ROW) {
				double new_balance = sqlite3_column_double(stmt_1, 0);
				cout << "Balance: " << new_balance << endl;
			}

			sqlite3_finalize(stmt_1);
		}

		sqlite3_close(DB);
	}
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

bool get_account_info(string& username, string& password) {
	sqlite3* DB;
	int rc;
	const char* sql;

	rc = sqlite3_open("Users.db", &DB);

	sql = "SELECT Name, Balance FROM Accounts WHERE Username = ? AND Password = ?";

	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(DB, sql, -1, &stmt, NULL);

	sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

	if (sqlite3_step(stmt) == SQLITE_ROW) {
		const unsigned char* name = sqlite3_column_text(stmt, 0);
		double balance = sqlite3_column_double(stmt, 1);
		string selection;

		cout << "Access granted." << endl << endl;

		cout << "Welcome, " << name << endl;
		cout << "Balance: " << balance << endl;

		sqlite3_finalize(stmt);
		sqlite3_close(DB);

		return true;
	}
	else {
		cout << "Invalid username or password." << endl;
		sqlite3_finalize(stmt);
		sqlite3_close(DB);

		return false;
	}
}

void login() {
	string username_input, password_input;

	cout << "--------------------" << endl << endl;
	cout << "RETURNING USER" << endl << endl;

	cout << "Username: ";
	cin >> username_input;

	cout << "Password: ";
	cin >> password_input;
	cout << endl;

	get_account_info(username_input, password_input);
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

	/*for (int i = 0; i < balance_create.length(); i++) {
		if (isalpha(balance_create[i])) {
			cout << "Balance cannot have letters." << endl;
			break;
		}
		else {
			cout << "Good" << endl;
		}
	}*/

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

	sql = "SELECT * FROM Accounts";

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
	string menu_items[] = { "1", "2", "3", "4", "5", "6" };
	string selection;

    cout << "- MERCURY BANK -" << endl << endl;

	do {
		cout << "Select an option from the menu below." << endl << endl;
		cout << "1 - Login  |  2 - Create an Account  |  3 - All Users  |  4 - Delete Account  |  5 - Deposit  |  6 - Exit" << endl << endl;
		cout << "Selection: ";
		cin >> selection;
		cout << endl;

		if (selection == menu_items[0]) {
			login();
			//withdraw();
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
			deposit();
			cout << endl;
		}
		else if (selection == menu_items[5]) {
			cout << "Thank you for using Mercury Bank!" << endl;
			exit(0);
		}
		else {
			cout << "Invalid selection. Please try again." << endl << endl;
		}
	} while (selection != menu_items[5]);

    cout << endl;
    return 0;
}