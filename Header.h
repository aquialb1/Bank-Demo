#pragma once
#include <iostream>
#include <string>

using namespace std;

class Account {
public:
	string name = "User";
	string username = "username";
	string password = "12345";

	string checking = "Checking: $";
	float checking_value = 0;
};

int main();

void account_entry();