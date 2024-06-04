#pragma once
#include <iostream>
#include <string>
#include <list>

using namespace std;

class Account {
public:
	string username = "username";
	string password = "12345";

	string name = "User";

	string checking = "Checking: $";
	float checking_value = 0;

	string savings = "Savings: $";
	float savings_value = 0;
};