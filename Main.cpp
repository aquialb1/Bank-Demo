#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include "sqlite3.h"
#include "Header.h"

using namespace std;

void deposit(string user) {
	sqlite3* DB;
	char* ErrMsg = 0;
	int rc;
	const char* sql;
	const char* data = "Callback function called.";
	
	string account_name = user, deposit_amount;
	bool is_valid_balance = false;

	string account_choice, checking = "Checking", savings = "Savings";

	cout << "Which account would you like to deposit to?" << endl;
	cin >> account_choice;

	if (account_choice == checking) {
		rc = sqlite3_open("Users.db", &DB);

		cout << "--------------------" << endl << endl;
		cout << "DEPOSIT" << endl << endl;

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

			sql = "UPDATE Accounts set Checking = Checking + ? WHERE Name = ? ";

			sqlite3_stmt* stmt;
			sqlite3_prepare_v2(DB, sql, -1, &stmt, NULL);

			sqlite3_bind_text(stmt, 1, deposit_char, strlen(deposit_char), SQLITE_STATIC);
			sqlite3_bind_text(stmt, 2, name_char, strlen(name_char), SQLITE_STATIC);

			rc = sqlite3_step(stmt);
			sqlite3_finalize(stmt);
			sqlite3_close(DB);

			if (rc != SQLITE_DONE) {
				cout << "Fail." << endl << endl;
			}
			else {
				cout << "Success." << endl << endl;
				return;
			}
		}
	}

	else if (account_choice == savings) {
		cout << "Savings";
	}

	else {
		cout << "Invalid" << endl << endl;
	}
}

void withdraw(string user) {
	sqlite3* DB;
	char* ErrMsg = 0;
	int rc;
	const char* sql;
	const char* data = "Callback function called.";

	string account_name = user, withdraw_amount;
	bool is_valid_withdraw = false;

	rc = sqlite3_open("Users.db", &DB);

	cout << "--------------------" << endl << endl;
	cout << "WITHDRAW" << endl << endl;

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

		sqlite3_bind_text(stmt, 1, withdraw_char, strlen(withdraw_char), SQLITE_STATIC);
		sqlite3_bind_text(stmt, 2, name_char, strlen(name_char), SQLITE_STATIC);

		rc = sqlite3_step(stmt);
		sqlite3_finalize(stmt);
		sqlite3_close(DB);

		if (rc != SQLITE_DONE) {
			cout << "Fail." << endl;
		}
		else {
			cout << "Success." << endl << endl;
			return;
		}
	}
}

void get_balances1(string user) {
	//TODO: Change to get username instead of name
	sqlite3* DB;
	int rc;
	const char* sql;

	string name = user;

	rc = sqlite3_open("Users.db", &DB);

	sql = "SELECT AccountNum, Type, Balance FROM Balances WHERE Username = ? ";

	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(DB, sql, -1, &stmt, NULL);

	sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
}

void get_balances0(string user) {
	sqlite3* DB;
	int rc;
	const char* sql;

	string name = user;

	rc = sqlite3_open("Users.db", &DB);

	sql = "SELECT Checking, Savings FROM Accounts WHERE Name = ? ";

	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(DB, sql, -1, &stmt, NULL);

	sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);

	if (sqlite3_step(stmt) == SQLITE_ROW) {
		double checking = sqlite3_column_double(stmt, 0);
		double savings = sqlite3_column_double(stmt, 1);

		cout << "Checking: $" << checking << endl;
		cout << "Savings: $" << savings << endl << endl;
	}
	else {
		cout << "Invalid." << endl;
	}
	sqlite3_finalize(stmt);
	sqlite3_close(DB);
	return;
}

void profile_entry(string user) {
	string name = user;
	string selection;

	do {
		cout << "--------------------" << endl << endl;
		cout << "Welcome, " << name << endl << endl;

		//get_balances(name);

		cout << "1 - Deposit  |  2 - Withdraw  |  3 - Logout/Menu" << endl << endl;
		cout << "Selection: ";
		cin >> selection;
		cout << endl;

		if (selection == "1") {
			deposit(name);
		}
		else if (selection == "2") {
			withdraw(name);
		}
		else if (selection == "3") {
			return;
		}
		else {
			cout << "Invalid selection. Please try again." << endl << endl;
		}
	} while (selection != "3");
}

bool login_verify(string& username, string& password) {
	sqlite3* DB;
	int rc;
	const char* sql;

	rc = sqlite3_open("Users.db", &DB);

	//sql = "SELECT Name FROM Accounts WHERE Username = ? AND Password = ? ";
	sql = "SELECT Username FROM Accounts WHERE Username = ? AND Password = ? ";

	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(DB, sql, -1, &stmt, NULL);

	sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

	//While loop?
	if (sqlite3_step(stmt) == SQLITE_ROW) {
		const unsigned char* user = sqlite3_column_text(stmt, 0);

		string name = reinterpret_cast<const char*>(user);

		sqlite3_finalize(stmt);
		sqlite3_close(DB);

		profile_entry(name);

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

	login_verify(username_input, password_input);
}

void create_profile() {
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
		cout << "Unable to create profile. Please try again." << endl;
	}
	else {
		cout << "Profile created successfully." << endl;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(DB);
}

void all_profiles() {
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

void delete_profile() {
	sqlite3* DB;
	char* ErrMsg = 0;
	int rc;
	const char* sql;
	const char* data = "Callback function called.";
	
	string profile_name;

	rc = sqlite3_open("Users.db", &DB);

	cout << "--------------------" << endl << endl;
	cout << "DELETE A PROFILE" << endl << endl;

	cout << "Profile Name: ";
	cin >> profile_name;
	cout << endl;

	const char* delete_char = &profile_name[0];

	sql = "DELETE FROM Accounts WHERE Name = ? ";

	sqlite3_stmt* stmt;
	sqlite3_prepare_v2(DB, sql, -1, &stmt, NULL);

	sqlite3_bind_text(stmt, 1, delete_char, strlen(delete_char), SQLITE_STATIC);

	rc = sqlite3_step(stmt);

	if (rc != SQLITE_DONE) {
		cout << "Unable to delete profile. Please try again." << endl;
	}
	else {
		cout << "Profile deleted successfully." << endl;
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
		cout << "1 - Login  |  2 - Create a Profile  |  3 - All Users  |  4 - Delete Profile  |  5 - Exit" << endl << endl;
		cout << "Selection: ";
		cin >> selection;
		cout << endl;

		if (selection == menu_items[0]) {
			login();
			cout << endl;
		}
		else if (selection == menu_items[1]) {
			create_profile();
			cout << endl;
		}
		else if (selection == menu_items[2]) {
			all_profiles();
			cout << endl;
		}
		else if (selection == menu_items[3]) {
			delete_profile();
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